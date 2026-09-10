/*
 * Copyright (c) 2026 Takashi Imai
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

enum lism_gesture_direction {
    LISM_GESTURE_NONE,
    LISM_GESTURE_LEFT,
    LISM_GESTURE_RIGHT,
    LISM_GESTURE_UP,
    LISM_GESTURE_DOWN,
};

enum lism_gesture_axis {
    LISM_GESTURE_AXIS_X,
    LISM_GESTURE_AXIS_Y,
};

struct lism_gesture_state {
    int32_t x;
    int32_t y;
    int64_t cooldown_until_ms;
    bool cooling_down;
};

void lism_gesture_state_reset(struct lism_gesture_state *state);

enum lism_gesture_direction lism_gesture_state_update(struct lism_gesture_state *state,
                                                       enum lism_gesture_axis axis, int32_t value,
                                                       bool sync, int64_t now_ms,
                                                       uint32_t threshold, uint32_t cooldown_ms);
