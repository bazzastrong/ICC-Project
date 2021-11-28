#include "extension.h"

int Dec_to_bin(int num) {
	long int binary(0), i(1), rem;
	while (num != 0)
	{
		rem = num % 2;
		binary = binary + (rem * i);
		num = num / 2;
		i *= 10;
	}
	return binary;
}
/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
