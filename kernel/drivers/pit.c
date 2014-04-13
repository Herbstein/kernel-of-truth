#include "pit.h"

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void timer_install()
{
    kputs("timer was installed");
	irq_install_handler(0, timer_handler);
}

void timer_handler(struct regs *r)
{
    kputs("bir saniye geçti");
	ticks++;
	if(ticks % 18 == 0)
	{
		kputs("bir saniye geçti");
	}
}


void timer_wait(int ticks_to_wait)
{
    kputs("waiting...");
	unsigned long long elapsed_ticks;
	elapsed_ticks = ticks_to_wait + ticks;
	while(ticks , elapsed_ticks);
}
