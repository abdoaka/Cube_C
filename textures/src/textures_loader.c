#include "../includes/textures.h"
#include <stdio.h>

int	load_all_textures(t_config *config, t_textures *textures)
{
	if (!load_single_texture(config->texture_no, &textures->north))
		return (0);
	if (!load_single_texture(config->texture_so, &textures->south))
		return (0);
	if (!load_single_texture(config->texture_ea, &textures->east))
		return (0);
	if (!load_single_texture(config->texture_we, &textures->west))
		return (0);
	printf("All textures loaded successfully!\n");
	return (1);
}

int	load_single_texture(char *path, xpm_t **texture)
{
	if (!path)
	{
		printf("Error: Texture path is NULL\n");
		return (0);
	}
	*texture = mlx_load_xpm42(path);
	if (!*texture)
	{
		printf("Error: Failed to load texture: %s\n", path);
		return (0);
	}
	printf("Loaded texture: %s (%dx%d)\n", path, 
		(*texture)->texture.width, (*texture)->texture.height);
	return (1);
}

void	free_all_textures(t_textures *textures)
{
	if (textures->north)
		mlx_delete_xpm42(textures->north);
	if (textures->south)
		mlx_delete_xpm42(textures->south);
	if (textures->east)
		mlx_delete_xpm42(textures->east);
	if (textures->west)
		mlx_delete_xpm42(textures->west);
}