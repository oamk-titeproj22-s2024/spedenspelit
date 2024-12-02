#include <Arduino_FreeRTOS.h>
#include <leds.h>



int numero;
bool result;

void setup() {
  initializeLeds();
// numero = random(2, 5);

xTaskCreate(MainTask, "Game", 100, NULL, 1, NULL);
xTaskCreate(IdleTask, "WaitInit", 100, NULL, 0, NULL);
}

void loop() {
}

static void MainTask(void* pvParameters) {
  show2(5);
  vTaskSuspend(NULL);
}

static void IdleTask(void* pvParameters) {
while(1) {
  show1();
  }
}
