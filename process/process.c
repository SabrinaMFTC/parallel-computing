/* This program is written based on the code available at https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/shm/example-1.html.
   It shows the communication between parent and child processes using shared memory.

   The following explanation is also adapted from the code obtained in the link above:
     The main function runs as a server and uses IPC_PRIVATE to request a private shared memory. Since the client is the server's child process created after the shared memory has been created and attached, the child client process will receive the shared memory in its address space and as a result no shared memory operations are required.
     This program asks for a shared memory of five integers and attaches this shared memory segment to its address space. Pointer ShmPTR points to the shared memory segment.
     Then, this program forks a child process to run function ClientProcess(). Thus, two identical copies of address spaces are created, each of which has a variable ShmPTR whose value is a pointer to the shared memory. As a result, the child process already knows the location of the shared memory segment and does not have to use shmget() and shmat().
     The parent waits for the completion of the child. For the child, it retrieves the five integers, which were stored there by the parent before forking the child, sums the first four and store this value in the fifth integer, prints them and exits. The wait() system call in the parent will detect this.
     The parent then multiplies the fifth integer value by 2 and finally exits.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void  ClientProcess(int []);

void  main(int  argc, char *argv[])
{
     int   ShmID;
     int   *ShmPTR;
     pid_t pid;
     int   status;

     if (argc != 5) {
          printf("Use: %s #1 #2 #3 #4\n", argv[0]);
          exit(1);
     }

     ShmID = shmget(IPC_PRIVATE, 5 * sizeof(int), IPC_CREAT | 0666);

     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }

     printf("Server has received a shared memory of five integers...\n");

     ShmPTR = (int*)shmat(ShmID, NULL, 0);

     if ((intptr_t) ShmPTR == -1) {
          printf("*** shmat error (server) ***\n");
          exit(1);
     }

     printf("Server has attached the shared memory...\n");

     ShmPTR[0] = atoi(argv[1]);
     ShmPTR[1] = atoi(argv[2]);
     ShmPTR[2] = atoi(argv[3]);
     ShmPTR[3] = atoi(argv[4]);
     ShmPTR[4] = 0;

     printf("Server has filled %d %d %d %d %d in shared memory...\n",
            ShmPTR[0], ShmPTR[1], ShmPTR[2], ShmPTR[3], ShmPTR[4]);

     printf("Server is about to fork a child process...\n");

     pid = fork();

     if (pid < 0) {
          printf("*** fork error (server) ***\n");
          exit(1);
     } else if (pid == 0) {
          ClientProcess(ShmPTR);
          exit(0);
     }

     wait(&status);
     printf("Server has detected the completion of its child...\n");

     printf("Value calculated in child = %d\n", ShmPTR[4]);
     printf("Value calculated in child * 2 = %d\n", ShmPTR[4] * 2);
     
     shmdt((void *) ShmPTR);
     printf("Server has detached its shared memory...\n");
     
     shmctl(ShmID, IPC_RMID, NULL);
     printf("Server has removed its shared memory...\n");
     
     printf("Server exits...\n");
     exit(0);
}

void  ClientProcess(int SharedMem[])
{
     printf("*** Client process started\n");

     SharedMem[4] = SharedMem[0] + SharedMem[1] + SharedMem[2] + SharedMem[3];

     printf("*** Client found %d %d %d %d %d in shared memory\n",
            SharedMem[0], SharedMem[1], SharedMem[2], SharedMem[3], SharedMem[4]);

     printf("*** Client is about to exit\n");
}
