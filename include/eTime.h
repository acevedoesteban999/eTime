#include "esp_log.h"
#include "driver/gptimer.h"
#include "esp_task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#define TIME_FRECUENCY_TIMER 40e6

void clear_timer_hard(gptimer_handle_t timer_handler);

void init_timer_hard(gptimer_handle_t timer_handler, int alarm, void *callback);

void clear_timer_soft(TimerHandle_t timer_handler);

void init_timer_soft(TimerHandle_t timer_handler, int alarm, void *callback);
