COMPILER = gcc
CFLAGS   = -g -std=c++11
LDFRAGS  = -L $(shell pg_config --libdir) -lpq  -lstdc++
LIBS     =
INCLUDE  = -I $(shell pg_config --includedir) -I $(shell pg_config --includedir-server)
TARGET   = ../bin/chppl
OBJDIR   = ./obj
SOURCES  = $(wildcard *.cpp)
OBJECTS  = $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))

all:
.PHONY: all clean

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFRAGS) $(CFLAGS)

$(OBJDIR)/%.o: %.cpp
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)
