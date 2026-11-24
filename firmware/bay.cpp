#include "bay.h"
#include "config.h"

// ----- Function Prototypes ----- //
static bool check_faults(Bay& b, const Inputs& in);
static void set_state(Bay& b, BayState next, uint32_t now_ms);
Outputs bay_step(Bay& b, const Inputs& in);

// ----- Set State Function ----- //
static void set_state(Bay& b, BayState next, uint32_t now_ms, FaultCode fault_code = FaultCode::None) {
  if (b.state == next) return; // No state change if current state already matches desired state
  
  b.prev_state     = b.state;
  b.state          = next;
  b.state_since_ms = now_ms;

  if (next == BayState::Fault) {
    b.fault = fault_code;
  } else {
    b.fault = FaultCode::None;
  }

}

// ----- Fault Check Function ----- //
static bool check_faults(Bay& b, const Inputs& in) {
  // Over-voltage fault check
  if (in.voltage_mv > MV_OVERVOLTAGE_FAULT) {
    set_state(b, BayState::Fault, in.now_ms, FaultCode::Overvoltage);
    return true;
  }

  // Under-voltage fault check
  if (in.voltage_mv < MV_UNDERVOLTAGE_FAULT) {
    set_state(b, BayState::Fault, in.now_ms, FaultCode::Undervoltage);
    return true;
  }

  // Over-temperature fault check
  if (in.temp_dc > TEMP_STOP_DC) {
    set_state(b, BayState::Fault, in.now_ms, FaultCode::Overtemperature);
    return true;
  }

  // Over-current fault check
  if (in.current_ma > MA_DISCHARGING) {
    set_state(b, BayState::Fault, in.now_ms, FaultCode::Overcurrent);
    return true;
  }

  // TODO: unexpected cell removal (voltage < V_PRESENT_MV while mid-test)
  // (void)b; (void)in;
  return false;
}

void bay_init(Bay& b) {
  b.state = BayState::Empty;
  b.state_since_ms = 0;
  b.capacity_mah_x1000 = 0;
}

Outputs bay_step(Bay& b, const Inputs& in) {
  if (check_faults(b, in)) {
    return Outputs{false, false, 0};
  } // TODO: Verify this check

  switch (b.state) {
    case BayState::Empty:
      // TODO: Switch logic
      break;

    case BayState::Armed:
      // TODO: Switch logic
      break;

    case BayState::Identifying:
      // TODO: Switch logic
      break;

    case BayState::Precheck:
      // TODO: Switch logic
      break;

    case BayState::Charge1:
      // TODO: Switch logic
      break;

    case BayState::Discharge:
      // TODO: Switch logic
      break;

    case BayState::Charge2:
      // TODO: Switch logic
      break;

    case BayState::Complete:
      // TODO: Switch logic
      break;

    case BayState::Fault:
      // Before entering this state, we need to store the previous state so we can return to it after the fault is cleared.
      // Run check_faults(), if it returns false then return to the previous state. If it returns true, stay in Fault.
      break;
  }

  // Outputs: Enable/disable charging/discharging based on the current state
  Outputs out{false, false};
  
  if (b.state == BayState::Charge1 || b.state == BayState::Charge2) {
    out.charge_en = true;
    // No charging current required, set by sense resistor in charging circuit
  } 
  
  else if (b.state == BayState::Discharge) {
    out.discharge_en = true;
    out.discharge_ma = DISCHARGE_MA;
  }
  return out;
}