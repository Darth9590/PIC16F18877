#ifndef THERMO_H_
#define THERMO_H_

#include <stdint.h>

/***************************************************************************
 ================================= DEFINES =================================
***************************************************************************/
//                                                      _
#define WRITE 0x90; // Address is 48 plus one bit for R/W, low for write
#define READ 0x91; // High for read



/**************************************************
 * Register Map and Pointer Addresses
 * P2 P1 P0 Register
 * 0  0  0  Temeprature Register (read only)
 * 0  0  1  Configuration Register (read/write)
 * 0  1  0  TLOW Register (read/write)
 * 0  1  1  THIGH Register (read/write)
 * 1  0  0  One Shot Register (write only)
 **************************************************/

#define TEMP_READ 0x00
#define TEMP_CONFIG 0x01

/******config bits*******/
#define SD 0x01 // Enable Shutdown mode
#define TM 0x02 // ALERT is in interupt mode other wise ALERT is comparator mode 0x00
#define POL 0x04 // ALERT is active high otherwise active low 0x00
#define FQ1 0x00 // Fault queue to trigger ALERT IE # of times
#define FQ2 0x08
#define FQ4 0x10
#define FQ6 0x18
#define OS 0x20 // One short mode, SD = 0x00 device is in shutdown but any value written to oneshot
                // register initiates a conversion

#define TEMP_LOW 0x02
#define TEMP_HIGH 0x03
#define TEMP_ONESHOT 0x04



/***************************************************************************
 =========================== Function Prototypes ===========================
 ***************************************************************************/


void Config_temp(uint8_t one_shot, uint8_t Fault_count, uint8_t Alert,
                 uint8_t Alert_control, uint8_t Shutdown);
void Read_temp(void);








/***************************************************************************
 =========================== Function Prototypes ===========================
 ***************************************************************************/


#endif // THERMO_H_
