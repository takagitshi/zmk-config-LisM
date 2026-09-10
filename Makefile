ROOT_DIR := $(abspath $(CURDIR))
WEST_WS := $(ROOT_DIR)/_west

# 並列数を環境変数 PARALLEL から取得。未設定の場合はCPUコア数を自動検出。
PARALLEL ?= $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)

.PHONY: all_p all all_studio_p all_studio setup-west single test-gesture clean check-build-tools

check-build-tools:
	@command -v yq >/dev/null || { echo 'yq is not installed.' >&2; exit 1; }
	@command -v west >/dev/null || { echo 'west is not installed.' >&2; exit 1; }

# studio を含まない全ビルド (並列実行)
all_p: check-build-tools
	@FILTER_MODE=exclude_studio bash scripts/build-matrix.sh --parallel=$(PARALLEL)

# studio を含まない全ビルド (逐次実行)
all: check-build-tools
	@FILTER_MODE=exclude_studio bash scripts/build-matrix.sh


# studio を含む全ビルド (並列実行)
all_studio_p: check-build-tools
	@FILTER_MODE=all bash scripts/build-matrix.sh --parallel=$(PARALLEL)

# studio を含む全ビルド (逐次実行)
all_studio: check-build-tools
	@FILTER_MODE=all bash scripts/build-matrix.sh


single: check-build-tools
	@bash scripts/build-single.sh

setup-west:
	@bash .devcontainer/setup-west.sh

test-gesture:
	@TEST_BIN="$$(mktemp -t lism-gesture-state-test.XXXXXX)"; \
		trap 'rm -f "$${TEST_BIN}"' EXIT; \
		cc -std=c11 -Wall -Wextra -Werror -Iinclude \
			src/gesture_state.c tests/gesture_state_test.c -o "$${TEST_BIN}"; \
		"$${TEST_BIN}"

clean:
	@echo "🧹 Cleaning firmware_builds/"
	@rm -rf "$(ROOT_DIR)/firmware_builds"
	@echo "🧹🧹🧹 Cleaned!! 🧹🧹🧹"
	@echo "To reset workspace (optional): rm -rf $(WEST_WS) && make setup-west"
