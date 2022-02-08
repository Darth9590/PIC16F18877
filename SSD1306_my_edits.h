/******************************************************************************
 SSD1306 OLED driver (SSD1306.c)                                              
                                                                              
 The driver is for I2C mode only.                                             
                                                                                                                                                            
 I2C Bus Write Data Format
 
 Co - Continuation bit ~ set to zero transmission contains only data bytes ~
 D/C# - Data/Command Selection bit ~ Set to 0 defines data as command, set to 1
                                     defines following data byte as data ~
 ACK - Acknowledgment
 SA0 - Slave address bit
 R/W# - Read/Write Selection bit ~ 0 is write, 1 is read ~
 S - Start Condition 
 P - Stop Condition
  
   0 1 2 3 4 5 6   7       0  1   2 3 4 5 6 7
 S|1|1|1|1|0|0| |R/W#|ACK|Co|D/C#| | | | | | |ACK| | | | | | | | |ACK|P|
 slave address                    control byte    MSB ~ data byte ~ LSB
                                                         n >= 0 bytes
 |1|1|1|1|0|0|SA0|R/W#| ~ SSD1306 Slave Address
 SA0 - Provides 
 |Co|D/C|0|0|0|0|0|0|ACK| ~ Control byte 
  
*******************************************************************************/


// ============================ GDDRAM Structure =========================== //
/*            No row re-mapping and column re-mapping
 *
 *     PAGE0 (COM0-COM7)   |________PAGE 0_________|
 *     PAGE0 (COM8-COM15)  |________PAGE 1_________|
 *     PAGE0 (COM16-COM23) |________PAGE 2_________|
 *     PAGE0 (COM24-COM31) |________PAGE 3_________|
 *
 *     S S S S
 *     E E E E
 *     G G G G
 *     0 1.. 127
 *     _ _ _ _
 *    |_|_|_|_| LSB D[0]
 *    |_|_|_|_|
 *    |_|_|_|_|             <----- One Page
 *    |_|_|_|_|
 *    |_|_|_|_|
 *    |_|_|_|_|
 *    |_|_|_|_|
 *    |_|_|_|_| MSB D[7]
 *     */


#include <stdint.h>
#include <stdbool.h>
#include "i2c_drivers.h"

// ============================== Definitions ============================== //

#define I2C_ADDRESS   0xF0 // 0b111100 is 0x3C address followed by two 0 for SAO 
                           // and write

#define SSD1306_129_32
#define LCDWIDTH             128
#define LCDHEIGHT            32

/* Commands */
#define SETCONTRAST          0x81
#define DISPLAYALLON_RESUME  0xA4
#define DISPLAYALLON         0xA5
#define NORMALDISPLAY        0xA6
#define INVERTDISPLAY_       0xA7
#define DISPLAYOFF           0xAE
#define DISPLAYON            0xAF
#define SETDISPLAYOFFSET     0xD3
#define SETCOMPINS           0xDA
#define SETVCOMDETECT        0xDB
#define SETDISPLAYCLOCKDIV   0xD5
#define SETPRECHARGE         0xD9
#define SETMULTIPLEX         0xA8
#define SETLOWCOLUMN         0x00
#define SETHIGHCOLUMN        0x10
#define SETSTARTLINE         0x40
#define MEMORYMODE           0x20
#define COLUMNADDR           0x21
#define PAGEADDR             0x22
#define COMSCANCOM0          0xC0
#define COMSCANCOM_N         0xC8 // Scan from COM[N-1] to COM0 where N is multuplixed ratio
#define SEGREMAP             0xA1
#define CHARGEPUMP           0x8D
#define EXTERNALVCC          0x01
#define SWITCHCAPVCC         0x02

/* Scrolling #defines */
#define ACTIVATE_SCROLL                      0x2F
#define DEACTIVATE_SCROLL                    0x2E
#define SET_VERTICAL_SCROLL_AREA             0xA3
#define RIGHT_HORIZONTAL_SCROLL              0x26
#define LEFT_HORIZONTAL_SCROLL               0x27
#define VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A

/* Global Variables */
uint8_t _vccstate, x_pos = 1, y_pos = 1;


bool wrap = true;

//--------------------------------------------------------------------------//


const char Font[] = {
0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x5F, 0x00, 0x00,
0x00, 0x07, 0x00, 0x07, 0x00,
0x14, 0x7F, 0x14, 0x7F, 0x14,
0x24, 0x2A, 0x7F, 0x2A, 0x12,
0x23, 0x13, 0x08, 0x64, 0x62,
0x36, 0x49, 0x56, 0x20, 0x50,
0x00, 0x08, 0x07, 0x03, 0x00,
0x00, 0x1C, 0x22, 0x41, 0x00,
0x00, 0x41, 0x22, 0x1C, 0x00,
0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
0x08, 0x08, 0x3E, 0x08, 0x08,
0x00, 0x80, 0x70, 0x30, 0x00,
0x08, 0x08, 0x08, 0x08, 0x08,
0x00, 0x00, 0x60, 0x60, 0x00,
0x20, 0x10, 0x08, 0x04, 0x02,
0x3E, 0x51, 0x49, 0x45, 0x3E,
0x00, 0x42, 0x7F, 0x40, 0x00,
0x72, 0x49, 0x49, 0x49, 0x46,
0x21, 0x41, 0x49, 0x4D, 0x33,
0x18, 0x14, 0x12, 0x7F, 0x10,
0x27, 0x45, 0x45, 0x45, 0x39,
0x3C, 0x4A, 0x49, 0x49, 0x31,
0x41, 0x21, 0x11, 0x09, 0x07,
0x36, 0x49, 0x49, 0x49, 0x36,
0x46, 0x49, 0x49, 0x29, 0x1E,
0x00, 0x00, 0x14, 0x00, 0x00,
0x00, 0x40, 0x34, 0x00, 0x00,
0x00, 0x08, 0x14, 0x22, 0x41,
0x14, 0x14, 0x14, 0x14, 0x14,
0x00, 0x41, 0x22, 0x14, 0x08,
0x02, 0x01, 0x59, 0x09, 0x06,
0x3E, 0x41, 0x5D, 0x59, 0x4E,
0x7C, 0x12, 0x11, 0x12, 0x7C,
0x7F, 0x49, 0x49, 0x49, 0x36,
0x3E, 0x41, 0x41, 0x41, 0x22,
0x7F, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x49, 0x49, 0x49, 0x41,
0x7F, 0x09, 0x09, 0x09, 0x01,
0x3E, 0x41, 0x41, 0x51, 0x73,
0x7F, 0x08, 0x08, 0x08, 0x7F,
0x00, 0x41, 0x7F, 0x41, 0x00,
0x20, 0x40, 0x41, 0x3F, 0x01,
0x7F, 0x08, 0x14, 0x22, 0x41,
0x7F, 0x40, 0x40, 0x40, 0x40,
0x7F, 0x02, 0x1C, 0x02, 0x7F,
0x7F, 0x04, 0x08, 0x10, 0x7F,
0x3E, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x09, 0x09, 0x09, 0x06,
0x3E, 0x41, 0x51, 0x21, 0x5E,
0x7F, 0x09, 0x19, 0x29, 0x46
};
const char Font2[] = {
0x26, 0x49, 0x49, 0x49, 0x32,
0x03, 0x01, 0x7F, 0x01, 0x03,
0x3F, 0x40, 0x40, 0x40, 0x3F,
0x1F, 0x20, 0x40, 0x20, 0x1F,
0x3F, 0x40, 0x38, 0x40, 0x3F,
0x63, 0x14, 0x08, 0x14, 0x63,
0x03, 0x04, 0x78, 0x04, 0x03,
0x61, 0x59, 0x49, 0x4D, 0x43,
0x00, 0x7F, 0x41, 0x41, 0x41,
0x02, 0x04, 0x08, 0x10, 0x20,
0x00, 0x41, 0x41, 0x41, 0x7F,
0x04, 0x02, 0x01, 0x02, 0x04,
0x40, 0x40, 0x40, 0x40, 0x40,
0x00, 0x03, 0x07, 0x08, 0x00,
0x20, 0x54, 0x54, 0x78, 0x40,
0x7F, 0x28, 0x44, 0x44, 0x38,
0x38, 0x44, 0x44, 0x44, 0x28,
0x38, 0x44, 0x44, 0x28, 0x7F,
0x38, 0x54, 0x54, 0x54, 0x18,
0x00, 0x08, 0x7E, 0x09, 0x02,
0x18, 0xA4, 0xA4, 0x9C, 0x78,
0x7F, 0x08, 0x04, 0x04, 0x78,
0x00, 0x44, 0x7D, 0x40, 0x00,
0x20, 0x40, 0x40, 0x3D, 0x00,
0x7F, 0x10, 0x28, 0x44, 0x00,
0x00, 0x41, 0x7F, 0x40, 0x00,
0x7C, 0x04, 0x78, 0x04, 0x78,
0x7C, 0x08, 0x04, 0x04, 0x78,
0x38, 0x44, 0x44, 0x44, 0x38,
0xFC, 0x18, 0x24, 0x24, 0x18,
0x18, 0x24, 0x24, 0x18, 0xFC,
0x7C, 0x08, 0x04, 0x04, 0x08,
0x48, 0x54, 0x54, 0x54, 0x24,
0x04, 0x04, 0x3F, 0x44, 0x24,
0x3C, 0x40, 0x40, 0x20, 0x7C,
0x1C, 0x20, 0x40, 0x20, 0x1C,
0x3C, 0x40, 0x30, 0x40, 0x3C,
0x44, 0x28, 0x10, 0x28, 0x44,
0x4C, 0x90, 0x90, 0x90, 0x7C,
0x44, 0x64, 0x54, 0x4C, 0x44,
0x00, 0x08, 0x36, 0x41, 0x00,
0x00, 0x00, 0x77, 0x00, 0x00,
0x00, 0x41, 0x36, 0x08, 0x00,
0x02, 0x01, 0x02, 0x04, 0x02
};

void I2C_Command(uint8_t data){
    
    uint8_t control = 0x00; // Co = 0 D/C# = 0 sending command
    
    I2C_Start();    // Start bit
    I2C_Write(I2C_ADDRESS); // Write address
    I2C_Write(control); // Write command mode
    I2C_Write(data); // Command
    I2C_Stop();     // Stop Bit
    
    
    
}

void SSD1306_Init(){
    I2C_Command(DISPLAYOFF);     // 0xAE
    I2C_Command(SETMULTIPLEX);  // 0xA8
    I2C_Command(0x1F);     // Sets MUX to 31 for 128x32 OLED. This means PAGE0 to PAGE3
                           // PAGE0 (COM0-COM7)
                           // PAGE1 (COM8-COM15)
                           // PAGE2 (COM16-COM23)
                           // PAGE3 (COM24-COM31)
    I2C_Command(SETDISPLAYOFFSET);     // 0xD3 Sets display RAM start line 0 - 63 with 0b00000
                                       // Example to move COM 16 to COM 0, 0b10000 || 0x10
    I2C_Command(0x00); //Offset is COM0
    I2C_Command(SETSTARTLINE);     //Sets display RAM start line register from 0-63
                                   // opcode is 0x40 to 0x7F which looks like 0b01XXXXX test
    I2C_Command(SEGREMAP);     // 0xA0 Wll map SEG0 (RESET) to either column address 0 (0xA0) or column address 127 (0xA1)
    I2C_Command(COMSCANCOM0);  // 0xC0 normal mode scan from COM0 to COM[N-1]
    I2C_Command(SETCOMPINS);  // 0xDA referenced page 44 in datasheet. opcode is 0b00XX0010. A[4]=0b sequential com pin configuration ~ A[4]=1b alernative come pin
                              // A[5]=0b Disable COM left/right remap ~ A[5]=1b Enable COM left/right remap
    I2C_Command(0x22);        // A[4]=0 A[5]=1
    I2C_Command(SETCONTRAST); // 0x81 double byte command, select 1 out of 256. 0x7F resets
    I2C_Command(0x7F);        // reset contrast
    I2C_Command(DISPLAYALLON); // 0xA5 Entire display ON output ignores the RAM content
    I2C_Command(NORMALDISPLAY); // 0xA6 for normal or 0xA7 for reverse. In normal, RAM data of 1 indicates an "ON" pixel while reverse a 0 indicates an "OFF" pixel
    I2C_Command(SETDISPLAYCLOCKDIV); // 0xD5 Display Clock Divide Ratio A[3:0] divide ration is 1 to 16.
                                     // Oscillator frequency A[7:4] defualt value is 1000b.
    I2C_Command(0x80);        // dafualt value ~380kHz
    I2C_Command(CHARGEPUMP); // 0x8D A[2]=0b disbale charge pump A[2]=1b enable charge pump opcode 010X00b
    I2C_Command(0x14);        //enable charge pump
    I2C_Command(DISPLAYON);   //Display ON normal mode
    
    
}

void ClearDisplay(){
    
    I2C_Command(COLUMNADDR); // set start column
    I2C_Command(0);          // set SEG0
    I2C_Command(PAGEADDR);   // Set start row and end row 3bits A[2:0] range 0-7d B[2:0] 0-7d
    I2C_Command(0);          // PAGE0
    I2C_Command(3);          // End at PAGE3 for 32 row OLED
    
    I2C_Start();          // Start bit
    I2C_Write(I2C_ADDRESS);   // write address of device
    I2C_Write(SETSTARTLINE);  // 0x40 Set display RAM start line register. Opcode 01xxxxxx range 0x40 ~ 7F.

    for(uint16_t i = 0; i < LCDHEIGHT * LCDWIDTH / 8; i++) // assign i as unisgned 16 and if it is less then ((128 *32)/8)= 512
        I2C_Write(0); // write 0 to clear display
    I2C_Stop(); // Sopt bit
               
}

void GotoXT(uint8_t x, uint8_t y){
 
    if((x > 21) || y > 8)
        return;
    x_pos = x;
    y_pos = y;
}

void PutC(uint8_t c) {
  uint8_t font_c;
  if((c < ' ') || (c > '~'))
    c = '?';
  I2C_Command(COLUMNADDR);
  I2C_Command(6 * (x_pos - 1));
  I2C_Command(6 * (x_pos - 1) + 4); // Column end address (127 = reset)

  I2C_Command(PAGEADDR);
  I2C_Command(y_pos - 1); // Page start address (0 = reset)
  I2C_Command(y_pos - 1); // Page end address
  
  I2C_Start();
  I2C_Write(I2C_ADDRESS);
  I2C_Write(, 0x40);
  
  for(uint8_t i = 0; i < 5; i++ ) {
    if(c < 'S')
      font_c = Font[(c - 32) * 5 + i];
    else
      font_c = Font2[(c - 'S') * 5 + i];
  
    I2C_Write(font_c);
  }
  I2C_Stop();

  x_pos = x_pos % 21 + 1;
  if (wrap && (x_pos == 1))
    y_pos = y_pos % 8 + 1;

}

