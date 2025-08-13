CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = librendering.a
AR = ar rcs

INCLUDES = -I../includes -Iincludes
HEADERS = ../includes/cub3rd.h includes/rendering.h

SRCS = src/draw.c src/raycasting.c src/render.c

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