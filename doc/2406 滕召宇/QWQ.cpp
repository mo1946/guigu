#include <iostream>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ������ѡ�������ּ���
vector<string> kaomoji = {
    "(���`��)?", "�r(���S��)�q", "(?? �� ?`)",
    "(��?��`A)", "��(?��`)��", "(??��`? )",
    "?(???)?", "(?_ _)?", "(�ޣ���)",
    "�c(?��`)/", "(���ϣ�)?", "(���n��?)",
    "(?-��-` )", "�c(???)��", "(�Ħ�`?)",
    "(???`?)","(��������)��","(�s����㣩�s�� �ߩ���",
    "(��o��)��","(�R?�Q)�g","( ???)?(._.`)"
};

void setupConsole() {
    // ���ÿ���̨����
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // �����������
    srand(static_cast<unsigned>(time(0)));
}

void clearScreen() {
    // ��Ч������ʽ
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    DWORD written;
    FillConsoleOutputCharacter(hOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, { 0,0 }, &written);
    SetConsoleCursorPosition(hOut, { 0,0 });
}

void printCentered(const string& text) {
    // ��ȡ����̨���
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // �������λ�ã�����Unicode�ַ���ȣ�
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding < 0) padding = 0;

    // ����ɫ���
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |
        (rand() % 6 + 10)); // �����ɫ
    cout << string(padding, ' ') << text << endl;
}

int main() {
    setupConsole();

    const int FRESH_RATE = 800; // �л���������룩
    const int TITLE_COLOR = 14; // ������ɫ����ɫ��

    while (true) {
        clearScreen();

        // ���Ʊ���
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TITLE_COLOR);
        cout << "==== ��������������� ====" << endl << endl;

        // ���ѡ��������
        int index = rand() % kaomoji.size();
        printCentered(kaomoji[index]);

        // ���Ƶײ�װ��
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); // ��ɫ
        cout << endl << "�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T" << endl;
        cout << " �� Ctrl+C �˳�����" << endl;

        Sleep(FRESH_RATE);
    }
    return 0;
}
   //ai����