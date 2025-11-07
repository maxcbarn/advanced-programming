CXX = g++
CXXFLAGS = -Wall
LDFLAGS  = -lraylib -lm
OBJDIR := obj
TARGET := app
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

debug: CXXFLAGS += -g -DDEBUG -DLOG
debug: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

log: CXXFLAGS += -DLOG
log: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(TARGET)
	rm -f $(OBJDIR)/*.o
