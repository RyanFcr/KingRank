#ifndef TEXTGEN_H_
#define TEXTGEN_H_

#include <iomanip>
#include <iostream>
using std::ostream; using std::string; 
using std::cout; using std::cin;

#include "common/Macro.h"

template<int ansiStyle = 0>
ostream& style(ostream& out) { 
    return out << "\033[" << ansiStyle << "m"; 
}

class TextGen {
public:
    static void PrintText(string s, string end = "\n") { cout << s << end; }
    static void PrintWarning(string s, string end = "\n") { cout << style<RED_> << s << style<RESET_> << end; }
    static string Input() {
        string input;
        PrintText("> ", "");
        getline(cin, input);
        return input;
    }
};

#endif // TEXTGEN_H_