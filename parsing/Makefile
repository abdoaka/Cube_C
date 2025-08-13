CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = parser

SRC = cube3d_parsing.c \
      getnextline/get_next_line.c \
      utils1.c \
	  utils2.c \
	  utils3.c \
	  utils4.c \
      helpers.c \
      map.c\
	  map_utils.c


OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Igetnextline -I.

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

