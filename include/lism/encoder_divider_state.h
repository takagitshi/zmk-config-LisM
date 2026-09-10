/*
 * Copyright (c) 2026 Takashi Imai
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

struct lism_encoder_divider_state {
    uint32_t direction;
    uint32_t count;
    bool has_direction;
};

void lism_encoder_divider_state_reset(struct lism_encoder_divider_state *state);

bool lism_encoder_divider_state_update(struct lism_encoder_divider_state *state,
                                       uint32_t direction, uint32_t divisor);
