/*
 * File:   ADC.c
 * Author: ahmad
 *
 * Created on November 10, 2022, 9:01 PM
 */
#include "WDT.h"

// Execute a reset
void WDTexec() {
    RCONbits.SWDTEN = 1;
}