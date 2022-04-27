TARGET = mes

CC = gcc
CFLAGS = -g

DIROBJ = ./obj
SUBDIR = server server/util cribbage cribbage/controller


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


#MinEnkleSever.o: MinEnkleSever.c server/server.h server/server_handler.h \
 server/server.h server/util/request_parser.h
#server.o: server/server.c server/server.h
#server_handler.o: server/server_handler.c server/server_handler.h server/server.h \
 server/util/request_parser.h server/util/helpers.h cribbage/controller/controller.h
#request_parser.o: server/util/request_parser.c server/util/request_parser.h
#helpers.o: server/util/helpers.c server/util/helpers.h server/util/request_parser.h
#card.o: cribbage/card.c cribbage/card.h
#cribbage.o: cribbage/cribbage.c cribbage/cribbage.h cribbage/board.h
#board.o : cribbage/board.c cribbage/board.h cribbage/card.h
#controller.o : cribbage/controller/controller.c cribbage/controller/controller.o