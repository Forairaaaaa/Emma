// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// #include "esp32-hal.h"
#include "soc/soc_caps.h"
#include "driver/ledc.h"
#include "esp32-hal-ledc.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define TAG "ledc"

#ifdef SOC_LEDC_SUPPORT_HS_MODE
#define LEDC_CHANNELS           (SOC_LEDC_CHANNEL_NUM<<1)
#else
#define LEDC_CHANNELS           (SOC_LEDC_CHANNEL_NUM)
#endif

//Use XTAL clock if possible to avoid timer frequency error when setting APB clock < 80 Mhz
//Need to be fixed in ESP-IDF
#ifdef SOC_LEDC_SUPPORT_XTAL_CLOCK
#define LEDC_DEFAULT_CLK        LEDC_USE_XTAL_CLK
#else
#define LEDC_DEFAULT_CLK        LEDC_AUTO_CLK
#endif

#define LEDC_MAX_BIT_WIDTH      SOC_LEDC_TIMER_BIT_WIDE_NUM

/*
 * LEDC Chan to Group/Channel/Timer Mapping
** ledc: 0  => Group: 0, Channel: 0, Timer: 0
** ledc: 1  => Group: 0, Channel: 1, Timer: 0
** ledc: 2  => Group: 0, Channel: 2, Timer: 1
** ledc: 3  => Group: 0, Channel: 3, Timer: 1
** ledc: 4  => Group: 0, Channel: 4, Timer: 2
** ledc: 5  => Group: 0, Channel: 5, Timer: 2
** ledc: 6  => Group: 0, Channel: 6, Timer: 3
** ledc: 7  => Group: 0, Channel: 7, Timer: 3
** ledc: 8  => Group: 1, Channel: 0, Timer: 0
** ledc: 9  => Group: 1, Channel: 1, Timer: 0
** ledc: 10 => Group: 1, Channel: 2, Timer: 1
** ledc: 11 => Group: 1, Channel: 3, Timer: 1
** ledc: 12 => Group: 1, Channel: 4, Timer: 2
** ledc: 13 => Group: 1, Channel: 5, Timer: 2
** ledc: 14 => Group: 1, Channel: 6, Timer: 3
** ledc: 15 => Group: 1, Channel: 7, Timer: 3
*/

uint8_t channels_resolution[LEDC_CHANNELS] = {0};

uint32_t ledcSetup(uint8_t chan, uint32_t freq, uint8_t bit_num)
{
    if(chan >= LEDC_CHANNELS || bit_num > LEDC_MAX_BIT_WIDTH){
        ESP_LOGE("TAG", "No more LEDC channels available! (maximum %u) or bit width too big (maximum %u)", LEDC_CHANNELS, LEDC_MAX_BIT_WIDTH);
        return 0;
    }

    uint8_t group=(chan/8), timer=((chan/2)%4);

    ledc_timer_config_t ledc_timer = {
        .speed_mode       = (ledc_mode_t)group,
        .duty_resolution  = (ledc_timer_bit_t)bit_num,
        .timer_num        = (ledc_timer_t)timer,
        .freq_hz          = freq,
        .clk_cfg          = LEDC_DEFAULT_CLK
    };
    if(ledc_timer_config(&ledc_timer) != ESP_OK)
    {
        ESP_LOGE("TAG", "ledc setup failed!");
        return 0;
    }
    channels_resolution[chan] = bit_num;
    return ledc_get_freq((ledc_mode_t)group,(ledc_timer_t)timer);
}

void ledcWrite(uint8_t chan, uint32_t duty)
{
    if(chan >= LEDC_CHANNELS){
        return;
    }
    uint8_t group=(chan/8), channel=(chan%8);

    //Fixing if all bits in resolution is set = LEDC FULL ON
    uint32_t max_duty = (1 << channels_resolution[chan]) - 1;

    if((duty == max_duty) && (max_duty != 1)){
        duty = max_duty + 1;
    }

    ledc_set_duty((ledc_mode_t)group, (ledc_channel_t)channel, duty);
    ledc_update_duty((ledc_mode_t)group, (ledc_channel_t)channel);
}

uint32_t ledcRead(uint8_t chan)
{
    if(chan >= LEDC_CHANNELS){
        return 0;
    }
    uint8_t group=(chan/8), channel=(chan%8);
    return ledc_get_duty((ledc_mode_t)group,(ledc_channel_t)channel);
}

uint32_t ledcReadFreq(uint8_t chan)
{
    if(!ledcRead(chan)){
        return 0;
    }
    uint8_t group=(chan/8), timer=((chan/2)%4);
    return ledc_get_freq((ledc_mode_t)group,(ledc_timer_t)timer);
}

uint32_t ledcWriteTone(uint8_t chan, uint32_t freq)
{
    if(chan >= LEDC_CHANNELS){
        return 0;
    }
    if(!freq){
        ledcWrite(chan, 0);
        return 0;
    }

    uint8_t group=(chan/8), timer=((chan/2)%4);

    ledc_timer_config_t ledc_timer = {
        .speed_mode       = (ledc_mode_t)group,
         .duty_resolution  = (ledc_timer_bit_t)10,
        .timer_num        = (ledc_timer_t)timer,
        .freq_hz          = freq, 
        .clk_cfg          = LEDC_DEFAULT_CLK
    };

    if(ledc_timer_config(&ledc_timer) != ESP_OK)
    {
        ESP_LOGE("TAG", "ledcSetup failed!");
        return 0;
    }
    channels_resolution[chan] = 10;

    uint32_t res_freq = ledc_get_freq((ledc_mode_t)group,(ledc_timer_t)timer);
    ledcWrite(chan, 0x1FF);
    return res_freq;
}

uint32_t ledcWriteNote(uint8_t chan, note_t note, uint8_t octave){
    const uint16_t noteFrequencyBase[12] = {
    //   C        C#       D        Eb       E        F       F#        G       G#        A       Bb        B
        4186,    4435,    4699,    4978,    5274,    5588,    5920,    6272,    6645,    7040,    7459,    7902
    };

    if(octave > 8 || note >= NOTE_MAX){
        return 0;
    }
    uint32_t noteFreq =  (uint32_t)noteFrequencyBase[note] / (uint32_t)(1 << (8-octave));
    return ledcWriteTone(chan, noteFreq);
}

void ledcAttachPin(uint8_t pin, uint8_t chan)
{
    if(chan >= LEDC_CHANNELS){
        return;
    }
    uint8_t group=(chan/8), channel=(chan%8), timer=((chan/2)%4);
    
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = pin,
        .speed_mode     = (ledc_mode_t)group,
        .channel        = (ledc_channel_t)channel,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = (ledc_timer_t)timer,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
}

// void ledcDetachPin(uint8_t pin)
// {
    // pinMatrixOutDetach(pin, false, false);
    // gpio_matrix_out(pin, 0x100, false, false);
    // ESP_LOGE(TAG, ".... :(");
// }

uint32_t ledcChangeFrequency(uint8_t chan, uint32_t freq, uint8_t bit_num)
{
    if(chan >= LEDC_CHANNELS || bit_num > LEDC_MAX_BIT_WIDTH){
        ESP_LOGE("TAG", "LEDC channel not available! (maximum %u) or bit width too big (maximum %u)", LEDC_CHANNELS, LEDC_MAX_BIT_WIDTH);
        return 0;
    }
    uint8_t group=(chan/8), timer=((chan/2)%4);

    ledc_timer_config_t ledc_timer = {
        .speed_mode       = (ledc_mode_t)group,
        .duty_resolution  = (ledc_timer_bit_t)bit_num,
        .timer_num        = (ledc_timer_t)timer,
        .freq_hz          = freq, 
        .clk_cfg          = LEDC_DEFAULT_CLK
    };

    if(ledc_timer_config(&ledc_timer) != ESP_OK)
    {
        ESP_LOGE("TAG", "ledcChangeFrequency failed!");
        return 0;
    }
    channels_resolution[chan] = bit_num;
    return ledc_get_freq((ledc_mode_t)group,(ledc_timer_t)timer);
}

static int8_t pin_to_channel[SOC_GPIO_PIN_COUNT] = { 0 };
static int cnt_channel = LEDC_CHANNELS;
void analogWrite(uint8_t pin, int value) {
  // Use ledc hardware for internal pins
  if (pin < SOC_GPIO_PIN_COUNT) {
    if (pin_to_channel[pin] == 0) {
      if (!cnt_channel) {
          ESP_LOGE("TAG", "No more analogWrite channels available! You can have maximum %u", LEDC_CHANNELS);
          return;
      }
      pin_to_channel[pin] = cnt_channel--;
      ledcAttachPin(pin, cnt_channel);
      ledcSetup(cnt_channel, 1000, 8);
    }
    ledcWrite(pin_to_channel[pin] - 1, value);
  }
}

int8_t analogGetChannel(uint8_t pin) {
    return pin_to_channel[pin] - 1;
}
