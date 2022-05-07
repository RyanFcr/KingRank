CXX = g++

objPath = ../obj
includePath = ../include

objs = $(objPath)/main.o

all : $(objs)
	make -C map;
	make -C text

$(objPath)/%.o: %.cpp
	$(CXX) $^ -c -o $@ -I $(includePath)