// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2023/5/8 by W2Wizard <main@w2wizard.dev>
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "internal.h"

void mlx_array_reserve(mlx_array_t* arr, size_t capacity)
{
	if (capacity > arr->capacity)
	{
		arr->data = realloc(arr->data, arr->type_size * capacity);
		arr->capacity = capacity;
	}
}
