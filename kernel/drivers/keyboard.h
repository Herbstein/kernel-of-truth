#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../io.h"
#include "../irq.h"
#include "../registers.h"
#include "../terminal.h"

//This array represents the scancodes for the QWERTY layout
extern unsigned char qwerty[128];

//Installs the keyboard to trigger when IRQ1 is triggered.
void keyboard_install();

// Handles the keyboard interrupt
void keyboard_handler(struct regs *r);

#endif
