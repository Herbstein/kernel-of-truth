#include <stddef.h>
#include <stdint.h>
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "terminal.h"
#include "kabort.h"
#include "kassert.h"


/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void init_i586()
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	//Allow Interrupt Requests.
	__asm__ __volatile__ ("sti"); 
} 
 
void kernel_main()
{
	init_i586();
	term_initialize();
	term_writestring("Hello, Kernel!");
	for(;;);
}
