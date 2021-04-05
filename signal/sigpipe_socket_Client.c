//Client Program:

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

/*---------------------------------------------------------------------*/
/*--- sig_pipe - SIGPIPE                                            ---*/
/*---------------------------------------------------------------------*/
void sig_pipe(int signum)
{
	printf("got it!\n");
	signal(SIGPIPE, sig_pipe);
}

/*---------------------------------------------------------------------*/
/*--- main - force a SIGPIPE error by connecting to an echo server  ---*/
/*--- and sending data while the server just terminates the         ---*/
/*--- connection.                                                   ---*/
/*---------------------------------------------------------------------*/
main()
{	struct sockaddr_in addr;
	int sd, byte_count, addr_size;

	signal(SIGPIPE, sig_pipe);
	if ( (sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		abort();
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 )
	{
		perror("127.0.0.1");
		abort();
	}
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
	{
		perror("Bind");
		abort();
	}
	if ( send(sd, "this is a test", 17, 0) < 0 )
		perror("send");
	sleep(1);
	if ( send(sd, "this is a test", 17, 0) < 0 )
		perror("send");
	close(sd);
}