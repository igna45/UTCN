#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include <pthread.h>
#include <semaphore.h>

sem_t sem_p5;
sem_t sem_t4_4_started, sem_t4_1_ended;
sem_t sem_p5_concurrency_limit;
sem_t sem_t5_11_running;
sem_t sem_p5_concurrency_limit, sem_t5_11_special;
int running_threads_count = 0;

pthread_mutex_t running_threads_mutex;
pthread_cond_t running_threads_cond;


void *thread_function_p4_1(void *arg) {

    sem_wait(&sem_t4_4_started);
    info(BEGIN, 4, 1);
    info(END, 4, 1);
    sem_post(&sem_t4_1_ended);

    return NULL;
}

void *thread_function_p4_2(void *arg) {

    info(BEGIN, 4, 2);
    info(END, 4, 2);

    return NULL;
}

void *thread_function_p4_3(void *arg) {

    info(BEGIN, 4, 3);
    info(END, 4, 3);

    return NULL;
}

void *thread_function_p4_4(void *arg) {

    info(BEGIN, 4, 4);
    sem_post(&sem_t4_4_started);
    sem_wait(&sem_t4_1_ended);
    info(END, 4, 4);

    return NULL;
}

void create_threads_P4()
{
    pthread_t thread_p4_1, thread_p4_2, thread_p4_3, thread_p4_4;

        pthread_create(&thread_p4_4, NULL, thread_function_p4_4, NULL);
        pthread_create(&thread_p4_1, NULL, thread_function_p4_1, NULL);
        pthread_create(&thread_p4_2, NULL, thread_function_p4_2, NULL);
        pthread_create(&thread_p4_3, NULL, thread_function_p4_3, NULL);

        pthread_join(thread_p4_1, NULL);
        pthread_join(thread_p4_2, NULL);
        pthread_join(thread_p4_3, NULL);
        pthread_join(thread_p4_4, NULL);
}

void *thread_function_p5(void *arg) {
    int thread_id = *((int *)arg);

    pthread_mutex_lock(&running_threads_mutex);
    running_threads_count++;
    if (running_threads_count >= 4) {
        pthread_cond_signal(&running_threads_cond);
    }
    pthread_mutex_unlock(&running_threads_mutex);

    sem_wait(&sem_p5_concurrency_limit);

    info(BEGIN, 5, thread_id);
    info(END, 5, thread_id);

    sem_post(&sem_p5_concurrency_limit);

    return NULL;
}

void *thread_function_p5_11(void *arg) {
    int thread_id = *((int *)arg);

    pthread_mutex_lock(&running_threads_mutex);
    while (running_threads_count < 5) {
        pthread_cond_wait(&running_threads_cond, &running_threads_mutex);
    }
    pthread_mutex_unlock(&running_threads_mutex);

    sem_wait(&sem_t5_11_special);

    info(BEGIN, 5, thread_id);
    info(END, 5, thread_id);

    sem_post(&sem_t5_11_special);

    return NULL;
}

void create_threads_P5() {
    pthread_t threads[50];
    int thread_ids[50];

    for (int i = 1; i <= 50; i++) {
        thread_ids[i - 1] = i;
        if (i == 11) {
            pthread_create(&threads[i - 1], NULL, thread_function_p5_11, (void *)&thread_ids[i - 1]);
        } else {
            pthread_create(&threads[i - 1], NULL, thread_function_p5, (void *)&thread_ids[i - 1]);
        }
    }

    for (int i = 0; i < 50; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main(int argc, char **argv)
{
    init();
    sem_init(&sem_t4_4_started, 0, 0);
    sem_init(&sem_t4_1_ended, 0, 0);
    sem_init(&sem_p5_concurrency_limit, 0, 5);
    sem_init(&sem_t5_11_special, 0, 1);
    pthread_mutex_init(&running_threads_mutex, NULL);
    info(BEGIN, 1, 0);

    //process P2
    if (fork() == 0) {

        info(BEGIN, 2, 0);

        //process P3 and P4
        if (fork() == 0) {

            info(BEGIN, 3, 0);

            //process P5
            if (fork() == 0) {

                info(BEGIN, 5, 0);
    		create_threads_P5();
    		info(END, 5, 0);
                exit(0);
            }

            wait(NULL);

            info(END, 3, 0);
            exit(0);
        } else {
            if (fork() == 0) {

                info(BEGIN, 4, 0);
                create_threads_P4();

                //process P6
                if (fork() == 0) {

                    info(BEGIN, 6, 0);

                    //process P7
                    if (fork() == 0) {

                        info(BEGIN, 7, 0);
                        info(END, 7, 0);
                        exit(0);
                    }

                    wait(NULL);

                    info(END, 6, 0);
                    exit(0);
                }

                //P6 terminate
                wait(NULL);

                info(END, 4, 0);
                exit(0);
            }
        }

        //P3 and P4 terminate
        wait(NULL);
        wait(NULL);

        info(END, 2, 0);
        exit(0);
    }

    //P2 terminate
    wait(NULL);

    info(END, 1, 0);

    sem_destroy(&sem_t4_4_started);
    sem_destroy(&sem_t4_1_ended);
    sem_destroy(&sem_p5_concurrency_limit);
    sem_destroy(&sem_t5_11_special);

    return 0;
}