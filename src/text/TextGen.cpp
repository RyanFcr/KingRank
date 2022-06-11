#include "text/TextGen.h"
#include <wchar.h>
#include <sstream>
#include <string>
#include "bag/Bag.h"
using std::istringstream;
using std::to_string;

#ifdef _WIN32
#include <Windows.h>
#endif

void TextGen::Init() {
#ifdef _WIN32
    // http://m.blog.csdn.net/article/details?id=52789570
    //控制台显示乱码纠正
    // system("chcp 65001"); //设置字符集（使用SetConsoleCP(65001)设置无效，原因未知）
    SetConsoleOutputCP(65001);
    CONSOLE_FONT_INFOEX info = {0};  // 以下设置字体来支持中文显示。
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = 16;  // leave X as zero
    info.FontWeight = FW_NORMAL;
    wcscpy(info.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
#endif
}

void TextGen::PrintTitle() {
    Print<title>("██╗  ██╗██╗███╗   ██╗ ██████╗ ██████╗  █████╗ ███╗   ██╗██╗  ██╗");
    Print<title>("██║ ██╔╝██║████╗  ██║██╔════╝ ██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝");
    Print<title>("█████╔╝ ██║██╔██╗ ██║██║  ███╗██████╔╝███████║██╔██╗ ██║█████╔╝");
    Print<title>("██╔═██╗ ██║██║╚██╗██║██║   ██║██╔══██╗██╔══██║██║╚██╗██║██╔═██╗ ");
    Print<title>("██║  ██╗██║██║ ╚████║╚██████╔╝██║  ██║██║  ██║██║ ╚████║██║  ██╗");
    Print<title>("╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝");
}

string TextGen::Input() {
    string input;
    Print("> ", "");
    getline(cin, input);
    return input;
}

int TextGen::InputInt() {
    string input;
    while (1) {
        Print("> ", "");
        getline(cin, input);
        istringstream iss(input);
        int val;
        char remain;
        if (iss >> val && !(iss >> remain))
            return val;
        else
            Print<warning>("请输入正确的指令!请输入一个整数");
    }
}