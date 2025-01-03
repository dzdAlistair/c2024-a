#include <iostream>
#include <vector>
#include <stack>
#include <chrono> // ���ڼ�ʱ
#include <conio.h> // ���ڼ�������
#include <windows.h> // ���ڿ���̨����

using namespace std;

// �Թ��ߴ�
const int ROWS = 15;
const int COLS = 30;

// �Թ���ͼ
char maze[ROWS][COLS];

// ��ҳ�ʼλ��
int playerRow = 1;
int playerCol = 1;

// ����λ��
int exitRow = ROWS - 2;
int exitCol = COLS - 2;

// ���ù��λ��
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ��ʼ���Թ���ȫ��Ϊǽ��
void initializeMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            maze[i][j] = '#';
        }
    }
}

// ��������Թ���ʹ��������������㷨��
void generateMaze(int startRow, int startCol) {
    // �������飺�ϡ��ҡ��¡���
    int dirRow[] = { -2, 0, 2, 0 };
    int dirCol[] = { 0, 2, 0, -2 };

    // ���������
    srand(time(nullptr));

    // ʹ��ջʵ�� DFS
    stack<pair<int, int>> stack;
    stack.push({ startRow, startCol });
    maze[startRow][startCol] = ' ';

    while (!stack.empty()) {
        int row = stack.top().first;
        int col = stack.top().second;
        stack.pop();

        // ������ҷ���
        int dirs[] = { 0, 1, 2, 3 };
        for (int i = 0; i < 4; ++i) {
            int j = rand() % 4;
            swap(dirs[i], dirs[j]);
        }

        // �����ĸ�����
        for (int i = 0; i < 4; ++i) {
            int newRow = row + dirRow[dirs[i]];
            int newCol = col + dirCol[dirs[i]];

            if (newRow > 0 && newRow < ROWS - 1 && newCol > 0 && newCol < COLS - 1 && maze[newRow][newCol] == '#') {
                maze[newRow][newCol] = ' ';
                maze[row + dirRow[dirs[i]] / 2][col + dirCol[dirs[i]] / 2] = ' '; // ��ͨ·��
                stack.push({ newRow, newCol });
            }
        }
    }

    // ���ó���
    maze[exitRow][exitCol] = 'E';
}

// ��ӡ�Թ�
void printMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

// �ƶ����
void movePlayer(int newRow, int newCol) {
    if (maze[newRow][newCol] != '#') { // ����Ƿ�ײǽ
        maze[playerRow][playerCol] = ' '; // �����ҵ�ǰλ��
        playerRow = newRow;
        playerCol = newCol;
        maze[playerRow][playerCol] = 'P'; // ���������λ��
    }
}

// ������
int main() {
    char input;
    bool gameOver = false;

    // ��ʼ���Թ�
    initializeMaze();
    generateMaze(1, 1); // �� (1, 1) ��ʼ�����Թ�

    // ������ҳ�ʼλ��
    maze[playerRow][playerCol] = 'P';

    // ���ع��
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // ��¼��ʼʱ��
    auto startTime = chrono::high_resolution_clock::now();

    while (!gameOver) {
        setCursorPosition(0, 0); // ������ƶ������Ͻ�
        printMaze();

        // ����Ƿ񵽴����
        if (playerRow == exitRow && playerCol == exitCol) {
            auto endTime = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
            cout << "��ϲ�㱦�����ӳ��˸���ҵ�Թ�����ʱ: " << duration.count() << " ��" << endl;
            gameOver = true;
            break;
        }

        // ��ȡ��������
        input = _getch();

        // ���������ƶ����
        switch (input) {
        case 'w': // ��
            movePlayer(playerRow - 1, playerCol);
            break;
        case 's': // ��
            movePlayer(playerRow + 1, playerCol);
            break;
        case 'a': // ��
            movePlayer(playerRow, playerCol - 1);
            break;
        case 'd': // ��
            movePlayer(playerRow, playerCol + 1);
            break;
        case 'q': // �˳���Ϸ
            gameOver = true;
            break;
        default:
            break;
        }
    }

    // �ָ������ʾ
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return 0;
}
