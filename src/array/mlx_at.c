// -----------------------------------------------------------------------------
// See README in the root project for more information.
// Codam Coding College, Amsterdam @ 2023/5/8 by W2Wizard <main@w2wizard.dev>
// -----------------------------------------------------------------------------

#include "MLX42/internal.h"

void* mlx_array_at(mlx_array_t* arr, size_t index)
{
	MLX_NONNULL(arr);
	MLX_ASSERT(index < arr->size && "Index out of bounds");
	return (char*)arr->data + arr->type_size * index;
}
