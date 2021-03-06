/**
loop back
@author Ryohei Fushimi <fushimi.ryohei@gmail.com>
 */
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
	if(argc < 2){
		printf("usage: %s [addr] [port]\n", argv[0]);
		return 1;
	}

	int s = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);

	printf("addr: %s\n", argv[1]);
	printf("port: %d\n", atoi(argv[2]));

	addr.sin_port = htons(atoi(argv[2]));
	int ret = connect(s, (struct sockaddr *)& addr, sizeof(addr));
	printf("connect status: %d\n", ret);

	if(ret != 0){
		printf("Invalid connection status (connectuion failure)\n");
		return 1;
	}

	char data[1024];
	int n;
	printf("%s\n", "start");
	int size = 0;
	
	while(n = read(s, data, 1) > 0){
		size ++;
		if(data[0] == EOF) break;
		send(0, data, 1, 0);
	}
	printf("size: %d\n", size);
	close(s);
	printf("close: %d\n", size);
	return 0;
}