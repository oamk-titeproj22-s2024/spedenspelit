#include <Arduino_FreeRTOS.h>
#include <leds.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;

volatile int numero;
volatile int binumero;
int randomness[5];
int randcount;
bool result;
const int bin = 0b1111100;

void setup() {
  initializeLeds();
  DDRK = 0x183;
  PORTK = 0x7C;
//  numero = random(2, 5);
//  binumero = bin & ~ (1 << (numero));
//xTaskCreate(StartTask, "Start", 100, NULL, 2, &TaskHandle_3);
xTaskCreate(MainTask, "Game", 100, NULL, 1, &TaskHandle_1);
xTaskCreate(IdleTask, "WaitInit", 100, NULL, 0, &TaskHandle_2);
}

void loop() {
}
//
//static void StartTask(void* pvParameters) {
//  numero = random(2, 5);
//  binumero = bin & ~ (1 << (numero));
//  vTaskSuspend(NULL);
////vTaskResume(TaskHandle_1);
//}

static void MainTask(void* pvParameters) {
//
//result = false;
    numero = random(2, 5);
    binumero = bin & ~ (1 << (numero));
    setLed(numero-2);
 
  if(PINK == binumero) {
    result = true;
    vTaskSuspend(NULL);
  }

  if(PINK != binumero && PINK != bin) {
    vTaskSuspend(NULL);
  }
 
  // vTaskSuspend(NULL);
}

static void IdleTask(void* pvParameters) {
//while(1) {
//  show1();
//  }
while(result == true) {
 numero = random(2, 5);
 vTaskResume(TaskHandle_1);
  }
  setAllLeds();
}
