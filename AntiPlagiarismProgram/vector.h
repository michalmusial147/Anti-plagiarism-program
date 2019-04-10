#pragma once
struct array_t
{
	float *ptr;
	int size;
	int capacity;
};
int create_array(struct array_t **a, int N);
int create(struct array_t *a, int N);
int add(struct array_t *a, float value);
void destroy(struct array_t *a);
void destroy_array(struct array_t **a);

float dot_product(const struct array_t *a, const struct array_t *b);
float length(const struct array_t *a);

