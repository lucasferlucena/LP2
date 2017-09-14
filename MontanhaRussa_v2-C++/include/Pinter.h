#ifndef PRINTER_H_
#define PRINTER_H_

#include "atomic"

using namespace std;

class Printer {
public:
	static void printInt(int i, string x);
	static void printString(string x, int i);

private:
	static atomic_flag lock;
};

#endif /* PRINTER_H_ */

