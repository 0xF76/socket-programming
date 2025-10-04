#include   <sys/types.h>   /* basic system data types */
#include   <sys/socket.h>  /* basic socket definitions */
#include   <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include   <arpa/inet.h>   /* inet(3) functions */
#include   <errno.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <unistd.h>
#include   <string.h>

#define MAXLINE 1024
#define SA      struct sockaddr

int main(int argc, char **argv)
{
	int	sockfd, n, err;
	struct sockaddr_in	servaddr;
	char buff[MAXLINE + 1];

	if (argc != 2){
		fprintf(stderr, "usage: %s <IPaddress> \n", argv[0]);
		return 1;
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		fprintf(stderr,"socket error : %s\n", strerror(errno));
		return 1;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */


	err = inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);
	if(err == -1) {
		fprintf(stderr,"ERROR: inet_pton error for %s : %s \n", argv[1], strerror(errno));
		return 1;
	} else if(err == 0) {
		fprintf(stderr,"ERROR: Invalid address family \n");
		return 1;
	}

	err = connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
	if (err < 0){
		fprintf(stderr,"connect error : %s \n", strerror(errno));
		return 1;
	}

	printf("Connected to %s\n", argv[1]);

	n = read(sockfd, buff, MAXLINE);
	if (n < 0) {
		fprintf(stderr,"read error : %s\n", strerror(errno));
		return 1;
	} else if(n > 0) {
		buff[n] = 0;
		if (fputs(buff, stdout) == EOF){
			fprintf(stderr,"fputs error : %s\n", strerror(errno));
			return 1;
		}
	}
	
	while(1) {
		fgets(buff, MAXLINE, stdin);
		buff[strcspn(buff, "\n")] = 0; // remove newline character
		
		err = write(sockfd, buff, strlen(buff));
		if(err < 0) {
			fprintf(stderr,"write error : %s\n", strerror(errno));
		}

		if (strncmp(buff, "exit", 4) == 0) {
			printf("Exiting...\n");
			break;
		}

		n = read(sockfd, buff, MAXLINE);
		if (n < 0) {
			fprintf(stderr,"read error : %s\n", strerror(errno));
			return 1;
		} else if(n > 0) {
			buff[n] = 0;
			printf("Server: ");
			if (fputs(buff, stdout) == EOF){
				fprintf(stderr,"fputs error : %s\n", strerror(errno));
				return 1;
			}
		}	
	}

	close(sockfd);
	return 0;
}
