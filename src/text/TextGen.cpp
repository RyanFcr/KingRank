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

void TextGen::PrintDirection(const Map& m, const Position& p) {
    if (p.fieldX >= 0 && p.fieldX < m.GetRowNum() && p.fieldY >= 0 && p.fieldY < m.GetColNum(p.fieldX)) {
        // Field Name
        string centerFieldName{m.GetField(p.fieldX, p.fieldY).GetName()};
        string leftFieldName{centerFieldName}, rightFieldName{centerFieldName};
        string upFieldName{centerFieldName}, downFieldName{centerFieldName};

        // Coordinate
        string leftCo{""}, rightCo{""}, upCo{""}, downCo{""};
        string centerCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY) + ")";

        // down
        if (p.sceneX - 1 < 0 && (p.fieldX == 0 || m.GetColNum(p.fieldX - 1) <= p.fieldY)) {
            downFieldName = "";
            downCo = "";
        } else if (p.sceneX - 1 < 0) {
            downFieldName = m.GetField(p.fieldX - 1, p.fieldY).GetName();
            downCo = "(" + std::to_string(fieldSize - 1) + "," + std::to_string(p.sceneY) + ")";
        } else
            downCo = "(" + std::to_string(p.sceneX - 1) + "," + std::to_string(p.sceneY) + ")";

        // up
        if (p.sceneX + 1 >= fieldSize && (p.fieldX == m.GetRowNum() - 1 || m.GetColNum(p.fieldX + 1) <= p.fieldY)) {
            upFieldName = "";
            upCo = "";
        } else if (p.sceneX + 1 >= fieldSize) {
            upFieldName = m.GetField(p.fieldX + 1, p.fieldY).GetName();
            upCo = "(" + std::to_string(0) + "," + std::to_string(p.sceneY) + ")";
        } else {
            upCo = "(" + std::to_string(p.sceneX + 1) + "," + std::to_string(p.sceneY) + ")";
        }
        // left
        if (p.sceneY - 1 < 0 && p.fieldY == 0) {
            leftFieldName = "";
            leftCo = "";
        } else if (p.sceneY - 1 < 0) {
            leftFieldName = m.GetField(p.fieldX, p.fieldY - 1).GetName();
            leftCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(fieldSize - 1) + ")";
        } else
            leftCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY - 1) + ")";

        // right
        if (p.sceneY + 1 >= fieldSize && p.fieldY == m.GetColNum(p.fieldX) - 1) {
            rightFieldName = "";
            rightCo = "";
        } else if (p.sceneY + 1 >= fieldSize) {
            rightFieldName = m.GetField(p.fieldX, p.fieldY + 1).GetName();
            rightCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(0) + ")";
        } else
            rightCo = "(" + std::to_string(p.sceneX) + "," + std::to_string(p.sceneY + 1) + ")";
        // draw the map

        // if left can go
        if (leftFieldName != "") {
            // up
            if (upFieldName != "") {
                PrintCenter(upFieldName, maxTerminalLenghth);
                PrintCenter(upCo, maxTerminalLenghth);
                PrintCenter("up state", maxTerminalLenghth);
                PrintCenter("|", maxTerminalLenghth);
                PrintCenter("|", maxTerminalLenghth);
                PrintCenter("|", maxTerminalLenghth);
            }

            // right
            if (rightFieldName != "") {
                PrintThree(leftFieldName, centerFieldName, rightFieldName, maxTerminalLenghth);
                PrintThree(leftCo, centerCo, rightCo, maxTerminalLenghth, "-");
                PrintThree("left state", "center", "right state", maxTerminalLenghth);
            } else {
                PrintTwo(leftFieldName, centerFieldName, maxTerminalLenghth);
                PrintTwo(leftCo, centerCo, maxTerminalLenghth, "-");
                PrintTwo("left state", "center", maxTerminalLenghth);
            }

            // down
            if (downFieldName != "") {
                PrintCenter("|", maxTerminalLenghth);
                PrintCenter("|", maxTerminalLenghth);
                PrintCenter("|", maxTerminalLenghth);
                PrintCenter(downFieldName, maxTerminalLenghth);
                PrintCenter(downCo, maxTerminalLenghth);
                PrintCenter("down state", maxTerminalLenghth);
            }
        } else {
            // up
            if (upFieldName != "") {
                Print(upFieldName);
                Print(upCo);
                Print("up state");
                Print("|");
                Print("|");
                Print("|");
            }

            if (rightFieldName != "") {
                PrintTwo(centerFieldName, rightFieldName, maxTerminalLenghth);
                PrintTwo(centerCo, rightCo, maxTerminalLenghth, "-");
                PrintTwo("center", "right state", maxTerminalLenghth);
            } else {
                Print(centerFieldName);
                Print(centerCo);
                Print("center");
            }
            // down
            if (downFieldName != "") {
                Print("|");
                Print("|");
                Print("|");
                Print(downFieldName);
                Print(downCo);
                Print("down state");
            }
        }
    } else {
        Print<warning>("You has entered an unknown field!");
    }
}

void TextGen::PrintBag(const Bag& bag) {
    Print("Weight Limit: " + to_string(bag.GetWeightLimit()));
    Print("Current Weight: " + to_string(bag.GetCurWeight()));
    PrintMedicine(bag.GetMedicineNames());
    PrintWeapon(bag.GetWeaponNames());
}

void TextGen::PrintMedicine(const vector<pair<string, int>> medicineNames) {
    Print("Medicines:");
    if (medicineNames.size() == 0) {
        Print("empty", "");
    } else {
        for (size_t i = 0; i < medicineNames.size(); i++) {
            Print(to_string(int(i)) + ". " + medicineNames[i].first + ":" + to_string(medicineNames[i].second), "  ");
        }
    }
    Print("");
}

void TextGen::PrintWeapon(const vector<string> weaponNames) {
    Print("Weapons:");
    if (weaponNames.size() == 0) {
        Print("empty", "");
    } else {
        for (size_t i = 0; i < weaponNames.size(); i++) {
            Print(to_string(int(i)) + ". " + weaponNames[i], " ");
        }
    }
    Print("");
}

void TextGen::PrintMoney(int money) {
    Print<reward>("Kin: " + to_string(money));
}

void TextGen::PrintSkills(const vector<string>& attackSkills, const vector<string>& supportSkills) {
    PrintAttackSkills(attackSkills);
    PrintSupportSkills(supportSkills);
}

void TextGen::PrintAttackSkills(const vector<string>& attackSkills) {
    /// @attention too long string!
    Print<warning>("Attack Skills:");
    if (attackSkills.size() == 0) {
        Print("empty", "");
    } else {
        for (size_t i = 0; i < attackSkills.size(); i++) {
            Print(to_string(int(i)) + ". " + attackSkills[i], " ");
        }
    }
    Print("");
}

void TextGen::PrintSupportSkills(const vector<string>& supportSkills) {
    /// @attention too long string!
    Print<buff>("Support Skills:");
    if (supportSkills.size() == 0) {
        Print("empty", "");
    } else {
        for (size_t i = 0; i < supportSkills.size(); i++) {
            Print(to_string(int(i)) + ". " + supportSkills[i], " ");
        }
    }
    Print("");
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
            Print<warning>("Invalid input! Please enter an integer!");
    }
}