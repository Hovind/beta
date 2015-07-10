all:
	cd Engine; make
	cd src; make

clean:
	cd Engine; make clean
	cd src; make clean

engine:
	cd Engine; make
src:
	cd src; make
	
rebuild:	clean all
