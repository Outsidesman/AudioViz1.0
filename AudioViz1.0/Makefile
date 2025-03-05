#
#   Copyright (c) 2025 - Matt C
#    All rights reserved.
#
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Include flags
INCFLAGS = -I/opt/homebrew/include

# Library flags
LIBFLAGS = -L/opt/homebrew/lib -lportaudio -lglfw -lGLEW -framework OpenGL

# Source files
SRC = main.cpp palettes.cpp sliders.cpp render.cpp audio.cpp

# Header files
HEADERS = palettes.h sliders.h render.h audio.h

# Output executable
TARGET = AudioViz_1.0

# Build the executable
$(TARGET): $(SRC) #$(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) \
	$(INCFLAGS) \
	$(LIBFLAGS)

# Make and run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -f $(TARGET)