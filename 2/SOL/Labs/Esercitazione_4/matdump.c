#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define DIM_LIMIT 512

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

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "worng input\n");
        return EXIT_FAILURE;
    }
    long dim;
    if(isNumber(argv[1], &dim)!=0){
        fprintf(stderr, "not a number\n");
        return EXIT_FAILURE;
    }
    if(dim > DIM_LIMIT){
        fprintf(stderr, "too big number\n");
        return EXIT_FAILURE;
    }
    int crea = (strncmp("crea", argv[1], strlen("crea"))==0);
    if(crea){
        float *mat=NULL;
       if(mat=(float*)malloc(dim*dim*sizeof(float))){
           for(long i=0; i<dim; i++){
               for(long j=0; j<dim; j++){
                   mat[i*dim+j] = (i+j)/2.0;
               }
           }

           FILE *fp1;
           if((fp1=fopen("./matdump.dat", "w"))==NULL){
               return EXIT_FAILURE;
           }
           fwrite(&mat[0], sizeof(float), dim*dim, fp1);
           if(fp1){fclose(fp1);}
           fp1=fopen("./matdump.txt", "w");
           for(long i=0; i<dim; i++){
               for(long j=0; j<dim; j++){
                   fprintf(fp1, "%f\n", mat[i*dim+j]);
               }
           }
           fclose(fp1);
       }else{
           return EXIT_FAILURE;
       }
            if(mat) free(mat);
    }else{
        float *mat = NULL;
        float *mat2 = NULL;
        mat =  (float*)malloc(dim*dim*sizeof(float));
        mat2 = (float*)malloc(dim*dim*sizeof(float));
        FILE *fp1, *fp2;
        fp1 = fopen("./matdump.dat", "r");
        fp2 = fopen("./matdump.txt", "r");
        free(mat);
        free(mat2);
    }
    return 0;
}