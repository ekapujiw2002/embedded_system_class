#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h> // add the FreeRTOS functions for Semaphores (or Flags).

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at
// any time.
SemaphoreHandle_t xSerialSemaphore;

// define two tasks for Blink & AnalogRead
void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskBlink3(void *pvParameters);

void TaskBlink1(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN,
                 HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(50 / portTICK_PERIOD_MS); // wait for one second
    digitalWrite(LED_BUILTIN,
                 LOW); // turn the LED off by making the voltage LOW
    vTaskDelay(50 / portTICK_PERIOD_MS); // wait for one second

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // We were able to obtain or "Take" the semaphore and can now access the
      // shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to
      // print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the state of the button:
      Serial.print(millis());
      Serial.println(" : TASK 1");

      // xSemaphoreGive(
      //     xSerialSemaphore); // Now free or "Give" the Serial Port for others.
    }
  }
}

void TaskBlink2(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(A0, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(A0, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(50 / portTICK_PERIOD_MS); // wait for one second
    digitalWrite(A0, LOW); // turn the LED off by making the voltage LOW
    vTaskDelay(50 / portTICK_PERIOD_MS); // wait for one second

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // We were able to obtain or "Take" the semaphore and can now access the
      // shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to
      // print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the state of the button:
      Serial.print(millis());
      Serial.println(" : TASK 2");

      xSemaphoreGive(
          xSerialSemaphore); // Now free or "Give" the Serial Port for others.
    }
  }
}

void TaskBlink3(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(A2, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(A2, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(100 / portTICK_PERIOD_MS); // wait for one second
    digitalWrite(A2, LOW); // turn the LED off by making the voltage LOW
    vTaskDelay(100 / portTICK_PERIOD_MS); // wait for one second

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // We were able to obtain or "Take" the semaphore and can now access the
      // shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to
      // print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the state of the button:
      Serial.print(millis());
      Serial.println(" : TASK 3");

      xSemaphoreGive(
          xSerialSemaphore); // Now free or "Give" the Serial Port for others.
    }
  }
}

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(1000);
  Serial.println(F("RTOS DEMO"));

  // while (!Serial) {
  //   ; // wait for serial port to connect. Needed for native USB, on LEONARDO,
  //     // MICRO, YUN, and other 32u4 based boards.
  // }

  // Semaphores are useful to stop a Task proceeding, where it should be paused
  // to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can
  // set it up here.
  if (xSerialSemaphore == NULL) // Check to confirm that the Serial Semaphore
                                // has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex(); // Create a mutex semaphore we
                                                // will use to manage the Serial
                                                // Port
    if ((xSerialSemaphore) != NULL)
      xSemaphoreGive((xSerialSemaphore)); // Make the Serial Port available for
                                          // use, by "Giving" the Semaphore.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(TaskBlink1, (const portCHAR *)"Blink1" // A name just forhumans
              ,
              128 // This stack size can be checked & adjusted by reading the
                  // Stack Highwater
              ,
              NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the
                      // highest, and 0 being the lowest.
              ,
              NULL);

  xTaskCreate(TaskBlink2, (const portCHAR *)"Blink2" // A name just forhumans
              ,
              128 // This stack size can be checked & adjusted by reading the
                  // Stack Highwater
              ,
              NULL, 3 // Priority, with 3 (configMAX_PRIORITIES - 1) beingthe
                      // highest, and 0 being the lowest.
              ,
              NULL);

  xTaskCreate(TaskBlink3, (const portCHAR *)"Blink3" // A name just forhumans
              ,
              128 // This stack size can be checked & adjusted by readingthe
                  // Stack Highwater
              ,
              NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) beingthe
                      // highest, and 0 being the lowest.
              ,
              NULL);

  Serial.println(F("RTOS DEMO START"));
}

void loop() {
  // Serial.println(F("LOOP"));
  // delay(1000);
}
