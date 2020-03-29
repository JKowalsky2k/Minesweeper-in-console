#ifndef board_BOARD_TEXT_VIEW_H
#define board_BOARD_TEXT_VIEW_H

#include "ms_board.h"

class MSBoardTextView {
	MinesweeperBoard &board;
public:
	explicit MSBoardTextView(MinesweeperBoard & board);
	void display();
};

#endif