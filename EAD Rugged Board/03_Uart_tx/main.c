#include "transmitter_uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
    char *portname = "/dev/ttyS3";
    int fd;
    char input[100]; // Buffer for user input

    // Open serial port
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }
    // Set serial port attributes
    if (set_interface_attribs(fd, B9600) < 0) {
        printf("Error setting serial port attributes\n");
        close(fd);
        return -1;
    }
   while (1) {
        // Get input from user
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
  // Transmit data
        uart_transmit(fd, input, strlen(input));
     // Sleep for a short duration before next iteration
        usleep(100000); // 100 ms
    }
    // Close serial port
    close(fd);
    return 0;
}
