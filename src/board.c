#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"

void
r_board_increase (board_t * board, int h, int v, int dir, int depth)
{
	if (h < 0 || 19 <= h || v < 0 || 19 <= v)
		return ;
	
	if (depth == 6)
		return ;
	
	switch (board->point[v][h].state) {
		case EMPTY :
			board->point[v][h].count[dir] += 1 ;
		case HOME :
			r_board_increase(board, h + board->dh[dir], v + board->dv[dir], dir, depth + 1) ;
			break ;
		case AWAY :
		case RED :
		default :
			break ;
	}
	return ;
}

void
r_board_decrease (board_t * board, int h, int v, int dir, int depth, int weight)
{
	fprintf(stderr,"h=%d, v=%d, dir=%d, depth=%d, weight=%d\n",h,v,dir,depth,weight);
	if (h < 0 || 19 <= h || v < 0 || 19 <= v)
		return ;
	
	if (depth == 6)
		return ;

	switch (board->point[v][h].state) {
		case EMPTY :
			board->point[v][h].count[dir] = weight ;
			r_board_decrease(board, h + board->dh[dir], v + board->dv[dir], dir, depth + 1, weight) ;
			break ; 
		case HOME :
			r_board_decrease(board, h + board->dh[dir], v + board->dv[dir], dir, depth + 1, weight + 1) ;
			break ;	
		case AWAY :
		case RED :
		default :
			break ;
	}
	return ;
}

/*** header declared functions ***/
board_t *
board_new()
{
	board_t * board = (board_t *)malloc(sizeof(board_t)) ;
	if (board == 0x0) {
		perror("board_new():board") ;
		exit(1) ;
	}
	
	board->point = (point_t **)malloc(sizeof(point_t *) * 19) ;
	if(board->point == 0x0) {
		perror("board_new():board->point") ;
		exit(1) ;
	}

	
	for (int i = 0; i < 19; i++) {
		board->point[i] = (point_t *)malloc(sizeof(point_t) * 19) ;
		if (board->point[i] == 0x0) {
			perror("board_new():board->point[i]") ;
			exit(1) ;
		}
	}

	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			point_init(&(board->point[i][j]), 8) ;

	board->dh = (int *)malloc(sizeof(int) * 8) ;
	if (board->dh == 0x0) {
		perror("board_new():board->dh") ;
		exit(1) ;
	}
	board->dv = (int *)malloc(sizeof(int) * 8) ;
	if (board->dh == 0x0) {
		perror("board_new():board->dv") ;
		exit(1) ;
	}

	int dh[8] = { 1, -1, 0, 0, 1, -1, 1, -1} ;
	int dv[8] = { 0, 0, 1, -1, 1, 1, -1, -1} ;
	
	for (int i = 0; i < 8; i++) {
		board->dh[i] = dh[i] ;
		board->dv[i] = dv[i] ;
	}

	return board ;
}

void
board_delete (board_t * board)
{
	//for (int i = 0; i < 19; i++)
	//	for (int j = 0; j < 19; j++)
	//		point_delete(board->point[i][j]) ;
	
	free(board) ;
}

void
board_increase (board_t * board, int h, int v)
{
	board->point[v][h].state = HOME ;

	for (int i = 0; i < 8; i++)
		r_board_increase(board, h + board->dh[i], v + board->dv[i], i, 1) ;
}

void
board_decrease (STATE s, board_t * board, int h, int v)
{
	printf("h=%d,v=%d",h,v) ;
	board->point[v][h].state = s ;
	printf("state %d\n", board->point[v][h].state) ;

	fprintf(stderr,"state\n") ;
	for (int i = 0; i < 8; i++)
		r_board_decrease(board, h + board->dh[i], v + board->dv[i], i, 1, 0) ;
}

int
board_max (board_t * board, int * h, int * v)
{
	int max = -1 ;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (board->point[i][j].state != EMPTY)
				continue ;

			int sum = point_sum(&(board->point[i][j])) ;
			if (max < sum) {
				max = sum ;
				*h = j ;
				*v = i ;
			}
		}
	}
	return max ;
}
