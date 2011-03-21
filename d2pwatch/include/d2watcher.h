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
#include "include.h"
#include <windows.h>

#ifndef __D2WATCHER_H__
#define __D2WATCHER_H__


/** @brief class handles a d2 instance */
class D2Watcher{
public:
	D2Watcher(std::string title);

	~D2Watcher();

	/** @brief checks if the d2 window exists */
	bool windowExists();

	/** @return true if the person is in a game */
	bool inGame();

	/** @brief flashes the d2 window */
	void flashWindow(uint count);

	/** @return the number of players in the game when playerCountChanged() was last called */
	inline uint getPlayerCount(){ return mThisPlayers; }

	/**
	* @brief checks if the player count has changed since this, was last called
	* @return the amount by which it has changed
	*/
	int playerCountChanged();
private:

	/** @brief reads the player count from memory */
	uint readPlayerCount();

	std::string mWinName;
	HWND mD2Hwnd;
	HANDLE mD2Hand;
	uint mLastPlayers;
	uint mThisPlayers;
};


#endif