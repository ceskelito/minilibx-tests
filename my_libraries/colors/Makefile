include ../../variables.mk

NAME = libcolors.a

OBJ = colors.o

INC_PATHS = -I$(MLXLIB_DIR)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(INC_PATHS) -o $@

$(NAME) : $(OBJ)
	$(AR) $@ $^ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
