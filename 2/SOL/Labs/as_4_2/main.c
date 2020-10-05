#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM_LIMIT 512

#define CHECK_EQ(X, val, str) \
    if((X)==val){             \
        perror(#str);         \
        exit(EXIT_FAILURE);   \
    }

#define CHECK_NEQ(X, val, str)   \
    if((X)!=val){                \
        perror(#str);            \
        exit(EXIT_FAILURE);      \
    }

typedef int(*F_t)(const void*, const void*, size_t);

int confronta(F_t cmp, const void *s1, const void *s2, size_t n){
    return cmp(s1,s2,n);
}

int main(int argc, char* argv[]){
    if(argc!=3){
        fprintf(stderr, "use %s <dim>crea|check", argv[0]);
        return(EXIT_FAILURE);
    }

    long dim = strtol(argv[1], NULL, 10);
    if(dim > DIM_LIMIT){
        fprintf(stderr, "dim troppo grande (%ld), deve essere massimo %d\n", dim, DIM_LIMIT);
        return(EXIT_FAILURE);
    }
    int crea = (strncmp("crea", argv[2], strlen("crea"))==0);
    if(crea){
        float *mat = NULL;

        CHECK_EQ(mat = (float*)malloc(dim*dim*sizeof(float)), NULL, "malloc");
    

        for(long i=0; i<dim; ++i){
            for(long j=0; j<dim; ++j){
                mat[i*dim+j]=(i+j)/2.0; 
            }
        }

        FILE *fp1;
        CHECK_EQ(fp1= fopen("./mat_dump.dat", "w"), NULL, "fopen");

        #if 1 // write singola
	        CHECK_NEQ(fwrite(&mat[0], sizeof(float), dim*dim, fp1), (dim*dim), "fwrite");
        #else // alternativamente 
	        for(long i=0;i<dim;++i)
	        for(long j=0;j<dim;++j) 
		    CHECK_NEQ(fwrite(&mat[i*dim+j], sizeof(float), 1, fp1), 1, "fwrite");    
        #endif
        fclose(fp1);

        CHECK_EQ(fp1= fopen("./mat_dump.txt", "w"), NULL, "fopen");
        for(long i=0; i<dim; ++i){
            for(long j=0; j<dim; ++j){
                if(fprintf(fp1, "%f\n", mat[i*dim+j])<0){
                    perror("fprintf");
                    return EXIT_FAILURE;
                }
            }
        }
        fclose(fp1);
        if(mat) free(mat);
    }else{ //check
        float *mat = NULL;
    	CHECK_EQ(mat = (float*)malloc(dim*dim*sizeof(float)), NULL, "malloc");
	
	    float *mat2 = NULL;
	    CHECK_EQ(mat2 = (float*)malloc(dim*dim*sizeof(float)), NULL, "malloc");
	    FILE *fp1;
	    CHECK_EQ(fp1=fopen("./mat_dump.dat", "r"), NULL, "fopen mat_dump.dat");
	    FILE *fp2;
	    CHECK_EQ(fp2=fopen("./mat_dump.txt", "r"), NULL, "fopen max_dump.txt");

	    char buf[128];
	    for(long i=0;i<dim;++i){
	        for(long j=0;j<dim;++j) {
		        if (fgets(buf, 128, fp2) == NULL) {
		            perror("fgets");
		            exit(-1);
                }
	        	buf[strlen(buf)-1]='\0';
		        mat[i*dim+j] = strtof(buf, NULL);
            }

	    }
	    fclose(fp2);
	
        #if 1 // read singola
	    CHECK_NEQ(fread(&mat2[0], sizeof(float), dim*dim, fp1),(dim*dim), "fread");
        #else // alternativamente
	    for(long i=0;i<dim;++i)
	    for(long j=0;j<dim;++j)
		CHECK_NEQ(fread(&mat2[i*dim+j], sizeof(float), 1, fp1), 1, "fread");
        #endif
	    fclose(fp1);

	
	    if (confronta(memcmp, mat, mat2, dim*dim*sizeof(float)) != 0) {
	        fprintf(stderr, "Le due matrici non corrispondono\n");
	        return EXIT_FAILURE;
    	}
	    fprintf(stdout, "Le due matrici sono uguali\n");
	    free(mat);
	    free(mat2);
    }
    return 0;
}