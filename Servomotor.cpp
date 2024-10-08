//Code1:

#include “mbed.h”
#include “rtos.h”
DigitalOut led1(PC_10);
DigitalOut led2(PC_11);
Thread Thread1, Thread2;

void led1_thread()
{
while(1)
{
led1=!led1;
Thread::wait(1000);
}
}
void led2_Thread()
{
while(1)
{
led2=!led2;
Thread::wait(500);
}
}
int main()
{
Thread1.start(led1_thread);
Thread2.start(led2_thread);
Thread::wait(10000);
Thread1.terminate();
while(1);
}

//Code2:
#include “mbed.h”
#include “rtos.h”
Serial PC(USBTX,USBRX);
Thread Thread1, Thread2;
Mutex mutex1;
int i=0;
void count(int i)
{
mutex1.lock();
PC.printf(“Count value before delay: %d\n\r”, i);
Thread::wait(1000);
PC.printf(“Count value after delay:%d\n\r”,i);
mutex1.unlock();
}
void increment ()
{
i=i+1;
count(i);
}
void decrement()
{
i=i-1;
count(i);
}
int main()
{
Thread1.start(increment);
Thread2.start(decrement);
Thread1.join();
Thread2.join();
}

Code3:

#include “mbed.h”
#include “rtos.h”
DigitalOut LED(PC_11);
DigitalOut SW(PC_10);
Thread Thread1;
void Flash()
{
Thread::signal_wait(0x1);
while(1)
{
LED=!LED;
Thread::wait(1000);
}
}
int main()
{
Thread1.start(Flash);
while(SW==0);
Thread1.signal_set(0x1);
while(1);
}

