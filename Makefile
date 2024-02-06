

SRCDIR = src
INCDIR = include

PROGRAM = Tetris

HFILES = $(INCDIR)/View.h \
		 $(INCDIR)/ViewGrid.h \
		 $(INCDIR)/Shader.h \
		 $(INCDIR)/ModelGenerator.h \
		 $(INCDIR)/Tetromino.h \
		 $(INCDIR)/TetrominoTransforms.h \
		 $(INCDIR)/Game.h \
		 $(INCDIR)/Grid.h \
		 $(INCDIR)/Angel.h \
		 $(INCDIR)/vec.h \
		 $(INCDIR)/mat.h

SOURCES = $(SRCDIR)/View.cpp \
		  $(SRCDIR)/ViewGrid.cpp \
		  $(SRCDIR)/Shader.cpp \
		  $(SRCDIR)/ModelGenerator.cpp \
		  $(SRCDIR)/Tetromino.cpp \
		  $(SRCDIR)/TetrominoTransforms.cpp \
		  $(SRCDIR)/Game.cpp \
		  $(SRCDIR)/Grid.cpp

OBJECTS = $(SOURCES:.cpp=.o)

INCLUDE = -I$(INCDIR) -I/usr/include
C++FLAGS = -g -Wall $(INCLUDE) -std=c++11
ARFLAGS = -rcuv
DEPENDFLAGS = -Y
LDFLAGS = -Wl,--no-as-needed
LIBS = -lGLEW -lGL -lglut -lm -lrt

.SUFFIXES: .SUFFIXES .cpp .o

all: $(PROGRAM)

.cpp.o: $(SOURCES) $(HFILES)
	g++ -c $(C++FLAGS) $< -o $(<:.cpp=.o)

$(PROGRAM): $(SRCDIR)/$(PROGRAM).o $(OBJECTS)
	g++ $(SRCDIR)/$(PROGRAM).o $(OBJECTS) -o $(PROGRAM) $(LIBS) $(LDFLAGS)

clean:
	rm -f $(PROGRAM) $(SRCDIR)/$(PROGRAM).o $(OBJECTS)