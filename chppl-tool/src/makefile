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

-include $(OBJDIR)/*.d
$(OBJDIR)/%.o: %.cpp
	@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -MD -MF $(@:.o=.d) -o $@ -c $<

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(OBJECTS:.o=.d) $(TARGET)
