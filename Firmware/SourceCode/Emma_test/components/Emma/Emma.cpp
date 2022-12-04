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

// #include <Emma_LovyanGFX.hpp>
// LGFX_ChappieCore lcd;



using namespace std;




int Emma::Init()
{
    PrintBoardInfos();

    






    while (1) {
        // cout << "?" << endl;
        delay(3000);
    }

    return 0;
}






/**
 * @brief Print board's infomations
 * 
 */
void Emma::PrintBoardInfos()
{
    /* Print Logo */
    printf(EmmaLogo.c_str());
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
    printf(" Minimum free heap size: %ld bytes\n", esp_get_minimum_free_heap_size());

    // printf(Cowsay("Emma HMI Core Boarad :)", 0).c_str());
}


/**
 * @brief Listen to the cow
 * 
 * @param whatCowSay 
 * @param ANSIcolor 
 * @return string what cow is saying
 */
string Emma::Cowsay(string whatCowSay, int ANSIcolor)
{
    string ret;

    /* Set corlor */
    if (ANSIcolor != 0)
        ret = "\033[0;" + to_string(ANSIcolor) + "m";
    
    /* Print dialog */
    ret.append(" ");
    ret.append(whatCowSay.length() + 2, '_');
    ret.append("\n< ");
    ret.append(whatCowSay);
    ret.append(" >\n ");
    ret.append(whatCowSay.length() + 2, '-');

    /* Print cow */
    ret.append(R"(
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
    )");
    ret.append("\033[0m\n");
    
    return ret;
}
