#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <stdbool.h>
#include <stddef.h>

#define NO_PARITY (0<<3)
#define EVEN_PARITY ((1<<3)|(0<<4)|(0<<5))
#define ODD_PARITY ((1<<3)|(1<<4)|(0<<5))
#define HIGH_PARITY ((1<<3)|(0<<4)|(1<<5))
#define LOW_PARITY ((1<<3)|(1<<4)|(1<<5))

#define ONE_STOP_BIT (0<<2)
#define TWO_STOP_BITS (1<<2)

#define DATA_BITS_5 (0<<0)|(0<<1)
#define DATA_BITS_6 (1<<0)|(0<<1)
#define DATA_BITS_7 (0<<0)|(1<<1)
#define DATA_BITS_8 (1<<0)|(1<<1)

#define DATA_AVAIL 0x1
#define TRANSMITTER_EMPTY 0x2
#define ERROR 0x4
#define STATUS_CHANGE 0x8

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8


void initialize_serial_port(int com_port);

bool is_data_available(int com_port);

char read_serial(int com_port);

void write_serial(int com_port, char data);

void write_serial_string(int com_port, char *data);

void read_serial_string(int com_port, char *buf, size_t len);


#endif