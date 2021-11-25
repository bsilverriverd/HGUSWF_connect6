//#ifndef BOARD_H
//#define BOARD_H

#include "point.h"

typedef struct _board {
	point_t point[19][19] ;
	int dh[8] ;
	int dv[8] ;
} board_t ;

board_t *
board_new() ;

void
board_delete (board_t * board) ;

void
board_increase (board_t * board, int h, int v) ;

void
board_decrease (STATE s, board_t * board, int h, int v) ;

int
board_max (board_t * board, int * h, int * v) ;

//#endif
