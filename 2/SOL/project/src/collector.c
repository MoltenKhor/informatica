#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <signal.h>

#include <utils.h>
#include <collector.h>

int collector_sock = 0;
int collector_acpt = 0;

struct sockaddr_un sckaddr;

int collector_connection(){
    if((collector_sock = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "ERROR: socket");
        return -1;
    }

    memset(&sckaddr, '0', sizeof(sckaddr));
    strncpy(sckaddr.sun_path, SOCKNAME, UNIX_PATH_MAX);
    sckaddr.sun_family = AF_LOCAL;

    if(bind(collector_sock, (struct sockaddr*) &sckaddr, sizeof(sckaddr)) == -1){
        fprintf(stderr, "Error: bind");
        return -1;
    }

    if(listen(collector_sock, 1) == -1){
        fprintf(stderr, "Error: listen");
        return -1;
    }

    if((collector_acpt = accept(collector_sock, NULL, NULL)) == -1){
        fprintf(stderr, "Error: accept");
        return -1;
    }
    return 0;
}

void c_conn_collector(){
    if(close(collector_sock) == -1){
        fprintf(stderr, "Error: socket collector close");
        return;
    }
    if(close(collector_acpt) == -1){
        fprintf(stderr, "Error: accept collector close");
    }
}

void unlink_socket(){
    unlink(SOCKNAME);
}

int collector_signal(){
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(sigact));
    sigact.sa_handler = SIG_IGN;

    if(sigaction(SIGHUP, &sigact, NULL) == -1){
        fprintf(stderr, "Error: collector SIGHUP\n");
        return -1;
    }
    if(sigaction(SIGQUIT, &sigact, NULL) == -1){
        fprintf(stderr, "Error: collector SIGQUIT\n");
        return -1;
    }
    if(sigaction(SIGINT, &sigact, NULL) == -1){
        fprintf(stderr, "Error: collector SIGINT\n");
        return -1;
    }
    if(sigaction(SIGPIPE, &sigact, NULL) == -1){
        fprintf(stderr, "Error: collector SIGPIPE\n");
        return -1;
    }
    if(sigaction(SIGTERM, &sigact, NULL) == -1){
        fprintf(stderr, "Error: collector SIGTERM\n");
        return -1;
    }
    if(sigaction(SIGUSR1, &sigact, NULL) == -1){
        fprintf(stderr, "Error: collector SIGUSR1\n");
        return -1;
    }
    return 0;
}

int response_Master(messsage_T* mess){
    int k;
    size_t len;
    errno = 0;

    if((k=readn(collector_acpt, &len, sizeof(size_t))) != sizeof(size_t)){
        if(k==0){
            return 0;
        }
        fprintf(stderr, "Error: collector, pathname length");
        return -1;
    }

    if(len == -1){
        return 2;
    }

    mess->path = malloc((len)*sizeof(char));
    memset(mess->path, '\0', len);

    if((k=readn(collector_acpt, mess->path, sizeof(char)*(len))) != len){
        if(k==0){
            return 0;
        }
        fprintf(stderr, "Error: reading path");
        free(mess->path);
        return -1;
    }

    if((k=readn(collector_acpt, &(mess->result), sizeof(long)))!= sizeof(long)){
        if(k==0){
            free(mess->path);
            return 0;
        }

        fprintf(stderr, "Error: reading result");
        free(mess->path);
        return -1;
    }
    return 1;
}
