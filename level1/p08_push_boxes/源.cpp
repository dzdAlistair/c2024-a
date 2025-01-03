#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

// �����Թ�Ԫ��
const char WALL = '#';
const char PLAYER = 'P';
const char BOX = 'B';
const char TARGET = 'T';
const char EMPTY = ' ';
const char BOX_ON_TARGET = 'X'; // ������Ŀ��λ����

// ���巽��
enum Direction { UP, DOWN, LEFT, RIGHT };

// ˫������ر���
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hBuffer = CreateConsoleScreenBuffer(
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE,
    NULL,
    CONSOLE_TEXTMODE_BUFFER,
    NULL
);
COORD bufferSize = { 80, 25 }; // ��������С
COORD bufferCoord = { 0, 0 };
SMALL_RECT writeRegion = { 0, 0, 79, 24 }; // д������

// ����˫����
void setDoubleBuffer() {
    SetConsoleActiveScreenBuffer(hBuffer);
}

// ���Ƶ�������
void drawToBuffer(const vector<vector<char>>& maze) {
    DWORD dwBytesWritten;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            WriteConsoleOutputCharacterA(hBuffer, &maze[i][j], 1, { (SHORT)j, (SHORT)i }, &dwBytesWritten);
        }
    }
}

// �Թ���
class MazeGame {
private:
    vector<vector<char>> maze; // �Թ���ͼ
    int playerX, playerY;      // ���λ��
    vector<pair<int, int>> boxes; // ����λ��
    vector<pair<int, int>> targets; // Ŀ��λ��
    int steps; // ����

public:
    MazeGame(const vector<vector<char>>& map) {
        maze = map;
        steps = 0;
        findPlayerAndObjects();
    }

    // ������ҡ����Ӻ�Ŀ��λ��
    void findPlayerAndObjects() {
        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                if (maze[i][j] == PLAYER) {
                    playerX = i;
                    playerY = j;
                }
                else if (maze[i][j] == BOX) {
                    boxes.emplace_back(i, j);
                }
                else if (maze[i][j] == TARGET) {
                    targets.emplace_back(i, j);
                }
            }
        }
    }

    // ��ʾ�Թ�
    void display() {
        drawToBuffer(maze); // ���Ƶ�������
        SetConsoleCursorPosition(hBuffer, { 0, (SHORT)maze.size() });
        cout << "Steps: " << steps << endl;
    }

    // �ƶ����
    bool move(Direction dir) {
        int dx = 0, dy = 0;
        switch (dir) {
        case UP: dx = -1; break;
        case DOWN: dx = 1; break;
        case LEFT: dy = -1; break;
        case RIGHT: dy = 1; break;
        }

        int newX = playerX + dx;
        int newY = playerY + dy;

        // ���߽��ǽ��
        if (maze[newX][newY] == WALL) {
            return false;
        }

        // �������
        auto it = find(boxes.begin(), boxes.end(), make_pair(newX, newY));
        if (it != boxes.end()) {
            int boxX = newX + dx;
            int boxY = newY + dy;
            if (maze[boxX][boxY] == WALL || find(boxes.begin(), boxes.end(), make_pair(boxX, boxY)) != boxes.end()) {
                return false; // ����ǰ����ǽ����һ������
            }
            // �ƶ�����
            *it = make_pair(boxX, boxY);
            maze[newX][newY] = EMPTY;
            maze[boxX][boxY] = (maze[boxX][boxY] == TARGET) ? BOX_ON_TARGET : BOX;
        }

        // �ƶ����
        maze[playerX][playerY] = EMPTY;
        maze[newX][newY] = PLAYER;
        playerX = newX;
        playerY = newY;
        steps++;
        return true;
    }

    // ����Ƿ�ʤ��
    bool isWin() {
        for (const auto& target : targets) {
            if (find(boxes.begin(), boxes.end(), target) == boxes.end()) {
                return false;
            }
        }
        return true;
    }

    // ��ȡ����
    int getSteps() const {
        return steps;
    }
};

// ���ļ������Թ�
vector<vector<char>> loadMazeFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<char>> maze;
    string line;
    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        maze.push_back(row);
    }
    return maze;
}

// ����������ļ�
void saveScoreToFile(int level, int steps) {
    ofstream file("scores.txt", ios::app);
    if (file.is_open()) {
        file << "Level " << level << ": " << steps << " steps\n";
        file.close();
    }
}

// ������
int main() {
    setDoubleBuffer(); // ����˫����

    vector<string> levels = { "levels/level1.txt", "levels/level2.txt", "levels/level3.txt" };
    for (size_t i = 0; i < levels.size(); ++i) {
        auto maze = loadMazeFromFile(levels[i]);
        MazeGame game(maze);

        while (true) {
            game.display();
            if (game.isWin()) {
                cout << "You win!" << endl;
                saveScoreToFile(i + 1, game.getSteps());
                break;
            }

            // ��ȡ��������
            if (_kbhit()) {
                char ch = _getch();
                Direction dir;
                switch (ch) {
                case 'w': dir = UP; break;
                case 's': dir = DOWN; break;
                case 'a': dir = LEFT; break;
                case 'd': dir = RIGHT; break;
                default: continue;
                }
                game.move(dir);
            }
        }
        cout << "Press any key to continue to the next level..." << endl;
        _getch();
    }

    // �ָ�Ĭ����Ļ������
    SetConsoleActiveScreenBuffer(hOutput);
    return 0;
}