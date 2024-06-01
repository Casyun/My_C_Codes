// 字符动画录制程序，用于制作字符动画并将每帧导出到txt文件中
// 注意：txt文件名序号需要手动修改


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 50
#define HEIGHT 25
#define MAX_RECORDINGS 5
#define FILENAME "records(num).txt"// 请手动修改序号

void drawScreen(char screen[HEIGHT][WIDTH], int player1X, int player1Y, int player2X, int player2Y) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = ' ';
        }
    }

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
void movePlayer(int *xPos, int *yPos, int xMov, int yMov) {
    *xPos += xMov;
    *yPos += yMov;

    // 确保图案位置在屏幕范围内
    if (*xPos < 2) *xPos = 2;
    else if (*xPos > WIDTH - 2) *xPos = WIDTH - 2;

    if (*yPos < 2) *yPos = 2;
    else if (*yPos > HEIGHT - 2) *yPos = HEIGHT - 2;
}

int main() {
    char screen[HEIGHT][WIDTH] = {' '};
    int player1X = 2, player1Y = 2;
    int player2X = WIDTH / 2, player2Y = HEIGHT / 2;
    int recordings[MAX_RECORDINGS][4] = {0};
    int recordingCount = 0;
    int xMov1, yMov1, xMov2, yMov2;
    char choice;

    while (1) {
        drawScreen(screen, player1X, player1Y, player2X, player2Y);
        printf("Player 1: Steps on X: ");
        scanf("%d", &xMov1);
        printf("Steps on Y: ");
        scanf("%d", &yMov1);

        printf("Player 2: Steps on X: ");
        scanf("%d", &xMov2);
        printf("Steps on Y: ");
        scanf("%d", &yMov2);

        movePlayer(&player1X, &player1Y, xMov1, yMov1);
        movePlayer(&player2X, &player2Y, xMov2, yMov2);

        printf("Record this position? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            if (recordingCount < MAX_RECORDINGS) {
                recordings[recordingCount][0] = player1X;
                recordings[recordingCount][1] = player1Y;
                recordings[recordingCount][2] = player2X;
                recordings[recordingCount][3] = player2Y;
                recordingCount++;
                printf("Recorded! \n");
            } else {
                printf("%d positions recorded, saving to file...\n", MAX_RECORDINGS);
                FILE *file = fopen(FILENAME, "w");
                if (file != NULL) {
                    for (int i = 0; i < MAX_RECORDINGS; i++) {
                        fprintf(file, "%d %d %d %d\n", recordings[i][0], recordings[i][1], recordings[i][2], recordings[i][3]);
                    }
                    fclose(file);
                    printf("Records saved as records(num).txt\n");// 请手动修改序号
                    break;
                } else {
                    printf("Error: Could not open file for writing.\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}