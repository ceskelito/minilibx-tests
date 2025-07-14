include ../variables.mk

NAME = close_on_esc

INC_PATHS = -I$(MLXLIB_DIR) -I$(IMGLIB_DIR) -I$(COLORS_DIR)
LIB_PATHS = -L$(MLXLIB_DIR) -L$(IMGLIB_DIR) -L$(COLORS_DIR)
LIBRARIES = -lmlx_Linux -lXext -lX11 -limglib -lcolors

SRCS = close_on_esc.c

OBJS =  $(SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC_PATHS) -o $@

$(NAME): $(OBJS) mlxlib
	$(CC) $(CFLAGS) $(OBJS) $(LIB_PATHS) $(LIBRARIES) -o $@

mlxlib:
	$(MAKE) -C $(MLXLIB_DIR)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

deepclean: clean
	$(MAKE) clean -C $(MLXLIB_DIR)

deepfclean: fclean
	$(MAKE) clean -C $(MLXLIB_DIR) # mlx makefile haven't fclean rule

re: fclean all

.PHONY: all clean fclean re mlxlib deepclean deepfclean

