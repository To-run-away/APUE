#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>


#define SOUCKET_POET 8000

int main()
{
    int socketfd, clientfd;
	struct sockaddr_in socketaddr,clientaddr;
	int len,datalen;
	int ret;
	char sockstr[128], buf[1024];
	int i;

	/* 打开一个 流式(tcp) socket接口 */
    socketfd = socket(AF_INET, SOCK_STREAM, 0 );
    if(socketfd < 0) {
        perror("socket\n");
        exit(1);
    }   

	/* 绑定服务器的ip地址,端口 */
	bzero(&socketaddr, sizeof(socketaddr));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_port = htons(SOUCKET_POET);
	socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(socketfd,(struct sockaddr *) &socketaddr, sizeof(socketaddr));
	if(ret < 0)
	{
		perror("bind\n");
		exit(1);
	}

    /* 设置对这个soucket进行监听 */ 
	listen(socketfd, 128);

	while(1)
	{
		/* 获取客户端的链接 */
		len = sizeof(clientaddr);
		clientfd = accept(socketfd,(struct sockaddr*) &clientaddr, &len);
		if(clientfd < 0)
		{
			perror("accept \n");
			exit(1);
		}
		printf("ipaddr = %s, %d\n",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr, sockstr, sizeof(sockstr)), 
				ntohs(clientaddr.sin_port));

		/* 服务器和客户端进行交互  */	
		//do something
		datalen = read(clientfd, buf, sizeof(buf));
		for(i = 0; i < datalen; i++)	
		{
			buf[i] = toupper(buf[i]);
		}
		write(clientfd, buf, datalen);

		close(clientfd);
	}
	
	close(socketfd);

    return 0;
}
