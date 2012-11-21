#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SIZE 26

int main() {
    int id;
    char *pointer;
    int i;

    id = shmget(2404, SIZE, 0666); // use created shared memory

    if (id >= 0) {
        pointer = (char*) shmat(id, 0, 0); // make memory available (attach memory)

        if (pointer == (char *)-1) {
            perror("shmat"); // -1 returned => error
        } else {
            printf("Inhalt von gemeinsamen Speicher: ");

            for (i = 0; i < SIZE; i++) {
                putchar(pointer[i]);
            }

            printf("\n");
            shmdt(pointer); // detach memory
        }
    } else {
        perror("shmget"); // -1 returned => error
    }

    return 0;
}