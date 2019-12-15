/*
    A program that spawns a single thread that calculates 
    F(n) Fibonacci number. Spawned thread then sets a
    global variable to the result. Main thread prints
    the result
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long int fibNum = 0;

/*
Prints out a hexadecimal representation of pthread_t
https://stackoverflow.com/questions/1759794/how-to-print-pthread-t
*/
void printPt(pthread_t pt) {
    unsigned char *ptc = (unsigned char*)(void*)(&pt);
    printf("0x");
    for (size_t i=0; i<sizeof(pt); i++) {
        printf("%02x", (unsigned)(ptc[i]));
    }
}

// Thread function
void* fib_runner(void* arg){

    //Get the expected int parameter
    long long int *n = (long long int*) arg;

    int p2, p1 = 0, curr = 1;

    for (long long int i = 1; i < *n ; i++) {
        p2 = p1;
        p1 = curr;
        curr = p2 + p1;
    }

    fibNum = curr;

    pthread_exit(0);
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage %s <fib number> \n", argv[0]);
        return -1;
    }

    //get argv #1 as int
    long long int term = atoll(argv[1]);

    //Thread ID
    pthread_t thId;

    //Create thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    //Create thread
    pthread_create(&thId, &attr, fib_runner, &term);

    printf("Main thread waiting for ");
    printPt(thId);
    printf(" to finish...\n");

    //Wait for join
    pthread_join(thId, NULL);

    printf("The %lluth Fibonacci number is: %llu \n",term,fibNum);

    return 0;
}