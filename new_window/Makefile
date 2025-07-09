NAME = new_window
SOURCE = $(NAME).c
OBJ = $(NAME).o
CC = gcc
# CFLAS = -Wall -Wextra -Werror

all:$(NAME)

%.o:%.c
	$(CC) -c $< -o $@

# If the libraries was not added in /usr/local/lib, we must prefix -Lpath/to/lib
$(NAME):$(OBJ)
	$(CC) $^ -lmlx_Linux -lXext -lX11 -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
