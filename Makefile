CXX := g++
CXXFLAGS := -std=c++17 -O2 -march=native -Wall -Wextra -Wpedantic
SRC_DIR := src
BIN_DIR := bin

PROGS := \
	constant_O1 \
	log_n_binary_search \
	n_sum \
	nlogn_merge_sort \
	n2_bubble_sort \
	exp_2n_fibonacci \
	factorial_permutations

SRCS := $(addprefix $(SRC_DIR)/,$(addsuffix .cpp,$(PROGS)))
BINS := $(addprefix $(BIN_DIR)/,$(PROGS))

all: $(BIN_DIR) $(BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
