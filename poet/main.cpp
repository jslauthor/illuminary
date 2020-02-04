#include "WordDatabase.h"

int main(int argc, char* argv[])
{
	if ( argc == 1 ) {
		return 0;
	}

	char* toRhyme = argv[1];

	WordDatabase db;
	if ( !db.load("dict.txt") ) {
		fprintf(stderr, "Error: Couldn't load dict.txt\n");
		return -1;
	}

	WordArray words;
	db.findRhymes(words, toRhyme, NULL );
	for( unsigned i = 0; i < words.size(); i++ ) {
		words[i]->print();
	}

	return 0;
}
