#include "eeprom.h"
#include <stdio.h>
#include <string.h>

// Main routine
int main(int argc, char *argv[]) {
    int Result = 0;
    cBoardEEPROM boardEEPROM, board;

    strcpy(boardEEPROM.ModuleID, "RBEEPROM1234");
    strcpy(boardEEPROM.SerialNo, "112233445566");
    strcpy(boardEEPROM.data, "Phytec Embedded Pvt Ltd");

    WriteBoardEEPROM(&boardEEPROM);

    memset(&board, 0x00, sizeof(board));

    // Read EEPROM 
    Result = ReadBoardEEPROM(&board);

    printf("[EEPROM content]=============================\n");
    printf("Module ID : %s\n", board.ModuleID);
    printf("Serial NO : %s\n", board.SerialNo);
    printf("Data      : %s\n", board.data);

    return 0;
}



