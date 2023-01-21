#include <jo/jo.h>
#include "util.h"

// shuffles an array of integers
void shuffleArray(unsigned int* array, unsigned int size)
{
    unsigned int i = 0;

    for (i = 0; i < size - 1; i++)
    {
        unsigned int j = i + jo_random(0xFFFF) / (0xFFFF / (size - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

// bound integer value between min - max-1;
void sanitizeValue(int* value, int min, int max)
{
    if(*value < min)
    {
        *value = max - 1;
    }
    else if(*value >= max)
    {
        *value = min;
    }
}

void errorPrint(char* message)
{
    while(1)
    {
        jo_printf(0, 0, message);
    }
}
