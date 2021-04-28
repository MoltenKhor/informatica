#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <ctype.h>

#define DEFAULT_MAX_LANE 2048

int isNumber(const char* s, long* n) {
  if (s==NULL) return 1;
  if (strlen(s)==0) return 1;
  char* e = NULL;
  errno=0;
  long val = strtol(s, &e, 10);
  if (errno == ERANGE) return 2;    // overflow/underflow
  if (e != NULL && *e == (char)0) {
    *n = val;
    return 0;   // successo 
  }
  return 1;   // non e' un numero
}

int wcount(const char buf[]) {
    static int flag=0;  // preservo lo stato tra due invocazioni
    char *p = (char*)&buf[0];
    int count = 0;

    // avevo iniziato a contare una parola nella chiamata precedente
    // pero' ero arrivato alla fine del buffer senza incontrare uno spazio
    // oppure '\n'
    if (flag && isspace(*p)) { flag=0; count = 1;}
    
    // togliamo tutti gli spazi ed i caratteri di controllo
    // iniziali in modo da iniziare con un carattere
    while(*p != '\0' && (iscntrl(*p) || isspace(*p))) ++p;

    while(*p != '\0') { 
	if (isspace(*p)) { // se ho uno spazio e se il carattere precedente 
	                   // non e' ne uno spazio 
	  if ( !isspace(*(p-1)) ) {  
	    ++count;
	    flag = 0;
	  }
	} else flag=1;  // ho iniziato una nuova parola
	++p;
    }
    return count; 
}

int main(int argc, char* argv[]){
    if(argc == 1){
        fprintf(stderr, "Usa: %s[-l -w -m <num> ] <nomefile> [<nomefile>...]\n", argv[0]);
        fprintf(stderr, "-l conta il numero di linee\n");
        fprintf(stderr, "-w conta il numero di parole\n");
        fprintf(stderr, "-m <num> setta la lunghezza massima di una riga a <num>, di default è: %d\n", DEFAULT_MAX_LANE);
        return EXIT_FAILURE;
    }
        int countline = 0, countword = 0;
        char opt;
        long max_line = DEFAULT_MAX_LANE;

        while((opt=getopt(argc, argv, ":lwm:"))!=1){
            switch(opt){
                case 'l': {
                    countline = 1;
                }break;
                case 'w': {
                    countword = 1;
                }break;
                case 'm': {
                    if((isNumber(optarg, &max_line)!=0)){
                        fprintf(stderr, "-m non è un numero valido, sarà usato \n");
                    }
                    if(max_line<=1){
                        fprintf(stderr, "buffer troppo piccolo\n");
                        return EXIT_FAILURE;
                    }
                }break;
                case '?': {
                    fprintf(stderr, "comando '-%c' non riconosciuto\n", optopt);
                }break;
                case ':': {
                    fprintf(stderr, "il comando -m deve essere un valore numerico\n");
                }break;
                default: ;
            }
        }
    if(countline+countword == 0){
        countword = 1;
        countline = 1;
    }
    char *line = malloc(max_line*sizeof(char));
    if(line == NULL){
        fprintf(stderr, "bad malloc\n");
        return EXIT_FAILURE;
    }
    
    while(argv[optind] != NULL){
        FILE *fp;
        long nline, nword;
        size_t len;
        char *filename = argv[optind];
        if((fp=fopen(filename, "r"))==NULL){
            fprintf(stderr, "apertura file\n");
            return EXIT_FAILURE;
        }

        nline = 0, nword = 0;
        while(fgets(line, max_line*sizeof(char), fp)){
            if((len=strlen(line))&& (line[len-1]=='\n')){
                ++nline;
            }
            if(countword) nword += wcount(line);
        }
        fclose(fp);
        if(countline && !countword){printf("%5ld %s\n", nline, argv[optind]);}
        if(!countline && countword){printf("%5ld %s\n", nword, argv[optind]);}
        if(countline && countword){printf("%5ld %5ld %s\n", nword, nline, argv[optind]);}
        ++optind;
    }
    free(line);
    return EXIT_SUCCESS;
}