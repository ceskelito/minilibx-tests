NAME = pixel_put
SOURCE = $(NAME).c
OBJ = $(NAME).o
CC = gcc
INC_PATH = -I../minilibx_linux
LIB_PATH = -L../minilibx_linux
LIBRARIES = -lmlx_Linux -lXext -lX11
# CFLAS = -Wall -Wextra -Werror

all:$(NAME)

%.o:%.c
	$(CC) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $^ $(INC_PATH) $(LIB_PATH) $(LIBRARIES) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
