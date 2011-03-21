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
#include "button.h"
//-------------------------------------------------------------------------------------------------
AddButton::AddButton(
					Cont* cont,
					wxWindow* parent,
					wxWindowID id,
					const wxString& label,
					const wxPoint& pos,
					const wxSize& size
					)
			: wxButton(parent, id, label, pos, size), mCont(cont){}
//-------------------------------------------------------------------------------------------------
RemoveButton::RemoveButton(
					Cont* cont,
					wxWindow* parent,
					wxWindowID id,
					const wxString& label,
					const wxPoint& pos,
					const wxSize& size
					)
			: wxButton(parent, id, label, pos, size), mCont(cont){}
//-------------------------------------------------------------------------------------------------
void AddButton::OnPress(wxCommandEvent& WXUNUSED(event)){mCont->OnAdd();}
//-------------------------------------------------------------------------------------------------
void RemoveButton::OnPress(wxCommandEvent& WXUNUSED(event)){mCont->OnRemove();}