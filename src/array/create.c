// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2023/5/8 by W2Wizard.
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

mlx_array_t* mlx_array_create(size_t type_size)
{
	mlx_array_t* arr = malloc(sizeof(mlx_array_t));
	arr->data = malloc(type_size * ARRAY_INITIAL_CAPACITY);
	arr->capacity = ARRAY_INITIAL_CAPACITY;
	arr->size = 0;
	arr->type_size = type_size;
	return arr;
}

void mlx_array_destroy(mlx_array_t* arr)
{
	free(arr->data);
	free(arr);
}

void mlx_array_push(mlx_array_t* arr, const void* item)
{
	if (arr->size == arr->capacity)
		mlx_array_reserve(arr, arr->capacity * 2);
	memcpy((char*)arr->data + arr->type_size * arr->size, item, arr->type_size);
	arr->size++;
}

void* mlx_array_at(mlx_array_t* arr, size_t index)
{
	assert(index < arr->size && "Index out of bounds");
	return (char*)arr->data + arr->type_size * index;
}
