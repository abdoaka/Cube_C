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

# Source files and headers
SRCS = src/main.c src/game/input.c src/game/movement.c src/game/camera.c \
       src/utils/cleanup.c src/utils/error.c src/utils/math_utils.c

OBJS = ${SRCS:.c=.o}
HEADERS = includes/cub3rd.h

# Library files
MLX_LIB = mlx/build/libmlx42.a
PARSING_LIB = parsing/libparsing.a
RENDERING_LIB = rendering/librendering.a
TEXTURES_LIB = textures/libtextures.a

# Main rule
all: $(NAME)

# Link everything - only when dependencies change
$(NAME): $(OBJS) $(MLX_LIB) $(PARSING_LIB) $(RENDERING_LIB) $(TEXTURES_LIB)
	$(CC) $(OBJS) $(PARSING_LIB) $(RENDERING_LIB) \
	$(TEXTURES_LIB) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

# Object files with header dependencies
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libraries only when needed
$(PARSING_LIB): parsing/src/*.c parsing/includes/*.h $(HEADERS)
	make -C parsing

$(RENDERING_LIB): rendering/src/*.c rendering/includes/*.h $(HEADERS)
	make -C rendering

$(TEXTURES_LIB): textures/src/*.c textures/includes/*.h $(HEADERS)
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