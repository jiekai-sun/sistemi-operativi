#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 4

struct information {
    int N;/*Number of threads it has to create*/
    char string[101];
    int index;
};

void *do_thread(void *info) {
    struct information *result, *pointer;
    int i = 0;
    int rc = 0;
    usleep(1000000);/*sleep for 1s*/
    result = ((struct information*)info);

    if (result->N > 1) {
        pthread_t threads[NUM_THREADS];

        for (i = 0; i < NUM_THREADS; i++)
        {
            /*Creating a copy of the original structure, it won't be freed here but in the threads it's being sent to*/
            pointer = malloc(sizeof(struct information));
            if (pointer == NULL) {
                perror("malloc failure\n");
                pthread_exit(NULL);
            }
            pointer->N = result->N-1;
            pointer->index = i;
            strcpy(pointer->string, "ciao");
            rc = pthread_create(&threads[i], NULL, do_thread, pointer); /*A & was put before threads[i] since I don't care about the array itself, but the specific value at the specific index*/
            if (rc) {
                printf("ERROR, return code from pthread_create is %d\n", rc);
                exit(-1);
            }
        }
        for (i = 0; i < NUM_THREADS; i++) {   
            /*waiting for the i-th thread to end*/
            rc = pthread_join(threads[i], (void**)&pointer);
            if (rc) {
                printf("pthread_join() failed: %d\n", rc);
                exit(1);
            }
            free(pointer);
        }
    }
    sprintf(result->string, "%d %d", result->N, result->index);
    pthread_exit(result);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc = 0, i = 0;
    struct information *myInfo = NULL;

    /*Creating threads*/
    for (i = 0; i < NUM_THREADS; i++)
    {
        /*allocating data structure*/
        myInfo = malloc(sizeof(struct information));
        if (myInfo == NULL) {
            perror("malloc failure\n");
            pthread_exit(NULL);
        }
        strcpy(myInfo->string, "prova");
        myInfo->N = NUM_THREADS - 1;
        myInfo->index = 0;

        rc = pthread_create(&threads[i], NULL, do_thread, myInfo); /*A & was put before threads[i] since I don't care about the array itself, but the specific value at the specific index*/
        if (rc) {
            printf("ERROR, return code from pthread_create is %d\n", rc);
            exit(1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++)
    {   
        /*waiting for the i-th thread to end*/
        rc = pthread_join(threads[i], (void**)&myInfo);
        if (rc) {
            printf("pthread_join() failed: %d\n", rc);
            exit(1);
        }
        printf("pthread n. %d with ID %d returns %s\n", i, (int) threads[i], myInfo->string);
        free(myInfo);

    }
    pthread_exit(NULL);
    return 0;
}