# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
# Executable name
TARGET = todoapp_v1
# Directories
SRCDIR = src
BUILDDIR = build
BINDIR = bin

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# Object files
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Dependency files
DEPS = $(OBJS:.o=.d)

# Default target
all: $(BINDIR)/$(TARGET)

# Linking
$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compiling with dependency generation
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean
clean:
	$(RM) -r $(BUILDDIR) $(BINDIR)

# Phony targets
.PHONY: all clean