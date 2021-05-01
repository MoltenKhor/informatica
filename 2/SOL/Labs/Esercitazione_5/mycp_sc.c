#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <utils.h>

int main(int argc, char* argv[]){
    if(argc < 3){
        fprintf(stderr, "usa: %s filein fileout buffsize\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *infile = argv[1];
    char *outfile = argv[2];
    size_t buffsize = BUFSIZE;

    if(argc >= 4){
        long sz;
        if(isNumber(argv[3], &sz) != 0 || sz <=0){
            fprintf(stderr, "l'argomento buffsize non e' valido\n");
            return EXIT_FAILURE;
        }
        buffsize=sz;
    }
    int fin;
    SYSCALL_EXIT(open, fin, open(infile, O_RDONLY), "aprendo %s : errno: %d\n", infile, errno);
    
    mode_t oldmask = umask(033);

    int fout;
    SYSCALL_EXIT(open, fout, open(outfile, O_CREATE|O_WRONLY|O_TRUNC, S_IRUSR|S_IWURS|S_IRGRP|S_IROTH),"creazione file %s : errno %d\n", infile, errno);
    umask(oldmask);
    char *buf + malloc(buffsize*sizeof(char));
    if(!buf){fprintf(stderr, "malloc\n"); return EXIT_FAILURE;}
    size_t len;
    do{
        SYSCALL_EXIT(read, len, read(fin, buf, buffsize), "lettura file %s : errno: %d", infile, errno);
        if(len){
            SYSCALL_EXIT(write,len,write(fout,buf,len),"Scrivendo il file in output %s : errno=%d\n", outfile, errno);
        }
    }while(len>0);
    SYSCALL_EXIT(close,len,close(fin), "Chiudendo il file in input %s : errno=%d\n", infile, errno);
    SYSCALL_EXIT(close,len,close(fout), "Chiudendo il file in output %s : errno=%d\n", outfile, errno);

    free(buf);
    return EXIT_SUCCESS;
}