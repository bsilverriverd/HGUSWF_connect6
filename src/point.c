#include <stdio.h>
#include <stdlib.h>

#include "point.h"

point_t *
point_new (int size)
{
	point_t * point = (point_t *)malloc(sizeof(point)) ;

	if (point == 0x0) {
		perror("point_new():point") ;
		exit(1) ;
	} ;

	point->state = EMPTY ;
	point->size = size ;

	point->count = (int *)calloc(size, sizeof(int)) ;
	if (point->count == 0x0) {
		perror("point_new():point->count") ;
		exit(1) ;
	} ;

	return point ;
}

void
point_init(point_t * point, int size)
{
	point->state = EMPTY ;
	point->size = size ;

	point->count = (int *)calloc(size, sizeof(int)) ;
	if (point->count == 0x0) {
		perror("point_new():point->count") ;
		exit(1) ;
	} ;
}

void
point_delete (point_t * point)
{
	free(point->count) ;
	free(point) ;
}

int
point_sum (point_t * point)
{
	int sum = 0 ;
	for (int i = 0; i < point->size; i++)
		sum += point->count[i] ;
	
	return sum ;
}
