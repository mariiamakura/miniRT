/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 01:02:24 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/03/09 11:03:47 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(texture);

	mlx_image_t* image = mlx_new_image(mlx, texture->width, texture->height);
	if (image == NULL)
		return (NULL);

	uint8_t* pixelx;
	uint8_t* pixeli;
	for (uint32_t i = 0; i < texture->height; i++)
	{
		pixelx = &texture->pixels[(i * texture->width) * texture->bytes_per_pixel];
		pixeli = &image->pixels[(i * image->width) * texture->bytes_per_pixel];
		memmove(pixeli, pixelx, texture->width * texture->bytes_per_pixel);
	}
	return (image);
}

bool mlx_draw_texture(mlx_image_t* image, mlx_texture_t* texture, uint32_t x, uint32_t y)
{
    MLX_NONNULL(image);
    MLX_NONNULL(texture);

    if (texture->width > image->width || texture->height > image->height)
        return (mlx_error(MLX_INVDIM));
    if (x > image->width || y > image->height)
        return (mlx_error(MLX_INVPOS));

    uint8_t* pixelx;
    uint8_t* pixeli;
    for (uint32_t i = 0; i < texture->height; i++)
    {
        pixelx = &texture->pixels[(i * texture->width) * texture->bytes_per_pixel];
        pixeli = &image->pixels[((i + y) * image->width + x) * texture->bytes_per_pixel];
        memmove(pixeli, pixelx, texture->width * texture->bytes_per_pixel);
    }
    return (true);
}

void mlx_delete_texture(mlx_texture_t* texture)
{
	MLX_NONNULL(texture);

	mlx_freen(2, texture->pixels, texture);
}
