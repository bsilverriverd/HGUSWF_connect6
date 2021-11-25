#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "weight.h"

void
r_weight_increase (weight_t * weight, int h, int v, int i, int j, int depth)
{
	if (h < 0 || 19 <= h || v < 0 || 19 <= v)
		return ;
	
	if (depth == 6)
		return ;
	
	switch (weight->point[v][h].state) {
		case EMPTY :
			weight->point[v][h].count[i] += 1 ;
		case HOME :
			r_weight_increase (weight, h + weight->dh[j][i], v + weight->dv[j][i], i, j, depth + 1) ;
			break ;
		case AWAY :
		case RED :
		default :
			break ;
	}
	return ;
}

int
r_weight_decrease (weight_t * weight, int h, int v, int i, int j, int depth)
{
	if (h < 0 || 19 <= h || v < 0 || 19 <= v)
		return 0;
	
	if (depth == 7)
		return depth ;

	int ret = r_weight_decrease(weight, h + weight->dh[j][i], v + weight->dv[j][i], i, j, depth + 1) ;

	switch (weight->point[v][h].state) {
		case EMPTY : 
			weight->point[v][h].count[i] = ret < depth ? ret : depth ;
			break ; 
		case HOME :
			break ;	
		case AWAY :
		case RED :
		default :
			ret = 0 ;
			break ;
	}
	return ret ;
}

/*** header declared functions ***/
weight_t *
weight_new()
{
	weight_t * weight = (weight_t *)malloc(sizeof(weight_t)) ;

	if (weight == 0x0) {
		perror("weight_alloc()") ;
		exit(1) ;
	}

	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			point_init(&(weight->point[i][j]), 4) ;//weight->point[i][j] = point_new(4) ;

	weight->dh = (int **)malloc(sizeof(int *) * 2) ;
	if (weight->dh == 0x0) {
		perror("weight_new():weight->dh") ;
		exit(1) ;
	}
	for (int i = 0; i < 2; i++) {
		weight->dh[i] = (int *)malloc(sizeof(int) * 4) ;
		if (weight->dh[i] == 0x0) {
			perror("weight_new():weight->dh[i]") ;
			exit(1) ;
		}
	}
	weight->dh = (int **)malloc(sizeof(int *) * 2) ;
	if (weight->dh == 0x0) {
		perror("weight_new():weight->dh") ;
		exit(1) ;
	}
	for (int i = 0; i < 2; i++) {
		weight->dh[i] = (int *)malloc(sizeof(int) * 4) ;
		if (weight->dh[i] == 0x0) {
			perror("weight_new():weight->dh[i]") ;
			exit(1) ;
		}
	}
	int dh[2][4] = { { -1, 0, -1, 1 }, { 1, 0, 1, -1 } } ;
	int dv[2][4] = { { 0, -1, -1, -1 }, { 0, 1, 1, 1 } } ; 
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			weight->dh[i][j] = dh[i][j] ;
			weight->dv[i][j] = dv[i][j] ;
		}
	}
	
	weight->point = (point_t **)malloc(sizeof(point_t *) * 19) ;
	if(weight->point == 0x0) {
		perror("weight_new():weight->point") ;
		exit(1) ;
	}

	
	for (int i = 0; i < 19; i++) {
		weight->point[i] = (point_t *)malloc(sizeof(point_t) * 19) ;
		if (weight->point[i] == 0x0) {
			perror("weight_new():weight->point[i]") ;
			exit(1) ;
		}
	}

	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			point_init(&(weight->point[i][j]), 4) ;


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
	{
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
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			for (int k = 0; k < 4; k++) {
				weight->point[i][j].count[k] = initial_weight[k][i][j] ;
			}
			printf("\n") ;
		}
	}
	return weight ;
}

void
weight_delete (weight_t * weight)
{
	//for (int i = 0; i < 19; i++)
	//	for (int j = 0; j < 19; j++)
	//		point_delete(weight->point[i][j]) ;
	
	free(weight) ;
}

void
weight_increase (weight_t * weight, int h, int v)
{
	weight->point[v][h].state = HOME ;

	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 4; i++)
			r_weight_increase(weight, h + weight->dh[j][i], v + weight->dv[j][i], i, j, 1) ;
}

void
weight_decrease (STATE s, weight_t * weight, int h, int v)
{
	weight->point[v][h].state = s ;

	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 4; i++)
			r_weight_decrease(weight, h + weight->dh[j][i], v + weight->dv[j][i], i, j, 1) ;
}

int
weight_max (weight_t * weight, int * h, int  * v)
{
	int max = -1 ;
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (weight->point[i][j].state != EMPTY)
				continue ;

			int sum = point_sum(&(weight->point[i][j])) ;
			if (max < sum) {
				max = sum ;
				*h = j ;
				*v = i ;
			}
		}
	}
	return max ;
}
