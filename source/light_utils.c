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

/*
* ,-----------------------------------------------------------------------------------------.
* |  0  |     |     |     |     |     |     |     |     |     |     |     |     |    13     |
* |-----------------------------------------------------------------------------------------+
* |    14  |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |    28   |     |     |     |     |     |     |     |     |     |     |     |     40      |
* |-----------------------------------------------------------------------------------------+
* |    41,42   |     |     |     |     |     |     |     |     |     |     |        54      |
* |-----------------------------------------------------------------------------------------+
* |   62  |   63  |   64  |                 65              |   66  |   67  |   68  |  69   |
* \-----------------------------------------------------------------------------------------/
*/
// Array with Modifier keys IDs (Esc, Tab, Ctrl, Enter etc) 
static const uint16_t modKeyIDs[] = {0, 13, 14, 28, 40, 41, 42, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69};

/*
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |  16 |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |         |  29 |  30 |  31 |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |     |     |     |     |     |     |     |     |     |                |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |       |       |       |
* \-----------------------------------------------------------------------------------------/
*/
// Array with WASD keys IDs
static const uint16_t wasdKeyIDs[] = {16, 29, 30, 31};

// Array with numbers keys IDs
static const uint16_t numKeyIDs[] = {1,2,3,4,5,6,7,8,9,10};

static uint16_t numLightsState[10] = { 0x1000 };

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

// Set WASD keys lighting to a specific color
void setWasdKeysColor(uint16_t* ledColors, uint16_t color){
    for (uint16_t i=0; i<LEN(wasdKeyIDs); ++i){
        ledColors[wasdKeyIDs[i]] = color;
    }
}

// Set number keys lighting to a specific color
void setNumbersColor(uint16_t* ledColors, uint16_t color){
    for (uint16_t i=0; i<LEN(numKeyIDs); ++i){
        ledColors[numKeyIDs[i]] = color;
    }
}

void saveNumLightsState(uint16_t* ledColors) {
    uint16_t j = 0;
    for (uint16_t i=1; i<=10; ++i){
        numLightsState[j] = ledColors[i];
        ++j;
    }
}

void restoreNumLightsState(uint16_t* ledColors) {
    // is not seted, do nothing
    if(numLightsState[0] == 1000) return;

    uint16_t j = 0;
    for (uint16_t i=1; i<=10; ++i){
        ledColors[i] = numLightsState[j];
        ++j;
    }
}

void resetNumLightsState(void) {
    for (uint16_t i=0; i<LEN(numLightsState); ++i){
        numLightsState[i] = 1000;
    }
}

uint16_t* splitColor(uint16_t color) {
    static uint16_t rgb[3] = { 0xF };
    if(color > 0xFFF) return rgb;
    // int color = B13;
    rgb[2] = color >> 8; // B
    rgb[1] = (color >> 4) - (rgb[2] << 4); // 1
    rgb[0] = color - ((color >> 4) << 4); // 3
    return rgb;
}
uint16_t joinColor(uint16_t rgb[]) {
    uint16_t x3 = rgb[2];
    uint16_t x2 = rgb[1];
    uint16_t x300 = x3 << 8;
    uint16_t x20 = x2 << 4;
    uint16_t color = x300 + x20 + rgb[0];
    return color;
}

uint16_t saturateUpColor(uint16_t color) {
    uint16_t* rgb = splitColor(color);

    bool all_parts_increased = true;
    for(uint16_t i = 0; i<3; ++i) {
        if(rgb[i] >= 0xF) {
            all_parts_increased = false;
            break;
        }
        rgb[i] += 1;
    }
    if(all_parts_increased)
        return joinColor(rgb);
    else 
        return color;
}

uint16_t saturateDownColor(uint16_t color) {
    uint16_t* rgb = splitColor(color);

    bool all_parts_decreased = true;
    for(uint16_t i = 0; i<3; ++i) {
        if(rgb[i] <= 0x1) {
            all_parts_decreased = false;
            break;
        }
        rgb[i] -= 1;
    }
    if(all_parts_decreased)
        return joinColor(rgb);
    else 
        return color;
}

void applyEffectAllKeys(uint16_t* ledColors, uint16_t (*effect)(uint16_t)){
    for (uint16_t i=0; i<NUM_COLUMN * NUM_ROW; ++i){
        if(ledColors[i] == 0) continue; // turned off leds doesnt get affected
        ledColors[i] = effect(ledColors[i]);
    }
}