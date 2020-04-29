#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

#define ON 0
#define OFF 1

xSemaphoreHandle xMutex;

static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, false);
}

//RED LED ON for 1 Second and with time slot 4.5
static void vLEDTaskRed(void *pvParameters) {

	while (1) {

		xSemaphoreTake(xMutex, 1000);

		Board_LED_Set(0, ON);

		vTaskDelay(configTICK_RATE_HZ);  //Delay to keep RED LED ON for 1 second

		Board_LED_Set(0, OFF);
		xSemaphoreGive(xMutex);
		//Here we provide 3.5s time Delay total time slot for RED is 4.5 second
		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ / 2);

	}
}

//GREEN LED with 1.5s advance delay then ON for 1s and with time slot 4.5
static void vLEDTaskGreen(void *pvParameters) {

	//delay for 1.5 seconds
	vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ / 2);
	while (1) {
		xSemaphoreTake(xMutex, 1000);
		Board_LED_Set(1, ON);

		vTaskDelay(configTICK_RATE_HZ); //Delay to keep GREEN LED ON for 1 second

		Board_LED_Set(1, OFF);
		xSemaphoreGive(xMutex);
		//Here we provide 3.5s time Delay total time slot for GREEN is 4.5 second
		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ / 2);

	}
}

//BLUE LED with 3s advance delay then ON for 1s and with time slot 4.5
static void vLEDTaskBlue(void *pvParameters) {

	//delay for 3 seconds
	vTaskDelay(3 * configTICK_RATE_HZ);

	while (1) {

		xSemaphoreTake(xMutex, 1000);
		Board_LED_Set(2, ON);

		vTaskDelay(configTICK_RATE_HZ); //Delay to keep BLUE LED ON for 1 second

		Board_LED_Set(2, OFF);
		xSemaphoreGive(xMutex);
		//Here we provide 3.5s time Delay total time slot for BLUE is 4.5 second
		vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ / 2);

	}
}

int main(void) {
	prvSetupHardware();

	xMutex = xSemaphoreCreateMutex();  // creating mutex

	xTaskCreate(vLEDTaskRed, (signed char* ) "vLEDTaskRed",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskGreen, (signed char* ) "vLEDTaskGreen",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskBlue, (signed char* ) "vLEDTaskBlue",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(xTaskHandle *) NULL);
	//Start the scheduler
	vTaskStartScheduler();
	//Should never arrive here
	return 1;
}

