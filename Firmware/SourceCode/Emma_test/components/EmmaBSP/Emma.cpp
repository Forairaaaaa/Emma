/**
 * @file Emma.cpp
 * @author Forairaaaaa
 * @brief Emma BSP
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Emma.h"
#include "sdkconfig.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"



/**
 * @brief BSP init 
 * 
 * @param enLcd 
 * @param enEncoder 
 * @param enLedRGB 
 * @param enBuzzer 
 */
void EMMA::Init(bool enLcd, bool enEncoder, bool enLedRGB, bool enBuzzer)
{
    /* LCD init */
    if (enLcd) {
        Lcd.init();
        Lcd.fillScreen(TFT_BLACK);
        Lcd.setBrightness(100);
        // Lcd.setRotation(1);
    }
    
    /* Print infomations */
    PrintBoardInfo(true);

    /* Encoder init */
    if (enEncoder) {
        Encoder.Init(EMMA_PIN_EC_A, EMMA_PIN_EC_B, EMMA_PIN_EC_BTN);
    }


}


/**
 * @brief Print board's infomations
 * 
 */
void EMMA::PrintBoardInfo(bool printOnLcd)
{
    /* Print Logo */
    printf("%s\n", Logo.c_str());
    printf(" Emma HMI Core Boarad :)\n BSP %s\n", BSP_VERISON);

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }
    printf(" %luMB %s flash\n", flash_size / (1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf(" Minimum free heap size: %ld bytes\n\n", esp_get_minimum_free_heap_size());

    /* Print infos on LCD */
    if (printOnLcd) {
        Lcd.setCursor(0, 0);
        Lcd.printf(Logo.c_str());
        Lcd.printf("\n Emma HMI Core Boarad :)\n BSP %s\n", BSP_VERISON);
        Lcd.printf(" %luMB %s flash\n", flash_size / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
        Lcd.printf(" Minimum free heap size: %ld bytes\n\n", esp_get_minimum_free_heap_size());
    }
}


/**
 * @brief Listen to the cow
 * 
 * @param whatCowSay 
 * @param ANSIcolor e.g. ANSI_BLUE
 * @return string that cow want to say
 */
std::string EMMA::Cowsay(std::string whatCowSay, int ANSIcolor)
{
    std::string ret;

    /* Set corlor */
    if (ANSIcolor != 0)
        ret = "\033[0;" + std::to_string(ANSIcolor) + "m";
    
    /* Print dialog */
    ret.append(" ");
    ret.append(whatCowSay.length() + 2, '_');
    ret.append("\n< ");
    ret.append(whatCowSay);
    ret.append(" >\n ");
    ret.append(whatCowSay.length() + 2, '-');
    ret.append(Cow);

    /* Reset color */
    if (ANSIcolor != 0)
        ret.append("\033[0m\n");
    else
        ret.append("\n");
    
    return ret;
}


void delay(uint32_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}
