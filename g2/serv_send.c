/**
loop back
@author Ryohei Fushimi <fushimi.ryohei@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("usage: %s [port] [file]\n", argv[0]);
		return 1;
	}

	int ss = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	bind(ss, (sockaddr*) &addr, sizeof(addr));

	int fs = open(argv[2], 0);
	if(fs < 0){
		printf("error: file open failed (%s)\n", argv[2]);
		return 1;		
	}

	listen(ss, 10);
	int s;
	unsigned int socklen = sizeof(addr);
	while(s = accept(ss, (sockaddr *) &addr, &socklen)){
		printf("accepted connection\n");
		unsigned char buffer[1024];
		int r;
		while((r = read(fs, buffer, 1024)) > 0){
			printf("sending data.. (%d bytes)", r);
			write(s, buffer, r);
		}
		close(s);
		printf("closed connection\n");
	}
	close(ss);
	return 0;
}