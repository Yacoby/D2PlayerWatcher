/*_LICENCE_BLOCK_
------------------------------------------------------------------
This source file is part of D2 Player Watcher

Copyright (c) 2007 Yacoby
Also see acknowledgements in the readme

D2 Player Watcher is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Morrowind Remake is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/licenses/gpl.txt

------------------------------------------------------------------
_LICENCE_BLOCK_*/
#include "d2watcher.h"

//-------------------------------------------------------------------------------------------------
//Code stolen from somewhere on EdgeOfNowhere. Ty whoever wrote it
static bool GetMemory(DWORD addr, LPVOID buf, DWORD size, HANDLE d2) {
   DWORD read;
   ReadProcessMemory(d2,(void*)addr,buf,size,&read);
   return (read==size);
}
//-------------------------------------------------------------------------------------------------
D2Watcher::~D2Watcher(){
	if ( mD2Hand )
		CloseHandle(mD2Hand);
}
//-------------------------------------------------------------------------------------------------
D2Watcher::D2Watcher(std::string title) : mWinName(title), mD2Hand(0){ 
	DWORD pID;
	if ( windowExists() ){
		GetWindowThreadProcessId (mD2Hwnd, &pID);
		mD2Hand = OpenProcess (PROCESS_VM_READ|PROCESS_VM_OPERATION, FALSE, pID);
		if (!mD2Hand) return;
		if ( !inGame() ) return;

		mThisPlayers = readPlayerCount();
		mLastPlayers = mThisPlayers;
	}
}
//-------------------------------------------------------------------------------------------------
bool D2Watcher::inGame(){
	DWORD addr, read;
	DWORD playerUnit[25];
	ReadProcessMemory (mD2Hand, (void*)(0x6FAB0000 + 0x11C1E0), &addr, sizeof(addr), &read);
	ReadProcessMemory (mD2Hand, (void*)addr, playerUnit, sizeof(playerUnit), &read);
	if (read != sizeof(playerUnit))
		return false;
	return true;
}
//-------------------------------------------------------------------------------------------------
bool D2Watcher::windowExists(){
	mD2Hwnd = FindWindow(D2_CLASS, mWinName.c_str());
	if ( !mD2Hwnd )return false;
	return true;
}
//-------------------------------------------------------------------------------------------------
int D2Watcher::playerCountChanged(){
	mThisPlayers = readPlayerCount();
	int change = mThisPlayers - mLastPlayers;
	mLastPlayers = mThisPlayers;
	return change;	 
}
//-------------------------------------------------------------------------------------------------
uint D2Watcher::readPlayerCount(){
		DWORD dw;
		int thisCount = 0;
		if(!GetMemory(0x6FAB0000+0x11C33C,&dw,sizeof(DWORD), mD2Hand))  return 0;
		while(dw){
			thisCount++;
			if(!GetMemory(dw+0x80,&dw,sizeof(DWORD), mD2Hand)) return 0;

			//can't be more than 8 people. This would happen when you have quit the game
			if ( thisCount > 8 )return 0;
		}
		return thisCount;
}
//-------------------------------------------------------------------------------------------------
void D2Watcher::flashWindow(uint count){
	FLASHWINFO flash;
	flash.cbSize = sizeof(FLASHWINFO);
	flash.hwnd = mD2Hwnd;
	flash.dwFlags = FLASHW_TRAY;
	flash.uCount = count;
	flash.dwTimeout = 0;
	FlashWindowEx(&flash);
}
//-------------------------------------------------------------------------------------------------