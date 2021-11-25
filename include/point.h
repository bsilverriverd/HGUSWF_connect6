#ifndef POINT_H
#define POINT_H

typedef enum {
	HOME,
	AWAY,
	RED,
	EMPTY,
} STATE ; 

typedef struct _point {
	STATE state ;
	int size ;
	int * count ;
} point_t ;

point_t *
point_new (int size) ;

void
point_delete (point_t * point) ;

int
point_sum (point_t * point) ;

void
point_init (point_t * point, int size) ;

#endif
