CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lncurses

# List of source files
SRCS = main.cpp src/Board.cpp src/Dashboard.cpp src/Game.cpp src/Drawable.cpp src/Character.cpp src/Empty.cpp
 
# List of object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = game

# Build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Pattern rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)
