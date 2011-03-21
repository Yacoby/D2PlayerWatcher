/*_LICENCE_BLOCK_
------------------------------------------------------------------
This source file is part of D2 Player Watcher

Copyright (c) 2007
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
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "include.h"
#include "cont.h"

//why the funk is there two of the same thing, with 1 func diffrent
class AddButton : public wxButton{
public:
	AddButton(Cont* cont, wxWindow* parent, wxWindowID id, const wxString& label = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	void OnPress(wxCommandEvent& WXUNUSED(event));
private:
	Cont* mCont;
};

class RemoveButton : public wxButton{
public:
	RemoveButton(Cont* cont, wxWindow* parent, wxWindowID id, const wxString& label = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	void OnPress(wxCommandEvent& WXUNUSED(event));
private:
	Cont* mCont;
};

#endif