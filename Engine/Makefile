
CC = g++
AR = ar rcs

CFLAGS = -Wall -std=c++11

LIBSRC = Window.cpp SpriteBatch.cpp Camera2D.cpp Engine.cpp Sprite.cpp GLSLProgram.cpp InputManager.cpp Exception.cpp IOManager.cpp ImageLoader.cpp ResourceManager.cpp TextureCache.cpp Time.cpp picoPNG.cpp
HEADSRC = Vertex.h GLTexture.h

LIB = ../lib/libEngine.a
HEADPATH = ../lib/Engine/

all: $(LIB)

OBJ = $(LIBSRC:.cpp=.o)
HEAD = $(LIBSRC:.cpp=.h)


$(LIB): $(OBJ)
	$(AR) $@ $^
	#rm -f $(OBJ)
	cp -t $(HEADPATH) $(HEAD) $(HEADSRC)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -f $(LIB) $(OBJ)

rebuild:	clean all

.PHONY: all rebuild clean




#Martin Korsgaard, 2006
