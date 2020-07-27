#include "board.h"
#include "hal.h"

/*
    Function Signatures
*/
void setAllKeysColor(uint16_t* ledColors, uint16_t color);
void setModKeysColor(uint16_t* ledColors, uint16_t color);
void setWasdKeysColor(uint16_t* ledColors, uint16_t color);
uint16_t* splitColor(uint16_t color);
uint16_t joinColor(uint16_t rgb[]);
uint16_t saturateUpColor(uint16_t color);
uint16_t saturateDownColor(uint16_t color);
void applyEffectAllKeys(uint16_t* ledColors, uint16_t (*effect)(uint16_t));
uint16_t brightUpColor(uint16_t color);
uint16_t brightDownColor(uint16_t color);
void saveAllLightsState(uint16_t* ledColors);
void restoreAllLightsState(uint16_t* ledColors);
void resetAllLightsState(uint16_t* ledColors);