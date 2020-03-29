#include <iostream>
#include "ms_board.h"
#include "ms_board_text_view.h"
#include "ms_text_controller.h"

int main() {
	srand(time(0));
    MinesweeperBoard board (10, 10, GameMode::EASY);
    MSBoardTextView view (board);
    MSTextController ctrl (board, view);

    ctrl.play();
   
    return 0;
}