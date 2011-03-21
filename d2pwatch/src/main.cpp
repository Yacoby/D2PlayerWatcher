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
#include "include.h"
#include "main.h"
#include "cont.h"
#include "funcs.h"
 
IMPLEMENT_APP(PlayerWatcher)

 //-------------------------------------------------------------------------------------------------
bool PlayerWatcher::OnInit(){

	loadSeDebugPrivilege();

	AppWin *frame = new AppWin(_T("D2 Player Watcher"), 50, 50, 350, 140);
 
	frame->Show(TRUE);
	SetTopWindow(frame);
	SetExitOnFrameDelete(true);
	return TRUE;
}

 //-------------------------------------------------------------------------------------------------
AppWin::AppWin( const wxChar *title, int xpos, int ypos, int width, int height)
: wxDialog( (wxDialog*) NULL, -1, title, wxPoint(xpos, ypos), wxSize(width, height) ){
	mCont = new Cont(this);
	mTicker = new Ticker(mCont);
	mTicker->Start(5000);
}
//-------------------------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(AppWin, wxDialog)
	EVT_CLOSE(AppWin::OnQuit)
END_EVENT_TABLE()
//-------------------------------------------------------------------------------------------------
void AppWin::OnQuit(wxCloseEvent& event){
	delete mCont;
	mTicker->Stop();
	delete mTicker;
	Destroy();
}
//-------------------------------------------------------------------------------------------------
Ticker::Ticker(Cont* cont)  : mCont(cont){}
//-------------------------------------------------------------------------------------------------
void Ticker::Notify(){
	Stop();

	uint count =  mCont->getWatchCount();
	for ( uint i = 0; i < count; i++ ){
		mCont->update(i);
	}

	Start();
}
//-------------------------------------------------------------------------------------------------