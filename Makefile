# CC this specifies a compiler to be used
CC = gcc

# SRC this specifies .c files
SRC = src/main.c src/window.c src/raycaster.c src/SDL_subfunctions.c \
	src/colors.c src/angles.c src/color_arithmetic.c src/map.c \
	src/color_operations.c src/draw_all_things.c src/draw_to_screen.c \
	src/window_status.c

# OBJ this specifies .o files
OBJ = $(SRC:.c=.o)

# NAME this specifies a name for our exectuable
NAME = 'The Maze Project'

# RM this specifies programs to delete the files
RM = rm -f

# SDL2 will run the sdl2-config program with necessary flags
SDL2 := $$(sdl2-config --cflags --libs)

# CFLAGS this specifies favorite compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# LFLAGS this specifies linker flags
# LFLAGS =

# Makefile must work even if when there's files in the folder
# that have same name as the rule
.PHONY: all clean oclean fclean re

# This rule will build our executable
# Makefile must not compile if a header file main.h is missing
all: include/main.h $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(SDL2) -o $(NAME)

# This rule will delete all Emacs and the Vim temporary files with the executable
clean:
	$(RM) *~ $(NAME)

# This rule will delete object files
oclean:
	$(RM) $(OBJ)

# This rule will delete all Emacs and the Vim temporary files, executable, and object files
fclean: clean oclean

# This rule will force recompilation of every source files
re: fclean all
