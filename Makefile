objPath = ./obj
target = a.exe

all:
	make -C src && make -C obj

run :
	make all;
	rm $(objPath)/*.o
	./a.exe

clean:
	rm $(objPath)/*.o
	rm $(target)