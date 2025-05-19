CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude 
SRC = main.cpp src/connection.cpp src/request.cpp src/server.cpp

BUILD_DIR = build

OBJ = $(SRC:.cpp=.o)
OBJ := $(addprefix $(BUILD_DIR)/, $(OBJ))

TARGET = $(BUILD_DIR)/app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
