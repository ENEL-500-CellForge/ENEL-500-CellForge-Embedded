#ifndef BAY_H
#define BAY_H
#include <stdint.h>

// One Bay = one cell slot. There are NUM_BAYS of them, each with its own FSM.

// ----- FSM States ----- //
enum class BayState : uint8_t {
  Empty,        // 0: Bay disabled by UI
  Enabled,      // 1: Bay enabled by UI, waiting for cell
  Identifying,  // 2: Cell inserted, generating ID
  Precheck,     // 3: Health checks (voltage, temperature, internal resistance)
  Charge1,      // 4: Charge to 4.2 V
  Discharge,    // 5: Discharge to 2.8 V to measure capacity
  Charge2,      // 6: Charge back to 4.2 V
  Complete,     // 7: Charge/discharge cycle complete, waiting for cell removal
  Fault         // 8: Latched until cell removed
};

// ----- Fault Codes ----- //
enum class FaultCode : uint8_t {
  None,             // 0: No fault
  Overvoltage,      // 1: Cell voltage exceeded MV_OVERVOLTAGE_FAULT
  Undervoltage,     // 2: Cell voltage dropped below MV_UNDERVOLTAGE_FAULT
  Overtemperature,  // 3: Cell temperature exceeded TEMP_STOP_DC
  Overcurrent       // 4: Cell current exceeded MA_DISCHARGING
};

// FSM Inputs via hal_read() (sampled once per tick).
// ********TODO: Define tick******** //
// ********TODO: Do we need more inputs******** //
struct Inputs {
  uint32_t now_ms;        // Current time (ms)
  int32_t  voltage_mv;    // Voltage (mV)
  int32_t  current_ma;    // Current (mA)
  int32_t  temp_dc;       // Temperature (0.1 degC)
  bool     chrg;          // MCU_CHRG from TP5100
  bool     stdby;         // MCU_STDBY from TP5100
  bool     enabled;       // IsReadyForCell from UI
  bool     id_confirmed;  // ********TODO: Define******** //
};

// FSM outputs via hal_write() (applied once per tick).
// ********TODO: Is it really once per tick? Define tick******** //
// ********TODO: Do we need more outputs?******** //
struct Outputs {
  bool     charge_en;     // True to enable charging (TP5100 EN pin for charging circuit), false to disable
  bool     discharge_en;  // True to enable discharging (TP5100 EN pin for discharging circuit), false to disable
};

struct Bay {
  BayState state;
  BayState prev_state;
  uint32_t state_since_ms;
  uint32_t capacity_mah_x1000;   // TODO: Do we need this here? Or can it just be in the discharge state?
};

#endif