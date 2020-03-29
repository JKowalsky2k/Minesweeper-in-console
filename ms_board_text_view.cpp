#include <iostream>

#include "ms_board_text_view.h"

MSBoardTextView::MSBoardTextView(MinesweeperBoard & board) : board(board){
}

void MSBoardTextView::display() {
	std::cout << "\n";
	for (int row = 0; row < board.getBoardHeight(); ++ row) {
		for (int col = 0; col < board.getBoardWidth(); ++col) {
			std::cout << board.getFieldInfo(row, col);
		}
		std::cout << "\n";
	}
}