#include <string.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>


Memory_Index *createMemory(long maxDim, long maxFiles){
    Memory_Index *memory = (Memory_Index*)malloc(sizeof(Memory_Index));
    
    if(!memory){
        return NULL;
    }

    memory->maxFiles = maxFiles;
    memory->memorySize = maxDim;
    memory->Table_size = (int)(maxDim*2);
    memory->memoryUsed = 0;
    memory->filesStored = 0;
    memory->files = (My_File**)calloc(memory->Table_size, sizeof(My_File*));


    for(int i=0; i<memory->Table_size; i++){
        memory->files[i] = NULL;
    }

    return memory;
}

long hash(long dim, char *pathname){
    long sum = 0;
    for(int i=0; i<strlen(pathname); i++){
        sum += (unsigned long)pathname[i];
    }
    return (sum*351)%dim;
}

My_File *createFileInMemory(char *path_name, long file_size, char *buffer, size_t path_size, size_t buffer_size){
    My_File *file = (My_File*)malloc(sizeof(My_File));
    if(!file){
        fprintf(stderr, "malloc file");
        free(file);
        return NULL;
    }

    file->next = NULL;
    file->pathName = malloc(path_size*sizeof(char));
    if(!file->pathName){
        free(file->pathName);
        free(file);
        return NULL;
    }
    strncpy(file->pathName, path_name, path_size);
    file->bufferSize = buffer_size;
    file->fileSize = file_size;
    file->pathSize = path_size;
    file->buffer = malloc(buffer_size*sizeof(char));
    if(!file->buffer){
        free(file->pathName);
        free(file->buffer);
        free(file);
        return NULL;
    }
    strncpy(file->buffer, buffer, buffer_size);

    return file;
}

int insertFileInMemory(Memory_Index *memory, int path_len, char *path_name, long file_size, long buffersize, char *buffer){
   
    My_File *file = createFileInMemory(path_name, file_size, buffer, path_len, buffersize);
   
    unsigned long file_index = hash(memory->Table_size, path_name);
    if(memory->files[file_index] == NULL){
        memory->files[file_index] = file;
    }else{
        My_File *curr = (memory->files[file_index]);
        if(strcmp(curr->pathName, file->pathName) == 0){
            fprintf(stderr, "file already exist.\n");
            free(curr);
            free(file);
            return 1;
        }
        while(curr->next != NULL){
            if(strcmp(curr->pathName, file->pathName) == 0){
                fprintf(stderr, "file already exist.\n");
                free(curr);
                free(file);
                return 1;
            }
        curr = curr->next;
        }
    curr->next = file;
    }
    memory->filesStored++;
    memory->memoryUsed += file_size;
    printf("file added, %ld stored, %ld memory used.\n",memory->filesStored, memory->memoryUsed);
    return 0;
}