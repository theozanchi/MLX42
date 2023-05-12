// -----------------------------------------------------------------------------
// See README in the root project for more information.
// Codam Coding College, Amsterdam @ 2023/5/8 by W2Wizard <main@w2wizard.dev>
// -----------------------------------------------------------------------------

#include "MLX42/internal.h"

mlx_array_t* mlx_array_create(size_t type_size)
{
	mlx_array_t* arr = malloc(sizeof(mlx_array_t));
	if (!arr)
		return NULL;
	if (!(arr->data = malloc(type_size * MLX_ARRAY__CAPACITY)))
	{
		free(arr);
		return NULL;
	}
	arr->size = 0;
	arr->capacity = MLX_ARRAY__CAPACITY;
	arr->type_size = type_size;
	return arr;
}
