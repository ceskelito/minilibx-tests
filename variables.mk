ROOT := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

# Common commands
CC		= gcc 
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f
MKDIR	= mkdir -p

# Libraries Directories
MY_LIBS_DIR	= $(ROOT)/my_libraries
MLXLIB_DIR	= $(ROOT)/minilibx-linux
IMGLIB_DIR	= $(MY_LIBS_DIR)/imglib
COLORS_DIR	= $(MY_LIBS_DIR)/imglib
