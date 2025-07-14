include ../../variables.mk

NAME = libmlxlib.a

SOURCES = mlxlib_core.c mlxlib_events.c mlxlib_colors.c mlxlib_drawing.c
OBJECTS = $(SOURCES:.c=.o)

INC_PATHS = -I$(MLXLIB_DIR) -I$(COLORS_DIR) -I$(IMGLIB_DIR)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC_PATHS) -o $@

$(NAME): $(OBJECTS)
	$(AR) $@ $^

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re