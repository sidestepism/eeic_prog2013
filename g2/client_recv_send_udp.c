#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

	int s = socket(PF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	addr.sin_port = htons(atoi(argv[2]));

//	printf("addr: %s\n", argv[1]);
//	printf("port(UDP): %d\n", atoi(argv[2]));

	
	char data[1024];
	int n;
//	printf("%s\n", "start");
	int size = 0;

	while((n = read(0, data, 1000)) > 0){
		printf("sending data: %d byte\n", n);
		int ret = sendto(s, data, n, 0, (const sockaddr *)&addr, sizeof(addr));
		if (size ++ > 50)break;
	}

	// send EOD
	memset(data, '1', 1024);
	int ret = sendto(s, data, 1000, 0, (const sockaddr *)&addr, sizeof(addr));
//	printf("sending EOF: 1000 byte\n");

	memset(data, 0, 1024);
	unsigned int addr_len = sizeof(addr);
	while((n = recvfrom(s, data, 1000, 0, (sockaddr *)&addr, &addr_len)) > 0){
		// check EOD (End of document)
		int ptr;
		for(ptr = 0; ptr < 1000; ptr ++){
			if(data[ptr] != '1') break;
		}
		if(ptr == 1000) break;
//		printf("ptr: %d\n", ptr);
		printf("size: %d\n", n);
		printf("%s", data);
		size += n;
		send(1, data, n, 0);
		memset(data, 0, 1024);
	}


	close(s);
	return 0;
}
