#
# Makefile
# lsolofri, 2015-02-11 13:51
#

NAME = 		rogue-like
CC = 		g++
CFLAGS =	-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	sw_vers
	xcodebuild -scheme ClientGame -project macosx/ClientGame.xcodeproj -configuration 'Release' -destination generic/platform='OS X' CONFIGURATION_BUILD_DIR='build'

clean:
	xcodebuild -scheme ClientGame -project macosx/ClientGame.xcodeproj -configuration 'Release' CONFIGURATION_BUILD_DIR='build' clean

exec:
	open macosx/build/ClientGame.app/

re: clean all

.PHONY: re fclean all

# vim:ft=make
#
