# Detect OS
UNAME := $(shell uname)

# 42 Norm requirements
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I./parsing
NAME = cub3D

# OS-specific linking
ifeq ($(UNAME), Linux)
    MLX_FLAGS = -ldl -lglfw -pthread -lm
else ifeq ($(UNAME), Darwin)
    MLX_FLAGS = -L/goinfre/absaadan/homebrew/opt/glfw/lib -lglfw
endif

# Source files and headers
SRCS = src/main.c src/game/input.c src/game/init.c src/game/movement.c src/game/camera.c \
    	src/utils/math_utils.c

OBJS = ${SRCS:.c=.o}
HEADERS = includes/cub3rd.h

# Library files
MLX_LIB = mlx/build/libmlx42.a
PARSING_LIB = parsing/libparsing.a
RENDERING_LIB = rendering/librendering.a
TEXTURES_LIB = textures/libtextures.a

# Main rule
all: $(NAME)

# Link everything
$(NAME): $(OBJS) $(MLX_LIB) $(PARSING_LIB) $(RENDERING_LIB) $(TEXTURES_LIB)
	$(CC) $(OBJS) $(PARSING_LIB) $(RENDERING_LIB) \
	$(TEXTURES_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

# Object files with header dependencies
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libraries - no file dependencies, just force rebuild when called
$(PARSING_LIB):
	make -C parsing

$(RENDERING_LIB):
	make -C rendering

$(TEXTURES_LIB):
	make -C textures

# Build MLX42 only if not exists
$(MLX_LIB):
	cmake mlx -B mlx/build && make -C mlx/build -j4

clean:
	rm -f $(OBJS)
	make -C parsing clean
	make -C rendering clean
	make -C textures clean

fclean: clean
	rm -f $(NAME)
	make -C parsing fclean
	make -C rendering fclean
	make -C textures fclean
	rm -rf mlx/build

re: fclean all

.PHONY: all clean fclean re
