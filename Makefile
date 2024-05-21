CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -fopenmp -Iinclude

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGETDIR = bin

TARGET_EXEC = main
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
TARGET := $(TARGETDIR)/$(TARGET_EXEC)

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES)
	@mkdir -p $(BUILDDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGETDIR)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: all
all: clean $(TARGET)
