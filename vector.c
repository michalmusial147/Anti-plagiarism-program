
//////////////////////////////////////////////////////////////////////////////////////

							// WEK			TORY //
//create, add, destroy, destroy_array, create_array, dot_product, length(dla tablic / wektorów).
//////////////////////////////////////////////////////////////////////////////////////
#include "vector.h"
#include  <stdlib.h>
#include  <stdio.h>
#include  <math.h>
int create(struct array_t *a, int N)
{
	if (a == NULL || N <= 0)
		return 1;
	a->ptr = (float*)malloc(sizeof(float)*N);
	if (a->ptr == NULL)
		return 2;
	a->size = 0;
	a->capacity = N;
	return 0;
}
int add(struct array_t *a, float value)
{
	if (a == NULL) 
		return 1;
	if (a->ptr == NULL)
		return 1;
	if (a->capacity <= 0 || a->size < 0)
		return 1;
	if (a->capacity == a->size) 
		return 2;
	*(a->ptr + a->size) = value;
	a->size++;
	return 0;
}
int create_array(struct array_t **a, int N)
{
	if (a == NULL)
		return 1;
	if (N <= 0)
		return 1;
	*a = (struct array_t*)malloc(sizeof(struct array_t));
	if (*a == NULL)
		return 2;
	(*a)->ptr = (float*)malloc(sizeof(float)*N);
	if ((*a)->ptr == NULL) 
	{
		free(*a);
		return 2;
	}
	(*a)->size = 0;
	(*a)->capacity = N;
	return 0;
}
void destroy(struct array_t *a)
{
	if(a!=NULL)
		if(a->ptr!=NULL)
			free(a->ptr);
	
	return;
}
void destroy_array(struct array_t **a)
{
	if (a == NULL)
		return;
	if (*a == NULL)
		return;
	free((*a)->ptr);
	free(*a);
	return;
}

float dot_product(const struct array_t *a, const struct array_t *b)
{
	if (a == NULL)
		return -1;
	if (a->ptr == NULL)
		return -1;
	if (b == NULL)
		return -1;
	if (b->ptr == NULL)
		return -1;
	if (a->size <= 0 || a->capacity <= 0)
		return -1;
	if (a->size > a->capacity)
		return -1;
	if (b->size > b->capacity)
		return -1;

	float sum = 0;
	for (int i = 0; i < a->size; i++)
	{
		sum += (*(a->ptr + i)) * (*(b->ptr + i));
	}
	return sum;
}
float length(const struct array_t *a)
{
	if (a == NULL)
		return -1;
	if (a->ptr == NULL)
		return -1;
	if (a->size <=0 ||  a->capacity<= 0)
		return -1;
	if (a->size > a->capacity)
		return -1;
	float sum = 0;
	for (int i = 0; i < a->size; i++)
	{
		sum += pow(*(a->ptr + i), 2);
	}
	return sqrt(sum);
}

