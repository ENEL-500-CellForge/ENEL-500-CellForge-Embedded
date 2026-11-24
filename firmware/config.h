#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

// ---- System ----
constexpr uint8_t  NUM_BAYS = 4;
constexpr uint32_t TICK_MS  = 100;   // control loop period

// ---- Limits (from the roadmap; tune on the bench) ----
constexpr int32_t MV_CUTOFF_CHARGING     = 4200;   // End of charge
constexpr int32_t MV_OVERVOLTAGE_FAULT   = 4300;   // Over-voltage fault
constexpr int32_t MV_CUTOFF_DISCHARGING  = 2800;   // End of discharge
constexpr int32_t MV_UNDERVOLTAGE_FAULT  = 2700;   // Under-voltage fault
constexpr int32_t MV_VREF                = 2400;   // DAC output for 1500 mA discharge
constexpr int32_t V_PRESENT_MV           = 500;    // cell "inserted" above this
constexpr int32_t TEMP_STOP_DC           = 450;    // Stop charging/discharging above this (in tenths of degC, aka 45.0 degC)
constexpr int32_t TEMP_CONTINUE_DC       = 400;    // Resume charging/discharging below this (in tenths of degC, aka 40.0 degC)
constexpr int32_t MA_DISCHARGING         = 1500;   // TODO: Do we use this? Or just Vref for discharge current control?

// ---- Pins (TODO: fill in from the schematic) ----
// constexpr uint8_t PIN_CHARGE_EN[NUM_BAYS]    = { ... };
// constexpr uint8_t PIN_DISCHARGE_EN[NUM_BAYS] = { ... };
// constexpr uint8_t PIN_CHRG[NUM_BAYS]         = { ... };
// constexpr uint8_t PIN_STDBY[NUM_BAYS]        = { ... };

// I2C addresses
constexpr uint8_t INA219_DISCHARGE_ADDR[NUM_BAYS] = {0x40, 0x41, 0x42, 0x43}; // Discharging circuit
constexpr uint8_t INA219_BATTERY_ADDR[NUM_BAYS]   = {0x44, 0x45, 0x46, 0x47}; // Input to battery (output from TP5100)
constexpr uint8_t INA219_INPUT_ADDR[NUM_BAYS]     = {0x4C, 0x4D, 0x4E, 0x4F}; // Input to TP5100
constexpr uint8_t INA219_INPUT_ADDR[NUM_BAYS] 


#endif