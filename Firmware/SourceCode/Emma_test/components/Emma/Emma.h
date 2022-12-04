/**
 * @file Emma.h
 * @author Forairaaaaa
 * @brief Emma BSP
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <iostream>
#include <string>

using namespace std;


#define BSP_VERISON     "v1.0"



const string EmmaLogo = R"(
 ______  __    __  __    __  ______
/\  ___\/\ "-./  \/\ "-./  \/\  __ \
\ \  __\\ \ \-./\ \ \ \-./\ \ \  __ \
 \ \_____\ \_\ \ \_\ \_\ \ \_\ \_\ \_\
  \/_____/\/_/  \/_/\/_/  \/_/\/_/\/_/

)";


class Emma {
private:
    int test;
public:
    int Init();
    void PrintBoardInfos();
    string Cowsay(string whatCowSay, int ANSIcolor);
    void PrintLogo();
};

