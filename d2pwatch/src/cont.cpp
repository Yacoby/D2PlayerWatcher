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
#include "cont.h"
//-------------------------------------------------------------------------------------------------

Cont::Cont(wxWindow* win) : mWindow(win) {

	mListBox = new wxListCtrl(mWindow,
                       LST_WATCHERS,
                       wxPoint( 20, 20 ),
                       wxSize( 200, 80 ),
					   wxLC_REPORT );
	mListBox->InsertColumn(0, "Title");
	mListBox->InsertColumn(0, "Players");

	mTxt = new wxTextCtrl(mWindow, TXT_WINNAME, _T("Diablo II"), wxPoint(230, 20));

	//add button
	mBtnAdd = new AddButton(this, mWindow, BTN_ADD, _T("Add"), wxPoint(230, 45));
	mBtnAdd->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddButton::OnPress));

	mBtnRemove = new RemoveButton(this, mWindow, BTN_REM, _T("Remove"), wxPoint(230, 70));
	mBtnRemove->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(RemoveButton::OnPress));
}
//-------------------------------------------------------------------------------------------------
Cont::~Cont(){
	uint count = mListBox->GetItemCount();
	for ( uint i = 0; i < count; ++i ) remove(0);
}
//-------------------------------------------------------------------------------------------------
void Cont::OnAdd(){
	D2Watcher* d2win = new D2Watcher(std::string(mTxt->GetValue().ToAscii()));
	if ( !d2win->windowExists() ){ delete d2win; return; }
	if ( !d2win->inGame() ){ delete d2win; return; }

	mListBox->InsertItem(mListBox->GetItemCount(), _T(toString(d2win->getPlayerCount())));
	mListBox->SetItem(mListBox->GetItemCount() - 1, 1, mTxt->GetValue());

	mListBox->SetItemPtrData(mListBox->GetItemCount() - 1, wxUIntPtr(d2win));
}
//-------------------------------------------------------------------------------------------------
void Cont::OnRemove(){
	if ( mListBox->GetSelectedItemCount() == 0 ) return;
    long item = -1;
    for ( ;; ) {
        item = mListBox->GetNextItem(item,
                                     wxLIST_NEXT_ALL,
                                     wxLIST_STATE_SELECTED);
        if ( item == -1 ) break;
        remove(item);
    }
}
//-------------------------------------------------------------------------------------------------
void Cont::remove(uint num){
	D2Watcher* d2 = (D2Watcher*)mListBox->GetItemData(num);
	delete d2;
	mListBox->DeleteItem(num);
}
//-------------------------------------------------------------------------------------------------
uint Cont::getWatchCount(){	
	return mListBox->GetItemCount(); 
}
//-------------------------------------------------------------------------------------------------
void Cont::update(uint num){
	D2Watcher* d2 = (D2Watcher*)mListBox->GetItemData(num);

	if ( !d2->windowExists() ){
		remove(num);
		return;
	}

	int change = d2->playerCountChanged();
	if ( change ){
		if ( d2->getPlayerCount() == 0 ){
			mListBox->SetItem(num, 0, _T("Not in Game"));
			return;
		}
		
		if ( change > 0 )
			d2->flashWindow(8);

		mListBox->SetItem(num, 0, _T(toString(d2->getPlayerCount())));
	}
}
//-------------------------------------------------------------------------------------------------