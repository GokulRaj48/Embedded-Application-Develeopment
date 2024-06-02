#include "transmitter_uart.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
// Function to set serial port attributes
int set_interface_attribs(int fd, int speed) {
    struct termios tty;
 if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }
cfsetispeed(&tty, (speed_t)speed);
 cfsetospeed(&tty, (speed_t)speed);
 tty.c_cflag |= (CLOCAL | CREAD);    // ignore modem controls, enable receiver
 tty.c_cflag &= ~CSIZE;               // clear character size mask
 tty.c_cflag |= CS8;                  // 8-bit characters
 tty.c_cflag &= ~PARENB;              // no parity bit
  tty.c_cflag &= ~CSTOPB;              // one stop bit
  tty.c_cflag &= ~CRTSCTS;             // no hardware flow control
  tty.c_iflag = IGNPAR;                // ignore parity errors
  tty.c_oflag = 0;                      // no output processing
  tty.c_lflag = 0;                      // no input processing
  tty.c_cc[VMIN] = 0;                  // read doesn't block
  tty.c_cc[VTIME] = 5;                 // 0.5 seconds read timeout
 if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
 }

    return 0;
}
// Function to transmit data over UART
void uart_transmit(int fd, const char* data, int size) {
    int wlen = write(fd, data, size);
    if (wlen != size) {
        printf("Error writing to serial port\n");
    }
}
