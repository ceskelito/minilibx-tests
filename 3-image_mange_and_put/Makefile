include ../variables.mk

NAME = image_put
SOURCE = $(NAME).c
OBJ = $(NAME).o

INC_PATH = -I$(MLXLIB_DIR)
LIB_PATH = -L$(MLXLIB_DIR)
LIBRARIES = -lmlx_Linux -lXext -lX11
# CFLAS = -Wall -Wextra -Werror

all:$(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< $(INC_PATH) -o $@

$(NAME):$(OBJ)
	$(CC) $^ $(INC_PATH) $(LIB_PATH) $(LIBRARIES) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
