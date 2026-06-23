CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude -m64
LDFLAGS := -m64
TARGET := factory_tool_system
SRC := $(wildcard src/*.cpp)
BUILD_DIR := build
OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)