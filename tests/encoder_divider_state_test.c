/* SPDX-License-Identifier: MIT */

#include <assert.h>
#include <stdio.h>

#include <lism/encoder_divider_state.h>

#define UP 1U
#define DOWN 2U

int main(void) {
    struct lism_encoder_divider_state state;

    lism_encoder_divider_state_reset(&state);
    assert(!lism_encoder_divider_state_update(&state, UP, 2));
    assert(lism_encoder_divider_state_update(&state, UP, 2));
    assert(!lism_encoder_divider_state_update(&state, UP, 2));
    assert(lism_encoder_divider_state_update(&state, UP, 2));

    lism_encoder_divider_state_reset(&state);
    assert(!lism_encoder_divider_state_update(&state, DOWN, 2));
    assert(lism_encoder_divider_state_update(&state, DOWN, 2));

    lism_encoder_divider_state_reset(&state);
    assert(!lism_encoder_divider_state_update(&state, UP, 2));
    assert(!lism_encoder_divider_state_update(&state, DOWN, 2));
    assert(lism_encoder_divider_state_update(&state, DOWN, 2));
    assert(!lism_encoder_divider_state_update(&state, UP, 2));
    assert(lism_encoder_divider_state_update(&state, UP, 2));

    lism_encoder_divider_state_reset(&state);
    for (int i = 0; i < 8; i++) {
        assert(!lism_encoder_divider_state_update(&state, i % 2 == 0 ? UP : DOWN, 2));
    }

    lism_encoder_divider_state_reset(&state);
    assert(!lism_encoder_divider_state_update(&state, UP, 2));
    lism_encoder_divider_state_reset(&state);
    assert(!lism_encoder_divider_state_update(&state, UP, 2));
    assert(lism_encoder_divider_state_update(&state, UP, 2));

    lism_encoder_divider_state_reset(&state);
    assert(lism_encoder_divider_state_update(&state, UP, 1));
    assert(lism_encoder_divider_state_update(&state, DOWN, 1));

    lism_encoder_divider_state_reset(&state);
    assert(!lism_encoder_divider_state_update(&state, UP, 0));
    assert(!state.has_direction && state.count == 0);

    puts("encoder_divider_state_test: PASS");
    return 0;
}
