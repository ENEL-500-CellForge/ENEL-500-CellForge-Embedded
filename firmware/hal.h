#ifndef HAL_H
#define HAL_H
#include "bay.h"

// Hardware access lives here so bay.cpp stays free of pins and I2C.
void   hal_init();                                  // I2C, GPIO, sensors
Inputs hal_read(uint8_t bay, uint32_t now_ms);      // sample one bay
void   hal_write(uint8_t bay, const Outputs& out);  // drive enable pins / Vref

#endif