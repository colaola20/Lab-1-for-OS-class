#include <iostream> 
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h> 
#include <cstdlib>
#include <time.h>
//using namespace std; 
  
int main() { 
    int i;
    int arr [20];
    //Using current system time as seed value
    unsigned int seed = time(0);
    int start, end;
    int min_num;

    //creating a random number array
    printf("The array: ");
    for (i = 0; i < 20; i++) {
        arr[i] = rand_r(&seed) % 101;
        printf("%d ", arr[i]);
        }
    printf("\n");


    int fd[2];
    //creating a pipe for parent and child processes
    if  (pipe(fd)==-1) {
        return 1;
    }

    //Creating a child process
    int id = fork();

    if (id == -1) {
        return 2;
    }

    if (id != 0) {
        // parent process is running
        start=0;
        min_num = arr[start];
        end= 10;
        printf("parent loop from 0 to  : %d\n",end);
    }
    else {
        //child procces is running
        start= 10;
        min_num = arr[start];
        end = 20;
        printf("child loop from  : %d\n",start);
    }

    
    //Finding a minimun in a half of the array
    for (i = start;i < end;i++){
        if (arr[i] < min_num) {
            min_num = arr[i];
        }
    }

    printf("The min num is: %d (from %d to %d)\n", min_num, start+1, end);

    if (id==0) {
        printf("\nchild's process id is  %d\n",getpid());
        //writing the minimum to the pipe
        write(fd[1],&min_num,sizeof(min_num));
        close(fd[1]);
    }
    else{
        printf("\nparent's process id is %d\n",getpid());
        close(fd[1]);
        int childMin;
        //reading the minimum from the pipe
        read(fd[0], &childMin,sizeof(int));
        close(fd[0]);

        int minimum;
        if (childMin < min_num) {
            minimum = childMin;
        } else {
            minimum = min_num;
        }

        printf("\nThe minimum number is : %d\n",minimum);
        }

    return 0;
}