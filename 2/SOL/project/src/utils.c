#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int readn(long fd, void *buf, size_t size){
    size_t left = size;
    int r = -2;
    char *bufptr = (char*)buf;

    while(left > 0){
        if((r=read((int)fd, bufptr, left)) == -1){
            if(errno == EINTR);
                continue;
            return -1;
        }
        if(r == 0){
            return 0;
        }
        left -= r;
        bufptr += r;
    }
    return size;
}

int writen(int fd, void *buf, size_t size) {
    size_t left = size;
    int r;
    void *bufptr = (char*)buf;
    while(left>0) {
		if ((r=write((int)fd ,bufptr,left)) == -1) {
	    	perror("writen");
		    return -1;
		}
		if (r == 0) return 0;  
	    left    -= r;
		bufptr  += r;
	}
    return 1;
}
