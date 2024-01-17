# Compiler settings
CXX = g++
CXXFLAGS = -Wall -Werror -Ofast -std=c++20 -Iinclude

# Linker settings
LDFLAGS = -L/path/to/custom/lib # If your libraries are in non-standard paths
LDLIBS = -lboost_system -lpthread -luv -lssl -lcrypto

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) \
          $(wildcard $(SRCDIR)/models/*.cpp) \
          $(wildcard $(SRCDIR)/dao/*.cpp) \
          $(wildcard $(SRCDIR)/services/*.cpp) \
          $(wildcard $(SRCDIR)/networking/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Executable name
EXECUTABLE = teamphotogenic

# Default target
all: $(BINDIR)/$(EXECUTABLE)

# Linking
$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

# Compiling
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# .PHONY to declare non-file targets
.PHONY: all clean
