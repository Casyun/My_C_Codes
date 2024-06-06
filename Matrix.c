// 《黑客帝国》开幕字符雨

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

#define WIDTH 100  
#define HEIGHT 30  
#define EMPTY ' '  

void hideCursor() {
    printf("\033[?25l"); // 隐藏光标
}
void drawScreen(char screen[HEIGHT][WIDTH], int* yPos, int* numDigits, bool* generating) {  
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {  
            screen[i][j] = EMPTY;
        }
    }

    // 在所有列生成随机数量的数字
    for (int j = 0; j < WIDTH; j++) {
        if (!generating[j]) {
            continue;
        }
        for (int i = 0; i < numDigits[j]; i++) {
            screen[yPos[j] + i][j] = '0' + rand() % 8; // 生成0-7的随机数字
        }
    }

    // 打印屏幕
    for (int i = 0; i < HEIGHT; i++) {  
        for (int j = 0; j < WIDTH; j++) {
            if (screen[i][j] != EMPTY) {
                printf("\033[32m%c\033[0m", screen[i][j]); // 设置亮绿色
            } else {
                printf(" ");
            }
        }
        printf("\n");  
    }  
}

int main() {  
    srand(time(0)); // 初始化随机数种子
    char screen[HEIGHT][WIDTH] = {EMPTY};  
    int yPos[WIDTH] = {0}; // 初始位置设为第一行
    int numDigits[WIDTH]; // 为每一列生成随机数字个数
    bool generating[WIDTH] = {false}; // 记录每一列是否正在生成新数字

    for (int j = 0; j < WIDTH; j++) {
        numDigits[j] = rand() % 8 + 3; // 生成3到10之间的随机数字个数
    }

    printf("Press any key to start...\n");
    getchar(); // 等待用户按下任意键开始

    while (true) {  
    drawScreen(screen, yPos, numDigits, generating);

    // 更新每一列的数字位置，并在数字触底时立即重新生成
    for (int j = 0; j < WIDTH; j++) {
        if (generating[j]) {
            yPos[j]++;
            
            // 检查是否需要重置列的位置（即数字已触底）
            if (yPos[j] >= HEIGHT - numDigits[j]) {
                yPos[j] = 1; // 重置yPos到起始位置
                numDigits[j] = rand() % 8 + 3; // 重新生成随机数字个数
                // 无需更改generating状态，保持该列继续生成数字
            }
        }
    }

        // 随机选择一个未生成数字的列开始生成新数字
        int randomCol = -1;
        for (int i = 0; i < WIDTH && randomCol == -1; i++) {
            randomCol = rand() % WIDTH;
            if (generating[randomCol]) randomCol = -1; // 如果选中的是正在生成的列，则重新选择
        }
        if (randomCol != -1) {
            generating[randomCol] = true;
            yPos[randomCol] = 1; // 重置yPos到起始位置
            numDigits[randomCol] = rand() % 8 + 3; // 重新生成随机数字个数
        }

        Sleep(50); 
        printf("\033[2J\033[H");
    }
}
