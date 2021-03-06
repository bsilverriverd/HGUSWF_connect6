//#ifndef WEIGHT_H
//#define WEIGHT_H

#include "point.h"

typedef struct _weight {
	point_t ** point ;
	int ** dh ;
	int ** dv ;
} weight_t ;

weight_t *
weight_new() ;

void
weight_delete (weight_t * weight) ;

void
weight_increase (weight_t * weight, int h, int v) ;

void
weight_decrease (STATE s, weight_t * weight, int h, int v) ;

int
weight_max (weight_t * weight, int * h, int  * v) ;

int
weight_get_sum_at (weight_t * weight, int h, int v) ;
/*
int initial_weight[4][19][19] = {
	{
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 }
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 },
		{ 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 },
		{ 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
		{ 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0 },
		{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0 },
		{ 1,2,3,3,3,3,3,3,3,3,3,3,3,3,2,1,0,0,0 },
		{ 1,2,3,4,4,4,4,4,4,4,4,4,4,4,3,2,1,0,0 },
		{ 1,2,3,4,5,5,5,5,5,5,5,5,5,5,4,3,2,1,0 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 0,1,2,3,4,5,5,5,5,5,5,5,5,5,5,4,3,2,1 },
		{ 0,0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,3,2,1 },
		{ 0,0,0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,2,1 },
		{ 0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{ 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	},
		{ 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1 },
		{ 0,0,0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,2,1 },
		{ 0,0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,3,2,1 },
		{ 0,1,2,3,4,5,5,5,5,5,5,5,5,5,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,6,6,6,6,6,6,6,6,6,5,4,3,2,1 },
		{ 1,2,3,4,5,5,5,5,5,5,5,5,5,5,4,3,2,1,0 },
		{ 1,2,3,4,4,4,4,4,4,4,4,4,4,4,3,2,1,0,0 },
		{ 1,2,3,3,3,3,3,3,3,3,3,3,3,3,2,1,0,0,0 },
		{ 1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0 }
	}
} ;
*/
//#endif
