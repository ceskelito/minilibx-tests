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
IMGLIB_DIR		= $(ADDITIVE_LIBS)/imglib
COLORS_DIR		= $(ADDITIVE_LIBS)/colors
MLXLIBWRAPPER_DIR	= $(ADDITIVE_LIBS)/mlxlib
