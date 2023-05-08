// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2023/5/8 by W2Wizard <main@w2wizard.dev>
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "internal.h"

mlx_array_t* mlx_array_create(size_t type_size)
{
	mlx_array_t* arr = malloc(sizeof(mlx_array_t));
	if (!arr)
		return NULL;
	if (!(arr->data = malloc(type_size * ARRAY_INITIAL_CAPACITY)))
	{
		free(arr);
		return NULL;
	}
	arr->capacity = ARRAY_INITIAL_CAPACITY;
	arr->size = 0;
	arr->type_size = type_size;
	return arr;
}
