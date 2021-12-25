#include <gb/gb.h>
#include "SimpleSprite.h"

UINT8 joypadPrevious;
UINT8 spriteX,spriteY;
INT8 velocityX,velocityY;

void main(void)
{

    // This enables Sound
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels

    DISPLAY_ON;
    SHOW_SPRITES;

    set_sprite_data(0,1,SimpleSprite);
    set_sprite_tile(0,0);
    move_sprite(0,84,88);

    // Set our default position
    spriteX=80;
    spriteY=72;

    // Set our default velocity to be moving down and to the right
    velocityX=0;
    velocityY=0;

    // Loop forever
    while(1) {
    
        // If the right button on the d-pad is held down
        if(joypad() & J_RIGHT){
        
            // Positive x velocity to move the sprite to the right
            velocityX=1;
            
        // If the right button on the d-pad is held down
        }else if(joypad() & J_LEFT){
        
            // negative x velocity to move the sprite to the left
            velocityX=-1;
        }else{
        
            // Zero x velocity means no horizontal movement
            velocityX=0;
        }
        

        // If the "A" button was just pressed
        if((joypad() & J_A) && !(joypadPrevious & J_A)){

            // Play a sound on channel 1
            NR10_REG=0X00;
            NR11_REG=0X81;
            NR12_REG=0X43;
            NR13_REG=0X73;
            NR14_REG=0X86;

            // Move the sprite downward
            spriteY+=8;

        // If the "B" button was just presssed
        } else if((joypad() & J_B) && !(joypadPrevious & J_B)){

            // Play a sound on channel 1
            NR10_REG=0X00;
            NR11_REG=0X81;
            NR12_REG=0X43;
            NR13_REG=0X73;
            NR14_REG=0X86;

            // Move the sprite up
            spriteY-=8;
        }

        // Apply our velocity
        spriteX+=velocityX;
        spriteY+=velocityY;

        // Position the first sprite at our spriteX and spriteY
        // All sprites are render 8 pixels to the left of their x position and 16 pixels ABOVE their actual y position
        // This means an object rendered at 0,0 will not be visible
        // x+5 and y+12 will center the 8x8 tile at our x and y position
        move_sprite(0,spriteX+4,spriteY+12);
        
        joypadPrevious=joypad();

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
