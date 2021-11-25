#include <stdio.h>

#include "notation.h"

int
parse_notation (char * stone, int * hor, int * ver)
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

int
compose_notation (char * stone, int hor1, int ver1, int hor2, int ver2)
{
	if (hor1 < 0 || 19 <= hor1 || ver1 < 0 || 19 <= ver1 ||
		hor2 < 0 || 19 <= hor2 || ver2 < 0 || 19 <= ver2)
		return 1 ;

	hor1 += 'A' ;
	if ('I' <= hor1)
		hor1 += 1 ;
	hor2 += 'A' ;
	if ('I' <= hor2)
		hor2 +=  1;
	ver1 += 1 ;
	ver2 += 1 ;

	sprintf(stone, "%c%02d:%c%02d", (char)hor1, ver1, (char)hor2, ver2) ;

	return 0 ;
}
