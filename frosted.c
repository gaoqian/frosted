#include "frosted.h"

#define IDLE() while(1){do{}while(0);}


void frosted_init(void)
{
    SystemInit(); /* SystemInit() -> Board_SystemInit() */
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
    Board_Init();
    syscalls_init();
}


void task0(void *arg)
{
    volatile int i = (int)arg;
    while(1) {
        i = jiffies;
    }
    (void)i;
}

void task1(void *arg)
{
    volatile int i = (int)arg;
    while(1) {
        i = jiffies;
    }
    (void)i;
}

void main(void) 
{
    volatile int ret = 0;

    frosted_init();

    /* c-lib and init test */
    uint32_t * temp = malloc(32);

    /* VFS test */
    struct fnode *dev = fno_create(NULL, "dev",fno_search("/"));
    struct fnode *null = fno_create(NULL, "null", dev);

    struct fnode *devnull = fno_search("/dev/null");
    


    sys_test(0xaa, 0xbb, 0xcc, 0xdd, 0xee);
    //sys_sleep(3000);
    //ret = sys_setclock(10);

    if (task_create(task0, (void *)42, 1) < 0)
        IDLE();
    if (task_create(task1, (void *)42, 1) < 0)
        IDLE();

    free(temp);
    
    /* Start the scheduler */
    sys_start();

    while(1) ;
}

