// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2021/12/27 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

/**
 * @file internal.h
 * @brief Internal header file for MLX42.
 * @details This file contains all the internal functions and variables
 * used by MLX42. This file is not meant to be included by the user but is meant
 * to be included by the MLX42 library itself.
 * @see MLX42.h
 */

#ifndef MLX42_INT_H
#define MLX42_INT_H
#define GETLINE_BUFF 1280
#define BPP			 sizeof(int32_t) /* Only support RGBA */
#define LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_NO_COMPILE_ALLOCATORS
#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#endif
#define MLX_SWAP_INTERVAL	   1
#define MLX_BATCH_SIZE		   12000
#define ARRAY_INITIAL_CAPACITY 8
#define MLX_ASSERT(cond, msg)  assert(cond&& msg);
#define MLX_NONNULL(var)	   MLX_ASSERT(var, "Value can't be null");
#include "KHR/khrplatform.h"
#include "MLX42/MLX42.h"
#include "glad/glad.h"
#include "lodepng/lodepng.h"
#include <GLFW/glfw3.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(__linux__)
#include <linux/limits.h>
#else
#include <limits.h>
#endif
#include <assert.h> /* assert, static_assert, ... */
#include <ctype.h>	/* isspace, isprint, ... */
#include <stdarg.h> /* va_arg, va_end, ... */
#include <string.h> /* strlen, memmove, ... */

// Global variables
// -----------------------------------------------------------------------------

/**
 * The shader code is extracted from the shader files and converted to a .c file
 * as a single string at compile time. This keeps shader files external but
 * still integrated into the program letting you use the executable anywhere
 * without having to take the shaders with you.
 *
 * Most modern frameworks like .NET do this by having resource files instead.
 *
 * @note Ideally in C23 you would be able to do this with #embed but that is
 * not supported here yet, then we can entirely remove this as well as the
 * shader files compile scripts in tools.
 */
extern const char *g_vert_shader, g_frag_shader;

// Settings array, use the enum 'key' to get the value.
extern int32_t g_settings[MLX_SETTINGS_MAX];

// Types
// -----------------------------------------------------------------------------

typedef struct
{
	float x;
	float y;
	float z;

	float u;
	float v;

	int8_t tex;
} vertex_t;

/**
 * There are two types of hooks, generic hooks and specialized hooks.
 *
 * Specialized: These hooks are used for a specific function and are used
 * to wrap the original function. These hooks are used to wrap GLFW functions
 * and are used to intercept GLFW events.
 *
 * Generic: These hooks are used for a specific function and are used
 * to wrap the original function. These hooks are to allow user code to be run
 * during the main loop of the program.
 */
typedef struct mlx_hook
{
	void* param;
	void (*func)(void*);
} mlx_hook_t;

// Define to make it easier to declare hooks.
#define DECLARE_GLFW_WRAP_HOOK(name, func)                                     \
	typedef struct                                                             \
	{                                                                          \
		void* param;                                                           \
		func* orig;                                                            \
	} name##_t;

DECLARE_GLFW_WRAP_HOOK(mlx_scroll, mlx_scrollfunc);
DECLARE_GLFW_WRAP_HOOK(mlx_mouse, mlx_mousefunc);
DECLARE_GLFW_WRAP_HOOK(mlx_cursor, mlx_cursorfunc);
DECLARE_GLFW_WRAP_HOOK(mlx_close, mlx_closefunc);
DECLARE_GLFW_WRAP_HOOK(mlx_resize, mlx_resizefunc);
DECLARE_GLFW_WRAP_HOOK(mlx_key, mlx_keyfunc);
#undef DECLARE_GLFW_WRAP_HOOK

/** @brief Storage data type for storing data in a dynamic array. */
typedef struct
{
	void* data;
	size_t capacity;
	size_t size;
	size_t type_size;
} mlx_array_t;

/**
 * @brief The window context, there can be multiple window contexts
 * at a time. Each window shares the same opengl context.
 */
typedef struct
{
	GLFWwindow* window;
	uint32_t initial_width;
	uint32_t initial_height;

	mlx_array_t* hooks;
	mlx_array_t* images;
	mlx_array_t* render_queue;

	mlx_scroll_t scroll_hook;
	mlx_mouse_t mouse_hook;
	mlx_cursor_t cursor_hook;
	mlx_key_t key_hook;
	mlx_resize_t resize_hook;
	mlx_close_t close_hook;
} mlx_window_ctx_t;

/**
 * @brief The opengl context, there should only ever be one context
 * at a time that is shared amongst all windows.
 */
typedef struct
{
	GLuint vao;
	GLuint vbo;
	GLuint shader;

	int32_t zdepth;
	int32_t bound_textures[16];
	int32_t batch_size;
	vertex_t batch_vertices[MLX_BATCH_SIZE];
} mlx_opengl_ctx_t;

/**
 * @brief A window's universal render queue, all images instances that are
 * drawn to a window are stored in this queue.
 */
typedef struct
{
	mlx_image_t* image;
	int32_t instanceid;
} mlx_drawcall_t;

/**
 * @brief The image context, stores the image's texture and the capacity
 * of the image's instances. Technicaly useless but i
 */
typedef struct mlx_image_ctx
{
	GLuint texture;
	size_t instances_capacity;
} mlx_image_ctx_t;

// Functions
//-----------------------------------------------------------------------------

void mlx_array_reserve(mlx_array_t* arr, size_t capacity);
mlx_array_t* mlx_array_create(size_t type_size);
void mlx_array_destroy(mlx_array_t* arr);
void mlx_array_push(mlx_array_t* arr, const void* item);
void* mlx_array_at(mlx_array_t* arr, size_t index);

bool mlx_error(mlx_errno_t val);
bool mlx_freen(int32_t count, ...);

bool mlx_getline(char** out, size_t* out_size, FILE* file);
uint32_t mlx_rgba_to_mono(uint32_t color);
int32_t mlx_atoi_base(const char* str, int32_t base);
uint64_t mlx_fnv_hash(char* str, size_t len);

#endif
