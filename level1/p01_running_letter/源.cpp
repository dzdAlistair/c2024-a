#include <iostream>
#include <windows.h> // ���� Sleep �� SetConsoleCursorPosition
#include <string>

// ���ù��λ��
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    std::string text = "Ali"; // Ҫ�ƶ�����ĸ�򵥴�
    int screenWidth = 120;    // ����̨��ȣ�����Ϊ 120��
    int position = 0;        // ��ǰ�ı�λ��
    int direction = 1;       // �ƶ�����1 ��ʾ���ң�-1 ��ʾ����

    while (true) {
        // �����һ֡���ı�
        setCursorPosition(position, 0);
        for (int i = 0; i < text.length(); ++i) {
            std::cout << " ";
        }

        // ����λ��
        position += direction;

        // ���߽�
        if (position + text.length() >= screenWidth) {
            direction = -1; // ����
        }
        else if (position <= 0) {
            direction = 1; // ����
        }

        // �������ı�
        setCursorPosition(position, 0);
        std::cout << text;

        Sleep(50); // ���� Sleep ʱ�䣬�ӿ��ƶ��ٶȣ�50 ���룩
    }

    return 0;
}