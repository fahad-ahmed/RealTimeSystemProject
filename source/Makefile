# Compiler settings - Can change to clang++ if preferred
CXX=g++
CXXFLAGS=-Wall -std=c++11

# Libraries to link against
LIBS=-lshout -lasound -ltinyxml2

# Source files listed row-wise for easier editing
SOURCES= \
    Mp3Reader.cpp \
    ShoutCast.cpp \
	MicrophoneListener.cpp \
	PriorityDrivenScheduler.cpp \
	EDFScheduler.cpp \
    TaskScheduler.cpp \
	ConfigReader.cpp \
    MainRTS.cpp

# Object files
OBJECTS=$(SOURCES:.cpp=.o)

# Executable name
EXEC=MainRTS

# Build all targets
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean build files
clean:
	rm -f $(OBJECTS) $(EXEC)

# Phony targets
.PHONY: all clean
