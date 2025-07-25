#include "bitboard.h"
#include "fen.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

MoveList* get_pawn_moves(Piece cur_piece, Bitboard my_pieces, Bitboard opp_pieces, int sq, int can_enpassant){
    static MoveList movelist; 
    movelist.count = 0;
    int row = floor(sq / 8);
    int col = sq - row * 8; 
    
    if (cur_piece.type == 'P'){
        if (row == 1 && GET_BIT(my_pieces, sq + 8) == 0x0ULL && GET_BIT(opp_pieces, sq + 8) == 0x0ULL
            && GET_BIT(my_pieces, sq + 16) == 0x0ULL && GET_BIT(opp_pieces, sq + 16) == 0x0ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq + 16, 0, 5);
                movelist.count++;
            }

        if (GET_BIT(my_pieces, sq + 8) == 0x0ULL && GET_BIT(opp_pieces, sq + 8) == 0x0ULL) {
            if (row == 6){
                for (int i = 0; i < 4; i++){
                    movelist.moves[movelist.count + i] = MAKE_MOVE(sq, sq + 8, i + 1, 4);
                }
                movelist.count += 4;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq + 8, 0, 0);
                movelist.count++;
            }
        }

        if (col < 7 && GET_BIT(opp_pieces, sq + 9) == 0x1ULL) {
            if (row == 6){
                for (int i = 0; i < 4; i++){
                    movelist.moves[movelist.count + i] = MAKE_MOVE(sq, sq + 9, i + 1, 4);
                }
                movelist.count += 4;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq + 9, 0, 1);
                movelist.count++;
            }
        } else if (col < 7 && can_enpassant > 0 && sq + 9 == can_enpassant){
            movelist.moves[movelist.count] = MAKE_MOVE(sq, sq + 9, 0, 2);
            movelist.count++;
        }

        if (col > 0 && GET_BIT(opp_pieces, sq + 7) == 0x1ULL) {
            if (row == 6){
                for (int i = 0; i < 4; i++){
                    movelist.moves[movelist.count + i] = MAKE_MOVE(sq, sq + 7, i + 1, 4);
                }
                movelist.count += 4;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq + 7, 0, 1);
                movelist.count++;
            }
        } else if (col > 0 && can_enpassant > 0 && sq + 7 == can_enpassant){
            movelist.moves[movelist.count] = MAKE_MOVE(sq, sq + 7, 0, 2);
            movelist.count++;
        }

    } else {
        if (row == 6 && GET_BIT(my_pieces, sq - 8) == 0x0ULL && GET_BIT(opp_pieces, sq - 8) == 0x0ULL
            && GET_BIT(my_pieces, sq - 16) == 0x0ULL && GET_BIT(opp_pieces, sq - 16) == 0x0ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq - 16, 0, 5);
                movelist.count++;
            }

        if (GET_BIT(my_pieces, sq - 8) == 0x0ULL && GET_BIT(opp_pieces, sq - 8) == 0x0ULL) {
            if (row == 1){
                for (int i = 0; i < 4; i++){
                    movelist.moves[movelist.count + i] = MAKE_MOVE(sq, sq - 8, i + 1, 4);
                }
                movelist.count += 4;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq - 8, 0, 0);
                movelist.count++;
            }
        }

        if (col < 7 && GET_BIT(opp_pieces, sq - 7) == 0x1ULL) {
            if (row == 1){
                for (int i = 0; i < 4; i++){
                    movelist.moves[movelist.count + i] = MAKE_MOVE(sq, sq - 7, i + 1, 4);
                }
                movelist.count += 4;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq - 7, 0, 1);
                movelist.count++;
            }
        } else if (col < 7 && can_enpassant > 0 && sq - 7 == can_enpassant){
            movelist.moves[movelist.count] = MAKE_MOVE(sq, sq - 7, 0, 2);
            movelist.count++;
        }

        if (col > 0 && GET_BIT(opp_pieces, sq - 9) == 0x1ULL) {
            if (row == 1){
                for (int i = 0; i < 4; i++){
                    movelist.moves[movelist.count + i] = MAKE_MOVE(sq, sq - 9, i + 1, 4);
                }
                movelist.count += 4;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, sq - 9, 0, 1);
                movelist.count++;
            }
        } else if (col > 0 && can_enpassant > 0 && sq - 9 == can_enpassant){
            movelist.moves[movelist.count] = MAKE_MOVE(sq, sq - 9, 0, 2);
            movelist.count++;
        }
    }

    return &movelist;
}

MoveList* get_knight_moves(Piece cur_piece, Bitboard my_pieces, Bitboard opp_pieces, int sq){
    static MoveList movelist; 
    movelist.count = 0;
    int row = floor(sq / 8);
    int col = sq - row * 8; 
    for (int curRow = row - 2; curRow <= row + 2; curRow++) {
      for (int curCol = col - 2; curCol <= col + 2; curCol++) {
        int to = curRow * 8 + curCol;
        if (
          curRow >= 0 &&
          curRow < 8 &&
          curCol >= 0 &&
          curCol < 8 &&
          abs(row - curRow) != abs(col - curCol) &&
          GET_BIT(my_pieces, to) == 0x0ULL &&
          curRow != row &&
          curCol != col
        ) {
            if (GET_BIT(opp_pieces, to) == 0x1ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 1);
                movelist.count++;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 0);
                movelist.count++;
            }
        }
      }
    }
    return &movelist;
}

MoveList* get_bishop_moves(Piece cur_piece, Bitboard my_pieces, Bitboard opp_pieces, int sq){
    static MoveList movelist; 
    movelist.count = 0;
    int row = floor(sq / 8);
    int col = sq - row * 8; 
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int idx = 0; idx < 4; idx++){
        for (int i = 1; i < 8; i++) {
            int curRow = row + directions[idx][0] * i;
            int curCol = col + directions[idx][1] * i;
            int to = curRow * 8 + curCol;
            if (curRow < 0 || curCol < 0 || curRow > 7 || curCol > 7) {
                break;
            } else if (GET_BIT(my_pieces, to) == 0x0ULL && GET_BIT(opp_pieces, to) == 0x0ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 0);
                movelist.count++;
            } else if (GET_BIT(opp_pieces, to) == 0x1ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 1);
                movelist.count++;
                break;
            } else {
                break;
            }
        }
    }
    return &movelist;
}

MoveList* get_rook_moves(Piece cur_piece, Bitboard my_pieces, Bitboard opp_pieces, int sq){
    static MoveList movelist; 
    movelist.count = 0;
    int row = floor(sq / 8);
    int col = sq - row * 8; 
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int idx = 0; idx < 4; idx++){
        for (int i = 1; i < 8; i++) {
            int curRow = row + directions[idx][0] * i;
            int curCol = col + directions[idx][1] * i;
            int to = curRow * 8 + curCol;
            if (curRow < 0 || curCol < 0 || curRow > 7 || curCol > 7) {
                break;
            } else if (GET_BIT(my_pieces, to) == 0x0ULL && GET_BIT(opp_pieces, to) == 0x0ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 0);
                movelist.count++;
            } else if (GET_BIT(opp_pieces, to) == 0x1ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 1);
                movelist.count++;
                break;
            } else {
                break;
            }
        }
    }
    return &movelist;
}

MoveList* get_queen_moves(Piece cur_piece, Bitboard my_pieces, Bitboard opp_pieces, int sq){
    static MoveList movelist; 
    movelist.count = 0;
    MoveList* bishop_moves = get_bishop_moves(cur_piece, my_pieces, opp_pieces, sq);
    MoveList* rook_moves = get_rook_moves(cur_piece, my_pieces, opp_pieces, sq);
    for (int i = 0; i < bishop_moves->count; i++){
        movelist.moves[movelist.count] = bishop_moves->moves[i];
        movelist.count++;
    }

    for (int i = 0; i < rook_moves->count; i++){
        movelist.moves[movelist.count] = rook_moves->moves[i];
        movelist.count++;
    }

    return &movelist;
}

MoveList* get_king_moves(Piece cur_piece, Bitboard my_pieces, Bitboard opp_pieces, int sq, char* can_castle){
    static MoveList movelist; 
    movelist.count = 0;
    int row = floor(sq / 8);
    int col = sq - row * 8; 
    for (int curRow = row - 1; curRow <= row + 1; curRow++) {
      for (int curCol = col - 1; curCol <= col + 1; curCol++) {
        int to = curRow * 8 + curCol;
        if (
          curRow >= 0 &&
          curRow < 8 &&
          curCol >= 0 &&
          curCol < 8 &&
          (GET_BIT(my_pieces, to) == 0x0ULL) &&
          (curRow != row || curCol != col)
        ) {
          if (GET_BIT(opp_pieces, to) == 0x1ULL) {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 1);
                movelist.count++;
            } else {
                movelist.moves[movelist.count] = MAKE_MOVE(sq, to, 0, 0);
                movelist.count++;
            }
        }
      }
    }

    if (cur_piece.type == 'K'){
        if (
        strchr(can_castle, 'K') &&
        (GET_BIT(my_pieces, 1) == 0x0ULL && GET_BIT(opp_pieces, 1) == 0x0ULL) &&
        (GET_BIT(my_pieces, 2) == 0x0ULL && GET_BIT(opp_pieces, 2) == 0x0ULL)
        ) {
            movelist.moves[movelist.count] = MAKE_MOVE(sq, 1, 0, 3);
            movelist.count++;
        }

        if (
        strchr(can_castle, 'Q') &&
        (GET_BIT(my_pieces, 4) == 0x0ULL && GET_BIT(opp_pieces, 4) == 0x0ULL) &&
        (GET_BIT(my_pieces, 5) == 0x0ULL && GET_BIT(opp_pieces, 5) == 0x0ULL) && 
        (GET_BIT(my_pieces, 6) == 0x0ULL && GET_BIT(opp_pieces, 6) == 0x0ULL) 
        ) {
            movelist.moves[movelist.count] = MAKE_MOVE(sq, 5, 0, 3);
            movelist.count++;
        }
    } else {
        if (
        strchr(can_castle, 'k') &&
        (GET_BIT(my_pieces, 57) == 0x0ULL && GET_BIT(opp_pieces, 57) == 0x0ULL) &&
        (GET_BIT(my_pieces, 58) == 0x0ULL && GET_BIT(opp_pieces, 57) == 0x0ULL)
        ) {
            movelist.moves[movelist.count] = MAKE_MOVE(sq, 57, 0, 3);
            movelist.count++;
        }

        if (
        strchr(can_castle, 'q') &&
        (GET_BIT(my_pieces, 60) == 0x0ULL && GET_BIT(opp_pieces, 60) == 0x0ULL) &&
        (GET_BIT(my_pieces, 61) == 0x0ULL && GET_BIT(opp_pieces, 61) == 0x0ULL) && 
        (GET_BIT(my_pieces, 62) == 0x0ULL && GET_BIT(opp_pieces, 62) == 0x0ULL) 
        ) {
            movelist.moves[movelist.count] = MAKE_MOVE(sq, 61, 0, 3);
            movelist.count++;
        }
    }

    return &movelist;
}

MoveList* get_all_moves_from_square(Piece cur_piece, Bitboard my_pieces, Bitboard opp_pieces, 
int sq, char* can_castle, int can_enpassant){
    char given_type = toupper(cur_piece.type);
    switch (given_type) {
      case 'P':
        return get_pawn_moves(cur_piece, my_pieces, opp_pieces, sq, can_enpassant);
      case 'N':
        return get_knight_moves(cur_piece, my_pieces, opp_pieces, sq);
      case 'B':
        return get_bishop_moves(cur_piece, my_pieces, opp_pieces, sq);
      case 'R':
        return get_rook_moves(cur_piece, my_pieces, opp_pieces, sq);
      case 'Q':
        return get_queen_moves(cur_piece, my_pieces, opp_pieces, sq);
      case 'K':
        return get_king_moves(cur_piece, my_pieces, opp_pieces, sq, can_castle);
    }

    return NULL;
}