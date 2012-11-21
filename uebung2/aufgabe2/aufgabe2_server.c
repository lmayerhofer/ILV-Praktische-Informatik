#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SIZE 26

int main() {
	int id;
	char *pointer;
	int i;

	id = shmget(2404, SIZE, IPC_CREAT | 0666); // create shared memory: returns id for memory segment or -1 (error)

	if (id >= 0) {
		pointer = (char*) shmat(id, 0, 0); // make memory available (attach memory)

		if (pointer == (char *) -1) {
			perror("shmat"); // -1 returned => error
		} else {
			for (i = 0; i < SIZE; i++) {
				pointer[i] = 'A' + i;
			}

			printf("Alphabet in gemeinsamen Speicher geschrieben.\n\n");
			shmdt(pointer); // detach memory
		}
	} else {
		perror("shmget"); // -1 returned => error
	}

	return 0;
}