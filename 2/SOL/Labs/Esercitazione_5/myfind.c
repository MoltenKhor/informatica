#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

#include "utils/include/utils.h"
#define MAX_NAME 256
static int quiet = 0;

int isdot(const char dir[]){
    int l = strlen(dir);
    if(l>0 && (dir[l-1] == '.')){
        return 1;
    }
    return 0;
}

char* cwd(){
    char *buf = malloc(MAX_NAME*sizeof(char));
    if(!buf){
        fprintf(stderr, "malloc\n");
        return NULL;
    }
    if(getcwd(buf, MAX_NAME)==NULL){
        if(errno==ERANGE){
            char* buf2 = realloc(buf, 2*MAX_NAME*sizeof(char));
            if(!buf2){
                perror("realloc");
                free(buf);
                return NULL;
            }
            buf = buf2;
            if(getcwd(buf, 2*MAX_NAME)==NULL){
                if(!quiet){
                    perror("cwd");
                    free(buf);
                    return NULL;
                }
            }
        }else{
            if(!quiet){
                perror("cwd");
                free(buf);
                return NULL;
            }
        }
    }
    return buf;
}

int find(const char directory[], const char filename[]){
    if(chdir(directory)==-1){
        if(!quiet){
            fprintf(stderr, "impossibile entrare nella directory\n");
            return 0;
        }
    }
    DIR *dir;
    if((dir=opendir("."))==NULL){
        if(!quiet){
            fprintf(stderr, "errore aprendo directory %s\n", directory);
            return -1;
        }
    }else{
            struct dirent *file;
            while((errno=0, file=readdir(dir))!=NULL){
                struct stat statbuf;
                if(stat(file->d_name, &statbuf)==-1){
                    if(!quiet){
                        perror("stat");
                        fprintf(stderr, "errore stat %s\n", file->d_name);
                    }
                    return -1;
                }
                if(S_ISDIR(statbuf.st_mode)){
                    if(!isdot(file->d_name)){
                        if(find(file->d_name, filename)!=0){
                            if(chdir("..")==-1){
                                fprintf(stderr, "impossibile risalire alle directory\n");
                                return -1;
                            }
                        }
                    }
                }else{
                    if(strncmp(file->d_name, filename, strlen(filename))==0){
                        char* buf = cwd();
                        if(buf==NULL) return -1;
                        printf("%s/%s %s", buf, file->d_name, ctime(&statbuf.st_mtime));
                        free(buf);
                    }
                }
            }
            if(errno != 0) perror("readir");
            closedir(dir);
        }
    return 1;
}

int main(int argc, char* argv[]){
    if(argc < 3 || argc > 4){
        fprintf(stderr, "numero argomenti errato, usare %s dir nomefile\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* dir = argv[1];
    const char* file = argv[2];

    struct stat statbuf;
    int r;

    SYSCAL_EXIT(stat, r, stat(dir, &statbuf), "facendo stat del nome %s, errore %d\n", dir, errno);
    if(!S_ISDIR(statbuf.st_mode)){
        fprintf(stderr, "%s non è una directory\n", dir);
        return EXIT_FAILURE;
    }
    find(dir, file);
    return EXIT_SUCCESS;
}