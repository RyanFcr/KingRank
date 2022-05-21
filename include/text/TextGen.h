#ifndef TEXTGEN_H_
#define TEXTGEN_H_

#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::ostream;
using std::string;

#include "common/Macro.h"
#include "map/Scene.h"
#include "map/Map.h"
#include "common/Global.h"

template <int ansiStyle = 0>
ostream &style(ostream &out)
{
    return out << "\033[" << ansiStyle << "m";
}

/// \brief Generate different styles of texts
class TextGen
{
public:
    static void Init();
    static void PrintTitle();
    static void PrintDirection(const Map &m, const Position &p);

    template <int ansiStyle = 0>
    static void Print(string s, string end = "\n")
    {
        cout << style<ansiStyle> << s << style<plain> << end;
    }
    template <int ansiStyle = 0>
    static void PrintNoEnd(string s, string end = "\n")
    {
        cout << style<ansiStyle> << s << style<plain>;
    }

    template <int ansiStyle = 0>
    static void PrintCenter(string s, int totalLength)
    {
        int len = s.length();
        if (len <= totalLength)
        {
            for (int i = 0; i < (totalLength - len) / 2; i++)
            {
                cout << " ";
            }
        }
        Print<ansiStyle>(s);
    }
    template <int ansiStyle = 0>
    static void PrintTwo(string s1, string s2, int totalLength, string end = "\n")
    {
        cout << style<ansiStyle> << s1 << style<plain>;
        int len1 = s1.length();
        int len2 = s2.length();
        if (len2 <= totalLength)
        {
            for (int i = 0; i < (totalLength - len2) / 2 - len1; i++)
            {
                cout << " ";
            }
        }
        Print<ansiStyle>(s2);
    }
    template <int ansiStyle = 0>
    static void PrintThree(string s1, string s2, string s3, int totalLength, string end = "\n")
    {
        cout << style<ansiStyle> << s1 << style<plain>;
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();
        if (len2 <= totalLength)
        {
            for (int i = 0; i < (totalLength  - len2) / 2 - len1; i++)
            {
                cout << " ";
            }
        }
        PrintNoEnd<ansiStyle>(s2);
        if (len3 <= totalLength)
        {
            for (int i = 0; i < (totalLength - len2 ) / 2 - len3; i++)
            {
                cout << " ";
            }
        }
        Print<ansiStyle>(s3);
    }
    // template <int ansiStyle = 0>
    // static void PrintTail(string s, int totalLength)
    // {
    //     int len = s.length();
    //     if (len <= totalLength)
    //     {
    //         for (int i = 0; i < (totalLength - len) ; i++)
    //         {
    //             cout << " ";
    //         }
    //     }
    //     Print<ansiStyle>(s);
    // }

    static string Input();
};

#endif // TEXTGEN_H_