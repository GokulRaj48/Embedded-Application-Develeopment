#ifndef BOARD_EEPROM_H
#define BOARD_EEPROM_H

// EEPROM content format
typedef struct _cBoardEEPROM {
    char ModuleID[16];
    char SerialNo[16];
    char data[512];
} cBoardEEPROM;

// Function declarations
int ReadBoardEEPROM(cBoardEEPROM* boardEEPROM);
void WriteBoardEEPROM(cBoardEEPROM* boardEEPROM);

#endif /* BOARD_EEPROM_H */


