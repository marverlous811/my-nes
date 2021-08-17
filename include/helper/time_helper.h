//
// Created by Ows on 14/08/2021.
//

#ifndef NES_CLOUD_TIME_HELPER_H
#define NES_CLOUD_TIME_HELPER_H

#include <chrono>
#include <thread>

static void delay_ms(unsigned int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif //NES_CLOUD_TIME_HELPER_H
