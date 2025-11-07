CXX = g++
CXXFLAGS = -Wall
LDFLAGS  = -lraylib
OBJDIR := obj
TARGET := app
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS)
	
debug: $(OBJS)
	$(CXX) $(CXXFLAGS) -DDEBUG -g -o app $(OBJS)
	
log: $(OBJS)
	$(CXX) $(CXXFLAGS) -DLOG -o app $(OBJS)
	
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm $(TARGET)
	rm $(OBJDIR)/*.o