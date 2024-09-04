CC = g++
CFLAGS = -std=c++11 -Wall

BIN_DIR = ./bin
OBJ_DIR = ./obj
TEST_DIR = ./test
SRC_DIR = ./src
INCLUDE_DIR = ./include

TARGET = $(BIN_DIR)/app.exe
TEST_EXECUTABLE = $(BIN_DIR)/test.exe

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
TESTS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
TEST_OBJS = $(TESTS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(TEST_EXECUTABLE): ${TEST_OBJS}
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(TEST_EXECUTABLE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -MMD -MP -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -MMD -MP -c $< -o $@

dirs:
	@mkdir -p $(dir $(OBJS))
	@mkdir -p $(BIN_DIR)

all: clean dirs $(TARGET)

test: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE)

run: all 
	${TARGET}

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

debug: CFLAGS += -g
debug: all
