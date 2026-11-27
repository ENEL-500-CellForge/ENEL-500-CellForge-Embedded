#include <Arduino.h>
#include "bay.h"
#include "config.h"
#include "hal.h"

static Bay bays[NUM_BAYS];
static TickType_t xLastWakeTime;
static const TickType_t xFrequency = pdMS_TO_TICKS(TICK_MS);

void setup() {
  Serial.begin(115200);
  xLastWakeTime = xTaskGetTickCount();
  hal_init();
  for (uint8_t i = 0; i < NUM_BAYS; i++) bay_init(bays[i]);
}

void loop() {
   xTaskDelayUntil(&xLastWakeTime, xFrequency);

  for (uint8_t i = 0; i < NUM_BAYS; i++) {
    Inputs  in  = hal_read(i, now);
    Outputs out = bay_step(bays[i], in);
    hal_write(i, out);
  }

  // TODO: every 10 s, hand each bay's telemetry to the network task
  // TODO: update the LCD (Nice-to-have)
}