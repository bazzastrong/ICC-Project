#include "extension.h"

int decimal_to_binary(const int& dec) {
  int i(0), n(0);
  int bin = dec;
  bool flag(true);
    while(flag) {
        if(pow(2,i) >= n) {
        flag = false;
        } else {
        ++i;
        }
    }
    for(int j(i); j > 0; --j) {
        if(pow(2, j) <= n) {
        bin = bin*10 + 1;
        n -= pow(2, j);
        } else {
        bin *= 10;
        }
    }
return bin;
}

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
