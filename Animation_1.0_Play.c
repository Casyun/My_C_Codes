// 字符动画播放程序，用于读取txt文件中每帧数据并显示，实现动画效果

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 25
#define MAX_RECORDINGS 5

void drawScreen(int recordings[][4], int index) {
    char screen[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = ' ';
        }
    }

    int player1X = recordings[index][0];
    int player1Y = recordings[index][1];
    int player2X = recordings[index][2];
    int player2Y = recordings[index][3];

    screen[player1Y-1][player1X] = 'O';
    screen[player1Y+1][player1X] = 'O';
    screen[player1Y][player1X-1] = 'O';
    screen[player1Y][player1X+1] = 'O';
    screen[player1Y][player1X] = 'O';

    screen[player2Y-1][player2X] = 'X';
    screen[player2Y+1][player2X] = 'X';
    screen[player2Y][player2X-1] = 'X';
    screen[player2Y][player2X+1] = 'X';
    screen[player2Y][player2X] = 'X';

    // 打印屏幕
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (screen[i][j] == 'O') {
                printf("\033[34m"); // 设置蓝色
                printf("%c ", screen[i][j]);
                printf("\033[0m"); 
            } else if (screen[i][j] == 'X') {
                printf("\033[31m"); // 设置红色
                printf("%c ", screen[i][j]);
                printf("\033[0m"); 
            } else {
                printf("%c ", screen[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int choice;
    printf("Enter the records file number (less than 10): ");
    scanf("%d", &choice);

    char filename[20];
    sprintf(filename, "records%d.txt", choice);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    int recordings[MAX_RECORDINGS][4];
    for (int i = 0; i < MAX_RECORDINGS; i++) {
        fscanf(file, "%d %d %d %d", &recordings[i][0], &recordings[i][1], &recordings[i][2], &recordings[i][3]);
    }
    fclose(file);

    for (int i = 0; i < MAX_RECORDINGS; i++) {
        drawScreen(recordings, i);
        Sleep(500);
        printf("\033[2J\033[H");
    }

    return 0;
}