ROOT			:= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
ADDITIVE_LIBS	:= $(ROOT)/my_libraries

# Common Commands
CC		= gcc
AR		= ar rcs
RM		= rm -f
MKDIR	= mkdir -p
CFLAGS	= -Wall -Wextra -Werror

# Libraries Directories
MLXLIB_DIR		= $(ROOT)/minilibx-linux
IMGLIB_DIR		= $(ADDITIVE_LIBS)/imglib # DEPRECATED -- use DATALIB instead
COLORS_DIR		= $(ADDITIVE_LIBS)/colors
DATALIB_DIR		= $(ADDITIVE_LIBS)/datalib

# Common Inclusion and Libraries directories

LIBRARIES_PATHS	= $(MLXLIB_DIR) $(IMGLIB_DIR) $(COLORS_DIR) $(DATALIB_DIR)
LIBS_NAME_FLAGS	= -lcolors -ldatalib -lmlx_Linux -lXext -lX11 

