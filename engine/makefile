CXX = g++
CXXFLAGS = -Wall -DDEBUG -g -lraylib
OBJDIR := obj
TARGET := app
SRCS := $(wildcard lib/*.hpp) $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp lib/%.hpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm $(TARGET)
	rm $(OBJDIR)/*.o