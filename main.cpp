#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/detail/find_format_store.hpp>
#include <boost/function/function_base.hpp>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <istream>
#include <stdexcept>
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
std::ostream& operator << (std::ostream &o, const vec2<T>& p) {
    return o << "x: " << p.x << ", y: " << p.y << std::endl;
}
template <typename T> 
inline bool operator != (const vec2<T>& p1, const vec2<T>& p2) {
    return (p1.x!=p2.x||p1.y!=p2.y);
}


struct BoardPiece {
    int type;
    int color;
    int moveCount = 0;
    int lastTurnMoved = 0;
    vec2<int> pos;
    BoardPiece(int t, int c) {
        type = t;
        color = c;
    }
};

std::ostream& operator<< (std::ostream &o, const BoardPiece& p) {
    return o << "Type: " << p.type << ", Color: " << p.color  << " LastMoved: " << p.lastTurnMoved << std::endl;
}

 struct {
    int toMove = 1;
    bool quit = false;
    bool inGame = false;
    bool isWhite = true;
    int turnCount = 0;
    bool inCheck = false;
    int check = 0;
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

bool itemsInPath(vec2<int> c, vec2<int> d) {
    if (c.x==d.x) {
        for (int i = c.y+1; i < abs(c.y-d.y);i++) {
            if (chess.board[c.x][i].type != 0) return true;
        }
    //in the same path
    } else if (c.y==d.y) {
        for (int i = c.x+1; i < abs(c.x-d.x);i++) {
            if (chess.board[i][c.y].type != 0) return true;
        }
    //fucking diagonals
    } else {
        int dx = d.x < c.x ? -1 : 1;
        int dy = d.y < c.y ? -1 : 1;
        for (int i = 1; i < abs(d.x-c.x);i++) {
            if (chess.board[c.x + (i*dx)][c.y + (i*dy)].type != 0) return true;
        }
    }
    return false;
}
BoardPiece itemInDirection(vec2<int> c, vec2<int> d) {
    // checks diagonals
    if (abs(d.x)+abs(d.y)==2)  {
        for (int i = 1; i < (d.x==-1?std::min(c.x, c.y):std::min(7-c.x, 7-c.y));i++) {
            chess.board[c.x + (i*d.x)][c.y + (i*d.y)].pos = {c.x + (i*d.x), c.y + (i*d.y)};
            if (chess.board[c.x + (i*d.x)][c.y + (i*d.y)].type != 0) return chess.board[c.x + (i*d.x)][c.y + (i*d.y)];
        }
    //checks straight lines
    }  else if (d.x==0) {
        for (int i = c.y+d.y; (d.y==-1?i>=0:i<8);(d.y==-1?i--:i++)) {
            chess.board[c.x][i].pos = {c.x, i};
            if (chess.board[c.x][i].type != 0) return chess.board[c.x][i];
        }
    } else if(d.y==0) {
        for (int i = c.x+d.x; (d.x==-1?i>=0:i<8);(d.x==-1?i--:i++)) {
            chess.board[i][c.y].pos = {i, c.y};
            if (chess.board[i][c.y].type != 0) return chess.board[i][c.y];
        }
    //check for L
    } else {

    }
    return BoardPiece(0, 0);
}
bool isKingInCheck(bool isWhite) {
    vec2<int> kingPos;
    std::vector<vec2<int>> knt;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chess.board[i][j].type == 1 && chess.board[i][j].color == isWhite) {
                kingPos = {i, j};
            } else if (chess.board[i][j].type == 4 && chess.board[i][j].color != isWhite) {
                knt.push_back({i,j});
            }
        }
    }
    for (int i : {1, 0, -1}) {
        for (int j : {1, 0, -1}) {
            if (abs(i)+abs(j)!=0) {
                BoardPiece item = itemInDirection(kingPos, {i, j});
                // KNIGHT
                // checks L
                for (vec2<int> k : knt) if (abs(k.x-kingPos.x)*abs(k.y-kingPos.y)==2) return true;
                if (item.type!=0 && item.color!=isWhite) {
                    int dx = (item.pos.x == kingPos.x ? 0 : item.pos.x < kingPos.x ? -1 : 1);
                    int dy = (item.pos.y == kingPos.y ? 0 : item.pos.y < kingPos.y ? -1 : 1);
                    // QUEEN CHECK
                    // checks if it is horizontal/vertical or in a diagonal
                    if (item.type==2 && !(abs(dx)+abs(dy)!=1 && abs(item.pos.y-kingPos.y)/abs(item.pos.x-kingPos.x)!=1)) return true;
                    // BISHOP
                    // checks if diagonal
                    if (item.type==3 && !(abs(item.pos.y-kingPos.y)/abs(item.pos.x-kingPos.x)!=1)) return true;
                    // ROOK
                    // checks if horizontal
                    if (item.type==5 && !(abs(dx)+abs(dy)!=1)) return true;
                    // PAWN
                    // checks if the king is on the correct side and if it isnt in front of the pawn
                    if (item.type==6 && (((item.pos.x-kingPos.x>0&&chess.toMove)||(item.pos.x-kingPos.x<0&&!chess.toMove)) && abs(kingPos.y-item.pos.y)==1)) return true;
                } 
            }
        }
    }
    return false;
}
//generates temp variables from the input pieces
//sets the target board piece to a blank and then swaps the piece moving it onto the square
//then checks if the king is in check from that move and if so it reverses the swap and returns false
//if the current turn's king is not in check and it is a test for the hasValidMoves function it reverses the values anyways and returns true as to not edit the boardpieces data
bool movePiece(BoardPiece *c, BoardPiece *t, bool enPassant = false, BoardPiece*ep=nullptr, bool test=false) {
    std::cout << "CHECK2: " << (test?isKingInCheck(!chess.toMove):isKingInCheck(chess.toMove)) << " " << test << std::endl;
    //if (test && isKingInCheck(chess.toMove)) return false;
    BoardPiece *tT = t;
    BoardPiece *epT = ep;
    if (enPassant) *ep = BoardPiece(0, 0);
    *t = BoardPiece(0, 0);
    std::swap(*c, *t);
    if (test?isKingInCheck(!chess.toMove):isKingInCheck(chess.toMove)) {
        std::swap(*c, *t);
        t = tT;
        if (enPassant) ep = epT;
        return false;
    }
    if (test) {
        std::swap(*c, *t);
        t = tT;
        if (enPassant) ep = epT;
        return true;
    }
    t->moveCount++;
    t->lastTurnMoved=chess.turnCount;
    return true;
}
vec2<bool> isValidMove(vec2<int> currentPos, vec2<int> targetedPos) {
    BoardPiece* current = &chess.board[currentPos.x][currentPos.y];
    BoardPiece* target = &chess.board[targetedPos.x][targetedPos.y];

    if (current->type != 0 && chess.toMove == current->color && currentPos != targetedPos && currentPos.x < 8 && currentPos.x > -1 && currentPos.y < 8 && currentPos.y > -1 && targetedPos.x < 8 && targetedPos.x > -1 && targetedPos.y < 8 && targetedPos.y > -1) {
        //TODO FOR ALL TYPES: promotion with select screen, checkmate and stalemate detection
        switch (current->type) {
            // KING
            case 1: {
                // King can only move one square at a time so yea
                if (abs(targetedPos.x-currentPos.x) > 1 || abs(targetedPos.y-currentPos.y) > 1) return {false, false};
                if (!itemsInPath(currentPos, targetedPos) && (target->color!=chess.toMove || target->type==0)) {
                    return {true, false};
                }
                return {false, false};
            break;
            }
            // QUEEN
            case 2: {
                int dx = (targetedPos.x == currentPos.x ? 0 : targetedPos.x < currentPos.x ? -1 : 1);
                int dy = (targetedPos.y == currentPos.y ? 0 : targetedPos.y < currentPos.y ? -1 : 1);
                if (abs(dx)+abs(dy)!=1 && abs(targetedPos.y-currentPos.y)/abs(targetedPos.x-currentPos.x)!=1) return {false, false};
                if (!itemsInPath(currentPos, targetedPos) && (target->color!=chess.toMove || target->type==0)) {
                    return {true, false};
                }
                return {false, false};
            break;
            }
            // BISHOP
            case 3: {
                int dx = (targetedPos.x == currentPos.x ? 0 : targetedPos.x < currentPos.x ? -1 : 1);
                int dy = (targetedPos.y == currentPos.y ? 0 : targetedPos.y < currentPos.y ? -1 : 1);
                if (abs(targetedPos.y-currentPos.y) == 0 || abs(targetedPos.x-currentPos.x)==0) return {false, false};
                if (abs(targetedPos.y-currentPos.y)/abs(targetedPos.x-currentPos.x)!=1) return {false, false};
                if (!itemsInPath(currentPos, targetedPos) && (target->color!=chess.toMove || target->type==0)) {
                    return {true, false};
                }
                return {false, false};
            break;
            }
            // KNIGHT
            case 4: {
                if (abs(targetedPos.x-currentPos.x)*abs(targetedPos.y-currentPos.y)!=2 || (target->color==chess.toMove && target->type!=0)) return {false, false};
                return {true, false};
            }
            // ROOK
            case 5: {
                int dx = (targetedPos.x == currentPos.x ? 0 : targetedPos.x < currentPos.x ? -1 : 1);
                int dy = (targetedPos.y == currentPos.y ? 0 : targetedPos.y < currentPos.y ? -1 : 1);
                if (abs(dx)+abs(dy)==2) return {false, false};
                if (!itemsInPath(currentPos, targetedPos) && (target->color!=chess.toMove || target->type==0)) {
                  return {true, false};
                }
                return {false, false};
            break;
            }
            // PAWN
            case 6: {
                //check if moving backwards
                if ((targetedPos.x-currentPos.x>0&&chess.toMove)||(targetedPos.x-currentPos.x<0&&!chess.toMove)) return {false, false};
                //checks if x(y) movement is equal to one or 2 if hasnt moved
                int movement = abs(targetedPos.x-currentPos.x);
                if (movement > 2||(current->moveCount!=0&&movement==2)) return {false, false};
                //non en passant/capture check
                if (targetedPos.y == currentPos.y) {
                    if (target->type != 0 || itemsInPath(currentPos, targetedPos)) return {false, false};
                    return {true, false};
                //en passant/capture code
                } else {
                    //moving too far left and right
                    if (abs(targetedPos.y-currentPos.y) > 1) return {false, false}; 
                    int dy = targetedPos.y-currentPos.y;
                    //en passant checks if there is a pawn next to us, if it has only moved once, and if the current position is in the 5th or 6th row, also if it has moved in the last turn, adn also if it is a different color
                    if (chess.board[currentPos.x][currentPos.y+dy].type==6 && chess.board[currentPos.x][currentPos.y+dy].moveCount==1 && (currentPos.x == 3 || currentPos.x == 4) && chess.board[currentPos.x][currentPos.y+dy].lastTurnMoved+1==chess.turnCount && chess.board[currentPos.x][currentPos.y+dy].color != chess.toMove && target->type==0) {
                        return {true, true};
                    }
                    if (target->type !=0 && target->color != chess.toMove) {
                        return {true, false};
                    }
                    return {false, false};
                }
            break;
            }
        }
        return {true, false};
    } else return {false, false};
}
// loop through all the possible pieces and all the possible moves on the board to see if there is a valid move that does not put the king in check
// calls the movepiece on test mode which doesnt modify any of the values

bool hasValidMoves(bool isWhite) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chess.board[i][j].type != 0 && chess.board[i][j].color == isWhite) {
                
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        vec2<bool> v = isValidMove({i, j}, {k, l});
                        if (v.x) {
                            if (movePiece(&chess.board[i][j], &chess.board[k][l], v.y, &chess.board[i][j+(l-j)], true)) return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void parseMoves() {
    std::string move;
    bool isValid = false;
    do {
        std::cout << "Enter a valid move (examples of notation: E4-E5 or G3-F5): ";
        //std::cin.ignore();
        std::getline(std::cin >> std::ws, move);
        for (char & c: move) c = toupper(c);
        //
        // IMPORTANT X AND Y ARE SWAPPED DUE TO HOW THE ROWS WORK!!!!
        // DOWN = MORE X
        // RIGHT = MORE Y
        //
        if (move.at(2) != '-' || move.size() != 5) continue;
        vec2<int> currentPos = {abs(atoi(&move.at(1))-8), int(move.at(0))-65 };
        vec2<int> targetedPos = {abs(atoi(&move.at(4))-8), int(move.at(3))-65 };
        vec2<bool> r = isValidMove(currentPos, targetedPos);
        std::cout << r << std::endl;
        if (r.x) {
            isValid = movePiece(&chess.board[currentPos.x][currentPos.y], &chess.board[targetedPos.x][targetedPos.y], r.y, &chess.board[currentPos.x][currentPos.y+(targetedPos.y-currentPos.y)]);
        }
    } while (!isValid);
    std::cout << "CHECK: " <<  isKingInCheck(!chess.toMove) << " MOVES: " << hasValidMoves(!chess.toMove) << " TOMove: " << !chess.toMove << std::endl;
    // first checks if the opposite king is in check then checks if the other side has valid moves
    // 
    if (isKingInCheck(!chess.toMove)) {
        chess.inCheck = true;
        chess.check = !chess.toMove;
    } else {
        chess.inCheck = false;
    }

    if (hasValidMoves(!chess.toMove)) {
        printBoard();
        if (chess.inCheck) {
            std::cout << (chess.toMove==1?"White":"Black") << " won the game!" << std::endl; 
        } else {
            std::cout << "Stalemate! Nobody won!" << std::endl;
        }
        chess.quit=true;
        return;
    }
    return;
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
                //clearScreen();
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
                //clearScreen();
                chess.toMove = !chess.toMove;
                chess.turnCount++;
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