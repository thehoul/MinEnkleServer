
OBJS = MinEnkleSever.o server/server.o server/server_handler.o \
 server/util/request_parser.o server/util/helpers.o cribbage/cribbage.o cribbage/card.o cribbage/board.o
NAME = mes
RUBS = $(OBJS) *~ core \#*\#
SUB_DIR = server/ server/util
LIBS = -lmagic
mes : $(OBJS)
	gcc -o $(NAME) $(OBJS) $(LIBS)

clean: 
	-@$(RM) $(RUBS)
	-@$(RM) $(NAME)

MinEnkleSever.o: MinEnkleSever.c server/server.h server/server_handler.h \
 server/server.h server/util/request_parser.h
server.o: server/server.c server/server.h
server_handler.o: server/server_handler.c server/server_handler.h server/server.h \
 server/util/request_parser.h server/util/helpers.h cribbage/cribbage.h
request_parser.o: server/util/request_parser.c server/util/request_parser.h
helpers.o: server/util/helpers.c server/util/helpers.h server/util/request_parser.h
card.o: cribbage/card.c cribbage/card.h
cribbage.o: cribbage/cribbage.c cribbage/cribbage.h cribbage/board.h
board.o : cribbage/board.c cribbage/board.h cribbage/card.h