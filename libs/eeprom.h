#ifndef EEPROM_H_
#define EEPROM_H_

/***************************************************************************
 ============================ Device Information ==========================
***************************************************************************/
/* 32-Kbit (4096 by 8)
 * write cycle 5mS
 * 32-byte page write mode
 * 32K is organized into 128 pages of 32 bytes
 * VCC 1.7 to 5 VDC
 *  */

/***************************************************************************
 ================================= Includes ===============================
***************************************************************************/

#include <stdint.h>


/***************************************************************************
 ================================= Defines ================================
***************************************************************************/

#define EEPROMWRITE 0xA0 // MSB nibble is 1010 followed by A2-A0 and finally a read
                          // write bite for the whole byte. Here A2-A0 is grounded
#define EEPROMREAD 0xA1 // A read sequence is high thus the 0x1
#define TEST_PATTERN 0x46

/***************************************************************************
 ======================== Function Prototypes =============================
***************************************************************************/

void byte_write(uint8_t addr1, uint8_t addr2, uint8_t data);
void page_write(uint8_t addr1, uint8_t addr2, uint8_t data, uint8_t count);
uint8_t current_addr(void);
uint8_t random_read(uint8_t addr1, uint8_t addr2);
void sequential_read(uint8_t addr1, uint8_t addr2, int loops);

#endif // EEPROM_H_
