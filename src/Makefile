.PHONY : all

CXX = g++

objPath = ..\obj
includePath = ..\include

objs = $(objPath)\main.o

all:
	make -C map
	make -C text

$(objPath)\%.o: %.cpp
	$(CXX) $^ -c -o $@ -I $(includePath)