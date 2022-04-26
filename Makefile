
OBJS = MinEnkleSever.o server/server.o server/server_handler.o server/util/request_parser.o
NAME = mes
RUBS = $(OBJS) *~ core \#*\#
SUB_DIR = server/ server/util
mes : $(OBJS)
	gcc -o $(NAME) $(OBJS)

clean: 
	-@$(RM) $(RUBS)
	-@$(RM) $(NAME)

MinEnkleSever.o: MinEnkleSever.c server/server.h server/server_handler.h \
 server/server.h server/util/request_parser.h
server.o: server/server.c server/server.h
server_handler.o: server/server_handler.c server/server_handler.h server/server.h \
 util/request_parser.h
request_parser.o: server/util/request_parser.c server/util/request_parser.h