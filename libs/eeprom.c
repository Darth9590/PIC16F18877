/***************************************************************************
 ============================= Waveforms ==================================
***************************************************************************/
/* Write Sequence

SCL  1                                               9
_    __    __    __    __    __    __    __    __    __
 |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
 |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |__|  |

SDA Write Address MSB
    ___         ___                             _
   / 1 \    0  / 1 \   0     A2    A1    A0   R/W    ACK /
__/     \_____/     \___________________________________/

SDA First Word Address MSB
  _____  _____  _____  _____  _____  _____  _____  ____  ____
 /  X  \/  X  \/  X  \/  X  \/ A12 \/ A11 \/ A10 \/ A9 \/ A8 \  ACK
/______/\_____/\_____/\_____/\_____/\_____/\_____/\____/\____/\_____

SDA Second Word Address MSB
  ____  ____  ____  ____  ____  ____  ____  ____
 / A7 \/ A6 \/ A5 \/ A4 \/ A3 \/ A2 \/ A1 \/ A0 \  ACK
/_____/\____/\____/\____/\____/\____/\____/\____/\_____

SDA Data MSB
  ____  ____  ____  ____  ____  ____  ____  ____        _______
 / D7 \/ D6 \/ D5 \/ D4 \/ D3 \/ D2 \/ D1 \/ D0 \  ACK / STOP by Master
/_____/\____/\____/\____/\____/\____/\____/\____/\____/

SDA Read Address MSB

    ___         ___                           _____
   / 1 \    0  / 1 \   0     A2    A1    A0  / R/W \  ACK  /
__/     \_____/     \_______________________/       \_____/
 */

/***************************************************************************
 ============================= Includes ==================================
***************************************************************************/

#include "eeprom.h"
#include "i2c_drivers.h"
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include <stdlib.h>

/***************************************************************************
 ============================ Global Variables =============================
***************************************************************************/

#define _XTAL_FREQ (16000000)

uint8_t data, rx_data, addr1, addr2;


/***************************************************************************
 ============================= Funcions ===================================
***************************************************************************/

/* Name: byte_write
 * Parameter: uint8_t addr1 - First word address location in EEPROM
 *            uint8_t addr2 - Second word address location in EEPROM
 *            uint8_t data - byte of data being written to EEPROM
 * Return: nothing
 * Description: Function takes the above three parameters and will start I2C comms then
 *              write at a specific address location user specified. Finally the data is
 *              then written to that location.
 */


void byte_write(uint8_t addr1, uint8_t addr2, uint8_t data){

    I2C_Start();
    I2C_Write(EEPROMWRITE); // I2C address of EEPROM
    I2C_Write(addr1);
    I2C_Write(addr2);
    I2C_Write(data);
    I2C_Stop();
    __delay_ms(10);

}

/* Name: page_write
 * Parameter: uint8_t addr1 - First word address location in EEPROM
 *            uint8_t addr2 - Second word address location in EEPROM
 *            uint8_t data - byte of data being written to EEPROM
 * Return: nothing
 * Description: Function takes the above three parameters and will start I2C comms then
 *              write at a specific address location user specified. Finally the data is
 *              then written to that location.
 */

void page_write(uint8_t addr1, uint8_t addr2, uint8_t data, uint8_t count){

     I2C_Start();
     I2C_Write(EEPROMWRITE);
     I2C_Write(addr1);
     I2C_Write(addr2);
     I2C_Write(data);
        
    
    
    for(int a = 0; a < count; a++){ // Loop 128 times to write to full EEPROM
       
        for(int b = 0; b < 32; b++){ // Loop 32 times writing test pattern
            I2C_Write(data);
            printf("%X %X %X  \n\r",addr1, addr2, data);
           
            if(addr2 < 0xFF){
                addr2++;
            }
            else {                    
                addr1++;
                addr2 = 0x00;
            }
            
        }  
            
            
       }   
        I2C_Stop();
        __delay_ms(10); // Delay for writing time
    }


uint8_t current_addr(void){


    I2C_Start();
    I2C_Write(EEPROMREAD);
    I2C_Single_Read(&rx_data);
    I2C_Stop();
    return rx_data;

}

uint8_t random_read(uint8_t addr1, uint8_t addr2){

       
    I2C_Start();
    I2C_Write(EEPROMWRITE);
    I2C_Write(addr1);
    I2C_Write(addr2);
    I2C_Start(); // Need a new start to read
    I2C_Write(EEPROMREAD);
    I2C_Single_Read(&rx_data);
    I2C_Stop();

    
    return rx_data;

}

void sequential_read(uint8_t addr1, uint8_t addr2, int loops){


    I2C_Start();
    I2C_Write(EEPROMWRITE);
    I2C_Write(addr1);
    I2C_Write(addr2);
    I2C_Start();
    I2C_Write(EEPROMREAD);
    

    for(uint8_t a = 0; a < loops; a++){
        
        for(uint8_t b = 0; b < 32; b++){
            I2C_Continious_Read(&rx_data, b);

        printf("0x%X%X 0x%X\r\n", addr1, addr2, rx_data);
        
           if(addr2 < 0xFF){
                addr2++;
            }
            else {
                 addr1++;
                 addr2 = 0x00;
            }
        }

    }
}
 


