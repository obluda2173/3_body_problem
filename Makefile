NAME	=	tbp

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -std=c++14 -DGL_SILENCE_DEPRECATION -I3_body_problem/eigen

SRC		=	src/circle/circle.cpp src/physics/rk4_tbp.cpp src/tbp/tbp.cpp
HEADER	=	src/circle/circle.hpp src/physics/rk4_tbp.hpp src/tbp/tbp.hpp
LIBS	=	glfw/lib-arm64/libglfw3.a
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re