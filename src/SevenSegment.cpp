#include "SevenSegment.h"
#include "Timer.h"

void initSevenSegmentPin()
{
    DDRC = 0xFF;  // Set all PORTC pins (PC0 - PC7) (Pin 37 - Pin 30)as output
    PORTC = 0x00; // Initialize all segments OFF (common cathode)
}

void countdown()
{
    int i = 0;
    while (i < 10)
    {
        if (i == 0)
        {                   // Starts from number 9 (a,b,c,d,f,g)
            PORTC = 0x6F;   // turn on PC0 until PC3, PC5, and PC6
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 1) // Number 8 (a,b,c,d,e,f,g)
        {
            PORTC = 0x7F;   // turn on PC0 until PC6
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 2) // Number 7 (a,b,c)
        {
            PORTC = 0x07;   // turn on PC0 until PC2
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 3) // Number 6 (a,c,d,e,f,g)
        {
            PORTC = 0x7D;   // turn on PC0, and PC2 until PC6
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 4) // Number 5 (a,c,d,f,g)
        {
            PORTC = 0x6D;   // turn on PC0, PC2, PC3, PC5, and PC6
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 5) // Number 4 (b,c,f,g)
        {
            PORTC = 0x66;   // turn on PC1, PC2, PC5, and PC6
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 6) // Number 3 (a,b,c,d,g)
        {
            PORTC = 0x4F;   // turn on PC0 until PC3 and PC6
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 7) // Number 2 (a,b,d,e,g)
        {
            PORTC = 0x5B;   // turn on PC0, PC1, PC3, PC4, and PC6
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else if (i == 8) // Number 1 (b,c)
        {
            PORTC = 0x06;   // turn on PC1 and PC2
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
        else // Number 0 (a,b,c,d,e,f)
        {
            PORTC = 0x3F;   // turn on PC0 until PC5
            delaySecond(1); // give 1 second delay (countdown)
            i++;
        }
    }
    PORTC = 0x00; // turn off the 7 Segment afterward
}