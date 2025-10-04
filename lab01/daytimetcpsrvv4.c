#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include 		<unistd.h>
#include        <time.h>                /* old system? */
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>

#define MAXLINE 1024

//#define SA struct sockaddr

#define LISTENQ 2

int
main(int argc, char **argv)
{
    int				listenfd, connfd;
    socklen_t			len;
    char				buff[MAXLINE], str[INET6_ADDRSTRLEN+1];
    time_t				ticks;
    struct sockaddr_in servaddr, cliaddr;

    if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr,"socket error : %s\n", strerror(errno));
        return 1;
    }

//sleep(3);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr  = htonl(INADDR_ANY);
    servaddr.sin_port   = htons(13);	/* daytime server */

    if ( bind( listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        fprintf(stderr,"bind error : %s\n", strerror(errno));
        return 1;
    }
//sleep(3);
    if ( listen(listenfd, LISTENQ) < 0){
        fprintf(stderr,"listen error : %s\n", strerror(errno));
        return 1;
    }
//sleep(3);
    for ( ; ; ) {
        len = sizeof(cliaddr);
            if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len)) < 0){
                fprintf(stderr,"accept error : %s\n", strerror(errno));
                continue;
        	}
//sleep(3);
        bzero(str, sizeof(str));
        inet_ntop(AF_INET, (struct sockaddr  *) &cliaddr.sin_addr.s_addr,  str, sizeof(str));
        printf("Connection from %s\n", str);

	while(n = read(connfd, buff, MAXLINE)) {
		recvline[n] = 0;
		err = fputs(buff, stdout);
		if(err == EOF) {
			fprintf(stderr, "fputs error: %s\n", strerror(errno));
			return 1;
		}
		fgets(buff, MAXLINE, stdin);
		err = write

	}

        //ticks = time(NULL);
        //snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        //if( write(connfd, buff, strlen(buff))< 0 )
       	//    fprintf(stderr,"write error : %s\n", strerror(errno));
        //close(connfd);
	}
}
