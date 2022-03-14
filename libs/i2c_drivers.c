#include "i2c_drivers.h"


#include <stdint.h>
#include <xc.h>
#include <stdio.h>
#include <pic16f18877.h>

/***************************************************************************
 ============================ Public Functions =============================
 ***************************************************************************/

/* Name: I2C_INIT
 * Parameter: void
 * Return: nothing
 * Description: Function initializes the ucontroller for I2C communication
 */


void I2C_Init(void){

    TRISB = 0x06; /* Sets up RB1 SCL and RB2 SDA as inputs */
    SSP2STATbits.SMP = 1;
    SSP2STATbits.CKE = 0;
    SSP2ADD = 0x09; /* Sets I2C clock to 400kHz */
    SSP2CON1bits.SSPEN = 1; /* Enables the SDA and SCL pins as source */
    SSP2CON1bits.SSPM = 0x08; /* I2C Master Mode clock = Fosc / (4 * (SSP1ADD +1)) */

    SSP2DATPPS = 0x0A;   //RB2->MSSP2:SDA2;
    SSP2CLKPPS = 0x09;   //RB1->MSSP2:SCL2;
    RB1PPS = 0x16;   //RB1->MSSP2:SCL2;
    RB2PPS = 0x17;   //RB2->MSSP2:SDA2;

}

/* Name: I2C_Start
 * Parameter: void
 * Return: nothing
 * Description: Function issues a start condition. Start condition is the transition of SDA
 * from a high to low state while SCL is high */


void I2C_Start(void){

    I2C_Idle_Check();
    SSP2CON2bits.SEN = 1;
    while(SSP2CON2bits.SEN == 1);
    SPxIF_flag_polling();

}

/* Name: I2C_Stop
 * Parameter: void
 * Return: nothing
 * Description: Function issues a stop condition. Stop condition is the transition of SDA
 * from a low to high state while SCL is high */

void I2C_Stop(void){

    I2C_Idle_Check();
    SSP2CON2bits.PEN = 1;
    SPxIF_flag_polling();


}

/* Name: I2C_Restart
 * Parameter: void
 * Return: nothing
 * Description: Function issues a reset. Reset is valid any time a stop is valid. Master can
 *  issue reset which has same effect on the slave that a start would in resetting
 *  all slave logic. */

void I2C_Restart(void){

    I2C_Idle_Check();
    SSP2CON2bits.RSEN = 1;

}

/* Name: I2C_Write
 * Parameter: uint8_t
 * Return: nothing
 * Description: Function writes the data. Load slave address first to SSPxBUF. MMSP will shift
 *  notACK to ACKSTAT CON2 register. Then you can load 8 bits of data. notACK is
 * shifted again. */

void I2C_Write(uint8_t I2C_data){

    I2C_Idle_Check();
    SSP2BUF = I2C_data;
    while(SSP2STATbits.BF == 1);
    SPxIF_flag_polling();


    }

/* Name: I2C_Read
 * Parameter: uint8_t
 * Return: nothing
 * Description: Function reads the data I2C. Load slave address to SSPxBUF. MMSP will shift
 *  notACK to ACKSTAT CON2 register. Set the RCEN bit of CON2. After 8th edge,
 * SSPxIF and BF are set.  Master sets ACK in ACKDT bit of CON2 and initiates the
 * ACK be setting ACKEN bit. */

void I2C_Read(uint8_t *rx_data){


    SSP2CON2bits.RCEN = 1;
    while(SSP2STATbits.BF == 0);
    SPxIF_flag_polling();
    *rx_data = SSP2BUF;
    I2C_Idle_Check();
    SSP2CON2bits.ACKEN = 1;
    SSP2CON2bits.ACKDT = 0;
    SPxIF_flag_polling();


}

/***************************************************************************
 ============================  Functions =============================
 ***************************************************************************/

/* Name: I2C_Idle_Check
 * Parameter: void
 * Return: nothing
 * Description: Function checks to see if I2C is idle or transmitting*/

void I2C_Idle_Check(void){

    while((SSP2STAT == 0x04) || (SSP2CON2 == 0x1f));

    /* Bit 2 of SSP1STAT is R/W and OR with SSPxCON2 SEN, RSEN, PEN, RCEN and ACKEN
     * will indicate if the MSSP in is IDEL mode */

}



/* Name: SPxIF_flag_polling
 * Parameter: void
 * Return: nothing
 * Description: Clears the interrupt flag */

void SPxIF_flag_polling(void){

    while(!PIR3bits.SSP2IF){

    }

    PIR3bits.SSP2IF = 0;
}

uint8_t I2C_ACK(){
    return SSP2CON2bits.ACKSTAT;
}
