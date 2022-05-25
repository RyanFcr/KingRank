#ifndef TEXTGEN_H_
#define TEXTGEN_H_

#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::ostream;
using std::string;

#include "bag/Bag.h"
#include "common/Global.h"
#include "common/Macro.h"
#include "map/Map.h"
#include "map/Scene.h"
#include "skill/AttackSkill.h"
#include "skill/SupportSkill.h"

template <int ansiStyle = 0>
ostream& style(ostream& out) {
    return out << "\033[" << ansiStyle << "m";
}

/// \brief Generate different styles of texts
class TextGen {
   public:
    static void Init();
    static void PrintTitle();
    static void PrintDirection(const Map& m, const Position& p);
    static void PrintBag(const Bag& bag);
    static void PrintMoney(int money);
    static void PrintSkill(const map<string, AttackSkill>& attackSkills,
                           const map<string, SupportSkill>& supportSkills);

    template <int ansiStyle = 0>
    static void Print(string s, string end = "\n");

    template <int ansiStyle = 0>
    static void PrintCenter(string s, int totalLength);

    template <int ansiStyle = 0>
    static void PrintTwo(string s1, string s2, int totalLength, string fill = " ");

    template <int ansiStyle = 0>
    static void PrintThree(string s1, string s2, string s3, int totalLength, string fill = " ");

    static string Input();
    static int InputInt();
};

template <int ansiStyle>
void TextGen::Print(string s, string end) {
    cout << style<ansiStyle> << s << style<plain> << end;
}

template <int ansiStyle>
void TextGen::PrintCenter(string s, int totalLength) {
    int len = s.length();
    if (len <= totalLength) {
        for (int i = 0; i < (totalLength - len) / 2; i++) {
            cout << " ";
        }
    }
    Print<ansiStyle>(s);
}

template <int ansiStyle>
void TextGen::PrintTwo(string s1, string s2, int totalLength, string fill) {
    cout << style<ansiStyle> << s1 << style<plain>;
    int len1 = s1.length();
    int len2 = s2.length();
    if (len2 <= totalLength) {
        for (int i = 0; i < (totalLength - len2) / 2 - len1; i++) {
            cout << fill;
        }
    }
    Print<ansiStyle>(s2);
}

template <int ansiStyle>
void TextGen::PrintThree(string s1, string s2, string s3, int totalLength, string fill) {
    cout << style<ansiStyle> << s1 << style<plain>;
    int len1 = s1.length();
    int len2 = s2.length();
    int len3 = s3.length();
    if (len2 <= totalLength) {
        for (int i = 0; i < (totalLength - len2) / 2 - len1; i++) {
            cout << fill;
        }
    }
    Print<ansiStyle>(s2, "");
    if (len3 <= totalLength) {
        for (int i = 0; i < (totalLength - len2) / 2 - len3; i++) {
            cout << fill;
        }
    }
    Print<ansiStyle>(s3);
}
#endif  // TEXTGEN_H_