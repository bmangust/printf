
.PHONY: all clean fclean re

NAME = print

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = main.c

OBJ = $(SRC:.c=.o)

LIB = -L. -lftprintf

INC = -I ./inc

MAKELIB = Makefile_lib

all: $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIB) $(INC) -o $(NAME)

$(OBJ): lib
	$(CC) $(FLAGS) -o $@ -c $(SRC) $(LIB) $(INC)

lib:
	make -f $(MAKELIB)

clean:
	rm $(OBJ)

fclean: make clean -f $(MAKELIB)
	rm $(NAME)

re: fclean all