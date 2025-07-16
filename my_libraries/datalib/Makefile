include ../../variables.mk

NAME = libdatalib.a
SRCS = datalib.c imglib/imglib.c
OBJS = $(SRCS:%.c=%.o)

LOC_INC_PATHS = -I../../minilibx-linux -I. -I./imglib

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(LOC_INC_PATHS) -o $@

$(NAME) : $(OBJS)
	$(AR) $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean fclean all
