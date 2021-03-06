/*
MIT License

Copyright (c) 2020 Marcin Borowicz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef UTILS_BUTTON_H
#define UTILS_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

struct button;

typedef enum {
    BUTTON_EVENT_RELEASE = 0,
    BUTTON_EVENT_PRESS,
    BUTTON_EVENT_CLICK,
    BUTTON_EVENT_HOLD,
    BUTTON_EVENT_LONG_HOLD
} button_event;

typedef bool (*button_is_pressed)(struct button *self);
typedef void (*button_event_callback)(struct button *self, button_event event, int counter);

typedef enum {
        BUTTON_STATE_RELEASE = 0,
        BUTTON_STATE_PRESS,
        BUTTON_STATE_HOLD,
        BUTTON_STATE_LONG_HOLD,
} button_state;

struct button_descriptor {
        button_is_pressed is_pressed;
        button_event_callback event_callback;

        uint32_t debounce_timeout;
        uint32_t click_timeout;
        uint32_t hold_timeout;
        uint32_t long_hold_timeout;
};

struct button {
        struct button_descriptor const *desc;
        uint32_t press_tick;
        uint32_t debounce_tick;
        bool is_pressed;
        int counter;
        button_state state;

        struct button *next;
};

void button_register(struct button *self, const struct button_descriptor *desc);
void button_unregister(struct button *self);
button_state button_get_state(struct button *self);
bool button_is_pressed_debounced(struct button *self);

void button_service(void);

extern uint32_t button_port_get_current_tick(void);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_BUTTON_H */
