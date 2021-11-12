#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "connsix.h"

char wbuf[10] ;	

int
is_empty (char hor, int ver)
{
	char pos[5] ;
	snprintf(pos, 4, "%c%02d", hor, ver) ;

	char status = get_stone_at(pos) ;

	if (status == 'E')
		return 1 ;
	else 
		return 0 ;
}

int
main ()
{
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

	char * first ;
	if (strcmp(color, "black") == 0) 
		first = draw_and_read("K10") ;
	else
		first = draw_and_read("") ;

	if (first == 0x0) {
		fprintf(stderr, "Error!\n") ;
		exit(EXIT_FAILURE) ;
	}
	printf("Read %s from server.\n", first) ;

	char hor1 = '\0' ;
	char hor2 = '\0' ;
	int ver1 = 0 ;
	int ver2 = 0 ;
	srand(time(0x0)) ;

	while (1) {
		do {
			hor1 = (rand() % 19) + 'A' ;
			hor1 += ('I' <= hor1) ? 1 : 0 ;
			ver1 = (rand() % 19) + 1 ;
			
			do {
				hor2 = (rand() % 19) + 'A' ;
				hor2 += ('I' <= hor2) ? 1 : 0 ;
				ver2 = (rand() % 19) + 1 ;
			} while (hor1 == hor2 && ver1 == ver2) ;
		} while (is_empty(hor1, ver1) == 0 || is_empty(hor2, ver2) == 0) ;
		
		snprintf(wbuf, 10, "%c%02d:%c%02d", hor1, ver1, hor2, ver2) ;

		char * rbuf = draw_and_read(wbuf) ;
		if (rbuf == 0x0) {
			printf("Error!\n") ;
			break ;
		}
		printf("Read %s from server.\n", rbuf) ;

		if (strcmp(rbuf, "WIN") == 0 || strcmp(rbuf, "LOSE") == 0 || strcmp(rbuf, "TIE") == 0)
			break ;
	}

	return 0 ;
}
