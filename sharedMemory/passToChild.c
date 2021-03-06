#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
	int fd[2];
	int childID = 0;

	// create pipe descriptors
	pipe(fd);

	// fork() returns 0 for child process, child-pid for parent process.
	if (fork() != 0) {
		// parent: writing only, so close read-descriptor.
		close(fd[0]);

		// send the childID on the write-descriptor.
		childID = 1;
		write(fd[1], &childID, sizeof(childID));
		printf("Parent(%d) send childID: %d\n", getpid(), childID);

		// close the write descriptor
		close(fd[1]);
	} else {
		// child: reading only, so close the write-descriptor
		close(fd[1]);

		// now read the data (will block until it succeeds)
		read(fd[0], &childID, sizeof(childID));
		printf("Child(%d) received childID: %d\n", getpid(), childID);

		// close the read-descriptor
		close(fd[0]);
	}
	return 0;
}