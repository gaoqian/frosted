#include "frosted.h"
#define IDLE() while(1){do{}while(0);}

/* The following needs to be defined by
 * the application code
 */
extern void init(void *arg);

int (*kdbg_write)(int, void *, int) = NULL;
    

void kdbg_set_write(int (*wr)(int, void *, int))
{
    kdbg_write = wr;
}

int _write(int file, char *ptr, int len) {
    if (kdbg_write) {
        return kdbg_write(file, ptr, len);
    }
}

void frosted_init(void)
{
    SystemInit(); /* SystemInit() -> Board_SystemInit() */
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);
    Board_Init();

    syscalls_init();
    vfs_init();
    kernel_task_init();
    frosted_scheduler_on();
}

/* OS entry point */
void main(void) 
{
    volatile int ret = 0;

    frosted_init();
    
    /* Create "init" task */
    if (task_create(init, (void *)0, 2) < 0)
        IDLE();

    while(1) {
        /* This is the kernel main loop */   
    }
}

