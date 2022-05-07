CXX = g++

objPath = ../../obj
includePath = ../../include

objs = $(objPath)/MapGen.o

all : $(objs)

$(objPath)/%.o: %.cpp
	$(CXX) $^ -c -o $@ -I $(includePath)