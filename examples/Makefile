include ../variables.mk

NAME = comprehensive_example

SOURCES = comprehensive_example.c
OBJECTS = $(SOURCES:.c=.o)

# Libraries
MLXLIBWRAPPER_LIB = $(MLXLIBWRAPPER_DIR)/libmlxlib.a
COLORS_LIB = $(COLORS_DIR)/libcolors.a
IMGLIB_LIB = $(IMGLIB_DIR)/libimglib.a

LIBS = $(MLXLIBWRAPPER_LIB) $(COLORS_LIB) $(IMGLIB_LIB)
INC_PATHS = -I$(MLXLIB_DIR) -I$(COLORS_DIR) -I$(IMGLIB_DIR) -I$(MLXLIBWRAPPER_DIR)

# Note: In a real environment, we'd link against actual MLX library
# LDFLAGS = -lmlx -lXext -lX11 -lm

all: build_libs $(NAME)

build_libs:
	@echo "Building dependencies..."
	@$(MAKE) -C $(COLORS_DIR)
	@$(MAKE) -C $(IMGLIB_DIR)
	@$(MAKE) -C $(MLXLIBWRAPPER_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC_PATHS) -o $@

$(NAME): $(OBJECTS) $(LIBS)
	@echo "Note: This example would normally link against MLX library"
	@echo "Compilation successful - objects created: $(OBJECTS)"
	@echo "Libraries used: $(LIBS)"
	@echo "In a real environment, run:"
	@echo "$(CC) $(OBJECTS) $(LIBS) -lmlx -lXext -lX11 -lm -o $(NAME)"

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(COLORS_DIR) fclean
	@$(MAKE) -C $(IMGLIB_DIR) fclean
	@$(MAKE) -C $(MLXLIBWRAPPER_DIR) fclean

re: fclean all

.PHONY: clean fclean all re build_libs