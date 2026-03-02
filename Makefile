CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++23 -Icnpy
BUILD_DIR = ./build
INCLUDE_DIR = cnpy
TARGET = monte-carlo-pi

LDLIBS = -lz
SOURCES := main.cpp cnpy/cnpy.cpp
OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean