NAME = putsquare
SOURCE = $(NAME).c
OBJ = $(NAME).o

LIBDIR = ../imglib

INC_PATHS = -I../minilibx_linux -I$(LIBDIR)
LIB_PATHS = -L../minilibx_linux -L$(LIBDIR)
LIBRARIES = -lmlx_Linux -lXext -lX11 -limglib

CFLAGS = -Wall -Wextra -Werror
CC = gcc

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(INC_PATHS) -o $@

$(NAME) : $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_PATHS) $(LIBRARIES) -o $@

$(LIB) :
	make -C $(LIBDIR)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
