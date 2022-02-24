/*
 * File:   main.c
 * Author: ryan
 *
 * Created on February 18, 2022, 4:28 PM
 */


// PIC16F18877 Configuration Bit Settings


#include <xc.h>
#include <pic16f18877.h>
#include <stdbool.h>

#include "../PIC16F18877/libs/SSD1306_drivers.h"  // Include SSD1306 OLED driver source code
#include "../PIC16F18877/libs/i2c_drivers.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/i2c2_master.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"

#define READ 0x51
#define WRITE 0x50

uint8_t highbyte;
uint8_t lowbyte;
uint8_t data;

/* void oled_put(char* c){
    while(*c != '\0'){
        PutC(*c);
    }
} 
 */

void send_string(const char *x)
{
    while (*x)
    {
        EUSART_Write(*x++);
    }
}

void writeByte( char slaveAddress, char highByte, char lowByte, char data){
    
    SSP2CON2bits.SEN = 1;
    
    while(SSP2CON2bits.SEN);
    PIR3bits.SSP2IF = 0;
    
    SSP2BUF = slaveAddress;
    while(!SSP2BUF);
    PIR3bits.SSP2IF =0 ;
    if( SSP2CON2bits.ACKSTAT){
        SSP2CON2bits.PEN = 1;
        while (SSP2CON2bits.PEN);
        return;
    }
    
       SSP2BUF = highByte;
    while(!SSP2BUF);
    PIR3bits.SSP2IF =0 ;
    if( SSP2CON2bits.ACKSTAT){
        SSP2CON2bits.PEN = 1;
        while (SSP2CON2bits.PEN);
        return;
    }
       SSP2BUF = lowByte;
    while(!SSP2BUF);
    PIR3bits.SSP2IF =0 ;
    if( SSP2CON2bits.ACKSTAT){
        SSP2CON2bits.PEN = 1;
        while (SSP2CON2bits.PEN);
        return;
    }
       SSP2BUF = data;
    while(!SSP2BUF);
    PIR3bits.SSP2IF =0 ;
    if( SSP2CON2bits.ACKSTAT){
        SSP2CON2bits.PEN = 1;
        while (SSP2CON2bits.PEN);
        return;
    }
    
   
    
}

void main(void) {
   
    data = 0xAA;
   
    SYSTEM_Initialize();
  
    
    I2C2_Initialize();
    
   
    SSP2CON1bits.SSPEN = 0;  
    
       
   writeByte(0xA0, 0x12, 0x34, 0x78);
    
    
    //I2C2_WriteNBytes(0x50, data, 2);
    
     
    
 
    

    
  
    
    return;

    
}
