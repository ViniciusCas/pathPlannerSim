CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I./elements -I./pathfinding

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = .
BUILD_DIR = build
ELEMENTS_DIR = elements
PATHFINDING_DIR = pathfinding

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/window.cpp \
       $(ELEMENTS_DIR)/node.cpp \
       $(ELEMENTS_DIR)/obstacle.cpp \
       $(ELEMENTS_DIR)/togglebutton.cpp \
       $(PATHFINDING_DIR)/RRT.cpp \
       $(PATHFINDING_DIR)/algorithm.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TARGET = rrt_pathfinding

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)
# Compiling the source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)  # Create the directory if it doesn't exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean
