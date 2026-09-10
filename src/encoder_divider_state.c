/*
 * Copyright (c) 2026 Takashi Imai
 *
 * SPDX-License-Identifier: MIT
 */

#include <lism/encoder_divider_state.h>

void lism_encoder_divider_state_reset(struct lism_encoder_divider_state *state) {
    state->direction = 0;
    state->count = 0;
    state->has_direction = false;
}

bool lism_encoder_divider_state_update(struct lism_encoder_divider_state *state,
                                       uint32_t direction, uint32_t divisor) {
    if (divisor == 0) {
        lism_encoder_divider_state_reset(state);
        return false;
    }

    if (!state->has_direction || state->direction != direction) {
        state->direction = direction;
        state->count = 0;
        state->has_direction = true;
    }

    state->count++;
    if (state->count < divisor) {
        return false;
    }

    state->count = 0;
    return true;
}
