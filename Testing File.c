#include <stdio.h>
#include <stdint.h>



const char Font[] = {
0x00, 0x00, 0x00, 0x00, 0x00, // sp 32d
0x00, 0x00, 0x2f, 0x00, 0x00, // ! 33d
0x00, 0x07, 0x00, 0x07, 0x00, // " 34d
0x14, 0x7f, 0x14, 0x7f, 0x14, // # 35d
0x24, 0x2a, 0x7f, 0x2a, 0x12, // $ 36d
0x23, 0x13, 0x08, 0x64, 0x62, // % 37d
0x36, 0x49, 0x55, 0x22, 0x50, // & 38d
0x00, 0x05, 0x03, 0x00, 0x00, // ' 39d
0x00, 0x1c, 0x22, 0x41, 0x00, // ( 40d
0x00, 0x41, 0x22, 0x1c, 0x00, // ) 41d
0x14, 0x08, 0x3E, 0x08, 0x14, // * 42d
0x08, 0x08, 0x3E, 0x08, 0x08, // + 43d
0x00, 0x00, 0xA0, 0x60, 0x00, // , 44d
0x08, 0x08, 0x08, 0x08, 0x08, // - 45d
0x00, 0x60, 0x60, 0x00, 0x00, // . 46d
0x20, 0x10, 0x08, 0x04, 0x02, // / 47d
0x3E, 0x51, 0x49, 0x45, 0x3E, // 0 48d
0x00, 0x42, 0x7F, 0x40, 0x00, // 1 49d
0x42, 0x61, 0x51, 0x49, 0x46, // 2 50d
0x21, 0x41, 0x45, 0x4B, 0x31, // 3 51d
0x18, 0x14, 0x12, 0x7F, 0x10, // 4 52d
0x27, 0x45, 0x45, 0x45, 0x39, // 5 53d
0x3C, 0x4A, 0x49, 0x49, 0x30, // 6 54d
0x01, 0x71, 0x09, 0x05, 0x03, // 7 55d
0x36, 0x49, 0x49, 0x49, 0x36, // 8 56d
0x06, 0x49, 0x49, 0x29, 0x1E, // 9 57d
0x00, 0x36, 0x36, 0x00, 0x00, // : 58d
0x00, 0x56, 0x36, 0x00, 0x00, // ; 59d
0x08, 0x14, 0x22, 0x41, 0x00, // < 60d
0x14, 0x14, 0x14, 0x14, 0x14, // = 61d
0x00, 0x41, 0x22, 0x14, 0x08, // > 62d
0x02, 0x01, 0x51, 0x09, 0x06, // ? 63d
0x32, 0x49, 0x59, 0x51, 0x3E, // @ 64d
0x7C, 0x12, 0x11, 0x12, 0x7C, // A 65d
0x7F, 0x49, 0x49, 0x49, 0x36, // B 66d
0x3E, 0x41, 0x41, 0x41, 0x22, // C 67d
0x7F, 0x41, 0x41, 0x22, 0x1C, // D 68d
0x7F, 0x49, 0x49, 0x49, 0x41, // E 69d
0x7F, 0x09, 0x09, 0x09, 0x01, // F 70d
0x3E, 0x41, 0x49, 0x49, 0x7A, // G 71d
0x7F, 0x08, 0x08, 0x08, 0x7F, // H 72d
0x00, 0x41, 0x7F, 0x41, 0x00, // I 73d
0x20, 0x40, 0x41, 0x3F, 0x01, // J 74d
0x7F, 0x08, 0x14, 0x22, 0x41, // K 75d
0x7F, 0x40, 0x40, 0x40, 0x40, // L 76d
0x7F, 0x02, 0x0C, 0x02, 0x7F, // M 77d
0x7F, 0x04, 0x08, 0x10, 0x7F, // N 78d
0x3E, 0x41, 0x41, 0x41, 0x3E, // O 79d
0x7F, 0x09, 0x09, 0x09, 0x06, // P 80d
0x3E, 0x41, 0x51, 0x21, 0x5E, // Q 81d
0x7F, 0x09, 0x19, 0x29, 0x46, // R 82d
0x46, 0x49, 0x49, 0x49, 0x31, // S 83d
0x01, 0x01, 0x7F, 0x01, 0x01, // T 84d
0x3F, 0x40, 0x40, 0x40, 0x3F, // U 85d
0x1F, 0x20, 0x40, 0x20, 0x1F, // V 86d
0x3F, 0x40, 0x38, 0x40, 0x3F, // W 87d
0x63, 0x14, 0x08, 0x14, 0x63, // X 88d
0x07, 0x08, 0x70, 0x08, 0x07, // Y 89d
0x61, 0x51, 0x49, 0x45, 0x43, // Z 90d
0x00, 0x7F, 0x41, 0x41, 0x00, // [ 91d
0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
0x00, 0x41, 0x41, 0x7F, 0x00, // ] 93d
0x04, 0x02, 0x01, 0x02, 0x04, // ^ 94d
0x40, 0x40, 0x40, 0x40, 0x40, // _ 95d
0x00, 0x01, 0x02, 0x04, 0x00, // ' 96d
0x20, 0x54, 0x54, 0x54, 0x78, // a 97d
0x7F, 0x48, 0x44, 0x44, 0x38, // b 98d
0x38, 0x44, 0x44, 0x44, 0x20, // c 99d
0x38, 0x44, 0x44, 0x48, 0x7F, // d 100d
0x38, 0x54, 0x54, 0x54, 0x18, // e 101d
0x08, 0x7E, 0x09, 0x01, 0x02, // f 102d
0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g 103d
0x7F, 0x08, 0x04, 0x04, 0x78, // h 104d
0x00, 0x44, 0x7D, 0x40, 0x00, // i 105d
0x40, 0x80, 0x84, 0x7D, 0x00, // j 106d
0x7F, 0x10, 0x28, 0x44, 0x00, // k 107d
0x00, 0x41, 0x7F, 0x40, 0x00, // l 108d
0x7C, 0x04, 0x18, 0x04, 0x78, // m 109d
0x7C, 0x08, 0x04, 0x04, 0x78, // n 110d
0x38, 0x44, 0x44, 0x44, 0x38, // o 111d
0xFC, 0x24, 0x24, 0x24, 0x18, // p 112d
0x18, 0x24, 0x24, 0x18, 0xFC, // q 113d
0x7C, 0x08, 0x04, 0x04, 0x08, // r 114d
0x48, 0x54, 0x54, 0x54, 0x20, // s 115d
0x04, 0x3F, 0x44, 0x40, 0x20, // t 116d
0x3C, 0x40, 0x40, 0x20, 0x7C, // u 117d
0x1C, 0x20, 0x40, 0x20, 0x1C, // v 118d
0x3C, 0x40, 0x30, 0x40, 0x3C, // w 119d
0x44, 0x28, 0x10, 0x28, 0x44, // x 120d
0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y 121d
0x44, 0x64, 0x54, 0x4C, 0x44, // z 122d
0x00, 0x08, 0x77, 0x00, 0x00, // { 123d
0x00, 0x7F, 0x00, 0x00, 0x00,// | 124d
0x00, 0x77, 0x08, 0x00, 0x00, // } 125d
0x10, 0x08, 0x10, 0x08, 0x00, // ~ 126d
                              };




/* I don't think this works TODO*/

void hex_extract(){
 uint8_t col;

  scanf("%su", &col);
  printf("You entered %X\n", col);

 // Lower nibble between 0x00 to 0x0F
  uint8_t lower_nibble = (col & 0x0F);
  printf("Lower nibble is: %X\n", lower_nibble);
  uint8_t upper_nibble = (col & 0xF0);
  printf("Upper nibble is: %X\n", upper_nibble);

 // Upper nibble between 0x10 to 0x1F

}


int main()
{

    for(uint8_t i = 0; i < 5; i++ ){
        char letter = Font[((126 - 32) * 5 + i)];
        printf("%X ", letter);
    }
}
//testing something
