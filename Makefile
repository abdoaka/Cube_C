# Detect OS
UNAME := $(shell uname)

# 42 Norm requirements
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
NAME = cub3d

# OS-specific linking
ifeq ($(UNAME), Linux)
    MLX_FLAGS = -ldl -lglfw -pthread -lm
else ifeq ($(UNAME), Darwin)
    MLX_FLAGS = -lglfw -L/usr/local/lib
endif

# Source files
SRCS = src/main.c src/game/input.c src/game/movement.c src/game/camera.c \
       src/utils/cleanup.c src/utils/error.c src/utils/math_utils.c

OBJS = ${SRCS:.c=.o}

# Required rules
all: libmlx modules $(NAME)

$(NAME): $(OBJS) libmlx modules
	$(CC) $(OBJS) parsing/libparsing.a rendering/librendering.a \
	textures/libtextures.a mlx/build/libmlx42.a $(MLX_FLAGS) -o $(NAME)

modules:
	make -C parsing
	make -C rendering
	make -C textures

libmlx:
	cmake mlx -B mlx/build && make -C mlx/build -j4

clean:
	rm -f $(OBJS)
	make -C parsing clean
	make -C rendering clean
	make -C textures clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx modules