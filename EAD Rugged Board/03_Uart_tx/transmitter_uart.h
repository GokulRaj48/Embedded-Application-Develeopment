#ifndef UART_H
#define UART_H
#include <stdio.h>
#include <termios.h>
// Function prototypes
int set_interface_attribs(int fd, int speed);
void uart_transmit(int fd, const char* data, int size);
#endif
