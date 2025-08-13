#include <stdio.h>
#include <stdlib.h>
#include "../mlx/include/MLX42/MLX42.h"

#define WIDTH 800
#define HEIGHT 600

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	main(void)
{
	mlx_t	*mlx;

	// Initialize MLX42
	mlx = mlx_init(WIDTH, HEIGHT, "Cub3D - MLX42 Test", true);
	if (!mlx)
		ft_error();
	
	printf("MLX42 initialized successfully!\n");
	printf("Window size: %dx%d\n", WIDTH, HEIGHT);
	printf("Press ESC or close window to exit\n");
	
	// Start the window loop
	mlx_loop(mlx);
	
	// Cleanup
	mlx_terminate(mlx);
	return (0);
}