#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>

enum GameMode 	{DEBUG, EASY, MEDIUM, HARD};
enum GameState 	{RUNNING, FINISHED_WIN, FINISHED_LOSS};

struct Field {
    bool isMine;
    bool isRevealed;
    bool isFlag;
};

class MinesweeperBoard {
    Field board[100][100];
    int board_width;
    int board_height;
    bool first_move;
    GameMode 	game_mode;
    GameState 	game_state;

    // zwraca podstawowe inforamcje dotyczace pola o danych wsporzednych
    std::string prepareDebugField(int field_row, int field_col)	const;
    // przyraca plansze do stanu poczatkowego (narazie tylko deklaracja) 
    //void		blankBorad();   
    // losowo wypelnia plansze podana iloscia min
    void		fillBoardWithMines(int how_many_mines);
    // sprawdza czy pole o danych wspolrzednych nalezy do naszej planszy 
    bool		isInBoard(int field_row, int field_col)			const;
    // sprawdza czy pole ma mine
    bool        isMine(int field_row, int field_col)            const;
    // algortym floodfill
    void        revealEmptyField(int field_row, int field_col, bool byHand=false);

public:
    MinesweeperBoard(int width, int height, GameMode mode);
    // wyswietla plasze ktory ulatwia testowanie
    void 		debugDisplay()                                    const;
    // zwraca szerokosc planszy
    int 		getBoardWidth()                                   const;
    // zwraca wysokosc planszy
    int 		getBoardHeight()                                  const;
    // zwraca liczbe min na planszy
    int 		getMineCount()                                    const;
    // liczy liczbe min wokol pola o danych wspolrzednych
    int 		countMines(int field_row, int field_col)          const;
    // zwraca informacje czy pole o danych wsporzednych ma flage
    bool 		hasFlag(int field_row, int field_col)            const;
    // ustawia lub usuwa flage z pola o danych wspolrzednych    
    void 		toggleFlag(int field_row, int field_col);
    // odkrywa pole o danych wspolrzednych
    void 		revealField(int field_row, int field_col);
    // zwraca informacje o tym czy pole o danych wspolrzednych zostalo odkryte 
    bool 		isRevealed(int field_row, int field_col)		  const;
    //
    char 		getFieldInfo(int field_row, int field_col)	      const;
	// zwraca aktulany stan gry
    GameState	getGameState() 									  const;
};


#endif
