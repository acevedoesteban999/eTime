#include "eTime.h"

//HARDW

// static bool gptimer_callback(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx)
// {
//     xQueueSendFromISR(queue,&_struct,pdMS_TO_TICKS(1)); 
//     return true;
// }

void clear_timer_hard(gptimer_handle_t timer_handler){
    if(timer_handler != NULL){
        if(gptimer_stop(timer_handler) == ESP_OK)
            if(gptimer_disable(timer_handler) == ESP_OK)
                gptimer_del_timer(timer_handler);
    }
}

void init_timer_hard(gptimer_handle_t timer_handler,int alarm,void* callback){
    //FOR REINIT
    
    clear_timer_hard(timer_handler);
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = TIME_FRECUENCY_TIMER
    };
    ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &timer_handler));
    
    gptimer_alarm_config_t alarm_config;
    alarm_config.alarm_count = alarm;
    alarm_config.reload_count = 0;
    alarm_config.flags.auto_reload_on_alarm = true;


    ESP_ERROR_CHECK(gptimer_set_alarm_action(timer_handler, &alarm_config));
    gptimer_start(timer_handler);
    
    gptimer_event_callbacks_t callbacks = {
        .on_alarm = callback,
    };
    ESP_ERROR_CHECK(gptimer_register_event_callbacks(timer_handler, &callbacks, NULL));
    ESP_ERROR_CHECK(gptimer_enable(timer_handler));
    ESP_ERROR_CHECK(gptimer_start(timer_handler));
    
}




// void timer_soft_callback(gptimer_handle_t xTimer) {
//     size_t index =  ( size_t )pvTimerGetTimerID(xTimer);
//     xQueueSendFromISR(queue,&_struct,pdMS_TO_TICKS(1)); 
// }

void clear_timer_soft(TimerHandle_t timer_handler){
    if (timer_handler != NULL && xTimerIsTimerActive(timer_handler) != pdFALSE){
        xTimerStop(timer_handler,1);
        xTimerDelete(timer_handler,1);
    }
}
   
void init_timer_soft(TimerHandle_t timer_handler,int alarm,void*callback ){
    clear_timer_soft(timer_handler);
    timer_handler = xTimerCreate(
        "timer_soft",              
        pdMS_TO_TICKS(alarm), 
        pdTRUE,                   
        NULL,
        callback             
    );
    xTimerStart(timer_handler,1);
}
