#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

struct thread_info {
    int index;
    pthread_t thread_id;
};

void *function(void *pointer) {
    pthread_t thread_id;
    int thread_result;
    struct thread_info *t_info;
    struct thread_info *pointer_to_struct;

    struct thread_info thread_info = *(struct thread_info*)pointer;
    printf("index: |%d| and thread_id: |%ld|\n", thread_info.index, thread_info.thread_id);

    if (thread_info.index < 100) {
        t_info = malloc(sizeof(struct thread_info));
        if (t_info == NULL) {
            perror("malloc failure");
            pthread_exit(NULL);
        }
        t_info->index = thread_info.index;
        t_info->thread_id = pthread_self();

        pointer_to_struct = malloc(sizeof(struct thread_info));
        if (pointer_to_struct == NULL) {
            perror("malloc failure");
            pthread_exit(NULL);
        }
        pointer_to_struct = t_info;

        usleep(1000);

        pointer_to_struct->index++;

        thread_result = pthread_create(&thread_id, NULL, function, pointer_to_struct);
        if (thread_result) {
            printf("ERROR: return code from pthread_create() is %d\n", thread_result);
            exit(-1);
        }
    }
    pthread_join(thread_info.thread_id, NULL);
    pthread_exit(NULL);
}
int main() {
    pthread_t thread_id;
    int thread_result;
    struct thread_info *t_info;
    struct thread_info *pointer_to_struct;

    t_info = malloc(sizeof(struct thread_info));
    if (t_info == NULL) {
        perror("malloc failure");
        pthread_exit(NULL);
    }
    t_info->index = 0;
    t_info->thread_id = pthread_self();

    pointer_to_struct = malloc(sizeof(struct thread_info));
    if (pointer_to_struct == NULL) {
        perror("malloc failure");
        pthread_exit(NULL);
    }
    pointer_to_struct = t_info;

    usleep(1000);

    pointer_to_struct->index++;

    thread_result = pthread_create(&thread_id, NULL, function, pointer_to_struct);
    if (thread_result) {
        printf("ERROR: return code from pthread_create() is %d\n", thread_result);
        exit(-1);
    }

    pthread_exit(NULL); /*necessario altrimenti l'intero processo finisce a causa del return*/
    return 1;
}