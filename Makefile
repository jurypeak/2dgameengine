CXX = g++
CXXFLAGS = -Wall -Wfatal-errors -std=c++17 -I./libs -I./include $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua

SRC = $(shell find src -name '*.cpp')
OBJ = $(SRC:.cpp=.o)
TARGET = crucialEngine

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

