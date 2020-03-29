#include <iostream>

#include "ms_text_controller.h"

MSTextController::MSTextController(MinesweeperBoard & board, MSBoardTextView & view) 
									: board(board), view(view) {
}

void MSTextController::play() {
	int row, col;
	char option;
	while (board.getGameState() == GameState::RUNNING) {
		board.debugDisplay();
		view.display();
		std::cout << "\n[o] Odslon pole\n";
		std::cout << "[f] Ustaw/Usun flage z pola\n";
		std::cout << "Podaj -> rzad / kolumna / opcja: ";
		std::cin >> row >> col >> option;
		switch (option) {
			case 'o': {
				board.revealField(row, col);
			}
			break;
			case 'f': {
				board.toggleFlag(row, col);
			}
			break;
		}
	}

	view.display();
	if (board.getGameState() == GameState::FINISHED_WIN)
		std::cout << "Wygrales :)\n";
	else
		std::cout << "Przegrales :(\n";
}