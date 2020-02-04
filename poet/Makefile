all: poet

poet: *.cpp dict.txt
	g++ -o poet *.cpp

dict.txt:
	perl dictgen.pl

clean: 
	-rm dict.txt poet
