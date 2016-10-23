#
#  Makefile
#  Image Processing Projet Template
#  by Ghanshyam Bhutra
#
# Determine the platform

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CC := clang++
else
	CC := g++
endif

SRCDIR := src
LIBDIR := lib
BUILDDIR := build
TARGETDIR := bin
INSTALLBINDIR := /usr/local/bin
TARGET := bin/project

# Normal CPP files
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -c
ifeq ($(UNAME_S),Linux)
	CFLAGS += -std=gnu++11 -O2 # -fPIC
else
	CFLAGS += -std=c++11 -stdlib=libc++ -O2 -Wno-deprecated 
endif

LIBPATH := -L /System/Library/Frameworks/OpenGL.framework/Libraries -L /System/Library/Frameworks/GLUT.framework -L /usr/local/lib
LIB := -lGL -lGLU -lm -lobjc -lstdc++ 
INC := -I include -I /usr/local/include
FRAMEWORK = -framework GLUT -framework OpenGL

$(TARGET): $(OBJECTS) $(OBJECTS2)
	@mkdir -p $(TARGETDIR)
	@echo " Linking..."
	@echo " $(CC) $(FRAMEWORK) $^ -o $(TARGET) $(LIBPATH) $(LIB)"; $(CC) $(FRAMEWORK) $^ -o $(TARGET) $(LIBPATH) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $< 

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

install:
	@echo " Installing...";
	@echo " cp $(TARGET) $(INSTALLBINDIR)"; cp $(TARGET) $(INSTALLBINDIR)
	
distclean:
	@echo " Un-Installing...";
	@echo " rm /usr/local/bin/CoralSeaServer"; rm /usr/local/bin/CoralSeaServer

.PHONY: clean
