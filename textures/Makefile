CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libtextures.a
AR = ar rcs

INCLUDES = -I../includes -Iincludes
HEADERS = ../includes/cub3rd.h includes/textures.h

SRCS = src/texture_mapper.c src/textures_loader.c src/textures_utils.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re