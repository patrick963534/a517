#include <stdio.h>
#include "mz_socket.h"

int main(int argc, char **args)
{
    rudp_socket_t *me = rudp_socket_new(3000, rudp_socket_type_client);

    printf("Hello World.\n");


    return 0;
}
