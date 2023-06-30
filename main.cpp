#include <boost/algorithm/string/classification.hpp>
#include <cstdio>
#include <ios>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <istream>
#include <string>
#include <vector>
#include <algorithm> 
#include <locale>
#include <codecvt>
#include <map>

template <typename T>
struct vec2 {
    T x;
    T y;
};
template <typename T> 
std::ostream& operator << (std::ostream &o, const vec2<T>& p)
{
    return o << "x: " << p.x << ", y: " << p.y << std::endl;
}


struct BoardPiece {
    int type;
    int color;
    BoardPiece(int t, int c) {
        type = t;
        color = c;
    }
};

std::ostream& operator<< (std::ostream &o, const BoardPiece& p) {
    return o << "Type: " << p.type << ", Color: " << p.color << std::endl;
}

 struct {
    int toMove = 1;
    bool quit = false;
    bool inGame = false;
    bool isWhite = true;
    std::vector<std::vector<BoardPiece>> board;
 } chess;


void reverse( char *start, char *end )
{
    while( start < end )
    {
        char c = *start;
        *start++ = *end;
        *end-- = c;
    }
}

char *reverse_char( char *start )
{
    char *end = start;
    while( (end[1] & 0xC0) == 0x80 ) end++;
    reverse( start, end );
    return( end+1 );
}

void reverse_string( char *string )
{
    char *end = string;
    while( *end ) end = reverse_char( end );
    reverse( string, end-1 );
}
void clearScreen() {
    system("clear");
}

void printBoard() {
    std::string board = "\n";
    // Unicode values for chess pieces, Black pieces then White pieces in order: King, Queen, Bishop, Knight, Rook
    // the chessboard fills top to bottom so then the position of 0, 0 would be the top left increasing as it goes
    std::string pieces[] = { "\u2654", "\u2655", "\u2657", "\u2658", "\u2656", "\u2659","\u265A", "\u265B", "\u265D", "\u265E", "\u265C", "\u265F"};
    for (int i = 0; i<8;i++) {
        board+= "  +---+---+---+---+---+---+---+---+\n";
        board+= std::to_string(8-i) + " |";
        for (int j = 0; j<8;j++) {
            if (chess.board[i][j].type == 0) {
                board+=/*(chess.board[i][j].color?" \u2B1C|":" \u2B1B|")*/"   |";
            } else board+=  " " + pieces[chess.board[i][j].type+(chess.board[i][j].color*6)-1]/*chess.board[i][j].type+(chess.board[i][j].color*6)-1*/+ " |"; 
        }
        board+="\n";
    }
    board+="  +---+---+---+---+---+---+---+---+\n";
    board+="    A   B   C   D   E   F   G   H  \n";
    std::vector<char> cstr(board.c_str(), board.c_str() + board.size() + 1);
    if (!chess.toMove)reverse_string(cstr.data());
    std::cout << cstr.data();
};

char getInput(std::string question, std::vector<char> valid) {
    char c;
    do {
        std::cout << question << std::endl;
        std::cout << "Type a letter: ";
        std::cin >> c;
    } while (std::find(valid.cbegin(), valid.cend(), c) == valid.cend());
    return c;
}

bool parseMoves() {
    std::string move;
    bool isValid = false;
    do {
        std::cout << "Enter a valid move (eg. E4-E5 or G3-F5): ";
        //std::cin.ignore();
        std::getline(std::cin >> std::ws, move);
        for (char & c: move) c = toupper(c);
        if (move.at(2) != '-' || move.size() != 5) continue;
        vec2<int> currentPos = {abs(atoi(&move.at(1))-8), int(move.at(0))-65 };
        vec2<int> targetedPos = {abs(atoi(&move.at(4))-8), int(move.at(3))-65 };

        std::cout << currentPos << chess.board[currentPos.x][currentPos.y] << chess.toMove << std::endl;
        if (chess.board[currentPos.x][currentPos.y].type != 0 && chess.toMove == chess.board[currentPos.x][currentPos.y].color) {
            
            switch (chess.board[currentPos.x][currentPos.y].type)
            case 6:
             //   if ()
            break;
            break;
        }
    } while (!isValid);
    return true;
}

void initBoard(bool isWhite) {
    chess.board = {{}, {}, {}, {}, {}, {}, {}, {}};
    chess.toMove = 1;
    std::vector<BoardPiece> base = {BoardPiece(5, 1), BoardPiece(4, 1), BoardPiece(3, 1), BoardPiece(2, 1), BoardPiece(1, 1), BoardPiece(3, 1), BoardPiece(4, 1), BoardPiece(5, 1)};
    std::vector<BoardPiece> pawns = {BoardPiece(6, 1),BoardPiece(6, 1), BoardPiece(6, 1), BoardPiece(6, 1), BoardPiece(6, 1), BoardPiece(6, 1), BoardPiece(6, 1), BoardPiece(6, 1)};
    chess.isWhite = isWhite;
    for (BoardPiece p : base) {
        p.color = 0;
        chess.board.at(0).push_back(p);
    }
    for (BoardPiece p : pawns) {
        p.color = 0;
        chess.board.at(1).push_back(p);
    }
    isWhite = !isWhite;
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            chess.board.at(i).push_back(BoardPiece(0, isWhite));
            isWhite = !isWhite;
        }
        isWhite = !isWhite;
    }
    for (BoardPiece p : pawns) {
        p.color = 1;
        chess.board.at(6).push_back(p);
    }
    for (BoardPiece p : base) {
        p.color = 1;
        chess.board.at(7).push_back(p);
    }
}


int main() {
    std::cout << "\
 ██████╗██╗  ██╗███████╗███████╗███████╗\n\
██╔════╝██║  ██║██╔════╝██╔════╝██╔════╝\n\
██║     ███████║█████╗  ███████╗███████╗\n\
██║     ██╔══██║██╔══╝  ╚════██║╚════██║\n\
╚██████╗██║  ██║███████╗███████║███████║\n\
 ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝" << std::endl;
    initBoard(true);
    printBoard();
    while (!chess.quit) {
        if (chess.inGame) std::cout << "It is " << (chess.toMove?"White's":"Black's") << " turn!" << std::endl;
        char r = getInput(std::string("What would you like to do? ") + (!chess.inGame?"(N)ew Game":"(F)orfeit Game") + " (M)ove (U)ndo (S)ave (L)oad (Q)uit", {'N', 'F', 'M', 'U', 'S', 'L', 'Q'});
        if (r == 'N') {
            if (chess.inGame) {
                std::cout << "You are already in a game! Enter F to quit!" << std::endl;
                continue;
            }
            else {
                char c = getInput("Do you want to be (W)hite or (B)lack?", {'W', 'B'});
                clearScreen();
                initBoard((c == 'W'));
                printBoard();
                chess.inGame = true;
            }
        } else if (r == 'F') {
            if (!chess.inGame) {
                std::cout << "You are not in a game! Enter N to start a new one!" << std::endl;
                continue;
            }
            else {
                chess.inGame = false;
                //stop a chess game
            }
        } else if (r == 'M') {
            if (!chess.inGame) {
                std::cout << "You are not in a game! Enter N to start a new one!" << std::endl;
                continue;
            } else {
                parseMoves();
                clearScreen();
                chess.toMove = !chess.toMove;
                printBoard();
            }
        } else if (r == 'U') {
            if (!chess.inGame) {
                std::cout << "You are not in a game! Enter N to start a new one!" << std::endl;
                continue;
            } else {
                //undo last move logic
            }
        } else if (r == 'S') {
            if (!chess.inGame) {
                std::cout << "You are not in a game! Enter N to start a new one!" << std::endl;
                continue;
            } else {
                //save to file or copy to clipboard
            }
        } else if (r == 'L') {
            if (chess.inGame) {
                std::cout << "You are already in a game! Enter Q to quit!" << std::endl;
                continue;
            } else {
                //load game from file or pgn??
            }
        } else break;
    };
    return 0;
}