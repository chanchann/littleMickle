#pragma once
#include <unistd.h>
#include <iostream>

// 原子实现 
// 补偿策略
// 就是n个线程同时进行原子操作,必然有n-1个线程失败
// 当自旋到一定次数时, 就把时间片让出, 尽快让原子操作成功的那个线程操作完
class Spinlock {
public:
    Spinlock() 
    : _lock(UNLOCK) {}
    void lock() {
        for (;;) {
            if (_lock == UNLOCK && __sync_bool_compare_and_swap(&_lock, UNLOCK, LOCK)) {
                return;
            }
            for (int n = 1; n < spin; n <<= 1) {
                for (int i = 0; i < n; i++) {
                    __asm__("pause");
                }
                if (_lock == UNLOCK && __sync_bool_compare_and_swap(&_lock, UNLOCK, LOCK)) {
                    return;
                }
            }
            sched_yield();
        }
    }
    void unlock() {
        _lock = UNLOCK;
    }

private:
    static constexpr uint16_t spin = 1 << 11;
    static constexpr uint8_t LOCK = 1;
    static constexpr uint8_t UNLOCK = 0;
    volatile uint8_t _lock;
};