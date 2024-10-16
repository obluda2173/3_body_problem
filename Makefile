NAME    = tbp

CC      = gcc

CFLAGS  = -Wall -Wextra -Werror

SRC     = src/tbp.c
HEADER  = src/tbp.h
OBJ     = $(SRC:.c=.o)
DBASE   = tbp.csv

SDL2_FLAGS = `sdl2-config --cflags --libs`

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(SDL2_FLAGS)

%.o: src/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(DBASE)

fclean: clean
	rm -f $(NAME) $(DBASE)

re: fclean all

.PHONY: all clean fclean re