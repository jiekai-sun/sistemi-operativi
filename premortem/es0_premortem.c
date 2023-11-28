#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
    int index;
    pthread_t threadId;
};

void *function(void *pointer) {
    pthread_t threadId;
    int threadCreationOutcome;
    struct thread_info *threadInfo;
    struct thread_info *structPointer;

    struct thread_info thread_info = *(struct thread_info*)pointer;
    printf("index: %d\n", thread_info.index);

    if (thread_info.index < 100) {
        threadInfo = malloc(sizeof(struct thread_info));
        if (threadInfo == NULL) {
            perror("malloc failure");
            pthread_exit(NULL);
        }
        threadInfo->index = thread_info.index;
        threadInfo->threadId = pthread_self();

        structPointer = malloc(sizeof(struct thread_info));
        if (structPointer == NULL) {
            perror("malloc failure");
            pthread_exit(NULL);
        }
        structPointer = threadInfo;

        usleep(1000);

        structPointer->index++;

        threadCreationOutcome = pthread_create(&threadId, NULL, function, structPointer);
        if (threadCreationOutcome) {
            printf("ERROR: return code from pthread_create() is %d\n", threadCreationOutcome);
            exit(-1);
        }
    }
    pthread_join(thread_info.threadId, NULL);
    pthread_exit(NULL);
    return NULL;
}
int main() {
    pthread_t threadId;
    int threadCreationOutcome;
    struct thread_info *threadInfo;
    struct thread_info *structPointer;

    threadInfo = malloc(sizeof(struct thread_info));
    if (threadInfo == NULL) {
        perror("malloc failure");
        pthread_exit(NULL);
    }
    threadInfo->index = 0;
    threadInfo->threadId = pthread_self();

    structPointer = malloc(sizeof(struct thread_info));
    if (structPointer == NULL) {
        perror("malloc failure");
        pthread_exit(NULL);
    }
    structPointer = threadInfo;

    usleep(1000);

    structPointer->index++;

    threadCreationOutcome = pthread_create(&threadId, NULL, function, structPointer);
    if (threadCreationOutcome) {
        printf("ERROR: return code from pthread_create() is %d\n", threadCreationOutcome);
        exit(-1);
    }

    pthread_exit(NULL); /*necessario altrimenti l'intero processo finisce a causa del return*/
    return 1;
}