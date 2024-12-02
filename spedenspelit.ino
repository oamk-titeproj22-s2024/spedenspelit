#include <Arduino_FreeRTOS.h>
#include <leds.h>

int numero;
bool result;
const int bin = 0b1111100;

void setup() {
  initializeLeds();
// numero = random(2, 5);
  DDRK = 0x183;
  PORTK = 0x7C;

xTaskCreate(MainTask, "Game", 100, NULL, 1, NULL);
xTaskCreate(IdleTask, "WaitInit", 100, NULL, 0, NULL);
}

void loop() {
}

static void MainTask(void* pvParameters) {
  numero = random(2, 5);
  setLed(numero);
  

  if(PINK != bin & ~ (1 << (numero+1))) {
    vTaskSuspend(NULL);
  }
  else {
    setAllLeds();
  }
  // vTaskSuspend(NULL);
}

static void IdleTask(void* pvParameters) {
while(1) {
  show1();
  }
}
