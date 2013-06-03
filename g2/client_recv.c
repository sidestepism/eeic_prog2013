#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
	if(argc < 1){
		printf("usage: %s [port]\n", argv[0]);
		return 1;
	}


	int s = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(atoi(argv[1]));
	int ret = connect(s, (struct sockaddr *)& addr, sizeof(addr));
	char data[1024];
	int n;

	while(n = read(s, data, 1) > 0){
		if(data[0] == EOF)break;
		write(1, data, 1);
	}
	close(s);
}
