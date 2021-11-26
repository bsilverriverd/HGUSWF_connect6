#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "notation.h"
#include "connsix.h"
#include "board.h"
#include "weight.h"

board_t * home_board ;
board_t * away_board ;
weight_t * home_weight ;
weight_t * away_weight ;

char wbuf[10] ;	

int
can_win (board_t * board, int * h, int * v)
{
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 19; j++) {
				if (board->point[i][j].state != EMPTY)
					continue ;
				for (int dir = 0; dir < 4; dir++) {
				int sum = board->point[i][j].count[dir*2] + board->point[i][j].count[dir*2+1] ;
				if (sum >= 4) {
					*h = j ;
					*v = i ;
					return 1 ;
				}
			}
		}
	}
	return 0 ;
}

int
calculate (board_t * board, weight_t * weight, int * h, int * v)
{
	int max = 0 ;
	for (int i = 0; i < 19; i++) {
		for(int j = 0; j < 19; j++) {
			int sum =  point_sum(&(board->point[i][j])) ;
			sum += point_sum(&(weight->point[i][j])) ;
			if (max < sum) {
				max = sum ;
				*h = j ;
				*v = i ;
			}
		}
	}
	return max ;
}

int
generate (board_t * hb, board_t * ab, weight_t * hw, weight_t * aw, int * h, int * v)
{
	int max = 0 ;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			int sum = point_sum(&(hb->point[i][j])) ;
			sum += point_sum(&(hw->point[i][j])) ;
			sum += point_sum(&(ab->point[i][j])) ;
			sum += point_sum(&(aw->point[i][j])) ;

			if (max < sum) {
				max = sum ;
				*h = j ;
				*v = i ;
			}
		}
	}
	return max ;
}	

void
set_redstones (char * redstones)
{
	char * redstone = strtok(redstones, ":") ;
	while (redstone != 0x0) {
		int h = -1 ;
		int v = -1 ;
		parse_notation(redstone, &h, &v) ;

		fprintf(stderr, "redstone %d %d\n", h, v) ;

		printf("%d\n", RED) ;
		board_decrease(RED, home_board, h, v) ;
		board_decrease(RED, away_board, h, v) ;
		weight_decrease(RED, home_weight, h, v) ;
		weight_decrease(RED, away_weight, h, v) ;

		redstone = strtok(0x0, ":") ;
	}
}

int
main ()
{
	home_board = board_new() ;
	away_board = board_new() ;
	home_weight = weight_new() ;
	away_weight = weight_new() ;
	
	char ip[20] ;
	int port = 0 ;
	char color[10] ;
	printf("Enter ip: ") ;
	scanf("%s", ip) ;
	printf("Enter port number: ") ;
	scanf("%d", &port) ;
	printf("Enter player color: ") ;
	scanf("%s", color) ;

	char * redstones = lets_connect(ip, port, color) ;
	if (redstones == 0x0) {
		fprintf(stderr, "Error!\n") ;
		exit(EXIT_FAILURE) ;
	}
	printf("Received %s redstones.\n", redstones) ;

	set_redstones(redstones) ;

	char * rbuf ;
	if (strcmp(color, "black") == 0) {
		board_increase(home_board, 9, 9) ;
		weight_increase(home_weight, 9, 9) ;
		board_decrease(AWAY, away_board, 9, 9) ;
		weight_decrease(AWAY, away_weight, 9, 9) ;
		rbuf = draw_and_read("K10") ;
	} else {
		rbuf = draw_and_read("") ;
	}

	while (1) {
		if (rbuf == 0x0) {
			fprintf(stderr, "Error!\n") ;
			exit(EXIT_FAILURE) ;
		}
		printf("Read %s from server.\n", rbuf) ;
		
		if (strcmp("WIN", rbuf) == 0 ||
			strcmp("LOSE", rbuf) == 0 ||
			strcmp("TIE", rbuf) == 0)
			break ;

		char * tok = strtok(rbuf, ":") ;
		while (tok != 0x0) {
			int h = -1 ;
			int v = -1 ;
			parse_notation(tok, &h, &v) ;
			board_increase(away_board, h, v) ;
			weight_increase(away_weight, h, v) ;
			board_decrease(AWAY, home_board, h, v) ;
			weight_decrease(AWAY, home_weight, h, v) ;

			tok = strtok(0x0, ":") ;
		}

		int hor[2], ver[2] ;
/*
		if (can_win(home_board, &hor[0], &ver[0]) == 1) {
			board_increase(home_board, hor[0], ver[0]) ;
			weight_increase(home_weight, hor[0], ver[0]) ;
			board_decrease(AWAY, away_board, hor[0], ver[0]) ;
			weight_decrease(AWAY, away_weight, hor[0], ver[0]) ;
			
			if (can_win(home_board, &hor[1], &hor[1]) == 1) {
			board_increase(home_board, hor[1], ver[1]) ;
			weight_increase(home_weight, hor[1], ver[1]) ;
			board_decrease(AWAY, away_board, hor[1], ver[1]) ;
			weight_decrease(AWAY, away_weight, hor[1], ver[1]) ;

			} else {
				calculate(away_board, away_weight, &hor[1], &ver[1]) ;
			board_increase(home_board, hor[1], ver[1]) ;
			weight_increase(home_weight, hor[1], ver[1]) ;
			board_decrease(AWAY, away_board, hor[1], ver[1]) ;
			weight_decrease(AWAY, away_weight, hor[1], ver[1]) ;

			}
		} else {*/
		for (int i = 0; i < 2; i++) {
			calculate(away_board, away_weight, &hor[i], &ver[i]) ;
			/*
			int home_h, home_v, away_h, away_v ;

			int home_sum = calculate(home_board, home_weight, &home_h, &home_v) ;
			int away_sum = calculate(away_board, away_weight, &away_h, &away_v) ;

			if (away_sum < home_sum) {
				hor[i] = home_h ;
				ver[i] = home_v ;
			} else {
				hor[i] = away_h ;
				ver[i] = away_v ;
			}
			*/
			/*
			generate(home_board, away_board, home_weight, away_weight, &hor[i], &ver[i]) ;
			*/
			board_increase(home_board, hor[i], ver[i]) ;
			weight_increase(home_weight, hor[i], ver[i]) ;
			board_decrease(AWAY, away_board, hor[i], ver[i]) ;
			weight_decrease(AWAY, away_weight, hor[i], ver[i]) ;
		}
		compose_notation(wbuf, hor[0], ver[0], hor[1], ver[1]) ;
		draw_and_read(wbuf) ;
		
	}

	printf("Game Over. You %s!\n", rbuf) ;

	return 0 ;
}
