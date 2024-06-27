// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-License-Identifier: MIT
// Copyright 2023 

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  pin_t pin_ao;
  pin_t pin_vcc;
  pin_t pin_gnd;
  uint32_t humidity_attr;
} chip_state_t;

static void chip_timer_event(void *user_data);

void chip_timer_event(void *user_data) {
  chip_state_t *chip = (chip_state_t*)user_data;
  float humidity = attr_read_float(chip->humidity_attr);
  float voltage = humidity * (5.0 / 100.0);
  if (pin_read(chip->pin_vcc) && !pin_read(chip->pin_gnd)) {
    pin_dac_write(chip->pin_ao, voltage);
  }
}

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  chip->pin_ao = pin_init("A0", ANALOG);
  chip->humidity_attr = attr_init("humidity", 50);
  chip->pin_vcc = pin_init("VCC", INPUT_PULLDOWN);
  chip->pin_gnd = pin_init("GND", INPUT_PULLUP);

  const timer_config_t timer_config = {
    .callback = chip_timer_event,
    .user_data = chip,
  };
  timer_t timer_id = timer_init(&timer_config);
  timer_start(timer_id, 1000, true);
  printf("Humidity Sensor\n");
}