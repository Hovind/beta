all:
	cd Engine; make
	cd src; make

clean:
	cd Engine; make clean
	cd src; make clean

rebuild:	clean all
