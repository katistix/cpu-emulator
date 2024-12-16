CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
SRC_DIR = src
BUILD_DIR = build
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/cpu.cpp $(SRC_DIR)/assembler.cpp
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXEC = $(BUILD_DIR)/cpu_emulator

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(EXEC) $(PROGRAM_FILE)

clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)

.PHONY: all run clean
