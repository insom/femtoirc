#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096
#define STDOUT 1

int do_connect(void) {
    struct sockaddr_in sa;
    int s;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = htonl(0x7f000001); // lolcathost
    sa.sin_port = htons(6667);
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s > 0) {
        if(connect(s, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
            close(s);
            s = -1;
        } else {
            fcntl(s, F_SETFL, O_NDELAY);
        }
    }
    return s;
}

int do_pipe(void) {
    int p;
    p = open("pipe", O_RDONLY|O_NONBLOCK);
    if(p > 0) {
        fcntl(p, F_SETFL, O_NDELAY);
    }
    return p;
}

int read_to(int input, int output, int pings) {
    char buffer[BUFFER_SIZE];
    int bytes;

    if((bytes = read(input, buffer, BUFFER_SIZE)) < 1) {
        return -1;
    } else {
        write(output, buffer, bytes);
        if(pings == 1) {
            char *ping = strstr(buffer, "PING ");
            if(ping != NULL) {
                ping[1] = 'O'; // turn that PING upside-PONG
                char *nl = strchr(ping, '\n');
                nl[1] = '\0';
                int length = (nl - ping) + 1;
                write(input, ping, length);
            }
        }
    }
}

int do_loop(int irc_socket, int pipe_fd) {
    fd_set fds;
    for(;;) {
        FD_SET(irc_socket, &fds);
        FD_SET(pipe_fd, &fds);
        if(select(pipe_fd + 1, &fds, NULL, NULL, NULL) < 0) {
            perror("select");
            return -1;
        } else {
            if(FD_ISSET(irc_socket, &fds)) {
                if(read_to(irc_socket, STDOUT, 1) < 0) {
                    return -1;
                }
            }
            if(FD_ISSET(pipe_fd, &fds)) {
                read_to(pipe_fd, irc_socket, 0); // we don't care about read failures
            }
        }
    }
}

int main(int c, char **v) {
    int irc_socket;
    int pipe_fd;
    char *me = getenv("LOGNAME");
    char buffer[BUFFER_SIZE] = {0};

    if((irc_socket = do_connect()) < 0) {
        perror("do_socket");
        return -1;
    }
    if((pipe_fd = do_pipe()) < 0) {
        perror("do_pipe");
        return -1;
    }
    sprintf(buffer, "USER %s %s %s %s\nNICK %s\n", me, me, me, me, me);
    write(irc_socket, buffer, strlen(buffer));
    if(do_loop(irc_socket, pipe_fd) < 0) {
        perror("do_loop");
        return -1;
    }
    return 0;
}
