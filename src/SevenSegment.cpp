#include "SevenSegment.h"

void initSevenSegmentPin()
{
    DDRC |= 0xFF; // Set all PORTC pins (PC0 - PC7) as output
    PORTC = 0xFF; // Initialize all segments OFF (common cathode)
}