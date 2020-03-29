#include "ms_board.h"

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode) {
    this->game_mode = mode;
    game_state = RUNNING;
    first_move = true;
    board_height    = width;
    board_width     = height;

    switch (game_mode) {
        case DEBUG: {
            for (int row = 0; row < board_height; ++row) {
                for (int col = 0; col < board_width; ++col) {
                    if (row == col or row == 0 or (col == 0 and row%2 == 0))
                        board[row][col].isMine = true;
                }
            }
        }
        break;
        case EASY: {
            int how_many_mines = board_width*board_height*0.1;
            fillBoardWithMines(how_many_mines);
        }
        break;
        case MEDIUM: {
            int how_many_mines = board_width*board_height*0.2;
            fillBoardWithMines(how_many_mines);
        }
        break;
        case HARD: {
            int how_many_mines = board_width*board_height*0.3;
            fillBoardWithMines(how_many_mines);
        }
        break;
    }
}

std::string MinesweeperBoard::prepareDebugField(int field_row, int field_col) const {
    std::string dbg_filed = "[";
    if (board[field_row][field_col].isMine == true)
        dbg_filed += "M";
    else
        dbg_filed += ".";

    if (board[field_row][field_col].isRevealed == true)
        dbg_filed += "o";
    else
        dbg_filed += ".";

    if (board[field_row][field_col].isFlag == true)
        dbg_filed += "f";
    else
        dbg_filed += ".";

    dbg_filed += "]";

    return dbg_filed;
}

void MinesweeperBoard::fillBoardWithMines(int how_many_mines) {
    while(true) {
        int mine_row = rand()%board_height;
        int mine_col = rand()%board_width;
        if (board[mine_row][mine_col].isMine == false) {
            board[mine_row][mine_col].isMine = true;
            how_many_mines--;
        }

        if (how_many_mines == 0)
            break;
    }
}

bool MinesweeperBoard::isInBoard(int field_row, int field_col) const{
    if (field_row < 0 or field_row > board_height-1
        or  field_col < 0 or field_col > board_width-1)
        return false;
    return true;
}

bool MinesweeperBoard::isMine(int field_row, int field_col) const{
    if (board[field_row][field_col].isMine)
        return true; 
    return false;
}

void MinesweeperBoard::revealEmptyField(int field_row, int field_col, bool byHand) {
    if (!isInBoard(field_row, field_col))
        return;

    if (!byHand)
        if (isRevealed(field_row, field_col))
            return;
    
    board[field_row][field_col].isRevealed = true;

    if (countMines(field_row, field_col) > 0) {
        return;
    }

    revealEmptyField(field_row + 1, field_col - 1);
    revealEmptyField(field_row + 1, field_col);
    revealEmptyField(field_row + 1, field_col + 1);

    revealEmptyField(field_row, field_col - 1);
    revealEmptyField(field_row, field_col + 1);
                
    revealEmptyField(field_row - 1, field_col - 1);
    revealEmptyField(field_row - 1, field_col);
    revealEmptyField(field_row - 1, field_col + 1);
}

// Public

void MinesweeperBoard::debugDisplay() const {
    for (int row = 0; row < board_height; ++row) {
        for (int col = 0; col < board_width; ++col) {
            std::cout << prepareDebugField(row, col);
        }
        std::cout << "\n";
    }
}

int MinesweeperBoard::getBoardWidth() const{
    return board_width;
}

int MinesweeperBoard::getBoardHeight() const{
    return board_height;
}

int MinesweeperBoard::getMineCount() const{
    int mine_counter = 0;
    switch (game_mode) {
        case DEBUG: {
            for (int row = 0; row < board_height; ++row) {
                for (int col = 0; col < board_width; ++col) {
                    if (board[row][col].isMine)
                        mine_counter++;
                }      
            }
        }
        break;
        case EASY: {
            mine_counter = board_width * board_height * 0.1;
        }
        break;
        case MEDIUM: {
            mine_counter = board_width * board_height * 0.2;
        }
        break;
        case HARD: {
            mine_counter = board_width * board_height * 0.3;
        }
        break;
    }
    return mine_counter;
}

int MinesweeperBoard::countMines(int field_row, int field_col) const{
    if (!isInBoard(field_row, field_col))
        return -1;

    if (!isRevealed(field_row, field_col))
        return -1;

    int mine_counter = 0;

    if (isInBoard(field_row, field_col+1))
        if (isMine(field_row, field_col+1))
            mine_counter += 1;

    if (isInBoard(field_row-1, field_col+1))
        if (isMine(field_row-1, field_col+1))
            mine_counter += 1;

    if (isInBoard(field_row-1, field_col))
        if (isMine(field_row-1, field_col))
            mine_counter += 1;

    if (isInBoard(field_row-1, field_col-1))
        if (isMine(field_row-1, field_col-1))
            mine_counter += 1;

    if (isInBoard(field_row, field_col-1))
        if (isMine(field_row, field_col-1))
            mine_counter += 1;

    if (isInBoard(field_row+1, field_col-1))
        if (isMine(field_row+1, field_col-1))
            mine_counter += 1;

    if (isInBoard(field_row+1, field_col))
        if (isMine(field_row+1, field_col))
            mine_counter += 1;
    if (isInBoard(field_row+1, field_col+1))
        if (isMine(field_row+1, field_col+1))
            mine_counter += 1;

    return mine_counter;
}

bool MinesweeperBoard::hasFlag(int field_row, int field_col) const{
    if (!isInBoard(field_row, field_col))
        return false;

    if (!board[field_row][field_col].isFlag)
        return false;

    if (isRevealed(field_row, field_col))
        return false;

    return true; 
}

bool MinesweeperBoard::isRevealed(int field_row, int field_col) const{
    if (board[field_row][field_col].isRevealed)
        return true;
    return false;
}

void MinesweeperBoard::toggleFlag(int field_row, int field_col) {
    if (getGameState() != RUNNING)
        return;

    if (!isInBoard(field_row, field_col))
        return;

    if (isRevealed(field_row, field_col))
        return;

    if (hasFlag(field_row, field_col))
        board[field_row][field_col].isFlag = false;
    else
        board[field_row][field_col].isFlag = true;
}

void MinesweeperBoard::revealField(int field_row, int field_col) {
    if (getGameState() != RUNNING)
        return;
    
    if (!isInBoard(field_row, field_col))
        return;
    
    if (isRevealed(field_row, field_col))
        return;
    
    if (hasFlag(field_row, field_col))
        return;
    
    if (isMine(field_row, field_col)) {
        if (first_move) {
            if (game_mode != DEBUG) {
                fillBoardWithMines(1);
                board[field_row][field_col].isMine = false;
                board[field_row][field_col].isRevealed = true;
            }
        }
        else {
            board[field_row][field_col].isRevealed = true;
            game_state = FINISHED_LOSS;
        }
    }
    else {
        board[field_row][field_col].isRevealed = true;
        if (countMines(field_row, field_col) == 0) {
            revealEmptyField(field_row, field_col, true);
        }
    }
    first_move = false;
}

char MinesweeperBoard::getFieldInfo(int field_row, int field_col) const{
    if (!isInBoard(field_row, field_col))
        return '#';

    if (!isRevealed(field_row, field_col) and hasFlag(field_row, field_col))
        return 'F';

    if (!isRevealed(field_row, field_col) and !hasFlag(field_row, field_col))
        return '_';

    if (isRevealed(field_row, field_col) and isMine(field_row, field_col))
        return 'x';

    if (isRevealed(field_row, field_col) and countMines(field_row, field_col) == 0)
        return ' ';

    if (isRevealed(field_row, field_col) and countMines(field_row, field_col) > 0) {
        std::string num = std::to_string(countMines(field_row, field_col));
        return num[0];
    }

    return '%';
}

GameState MinesweeperBoard::getGameState() const{
    if (game_state == FINISHED_LOSS)
        return FINISHED_LOSS;

    int mine_counter = 0;
    for (int row = 0; row < board_height; ++row) {
        for (int col = 0; col < board_width; ++col) {
            if (board[row][col].isRevealed == false)
                mine_counter += 1;
        }
    }

    if (mine_counter == getMineCount())
        return FINISHED_WIN;
    return RUNNING;   
}