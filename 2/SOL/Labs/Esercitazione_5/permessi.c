#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "utils/include/utils.h"
#include <errno.h>

void permessi(const char file[]){
    struct stat buf;
    int r;
    SYSCAL_EXIT(stat, r, stat(file, &buf), "facendo stat\n", file, errno);

    char mode[11] = {'-','-','-','-','-','-','-','-','-','-','\0'};
    if(S_ISDIR(buf.st_mode))    mode[0]='d';
    if(S_ISCHR(buf.st_mode))    mode[0]='c';
    if(S_ISBLK(buf.st_mode))    mode[0]='b';
    if(S_ISFIFO(buf.st_mode))   mode[0]='p';
    if(S_ISLNK(buf.st_mode))    mode[0]='l';
    if(S_ISSOCK(buf.st_mode))   mode[0]='s';

    if(S_IRUSR & buf.st_mode)    mode[1]='r';
    if(S_IWUSR & buf.st_mode)    mode[2]='w';
    if(S_IXUSR & buf.st_mode)    mode[3]='x';

    if(S_IRGRP & buf.st_mode)    mode[4]='r';
    if(S_IWGRP & buf.st_mode)    mode[5]='w';
    if(S_IXGRP & buf.st_mode)    mode[6]='x';

    if(S_IROTH & buf.st_mode)    mode[7]='r';
    if(S_IWOTH & buf.st_mode)    mode[8]='w';
    if(S_IXOTH & buf.st_mode)    mode[9]='x';

    struct passwd *pw= getpwuid(buf.st_uid);
    struct group *gp = getgrgid(buf.st_gid);

    fprintf(stdout, "%-20s (%-7u): %-10ld %-s %-s,%-s %-s", file, (unsigned)buf.st_ino, buf.st_size, mode, pw->pw_name, gp->gr_name, ctime(&buf.st_mtime));


}

int main(int argc, char* argv[]){

    if(argc == 1){
        fprintf(stderr, "pochi argomenti\n");
        return EXIT_FAILURE;
    }
    for(int i=1; i<argc; i++){
        permessi(argv[i]);
    }
}