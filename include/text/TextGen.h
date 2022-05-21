#ifndef TEXTGEN_H_
#define TEXTGEN_H_

#include <iomanip>
#include <iostream>
using std::ostream; using std::string; 
using std::cout; using std::cin;

#include "common/Macro.h"
#include "map/Scene.h"
#include "map/Map.h"
#include "common/Global.h"

template<int ansiStyle = 0>
ostream& style(ostream& out) { 
    return out << "\033[" << ansiStyle << "m"; 
}

/// \brief Generate different styles of texts
class TextGen {
public:
    static void Init();
    static void PrintTitle();
    static void PrintDirection(const Map &m, const Position &p);
    
    template<int ansiStyle = 0>
    static void Print(string s, string end = "\n") {
        cout << style<ansiStyle> << s << style<plain> << end;
    }

    template<int ansiStyle = 0>
    static void PrintCenter(string s, int totalLength) {
        int len = s.length();
        if (len <= totalLength) {
            for (int i = 0; i < (totalLength - len) / 2; i++) {
                cout << " ";
            }
        }
        Print<ansiStyle>(s);
    }

    static string Input();
};

#endif // TEXTGEN_H_