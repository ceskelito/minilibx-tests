include ../variables.mk

NAME = putshape
SOURCE = $(NAME).c
OBJ = $(NAME).o

INC_PATHS = -I$(MLXLIB_DIR) -I$(IMGLIB_DIR)
LIB_PATHS = -L$(MLXLIB_DIR) -L$(IMGLIB_DIR)
LIBRARIES = -limglib -lmlx_Linux -lXext -lX11 -lm

CFLAGS = -Wall -Wextra -Werror
CC = gcc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC_PATHS) -o $@

$(NAME): $(OBJ) imglib mlxlib
	$(CC) $(CFLAGS) $(OBJ) $(LIB_PATHS) $(LIBRARIES) -o $@

mlxlib: 
	make -C $(MLXLIB_DIR)

imglib:
	make -C $(IMGLIB_DIR)

clean:
	rm -f $(OBJ)

deeclean: clean
	make clean -C $(IMGLIB_DIR)
	make clean -C $(MLXLIB_DIR)

fclean: clean
	rm -f $(NAME)

deepfclean: fclean
	make fclean -C $(IMGLIB_DIR)
	make clean -C $(MLXLIB_DIR) # The mlx makefile haven't the fclean rule

re : all clean fclean deepclean deepfclean imglib mlxlib
