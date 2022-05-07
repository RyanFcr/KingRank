#include "text/TextGen.h"
#include <wchar.h>

#ifdef _WIN32
    #include <Windows.h>
#endif

void TextGen::PrintTitle() {
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
    cout << style<YELLOW_>;
    PrintText("██╗  ██╗██╗███╗   ██╗ ██████╗ ██████╗  █████╗ ███╗   ██╗██╗  ██╗");
    PrintText("██║ ██╔╝██║████╗  ██║██╔════╝ ██╔══██╗██╔══██╗████╗  ██║██║ ██╔╝");
    PrintText("█████╔╝ ██║██╔██╗ ██║██║  ███╗██████╔╝███████║██╔██╗ ██║█████╔╝");
    PrintText("██╔═██╗ ██║██║╚██╗██║██║   ██║██╔══██╗██╔══██║██║╚██╗██║██╔═██╗ ");
    PrintText("██║  ██╗██║██║ ╚████║╚██████╔╝██║  ██║██║  ██║██║ ╚████║██║  ██╗");
    PrintText("╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝");
    cout << style<RESET_>;
}