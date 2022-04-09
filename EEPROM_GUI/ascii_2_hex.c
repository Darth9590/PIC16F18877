uint8_t get_hex(uint8_t c);
uint8_t create_hex(int c);

uint8_t get_hex(uint8_t letter){
    
    switch(letter){
        
        case 0x30:
            letter = 0x00;
            return letter;
        case 0x31:
            letter = 0x01;
            return letter;
        case 0x32:
            letter = 0x02;
            return letter;
        case 0x33:
            letter = 0x03;
            return letter;
        case 0x34:
            letter = 0x04;
            return letter;
        case 0x35:
            letter = 0x05;
            return letter;
        case 0x36:
            letter = 0x06;
            return letter;
        case 0x37:
            letter = 0x07;
            return letter;
        case 0x38:
            letter = 0x08;
            return letter;
        case 0x39:
            letter = 0x09;
            return letter;
        case 0x41:
        case 0x61:
            letter = 0x0A;
            return letter;
        case 0x42:
        case 0x62:
            letter = 0x0B;
            return letter;
        case 0x43:
        case 0x63:
            letter = 0x0C;
            return letter;
        case 0x44:
        case 0x64:
            letter = 0x0D;
            return letter;
        case 0x45:
        case 0x65:
            letter = 0x0E;
            return letter;
        case 0x46:
        case 0x66:
            letter = 0x0F;
            return letter;

    }          
   
}

 uint8_t create_hex(int c){
 while(1){
    if(c == 0 || c == 2 || c == 4 || c == 6){
        hex = test2[c];
        hex <<= 4;
        hex2 = hex;
        
        break;
    }
    else if(c == 1){
        hex = test2[c];
        hex2 |= hex;
        addr1 = hex2;
        
        break;
    }
    else if( c == 3){
        hex = test2[c];
        hex2 |= hex;               
        addr2 = hex2;
       
        break;
    }

    else if(c == 5){
        hex = test2[c];
        hex2 |= hex;
        data = hex2;
        
        break;
    }
    
    else if(c == 7){
        hex = test2[c];
        hex2 |= hex;
        count = hex2;
        
        break;
    }


    else{
        break;
    }
 }
    
 } 
