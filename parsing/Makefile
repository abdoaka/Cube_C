CC = cc
CFLAGS = -Wall -Wextra -Werror -Igetnextline -I.
NAME = libparsing.a           # Changed to library
AR = ar rcs                   # Added archiver

SRC = cube3d_parsing.c \
	getnextline/get_next_line.c \
	getnextline/get_next_line_utils.c \
	utils1.c utils2.c utils3.c utils4.c \
	helpers.c map.c map_utils.c

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