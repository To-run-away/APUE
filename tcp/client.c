#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>


#define SOUCKET_POET 8000

int main(int argc, char *argv[])
{
    int  clientfd;
	struct sockaddr_in clientaddr;
	int len;
	int ret;
	char sockstr[128];
	char str[1023];
	
	if(argc != 2)
	{
		printf("./%s str",argv[0]);
		return 1;
	}

    clientfd = socket(AF_INET, SOCK_STREAM, 0 );
    if(clientfd < 0) {
        perror("socket\n");
        exit(1);
    }   

	bzero(&clientaddr, sizeof(clientaddr));
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_port = htons(SOUCKET_POET);
	inet_pton(AF_INET, "192.168.0.101",&clientaddr.sin_addr.s_addr );
//	ret = bind(clientfd,(struct sockaddr *) &clientaddr, sizeof(clientaddr));
	ret = connect(clientfd,(struct sockaddr *) &clientaddr, sizeof(clientaddr));
	if(ret < 0)
	{
		perror("connect\n");
		exit(1);
	}

	
	write(clientfd, argv[1],strlen(argv[1]));
	read(clientfd, str, sizeof(str));

	str[strlen(argv[1])] = '\0';
	printf("%s\n",str);

	close(clientfd);





    return 0;
}
