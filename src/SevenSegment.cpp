#include "SevenSegment.h"

void initSevenSegmentPin()
{
    DDRC |= 0xFF; // Set all PORTC pins (PC0 - PC7) as output
    PORTC = 0x00; // Initialize all segments OFF (common cathode)
}