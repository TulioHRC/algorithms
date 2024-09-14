CC = g++
CFLAGS = -std=c++11 -Wall

TEST_DIR = ./tests
OBJ_DIR = ./tests/obj
BIN_DIR = ./tests/bin

TEST_EXECUTABLE = $(BIN_DIR)/test.exe
UI_SPECIFIC_TESTS = $(TEST_DIR)/ui_sort_test.cpp
ALL_TESTS = $(wildcard $(TEST_DIR)/*.cpp)

ALL_TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(ALL_TESTS))

SPECIFIC_TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(UI_SPECIFIC_TESTS))

dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

$(TEST_EXECUTABLE): dirs | $(ALL_TEST_OBJS)
	$(CC) $(CFLAGS) $(ALL_TEST_OBJS) -o $(TEST_EXECUTABLE)

$(BIN_DIR)/UI_SPECIFIC_TESTS.exe: dirs | $(SPECIFIC_TEST_OBJS)
	$(CC) $(CFLAGS) $(SPECIFIC_TEST_OBJS) -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TEST_EXECUTABLE)

ui-test: $(BIN_DIR)/UI_SPECIFIC_TESTS.exe
	$(BIN_DIR)/UI_SPECIFIC_TESTS.exe

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: dirs all ui-test clean
