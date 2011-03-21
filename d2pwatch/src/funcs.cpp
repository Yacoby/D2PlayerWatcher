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
#include "funcs.h"

bool loadSeDebugPrivilege(){
	HANDLE	hToken;
	LUID	Val;
	TOKEN_PRIVILEGES tp;

	if (!OpenProcessToken (GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Val)){
		CloseHandle(hToken);
		return FALSE;
	}
	
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = Val;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof (tp), NULL, NULL)){
		CloseHandle(hToken);	
		return FALSE;
	}

	CloseHandle(hToken);

	return TRUE;
}
