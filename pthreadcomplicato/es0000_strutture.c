#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 4

struct information {
    int N;/*Number of threads it has to create*/
    char string[101];
    int index;
};

void *do_thread(void*) {
    
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc, i;
    struct information *myInfo;
    struct information *infoPointer;

    printf("the main is thread no: %u\n", (int) pthread_self());

    /*allocating data structure*/
    myInfo = malloc(sizeof(struct information));
    if (myInfo == NULL) {
        perror("malloc failure\n");
        pthread_exit(NULL);
    }
    myInfo->index = 4;
    *myInfo->string = '\0';
    myInfo->N =4;

    /*Creating threads*/
    for (i = 0; i < NUM_THREADS; i++)
    {
        /*Creating a copy of the original structure, it won't be freed here but in the threads it's being sent to*/
        infoPointer = malloc(sizeof(struct information));
        if (infoPointer == NULL) {
            perror("malloc failure\n");
            pthread_exit(NULL);
        }
        infoPointer = myInfo; /*Copying a struct's value to the new one, this works as long as the struct doesn't contain a "string" made out of pointers*/
        rc = pthread_create(&threads[i], NULL, do_thread, infoPointer); /*A & was put before threads[i] since I don't care about the array itself, but the specific value at the specific index*/
        if (rc) {
            printf("ERROR, return code from pthread_create is %d\n", rc);
            exit(-1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++)
    {   
        int error;
        void *infoPointer;

        /*waiting for the i-th thread to end*/
        error = pthread_join(threads[i], &infoPointer);
        if (error) {
            printf("pthread_join() failed: %d\n", error);
            exit(-1);
        } else {
            printf("pthread no %d with ID %d returns %s\n", i, (int) threads[i], (*(struct information*)(infoPointer)).string);
            free(infoPointer);
        }
    }
    free(myInfo);
    pthread_exit(NULL);
    return 0;
}