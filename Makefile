CC = g++
CFLAGS = -std=c++11 -Wall

TEST_DIR = ./tests
OBJ_DIR = ./tests/obj
BIN_DIR = ./tests/bin

TEST_EXECUTABLE = $(BIN_DIR)/test.exe
UI_SPECIFIC_TESTS = $(TEST_DIR)/ui_sort_test.cpp
SORT_SPECIFIC_TESTS = $(TEST_DIR)/sort_algorithms_test.cpp
ALL_TESTS = $(wildcard $(TEST_DIR)/*.cpp)

ALL_TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(ALL_TESTS))

UI_SPECIFIC_TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(UI_SPECIFIC_TESTS))
SORT_SPECIFIC_TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SORT_SPECIFIC_TESTS))

dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

$(TEST_EXECUTABLE): dirs | $(ALL_TEST_OBJS)
	$(CC) $(CFLAGS) $(ALL_TEST_OBJS) -o $(TEST_EXECUTABLE)

$(BIN_DIR)/UI_SPECIFIC_TESTS.exe: dirs | $(UI_SPECIFIC_TEST_OBJS)
	$(CC) $(CFLAGS) $(UI_SPECIFIC_TEST_OBJS) -o $@

$(BIN_DIR)/SORT_SPECIFIC_TESTS.exe: dirs | $(SORT_SPECIFIC_TEST_OBJS)
	$(CC) $(CFLAGS) $(SORT_SPECIFIC_TEST_OBJS) -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TEST_EXECUTABLE)

ui-test: $(BIN_DIR)/UI_SPECIFIC_TESTS.exe
	$(BIN_DIR)/UI_SPECIFIC_TESTS.exe

sort-test: $(BIN_DIR)/SORT_SPECIFIC_TESTS.exe
	$(BIN_DIR)/SORT_SPECIFIC_TESTS.exe

test: ui-test sort-test

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: dirs all ui-test clean
