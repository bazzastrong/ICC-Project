#include "extension.h"

int Dec_to_bin(int num) {
	int binary(0), i(1), r;
	while (num != 0){
		r = num % 2;
		binary = binary + (r * i);
		num = num / 2;
		i *= 10;
	}
return binary;
}

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
