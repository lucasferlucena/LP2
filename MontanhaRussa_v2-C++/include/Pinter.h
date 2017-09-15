#ifndef PRINTER_H_
#define PRINTER_H_

#include "atomic"
#include "string"

using namespace std;

class Printer {
public:
	static void printInt(int i, string x);
	static void printInt(int i);
	static void printStringE(string x, int i, int n);
	static void printStringS(string x, int i, int n);
	static void printString(string x);

private:
    static string txt;
    static string txts;
	static atomic_flag lock;
};

#endif /* PRINTER_H_ */

