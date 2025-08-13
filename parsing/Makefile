CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libparsing.a
AR = ar rcs

INCLUDES = -I../includes -Iincludes
HEADERS = ../includes/cub3rd.h includes/parsing.h

SRCS = src/parse_colors.c src/parse_file.c src/parse_map.c \
       src/parse_textures.c src/parse_utils.c

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