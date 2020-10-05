#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

#define DEFAULT_MAX_LINE 2048

extern int optind;

int wcount(const char buf[]){
    char *p = (char*)&buf[0];
    int count=0, flag=0;
    while(*p != '\0' && (iscntrl(*p) || isspace(*p))) ++p;
    while(*p != '\0') { 
	if (isspace(*p)) {  // se ho uno spazio e se il carattere precedente 
	                    // non e' ne uno spazio ne un carattere di controllo....
	    if ( !isspace(*(p-1)) && !iscntrl(*(p-1)) ) { 
		++count;
		flag = 0;
	    }
	} else flag=1;  // ho iniziato una nuova parola
	++p;
    }
    return (flag) ? count+1:count;
}

int main(int argc, char* argv[]){
    if(argc==1){
        fprintf(stderr, "usa: %s [-l -w -m <num> ] <nome-file> [<nome-file> ...]\n", argv[0]);
	    fprintf(stderr, " -l conta il numero di linee\n");
	    fprintf(stderr, " -w conta il numero di parole\n");
	    fprintf(stderr, " -m <num> setta la lunghezza massima di una linea a <num>\n");
        exit(EXIT_FAILURE);
    }

    int countline = 0, countword = 0;
    char opt;
    long max_line = DEFAULT_MAX_LINE;

    while((opt = getopt(argc, argv, "lwm:"))!= -1){
        switch(opt){
            case 'l':{
                countline = 1;
            }break;
            case 'w':{
                countword=1;
            }break;
            case 'm':{
                max_line = strtol(optarg, NULL, 10);
            }break;
            default: ;
        }
    }
    if((countline + countword) == 0){ countline = 1; countword = 1; }
    char *line = malloc(max_line*sizeof(char)); //buffer
    if(!line){
        perror("malloc line");
        exit(EXIT_FAILURE);
    }

    while(argv[optind] != NULL){
        FILE *fp; //filepointer
        long numline, numword; //contatori

        char* filename = argv[optind];

        if((fp=fopen(filename, "r"))==NULL){
            perror("file error");
            exit(EXIT_FAILURE);
        }
        numline=numword=0;
        while(fgets(line, max_line, fp)!=NULL){
            if(line[strlen(line)-1]=='\n'){
               ++numline; 
            }
            if(countword){ countword += wcount(line);}
        }
        fclose(fp);
        if (countline && !countword) printf("%5ld %s\n", numline, argv[optind]);
	    if (!countline && countword) printf("%5ld %s\n", numword, argv[optind]);
	    if (countline && countword)  printf("%5ld %5ld %s\n", numline, numword, argv[optind]);
	    ++optind;
    }
    if(line) free(line);

    return 0;
}