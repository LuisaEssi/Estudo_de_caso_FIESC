
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void tarefa1(void *pvParameters);
void tarefa2(void *pvParameters);

xSemaphoreHandle mutex;

float temperatura = 0;

int main(void)
{    

    mutex = xSemaphoreCreateMutex();

    xTaskCreate(&tarefa1, "Tarefa 1", 1024, NULL, 1, NULL);  
    xTaskCreate(&tarefa2, "Tarefa 2'", 1024, NULL, 1, NULL);
 
    vTaskStartScheduler();

    return 0;
}

void tarefa1 (void *pvParameters)
{
    for (;;)
    { 
        if(xSemaphoreTake(mutex, 500/portTICK_PERIOD_MS) ){
            temperatura += 1.5;
            printf("Temperatura (Celsius): %.3f\n", temperatura);
            // printf("%d\n",xTaskGetTickCount());
            xSemaphoreGive(mutex);
        }        
        vTaskDelay(1000/portTICK_PERIOD_MS);  
    }
}

void tarefa2(void *pvParameters)
{
    for (;;)
    {
        if(xSemaphoreTake(mutex, 500/portTICK_PERIOD_MS) ){
            temperatura = (temperatura * 1.8) + 32;
            printf("Temperatura (Fahrenheit): %.3f\n", temperatura);
            // printf("%d\n",xTaskGetTickCount());
            temperatura = (temperatura-32)/1.8;
            xSemaphoreGive(mutex);
        }
        vTaskDelay(500/portTICK_PERIOD_MS); 

    }
}

