CXX = g++
CSSFLAGS = -std=c++17 -Wall -Wextra -O2

#directories
SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/mp

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

LIBS = -lws2_32

all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# Rule to build object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILDDIR)

# Phony targets
.PHONY: all clean