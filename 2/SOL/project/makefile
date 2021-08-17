CC			= gcc
AR			= ar
ARFLAGS		= rvs
CFLAGS		+= -std=c99 -Wall -Werror -g
INCDIR		= ./utils/includes -I ./threadpool
INCLUDES	= -I. -I $(INCDIR)
LDFLAGS		= -L.
OPTFLAGS	= #-03
LIBS		= -lpthread

TARGETS		= client server

.PHONY: all clean cleanall test1 test2 test3
.SUFFIXES: .c .h

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c -o $@ $<

all	: $(TARGETS)

server: server.o threadF.o memory.o libPool.a
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

libPool.a: ./threadpool/threadpool.o ./threadpool/threadpool.h
	$(AR) $(ARFLAGS) $@ $<

server.o:	server.c 

client:		client.o api.o

client.o:	client.c

threadF.o:	threadF.c 

./threadpool/threadpool.o: ./threadpool/threadpool.c

api.o: api.c

api.c:	api.h

memory.o: memory.c


clean		: 
	rm -f $(TARGETS)
cleanall	: clean
	\rm -f *.o *~ *.a ./threadpool/*.o threadpool/*~
