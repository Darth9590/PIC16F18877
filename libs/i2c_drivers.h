/*RCJK I2C Drivers PIC16F18877*/

#ifndef I2C_DRIVERS_H
#define I2C_DRIVERS_H

#include <stdint.h>


// ========================== How the signal works ========================= //
/*    SEN=1  SEN=0       ADDRESS                         R/W  ACK=0                 
 *      ____      __    __    __    __    __    __    __    
 * SDA |    |    |  |  |  |  |  |  |  |  |  |  |  |  |  |  
 *     |    |____|A7|__|A6|__|A5|__|A4|__|A3|__|A2|__|A1|__________
 
 
 */
/***************************************************************************
 =========================== Function Prototypes ===========================
 ***************************************************************************/

void I2C_Init(void);
void I2C_Idle_Check(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Restart(void);
void I2C_Read(uint8_t *rx_data);
void I2C_Write(uint8_t I2C_data);
void SPxIF_flag_polling(void);
uint8_t I2C_ACK(void);



#endif
