#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *threadFunc(void *arg)
{
    char *str;
    int i = 0;

    str=(char*)arg;

    while(i < 15)
    {
        usleep(1);
        printf("threadFunc says: %s\n",str);
        ++i;
    }

    int* ret = (int*)malloc(sizeof(int));
    *ret = 42;
    pthread_exit(ret);
}

int main(void)
{
    pthread_t pth;    // this is our thread identifier
    int i = 0;

    pthread_create(&pth, NULL, threadFunc, "foo");
    
    while(i < 10)
    {
        usleep(1);
        printf("main is running...\n");
        ++i;
    }

    printf("main waiting for thread to terminate...\n");
    int *ret = NULL;
    pthread_join(pth, (void**)&ret);
    printf("%d\n", *ret);

    return 0;
}
