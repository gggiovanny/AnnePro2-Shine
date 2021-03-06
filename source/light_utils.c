/*
    ===  Lighting Utilities  ===
    This file contains functions useful for coding lighting profiles
*/
#include "light_utils.h"

/*
    #define Directives declaration
*/
#define LEN(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


/*
    Static Declarations
*/

// An array of basic colors used accross different lighting profiles
static const uint16_t colorPalette[] = {0xF00, 0xFF0, 0x0F0, 0x0FF, 0x00F, 0xF0F, 0x5FF};

// Array with Modifier keys IDs (Esc, Tab, Ctrl, Enter etc) 
static const uint16_t modKeyIDs[] = {0, 13, 14, 28, 40, 41, 42, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69};

/*
    Function declarations
*/

// Set all keys lighting to a specific color
void setAllKeysColor(uint16_t* ledColors, uint16_t color){
    for (uint16_t i=0; i<NUM_COLUMN * NUM_ROW; ++i){
        ledColors[i] = color;
    }
}

// Set modifier keys lighting to a specific color
void setModKeysColor(uint16_t* ledColors, uint16_t color){
    for (uint16_t i=0; i<LEN(modKeyIDs); ++i){
        ledColors[modKeyIDs[i]] = color;
    }
}