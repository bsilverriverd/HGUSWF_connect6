#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "notation.h"
#include "connsix.h"
#include "board.h"
#include "weight.h"

board_t * home ;
board_t * away ;
weight_t * weight ;

char wbuf[10] ;	

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
		board_decrease(RED, home, h, v) ;
		board_decrease(RED, away, h, v) ;
		weight_decrease(RED, weight, h, v) ;

		redstone = strtok(0x0, ":") ;
	}
}

int
main ()
{
	home = board_new() ;
	away = board_new() ;
	weight = weight_new() ;
	
	for (int i = 0; i < 8; i++)
		printf("dh[%d]=%d\n", i, home->dh[i]) ;

	int a, b ;
	printf("home_max=%d\n", board_max(home, &a, &b)) ;
	printf("away_max=%d\n", board_max(away, &a, &b)) ;
	printf("weight_max=%d\n", weight_max(weight, &a, &b)) ;
	
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
		board_increase(home, 9, 9) ;
		board_decrease(AWAY, away, 9, 9) ;
		weight_increase(weight, 9, 9) ;
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
			board_increase(away, h, v) ;
			board_decrease(AWAY, home, h, v) ;
			weight_decrease(AWAY, weight, h, v) ;

			tok = strtok(0x0, ":") ;
		}

		int hor1, ver1, hor2, ver2 ;

		weight_max(weight, &hor1, &ver1) ;
		board_increase(home, hor1, ver1) ;
		board_decrease(AWAY, away, hor1, ver1) ;
		weight_increase(weight, hor1, ver1) ;

		weight_max(weight, &hor2, &ver2) ;
		board_increase(home, hor2, ver2) ;
		board_decrease(AWAY, away, hor2, ver2) ;
		weight_increase(weight, hor2, ver2) ;

		compose_notation(wbuf, hor1, ver1, hor2, ver2) ;
		
		draw_and_read(wbuf) ;
		
	}

	printf("Game Over. You %s!\n", rbuf) ;
	
	board_delete(home) ;
	board_delete(away) ;
	weight_delete(weight) ;

	return 0 ;
}
