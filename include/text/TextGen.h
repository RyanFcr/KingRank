#ifndef TEXTGEN_H_
#define TEXTGEN_H_

#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::ostream;
using std::string;

#include "common/Global.h"
#include "common/Macro.h"

template <int ansiStyle = 0>
ostream& style(ostream& out) {
    return out << "\033[" << ansiStyle << "m";
}

/// \brief Generate different styles of texts
class TextGen {
   public:
    static void Init();
    static void PrintTitle();

    template <int ansiStyle = 0>
    static void Print(string s, string end = "\n");

    static void Print(string s, string end = "\n", int ansiStyle = 0);

    static void PrintCenter(string s, int totalLength, int ansiStyle = 0);

    static void PrintTwo(string s1,
                         string s2,
                         int totalLength,
                         string fill = " ",
                         int ansiStyle1 = 0,
                         int ansiStyle2 = 0);

    static void PrintThree(string s1,
                           string s2,
                           string s3,
                           int totalLength,
                           string fill = " ",
                           int ansiStyle1 = 0,
                           int ansiStyle2 = 0,
                           int ansiStyle3 = 0);

    static string Input();
    static int InputInt();
};

template <int ansiStyle>
void TextGen::Print(string s, string end) {
    cout << style<ansiStyle> << s << style<plain> << end;
}
#endif  // TEXTGEN_H_