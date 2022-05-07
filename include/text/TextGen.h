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

/// \brief Generate different styles of texts
class TextGen {
public:
    static void PrintTitle();
    
    static void PrintText(string s, string end = "\n") { cout << s << end; }
    static void PrintRequest(string s, string end = "\n") { cout << style<CYAN_> << s << style<RESET_> << end; }
    static void PrintReward(string s, string end = "\n") { cout << style<YELLOW_> << s << style<RESET_> << end; }
    static void PrintWarning(string s, string end = "\n") { cout << style<RED_> << s << style<RESET_> << end; }
    
    static string Input() {
        string input;
        PrintText("> ", "");
        getline(cin, input);
        if (input == "quit") {
            PrintText("Bye!");
            exit(0);
        }
        return input;
    }
};

#endif // TEXTGEN_H_