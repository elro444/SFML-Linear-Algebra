CC = g++

UTIL_DIR = lib/GlobalUtil

INC_DIRS = include lib $(UTIL_DIR)
MACROS = "-DUNUSED(x)=(void)(x)" -DSFML_STATIC
CFLAGS = -g -O3 -std=c++17 -static $(MACROS) $(addprefix -I,$(INC_DIRS))

LIB_DIRS = lib/SFML-libs
LIBRARIES = sfml-graphics-s sfml-network-s sfml-window-s sfml-audio-s sfml-system-s
LIBRARIES += opengl32 freetype winmm gdi32 openal32 flac vorbisenc vorbisfile vorbis ogg ws2_32
LDFLAGS = -static $(addprefix -L,$(LIB_DIRS)) $(addprefix -l,$(LIBRARIES))

# Object files dir
BUILD_DIR = build

# Re-compile if these were changed..
# DEPS = $(wildcard include/*.hpp)

TARGET = LinearAlgebra.exe
SOURCES = $(wildcard Scenes/*.cpp) $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,%,$(patsubst Scenes/%.cpp,%,$(SOURCES)))
OBJS = $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(OBJECTS)))
# OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

.PHONY: default clean run

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

run: $(TARGET)
	.\$(TARGET)

$(BUILD_DIR)/%.o : src/%.cpp | $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.o : Scenes/%.cpp | $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/util.o: $(UTIL_DIR)/util.cpp $(UTIL_DIR)/util.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR):
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@rm $(TARGET)
