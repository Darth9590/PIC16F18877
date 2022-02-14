#include <stdio.h>
#include <stdint.h>

uint8_t Binarray[80];
uint8_t NewBin[80];
int array_size = 80;
int Position = 0;
int Reverse_Pos = 0;
int LowerLimit = 0;

uint8_t Font[10] ={
    0x15, 0x62, 0xA0, 0xF2, 0xE4,
    0x2C, 0x00, 0x5F, 0x08, 0xAA,
};


int main(){
    int a, c = 0 , i, d, k;

    /* For loop, assigns Font[number] to value. Then ANDs value and 0x80 to get 8th place
     *Conintues to shift right by one bit and stops when i hits 0 */
    for(int b = 0; b < 10; b++){
        uint8_t value = Font[b];
        for(i = 0x80; i != 0;i >>= 1, a++){
            Binarray[a] = ((value & i)?'1':'0');
            printf("%c", Binarray[a]);
        }
        //printf("\n");
    }


    a = 0, c = 0, d = 0; /* Initalize Variables */

    /* Loop to reverse first 8 bits and place into new array */

    Reverse_Pos = 7;
    for(;Reverse_Pos < 80;){

        for(i = Reverse_Pos; i >= LowerLimit && i < 80; i--){

        NewBin[a] = Binarray[i]; /* A never goes above 8 */
        a++;
        }
        c++;
        Reverse_Pos = ((8 * c) - 1);
        LowerLimit = (8 * c);

        printf("\nReverse: %d\nLowerLimit: %d\n%d\n", Reverse_Pos, LowerLimit, a);
    }

    /* Need to increase the above loop by 8 bits each time */

    Position = 7; /* Sets starting position */
    /* Loop to remove the first 8 bits from the array Binarray so we can only reverse 8 bits
     * at a time for the above loop */

    for(c = 0;c < 8; c++){ /* loop 8 times, starts at 0 */

        /* This loop removes one position at a time then proceeds to shift everything in the array down */
        for(; Position < 80 ; Position++){ /* For positon that is less then 80 (size of array) */
            Binarray[Position] = Binarray[Position +1]; /* Position = Position + 1 */
        }

        Position = (7 - c); /* Need to change the position becuase we need to remove the first 8 bits*/
        //printf(" %d %d", Position, c);
        }

    printf("\n\n");
    for(int b = 0; b < 80; b++){
        printf("%c",Binarray[b]);
    }
    printf("\n");
    for(int b = 0; b < 80; b++){
        printf("%c",NewBin[b]);
    }
    printf("\n");
    c = 0;
    //printf("\n");
    for(a = 0; a < 80; a++){
        uint8_t value = NewBin[a];
        c++;
        printf("%c", value);
        
       // if(c % 8 == 0)
          //  printf("\n");
    }
    }
