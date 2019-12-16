/*
    A program that spawns multiple threads that calculate 
    F(n) Fibonacci number.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Used to pass and get values from threads
struct fib_runner_args{
    long long int term;
    long long int answer;
};

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

    //Get the expected ib_runner_args struct
    struct fib_runner_args *runner_struct = (struct fib_runner_args*) arg;

    int p2, p1 = 0, curr = 1;

    for (long long int i = 1; i < runner_struct->term ; i++) {
        p2 = p1;
        p1 = curr;
        curr = p2 + p1;
    }

    runner_struct->answer = curr;

    pthread_exit(0);
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage %s <nth fib #1> <nth fib #2> ... <nth fib #n> \n", argv[0]);
        return -1;
    }

    //Number of arguments (1st one is program name)
    int numArgs = argc - 1;

    //Create array of Thread IDs
    pthread_t thId[numArgs];

    //Array of ib_runner_args structs
    struct fib_runner_args args[numArgs];

    for(int i = 0; i < numArgs; i++){

        args[i].term = atoll(argv[i+1]);

        //Create thread with default attributes
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        //Create thread
        pthread_create(&thId[i], &attr, fib_runner, &args[i]);
    }

    //Wait for all threads to join
    for(int i = 0; i < numArgs; i++){
        printf("Main thread waiting for ");printPt(thId[i]);printf(" to join...\n");
        pthread_join(thId[i], NULL);
        printf("The %lluth Fibonacci number is: %llu \n",args[i].term,args[i].answer);
    }

    return 0;
}
