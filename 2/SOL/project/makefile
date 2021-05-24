CC			= gcc
AR			= AR
CFLAGS		+= -std=c99 -Wall -Werror -g
INCDIR		= 
INCLUDES	= #-I. -I $(INCDIR)
LDFLAGS		= #-L.
OPTFLAGS	= #-03
LIBS		= -lpthread

TARGETS		= server client

.PHONY: all clean cleanall test1 test2 test3
.SUFFIXES: .c .h

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c -o $@ $<

all	: $(TARGETS)

server.o:	server.c

client.o:	client.c api.c

api.c:	api.h

clean		: 
	rm -f $(TARGETS)
cleanall	: clean
	\rm -f *.o *~
