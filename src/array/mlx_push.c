// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2023/5/8 by W2Wizard <main@w2wizard.dev>
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "internal.h"

void mlx_array_push(mlx_array_t* arr, const void* item)
{
	if (arr->size == arr->capacity)
		mlx_array_reserve(arr, arr->capacity * 2);
	memcpy((char*)arr->data + arr->type_size * arr->size, item, arr->type_size);
	arr->size++;
}
