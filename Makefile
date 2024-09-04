CC = g++
CFLAGS = -std=c++11 -Wall

BIN_DIR = ./bin
OBJ_DIR = ./obj
SRC_DIR = ./src
INCLUDE_DIR = ./include

TARGET = $(BIN_DIR)/app.exe

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) # Cria os diretórios para os objetos
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -MMD -MP -c $< -o $@

dirs:
	@mkdir -p $(dir $(OBJS))
	@mkdir -p $(BIN_DIR)

all: clean dirs $(TARGET)

run: all 
	${TARGET}

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

debug: CFLAGS += -g
debug: all
