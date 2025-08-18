CC = cc
CFLAGS = -Wall -Wextra -Werror -Igetnextline -I.
NAME = libparsing.a
AR = ar rcs

# Remove main.c
SRC = getnextline/get_next_line.c \
      utils1.c utils2.c utils3.c utils4.c \
      helpers.c map.c map_utils.c \
      parse_file.c parse_config.c player_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re