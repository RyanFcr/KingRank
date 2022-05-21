#include "text/TextGen.h"
#include <wchar.h>

#ifdef _WIN32
    #include <Windows.h>
#endif

void TextGen::Init() {
#ifdef _WIN32
    //http://m.blog.csdn.net/article/details?id=52789570
    //控制台显示乱码纠正
   // system("chcp 65001"); //设置字符集（使用SetConsoleCP(65001)设置无效，原因未知）
    SetConsoleOutputCP (65001);
    CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。
    info.cbSize = sizeof(info);
    info.dwFontSize.Y = 16; // leave X as zero
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

void TextGen::PrintDirection(const Map &m, const Position &p) {
    /// @attention high coupling!
    if (p.fieldX >= 0 && p.fieldX < m.GetRowNum() && p.fieldY >= 0 && p.fieldY < m.GetColNum(p.fieldX)) {
        // Field Name
        string centerFieldName{m.GetField(p.fieldX, p.fieldY).GetName()};
        string leftFieldName{centerFieldName}, rightFieldName{centerFieldName};
        string upFieldName{centerFieldName}, downFieldName{centerFieldName};

        // Coordinate
        string leftCo{""}, rightCo{""}, upCo{""}, downCo{""};
        string centerCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY) + ")";
        
        // left
        if (p.sceneX - 1 < 0 && p.fieldX == 0) {
            leftFieldName = "";
            leftCo = "";
        }
        else if (p.sceneX - 1 < 0) {
            leftFieldName = m.GetField(p.fieldX - 1, p.fieldY).GetName();
            leftCo = "(" + std::to_string(fieldSize - 1) + "," + std::to_string(p.sceneY) + ")";
        }
        else
            leftCo = "(" + std::to_string(p.sceneX - 1) + "," + std::to_string(p.sceneY) + ")";

        // right
        if (p.sceneX + 1 >= fieldSize && p.fieldX == m.GetRowNum() - 1) {
            rightFieldName = "";
            rightCo = "";
        }
        else if (p.sceneX + 1 >= fieldSize) {
            rightFieldName = m.GetField(p.fieldX + 1, p.fieldY).GetName();
            rightCo = "(" + std::to_string(0) + "," + std::to_string(p.sceneY) + ")";
        }
        else
            rightCo = "(" + std::to_string(p.sceneX + 1) + "," + std::to_string(p.sceneY) + ")";

        // down
        if (p.sceneY - 1 < 0 && p.fieldY == 0) {
            downFieldName = "";
            downCo = "";
        }
        else if (p.sceneY - 1 < 0) {
            downFieldName = m.GetField(p.fieldX, p.fieldY - 1).GetName();
            downCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(fieldSize - 1) + ")";
        }
        else
            downCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY - 1) + ")";

        // up
        if (p.sceneY + 1 >= fieldSize && p.fieldY == m.GetColNum(p.fieldX) - 1) {
            upFieldName = "";
            upCo = "";
        }
        else if (p.sceneY + 1 >= fieldSize) {
            upFieldName = m.GetField(p.fieldX, p.fieldY + 1).GetName();
            upCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(0) + ")";
        }
        else
            upCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY + 1) + ")"; 
        
        // draw the map
        // up
        if (upFieldName != "") {
            PrintCenter(upFieldName, maxTerminalLenghth);
            PrintCenter(upCo, maxTerminalLenghth);
            PrintCenter("test state", maxTerminalLenghth);
            PrintCenter("⇑", maxTerminalLenghth);
        }
        // left
        if (leftFieldName != "") {

        }
        Print(centerFieldName);
        Print(centerCo);
        Print<buff>("test");
        // right
        if (rightFieldName != "") {

        }
        // down
        if (downFieldName != "") {

        }
    }
    else {
        Print<warning>("You has entered an unknown field!");
    }                           
}

string TextGen::Input() {
    string input;
    Print("> ", "");
    getline(cin, input);

    if (input == "quit") {
        Print("Bye!");
        exit(0);
    }
    return input;
}