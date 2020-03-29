#ifndef board_TEXT_CONTROLLER_H
#define board_TEXT_CONTROLLER_H

#include "ms_board.h"
#include "ms_board_text_view.h"

class MSTextController {
	MinesweeperBoard &board;
	MSBoardTextView &view;	
public:
	MSTextController(MinesweeperBoard & board, MSBoardTextView & view);
	void play();
};

#endif