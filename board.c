#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
parse (char * stone, int * hor, int * ver)
{
	char a = '\0' ;
	int _hor = -1 ;
	int _ver = -1 ;
	int n = 0 ;
	if (sscanf(stone, "%c%2d", &a, &_ver) != 2)
		return 1 ;

	if ('a' <= a && a <= 'h') {
		_hor = a - 'a' ;
	} else if ('A' <= a && a <= 'H') {
		_hor = a - 'A' ;
	} else if ('j' <= a && a <= 't') {
		_hor = a - 'a' - 1 ;
	} else if ('J' <= a && a <= 'T') {
		_hor = a - 'A' - 1 ;
	} else {
		return 1 ;
	}
	
	if (0 < _ver && _ver <= 19) {
		_ver -= 1 ;
	} else {
		return 1 ;
	}
	
	*hor = _hor ;
	*ver = _ver ;

	return 0 ;	
}

typedef enum {
	HOME,
	AWAY,
	RED,
	EMPTY,
} STATE ; 

typedef enum {
	L,
	R,
	T,
	B,
	LT,
	RT,
	LB,
	RB,
} LEVEL ;

const int dh[8] = { 1, -1, 0, 0, 1, -1, 1, -1} ;
const int dv[8] = { 0, 0, 1, -1, 1, 1, -1, -1} ;

typedef struct _point {
	STATE state ;
	int count[8] ;
} point_t ;

typedef struct _board {
	point_t point[19][19] ;
} board_t ;

void
rec_increase (board_t * board, int h, int v, int dir, int depth)
{
	if (h <= 0 || 19 <= h || v <= 0 || 19 <= v)
		return ;
	
	if (depth == 6)
		return ;
	
	switch (board->point[v][h].state) {
		case EMPTY :
			board->point[v][h].count[dir] += 1 ;
		case HOME :
			rec_increase(board, h + dh[dir], v + dv[dir], dir, depth + 1) ;
			break ;
		case AWAY :
		case RED :
		default :
			break ;
	}
	return ;
}

void
rec_decrease (board_t * board, int h, int v, int dir, int depth, int weight)
{
	if (h <= 0 || 19 <= h || v <= 0 || 19 <= v)
		return ;
	
	if (depth == 6)
		return ;

	switch (board->point[v][h].state) {
		case EMPTY :
			board->point[v][h].count[dir] = weight ;
			rec_decrease(board, h + dh[dir], v + dv[dir], dir, depth + 1, weight) ;
			break ; 
		case HOME :
			rec_decrease(board, h + dh[dir], v + dv[dir], dir, depth + 1, weight + 1) ;
			break ;	
		case AWAY :
		case RED :
		default :
			break ;
	}
	return ;
}

void
point_init (point_t * point)
{
	point->state = EMPTY ;
	for (int i = 0; i < sizeof(point->count)/sizeof(point->count[0]); i++)
		point->count[i] = 0 ; 
}

////////
board_t *
board_alloc()
{
	board_t * board = (board_t *)malloc(sizeof(board_t)) ;

	if (board == 0x0) {
		perror("board_alloc()") ;
		exit(1) ;
	}
	
	return board ;
}

void
board_init (board_t * board)
{
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			point_init(&(board->point[i][j])) ;
}

void
increase_board (board_t * board, char * stone) {
	int h = -1 ;
	int v = -1 ;
	parse(stone, &h, &v) ;

	board->point[v][h].state = HOME ;

	for (int i = 0; i < 8; i++) {
		rec_increase(board, h + dh[i], v + dv[i], i, 1) ;
	}
}

void
decrease_board (STATE s, board_t * board, char * stone)
{
	int h = -1 ;
	int v = -1 ;
	parse(stone, &h, &v) ;

	board->point[v][h].state = s ;

	for (int i = 0; i < 8; i++) {
		rec_decrease(board, h + dh[i], v + dv[i], i, 1, 0) ;
	}
}

#endif


















