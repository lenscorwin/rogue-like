#
# Makefile
# lsolofri, 2015-02-11 13:51
#

NAME = 		rogue-like
CC = 		g++
CFLAGS =	-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	xcodebuild -scheme ClientGame -project macosx/ClientGame.xcodeproj archive

clean:
	xcodebuild -scheme ClientGame -project macosx/ClientGame.xcodeproj clean

exec:
	open macosx/Published/My\ GameJam\ Game/My\ GameJam\ Game.app/

re: clean all

.PHONY: re fclean all

# vim:ft=make
#
