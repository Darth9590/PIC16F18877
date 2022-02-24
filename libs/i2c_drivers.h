#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* ======= DEFINES ========= */
#define ARRAY_SIZE 40
#define ROW_SIZE 5


/* ========= Global Variables =========== */
uint8_t Binarray[ARRAY_SIZE];
uint8_t NewBin[ARRAY_SIZE];
char Final_image[ARRAY_SIZE];
int Position = 0;
int LowerLimit = 0;

/* Array size is 16 bits for each hex value * 5 * row
 * Example: 0x15, 0x62, 0xA0, 0xF2, 0xE4,

 * 8 * 5  = 40 */


/* Your font goes here */
uint8_t Font[ARRAY_SIZE] ={
0x55, 0x2A, 0x55, 0x2A, 0x55,};


int main(){
    int a, c, d, i;

    printf("You entered: \n");    

    for(int b = 0; b < 5; b++){
        printf("0x%02X ",Font[b]);
    }
    printf("\n\n");

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
    /* Takes the reversed array and makes it look nice by repalcing 1s and 0s with blanks and stars */
    for(i = 0; i < ARRAY_SIZE; i++){
        if( NewBin[i] == '0' ){
            Final_image[i] = ' ';
        }
        else if( NewBin[i] == '1' ){
            Final_image[i] = '*';
        }
       // printf("%c", Final_image[i] );
    }

    /* Initalize all variables for the upcoming for loops.
     * a counts how many times we go through the array
     * i tells where in the array we print
     * c keeps track of how many times we are printing and will \n every 5 thus needs to be 1 to start
     * d keeps track of which if statement we need to be so i is assigned to the correct value */
    int lower_limit = 1;
    int upper_limit = 2;
    int reset_i = 1;
    bool flag_i = false; // Used to reset i
     /* for loop while less then array size we increase a by 1 each iteration
       * purpose of for loop is to print out LSB first left to right
       * essentially we flipped it from little endian to big. Since we want to print each
       * first bit of the byte, we add 8 to i.  */
    for( a = 0, i = 0, c = 1, d = 0; a < ARRAY_SIZE; a++ ){
         for(; d < ROW_SIZE; c++, d++, i += 8 ){ // for loop where d is size of row IE character width
             printf("%c", Final_image[i]);
            if( c % ROW_SIZE == 0 ){ // have we hit the end of row
                printf("\n"); // New line

                 }

         }

         /* The above for loops can only hand the first bit of the byte. These loops handle the rest
           * of translation. X is added which keeps track of when we hit 5 bits for a new line. X is added
           * to reset_i which starts it over but at the next bit. Have to inlcude a flag to -8 since the for
           * loop adds 8 */
         for(int x = 0, i = 1;
             /* upper and lower limit keep the loop to the contained byte I want to transpose */
             d >= (ROW_SIZE * lower_limit) && d < (ROW_SIZE * upper_limit ) && d < ARRAY_SIZE;
             c++, d++, i += 8){
             /* Flag event to cancel out the + 8 */
             if( flag_i == true ){
                 i -= 8;
                 flag_i = false;
             }
             printf("%c", Final_image[i]); // Print the array
            if( c % 5 ==0 ){ // have we hit the end of row
                printf("\n"); // New line
                ++x;
                i = (reset_i + x); // set i to the new value to start from
                flag_i = true; // raise flag

            }
            /* if d + 1 since it starts at 0, equalts the upper limit then increase limits by one */
            if( (d + 1) == (ROW_SIZE * upper_limit)){
                lower_limit += 1;
                upper_limit += 1;
            }
         }
     }


/* For debugging purpose */
    /* printf("\n\n");
     for(int b = 0; b < ARRAY_SIZE; b++){
        printf("%c",Binarray[b]);
    }
    printf("\n");
    for(int b = 0; b < ARRAY_SIZE; b++){
        printf("%c",NewBin[b]);
    } */
}
