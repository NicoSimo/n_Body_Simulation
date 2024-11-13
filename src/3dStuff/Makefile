# Variables for paths and flags
CC = g++
CFLAGS = -I/opt/homebrew/opt/glfw/include -I/opt/homebrew/opt/glew/include -DGL_SILENCE_DEPRECATION
LDFLAGS = -L/opt/homebrew/opt/glfw/lib -L/opt/homebrew/opt/glew/lib -lglfw -lGLEW -framework OpenGL
TARGET = test
SRC = test.cpp

# Build target
$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS) $(LDFLAGS)

# Clean target
clean:
	rm -f $(TARGET)
