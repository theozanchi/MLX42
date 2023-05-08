// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2023/5/8 by W2Wizard <main@w2wizard.dev>
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "internal.h"

void mlx_array_destroy(mlx_array_t* arr)
{
	mlx_freen(2, arr->data, arr);
}
