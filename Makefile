TARGET = mes

CC = gcc
CFLAGS = -g

DIROBJ = ./obj
SUBDIR = server server/util cribbage cribbage/controller cribbage/util


INCS = $(wildcard *.h $(foreach fd, $(SUBDIR), $(fd)/*.h))
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIR), $(fd)/*.c))
OBJS = $(SRCS:c=o)

RUBS = $(OBJS) *~ core \#*\#
LIBS = -lmagic

.PHONY: clean echoes

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

clean: 
	-@$(RM) $(RUBS)
	-@$(RM) $(NAME)

print: $(OBJS)
	@echo $?