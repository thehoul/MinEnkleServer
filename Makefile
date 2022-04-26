
OBJS = MinEnkleSever.o server/server.o server/server_handler.o
NAME = mes
RUBS = $(OBJS) *~ core \#*\#

mes : $(OBJS)
	gcc -I server/ -o $(NAME) $(OBJS)

clean: 
	-@$(RM) $(RUBS)
	-@$(RM) $(NAME)

MinEnkleSever.o: MinEnkleSever.c server/server.h server/server_handler.h
server.o: server/server.c server/server.h
server_handler.o: server/server_handler.c server/server_handler.h server/server.h