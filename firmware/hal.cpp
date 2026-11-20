#include "hal.h"
#include "config.h"
#include <Arduino.h>

void hal_init() {
  // TODO: Wire.begin(), pinMode() for enable pins and CHRG/STDBY inputs
  // TODO: init INA219 (x NUM_BAYS) and ADS1115
}

Inputs hal_read(uint8_t bay, uint32_t now_ms) {
  Inputs in{};
  in.now_ms = now_ms;
  // TODO: in.voltage_mv  <- INA219 for this bay
  // TODO: in.current_ma  <- INA219 for this bay
  // TODO: in.temp_dc     <- ADS1115 + thermistor conversion
  // TODO: in.chrg/stdby  <- digitalRead() (check polarity: probably active-low)
  // TODO: in.armed / in.id_confirmed <- from network task (shared state)
  (void)bay;
  return in;
}

void hal_write(uint8_t bay, const Outputs& out) {
  // TODO: digitalWrite charge enable / discharge enable for this bay
  // TODO: set discharge current (Vref DAC) from out.discharge_ma
  (void)bay; (void)out;
}