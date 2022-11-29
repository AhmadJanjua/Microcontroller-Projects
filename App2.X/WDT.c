/*
 * File:   ADC.c
 * Author: ahmad
 *
 * Created on November 10, 2022, 9:01 PM
 */
#include "WDT.h"

void WDTexec() {
    RCONbits.SWDTEN = 1;
}