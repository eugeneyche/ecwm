CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := ecwm
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS :=
LIB := -lX11
INC := -Iinclude

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIB) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) -rf $(BUILDDIR) $(TARGET)

new: clean $(TARGET)

.PHONY:
	clean
