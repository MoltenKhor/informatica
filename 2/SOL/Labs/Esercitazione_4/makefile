CC		=  gcc
CFLAGS	        += -std=c99 -Wall

SOURCES		= $(wildcard *.c)
TARGETS		= $(SOURCES:.c=)

.PHONY: all cleanall
.SUFFIXES: .c .h

all		: $(TARGETS)

clean		: 
	-rm -f $(TARGETS)