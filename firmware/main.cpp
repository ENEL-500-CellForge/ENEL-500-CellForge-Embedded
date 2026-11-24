#include <Arduino.h>
#include "bay.h"
#include "config.h"
#include "hal.h"

static Bay bays[NUM_BAYS];
static uint32_t next_tick_ms = 0;

void setup() {
  Serial.begin(115200);
  hal_init();
  for (uint8_t i = 0; i < NUM_BAYS; i++) bay_init(bays[i]);

  // TODO: start the network task (Wi-Fi, HTTPS to the Web API).
  // Keep it separate from this loop so a slow request never blocks safety.
}

void loop() {
  const uint32_t now = millis();
  if ((int32_t)(now - next_tick_ms) < 0) return;   // not time yet
  next_tick_ms = now + TICK_MS;

  for (uint8_t i = 0; i < NUM_BAYS; i++) {
    Inputs  in  = hal_read(i, now);
    Outputs out = bay_step(bays[i], in);
    hal_apply(i, out);
  }

  // TODO: every 10 s, hand each bay's telemetry to the network task
  // TODO: update the LCD (Nice-to-have)
}