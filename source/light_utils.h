#include "board.h"
#include "hal.h"

/*
    Function Signatures
*/
void setAllKeysColor(uint16_t* ledColors, uint16_t color);
void setModKeysColor(uint16_t* ledColors, uint16_t color);
void setWasdKeysColor(uint16_t* ledColors, uint16_t color);
void setNumbersColor(uint16_t* ledColors, uint16_t color);
void saveNumLightsState(uint16_t* ledColors);
void restoreNumLightsState(uint16_t* ledColors);
void resetNumLightsState(void);
uint16_t* splitColor(uint16_t color);
uint16_t joinColor(uint16_t rgb[]);
uint16_t saturateUpColor(uint16_t color);
uint16_t saturateDownColor(uint16_t color);
void applyEffectAllKeys(uint16_t* ledColors, uint16_t (*effect)(uint16_t));
