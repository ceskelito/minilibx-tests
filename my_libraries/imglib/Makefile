NAME = libimglib.a
SOURCE = imglib.c
OBJ = imglib.o

INC_PATHS = -I../minilibx-linux

CC = gcc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = -rcs

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(INC_PATHS) -o $@

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $@ $^ 
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
