//utilizzo il prototipo di metodi presenti in altri file, il linker li cercherà nelle librerie standard
int printf(const char *format, ...);
int getopt(int argc, char * const argv[], const char *optstring);

//utilizzo extern per richiamare variabili provenienti da file esterni, il linker li cercherà nelle librerie standard
extern char *optarg;
extern int optopt;                  

int main(int argc, char *argv[]) {
  int opt;
  while ((opt = getopt(argc,argv, ":n:m:h")) != -1) {
    switch(opt) {
    case 'n':
    case 'm':printf("l'argomento di '-%c' e' '%s'\n",opt,optarg); break;
    case 'h':printf("'-h' non ha argomenti\n"); break;
    case ':':printf("'-%c' richiede un argomento\n", optopt); break;
    case '?':printf("'-%c' non e' riconosciuta\n", optopt);
    default:;
    }
  }  
  return 0;
}