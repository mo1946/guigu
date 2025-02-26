#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// 精心挑选的颜文字集合
vector<string> kaomoji = {
    "(￣ー￣)?"， "╮(￣⊿￣)╭"， "(?? ω ?`)"，
    "(；?Д`A)"， "┐(?д`)┌"， "(??ω`? )"，
    "?(???)?"， "(?_ _)?"， "(＾ｖ＾)"，
    "ヽ(?▽`)/"， "(￣∠￣)?"， "(ó﹏ò?)"，
    "(?-ω-` )"， "ヽ(???)ノ"， "(つω`?)"，
    "(???`?)"，"(～￣▽￣)～"，"(╯°□°）╯︵ ┻━┻"，
    "(⊙o⊙)？"，"(≧?≦)ゞ"，"( ???)?(._.`)"
};

void setupConsole() {
    // 设置控制台参数
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // 设置随机种子
    srand(static_cast<unsigned>(time(0)));
}

void clearScreen() {
    // 高效清屏方式
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    DWORD written;
    FillConsoleOutputCharacter(hOut, ' ', csbi.dwSize。X * csbi.dwSize。Y， { 0，0 }, &written);
    SetConsoleCursorPosition(hOut, { 0，0 });
}

void printCentered(const string& text) {
    // 获取控制台宽度
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow。Right - csbi.srWindow。Left + 1;

    // 计算居中位置（考虑Unicode字符宽度）
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;

    // 带颜色输出
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
        (rand() % 6 + 10)); // 随机亮色
    cout << string(padding, ' ') << text << endl;
}

int main() {
    setupConsole();

    const int FRESH_RATE = 800; // 切换间隔（毫秒）
    const int TITLE_COLOR = 14; // 标题颜色（黄色）

    while (true) {
        clearScreen();

        // 绘制标题
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TITLE_COLOR);
        cout << "==== 颜文字随机播放器 ====" << endl << endl;

        // 随机选择颜文字
        int index = rand() % kaomoji.size();
        printCentered(kaomoji[index]);

        // 绘制底部装饰
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE)， 8); // 灰色
        cout << endl << "════════════════════════" << endl;
        cout << " 按 Ctrl+C 退出程序" << endl;

        Sleep(FRESH_RATE);
    }
    return 0;
}
   //我懒，ai的😊
