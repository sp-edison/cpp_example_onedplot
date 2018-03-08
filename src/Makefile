TARGET		= Hello.x

CXX			= g++
CXXFLAGS    =
LINKER		= g++
LFLAGS		= 

BINDIR		= ../bin

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

.SUFFIXES : .cpp .o

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(BINDIR) $(OBJS)
	$(LINKER) $(LFLAGS) -o $@ $(OBJS)
	@echo "Linking complete!"

$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm -rf $(OBJS) $(BINDIR)/$(TARGET)
