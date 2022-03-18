# PIC16F18877
My attempts at learning C and Microcontrollers.

# OLED Project
Purpose of project is to write my own drivers for the SSD1306 OLED learning how to interpret data sheet, how addressing and paging works for OLEDs and continue to learn C in something I enjoy. 
## OLED_project Folder
This is where any MCC generated files live. I plan to not use them as much as possible for my learning sake but I needed a ESUART now! 
## libs
This is where all files I write live. 
### SSD1306_drivers.h - drivers for the SSD1306
### Testing File.c - what happens if I do this?
### draw_image.c 
This program draws hex value bits copying how the OLED is currently set up in the drivers. Each segment (column) starts with the LSB first. I needed to flips bits since when I enter 0x41 the MSB is on the left. It was also a requiement to only flip one byte at a time. An example font can contain 5 bytes. 

What it looks like:

![image](https://user-images.githubusercontent.com/60046091/155479126-87249629-a528-4b38-b4f4-f66e22e43925.png)
![image](https://user-images.githubusercontent.com/60046091/155479174-fc7d6eb9-7ba1-4f92-ae96-789b716c3a81.png)
![image](https://user-images.githubusercontent.com/60046091/155479223-96e0adf2-dc60-48e2-9e02-777e40fc0c44.png)
![image](https://user-images.githubusercontent.com/60046091/155479267-9b27d0a4-288d-4a5b-9b63-cd9761c1b0f6.png)

### I2C_drivers.h/C - My attempt at I2C communication, currently WORKING on PIC16F18877. 

Anyone can feel free to use. 
