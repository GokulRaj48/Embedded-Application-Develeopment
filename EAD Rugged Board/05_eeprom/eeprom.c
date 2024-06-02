#include "eeprom.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// EEPROM path
static const char EEPROM_FILE_BOARD[] = "/sys/class/i2c-adapter/i2c-0/0-0050/eeprom";

// Read board EEPROM
int ReadBoardEEPROM(cBoardEEPROM* boardEEPROM) {
    int Fd = 0;
    int ReadBytes = 0;
    memset(boardEEPROM, 0, sizeof(*boardEEPROM));

    if ((Fd = open(EEPROM_FILE_BOARD, O_RDONLY)) < 0) {
        printf("EEPROM_FILE_BOARD open error: %s\n", strerror(errno));
        return -1;
    }

    ReadBytes = read(Fd, boardEEPROM, sizeof(*boardEEPROM));
    if (ReadBytes < 0) {
        printf("EEPROM_FILE_SOM read error: %s\n", strerror(errno));
        close(Fd);
        return -1;
    }
    close(Fd);

    return 0;
}

// Write board EEPROM 
void WriteBoardEEPROM(cBoardEEPROM* boardEEPROM) {
    int Fd = 0;
    int WriteBytes = 0;

    if ((Fd = open(EEPROM_FILE_BOARD, O_WRONLY)) < 0) {
        printf("EEPROM_FILE_BOARD open error: %s\n", strerror(errno));
        return;
    }

    WriteBytes = write(Fd, boardEEPROM, sizeof(*boardEEPROM));
    if (WriteBytes < sizeof(*boardEEPROM)) {
        if (WriteBytes < 0)
            printf("EEPROM_FILE_BOARD write error : %s\n", strerror(errno));
        else
            printf("EEPROM_FILE_BOARD write error : Partial write to EEPROM (%d)\n", WriteBytes);
    }

    close(Fd);
}

