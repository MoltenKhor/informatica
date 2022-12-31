#ifndef COLLECTOR_H_
#define COLLECTOR_H_

#include <format.h>

#define UNIX_PATH_MAX 108

int collector_signal();

void unlink_socket();

int collector_connection();

void c_conn_collector();

int response_Master(message_T* mess);

#endif