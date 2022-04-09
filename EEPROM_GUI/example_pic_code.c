void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    I2C_Init();
    
          
   
    letter = getch();
    
    
    
    
    
    switch(letter){
   
        case '1':
        {
        for(int i = 0; i < 6; i++){
            letter = getch();
            test[i] = letter;
            
       }
       
         for(int i = 0; i < 6; i++){
            test2[i] = get_hex(test[i]);
            
         }
        
        for(int i = 0; i < 6; i++){
            create_hex(i);

        }
            byte_write(addr1, addr2, data);
            
           
            break;
        }
        case '2': 
        {
            
        for(int i = 0; i < 6; i++){
            letter = getch();
            
            test[i] = letter;
           
       }
        
        for(int i = 0; i < 3; i++){
             str[i] = getch();
             count2  = atoi(str);
        }
        
         for(int i = 0; i < 6; i++){
            test2[i] = get_hex(test[i]);
            
         }
        
        for(int i = 0; i < 6; i++){
            
            create_hex(i);

        } 
        
        
            page_write(addr1, addr2, data, count2);
            break;
        }
        case '3':
        {
         for(int i = 0; i < 4; i++){
            letter = getch();
            test[i] = letter;
            
       }
         for(int i = 0; i < 3; i++){
             str[i] = getch();
             count2  = atoi(str);

         }
        
         for(int i = 0; i < 4; i++){
            
            test2[i] = get_hex(test[i]);

         }
        
        for(int i = 0; i < 4; i++){
            create_hex(i);

        }
        
            sequential_read(addr1, addr2, count2);
            break;
        }
        case '4':
        {
               for(int i = 0; i < 4; i++){
            letter = getch();
            test[i] = letter;
            
       }
        
         for(int i = 0; i < 4; i++){
            test2[i] = get_hex(test[i]);
            
         }
        
        for(int i = 0; i < 4; i++){
            create_hex(i);

        }
            data = random_read(addr1, addr2);
            printf("%X\n", data);
            break;
        }

    }
        
    } 
