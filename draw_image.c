#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* ======= DEFINES ========= */
#define ARRAY_SIZE 80
#define ROW_SIZE 5


/* ========= Global Variables =========== */
uint8_t Binarray[ARRAY_SIZE];
uint8_t NewBin[ARRAY_SIZE];
int Position = 0;
int LowerLimit = 0;

/* Array size is 16 bits for each hex value * 5 * row
 * Example: 0x15, 0x62, 0xA0, 0xF2, 0xE4,
           0x2C, 0x00, 0x5F, 0x08, 0xAA,

 * 8 * 5 * 2 = */

uint8_t Font[ARRAY_SIZE] ={
0x14, 0x14, 0x14, 0x14, 0x14,
0x7F, 0x41, 0x41, 0x41, 0x3E,
};


int main(){
    int a, c, d, i;

    /* For loop, assigns Font[number] to value. Then ANDs value and 0x80 to get 8th place
     *Conintues to shift bit right by one bit and stops when i hits 0 */
    for(int b = 0; b < 10; b++){
        uint8_t value = Font[b];
        for(i = 0x80; i != 0;i >>= 1, a++){
            Binarray[a] = ((value & i)?'1':'0');
        }
    }


    a = 0, c = 2, i = 0; // Initalize Variables  for the loop to work out, c must start at two

    /* Loop to reverse first 8 bits and place into new array */

    int Reverse_Pos = 7; // Starting positions for i
    for(;Reverse_Pos < ARRAY_SIZE;){ // loop until array is less then the array size
        for(i = Reverse_Pos; i >= LowerLimit && i < ARRAY_SIZE; i--){ /* i is set to reverse starting position. Lower limit prevents it from taking wrong byte
                                                                * meaning if positon is 23 then lower limit is 16. Again must be less then 80, then i minus 1 */
        NewBin[a] = Binarray[i]; /* The loop goes 8 times but then after does not becuase it take only one or two tries
                                  *until reverse_pos is lower then lower limit */
        a++; // Increment NewBin by 1

        }

        Reverse_Pos = ((8 * c) - 1); /* This increase keeps Reverse_Pos by a byte each main for loop.
                                       * Must subtract one since we start at 0 in the array.
                                       * example first loop: (8 * 2) = 16 - 1 = 15 start location. */
        LowerLimit = (8 * c - 8);/* As mentioned above, lower limit needs to be set as a stop point
                                   * example first loop: (8 * 2) = 16 - 8 = 8; start pos 15 end pos 8*/
        c++; // Increment c by one for next loop

    }
    /* Initalize all variables for the upcoming for loops.
     * a counts how many times we go through the array
     * i tells where in the array we print
     * c keeps track of how many times we are printing and will \n every 5 thus needs to be 1 to start
     * d keeps track of which if statement we need to be so i is assigned to the correct value */
    int lower_mult = 1;
    int upper_mult = 2;
    int reset_i = 1;
    bool flag_i = false;
    for( a = 0, i = 0, c = 1, d = 0; a < ARRAY_SIZE; a++ ){
         for(; d < ROW_SIZE; c++, d++, i += 8 ){
             printf("%c", NewBin[i]);
           //printf(" i %d c %d ", i, c);
            if( c % 5 == 0 ){
                printf("\n");

                 }

         }
         //printf(" %d %d", lower_mult, upper_mult);
         //printf("%d", i);
         for(int x = 0, i = 1;
             d >= (ROW_SIZE * lower_mult) && d < (ROW_SIZE * upper_mult ) && d < ARRAY_SIZE;
             c++, d++, i += 8){
             if( flag_i == true ){
                 i -= 8;
             }
            // printf("i %d ", i);
             printf("%c", NewBin[i]);
            //  printf("i %d x %d   ", i, x);
            if( c % 5 ==0 ){
                printf("\n");
                ++x;
                i = (reset_i + x);
               // printf("value of i: %d", i);
                flag_i = true;

            }
                     // printf(" %d  ", i);
//printf("\n%d %d\n", ROW_SIZE * upper_mult, d);

            if( (d + 1) == (ROW_SIZE * upper_mult)){
             //   printf(" %d ", d);
                lower_mult += 1;
                upper_mult += 1;
            }
         }
     }



    printf("\n\n");
     for(int b = 0; b < ARRAY_SIZE; b++){
        printf("%c",Binarray[b]);
    }
    printf("\n");
    for(int b = 0; b < ARRAY_SIZE; b++){
        printf("%c",NewBin[b]);
    }
}
