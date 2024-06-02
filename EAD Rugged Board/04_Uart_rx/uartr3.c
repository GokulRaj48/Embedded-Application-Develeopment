#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int set_interface_attribs(int fd, int speed) {
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetispeed(&tty, (speed_t)speed);
    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;                 /* 8-bit characters */
    tty.c_cflag &= ~PARENB;             /* no parity bit */
    tty.c_cflag &= ~CSTOPB;             /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;            /* no hardware flow control */

    tty.c_iflag = IGNPAR;
    tty.c_lflag = 0;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

int main() {
    char *portname = "/dev/ttyS3";
    int fd;
    int wlen;
    int rdlen;
    int ret;

    char arr[BUFFER_SIZE];
    unsigned char buf[BUFFER_SIZE];
    unsigned char rbuf[BUFFER_SIZE];

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    set_interface_attribs(fd, B9600);

    while (1) {
        // Receive data
        rdlen = read(fd, rbuf, sizeof(rbuf));
        if (rdlen < 0) {
            printf("Error reading from %s: %s\n", portname, strerror(errno));
            continue;
        } else if (rdlen == 0) {
            printf("No data received\n");
            continue;
        } else {
            rbuf[rdlen] = '\0'; // Null terminate the received data
            printf("Received: %s\n", rbuf);
            memset(rbuf, 0, sizeof(rbuf)); // Clear the buffer
        }
    }

    close(fd);

    return 0;
}

