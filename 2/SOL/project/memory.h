#ifndef MEMORY_H_
#define MEMORY_H_

#include <string.h>

typedef struct my_file{
    long fileSize;
    char *pathName;
    char *buffer;
    size_t bufferSize;
    size_t pathSize;
    struct my_file *next;
}My_File;

typedef struct memory_index{
    long memorySize;
    long maxFiles;
    long memoryUsed;
    long filesStored;
    long Table_size;
    My_File** files;
}Memory_Index;

long hash(long dim, char *pathname);

Memory_Index *createMemory(long maxDim, long maxFiles);

My_File *createFileInMemory(char *path_name, long file_size, char *buffer, size_t path_size, size_t buffer_size);int insertFileInMemory(Memory_Index *memory, int path_len, char *path_name, long file_size, long buffersize, char *buffer);
    
int insertFileInMemory(Memory_Index *memory, int path_len, char *path_name, long file_size, long buffersize, char *buffer);    
#endif
