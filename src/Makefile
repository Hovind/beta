CC = g++

CFLAGS = -Wall -std=c++11  -I../lib/Engine -I../headers

LDFLAGS = -lSDL2 -lGLEW -lGL -L../lib -lEngine

SRC = GameException.cpp Box.cpp Game.cpp Interface.cpp TileList.cpp Grid.cpp Map.cpp Node.cpp OpenSet.cpp ClosedSet.cpp Troll.cpp Unit.cpp main.cpp

TARGET = ../alpha

all: $(TARGET)

OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)
	#rm -f $(OBJ)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)

rebuild:	clean all

.PHONY: all rebuild clean
