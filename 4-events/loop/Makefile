include ../../variables.mk

NAME = rainbow

I_FLAGS = $(addprefix -I, $(LIBRARIES_PATHS))
L_FLAGS = $(addprefix -L, $(LIBRARIES_PATHS))

SRCS = $(NAME).c

OBJS = $(SRCS:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) $(I_FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(L_FLAGS) $(LIBS_NAME_FLAGS) -o $@

clean:
	$(RM) $(OBJS)

deepclean: clean
	$(MAKE) -C clean $(IMGLIB_DIR)
	$(MAKE) -C clean $(COLORS_DIR)
	$(MAKE) -C clean $(MLXLIB_DIR)

deepfclean: fclean
	$(MAKE) -C fclean $(IMGLIB_DIR)
	$(MAKE) -C fclean $(COLORS_DIR)
	$(MAKE) -C clean $(MLXLIB_DIR) # mlx's make haven't fclean rule 

fclean: clean
	$(RM) $(NAME)

re: fclean all

deepre: deepfclean all

.PHONY: clean fclean all deepclean deepfclean deepre
