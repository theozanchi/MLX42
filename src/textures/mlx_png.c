// -----------------------------------------------------------------------------
// See README in the root project for more information.
// Codam Coding College, Amsterdam @ 2022/02/16 by W2Wizard <main@w2wizard.dev>
// -----------------------------------------------------------------------------

#include "MLX42/internal.h"

//= Public =//

mlx_texture_t* mlx_load_png(const char* path)
{
	MLX_NONNULL(path);

	mlx_texture_t* image;
	if (!(image = malloc(sizeof(mlx_texture_t))))
		return ((void*)mlx_error(MLX_MEMFAIL));

	uint32_t error;
	image->bytes_per_pixel = BPP;
	if ((error = lodepng_decode32_file(&image->pixels, &image->width, &image->height, path)))
	{
		free(image);
		// Explicitly print error on purpose
		fprintf(stderr, "MLX42: LodePNG: %s\n", lodepng_error_text(error));
		return ((void*)mlx_error(MLX_INVPNG));
	}
	return (image);
}
