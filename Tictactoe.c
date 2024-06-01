// 井字棋游戏

#include <stdio.h>

// 定义棋盘大小
#define BOARD_SIZE 3

// 初始化棋盘
char board[BOARD_SIZE][BOARD_SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}; 

// 打印棋盘
void printBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// 检查是否有获胜情况
int checkWin(char player) {
    // 检查行列
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }

    // 检查对角线
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }

    return 0;
}

// 主函数
int main() {
    char player = 'X'; 
    int game_over = 0;

    while (!game_over) {
        printBoard();
        int row, col;
        printf("Player %c, enter your move (row and column): ", player);
        scanf("%d %d", &row, &col);

        // 检查输入是否有效(越界？重叠？)
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = player; // 更新棋盘状态
        game_over = checkWin(player); // 检查是否获胜
        
        //无人获胜，切换玩家
        if (!game_over) {
            if (player == 'X') {
                player = 'O';
            } else {
                player = 'X';
            }
        }
    }

    printf("Player %c wins!\n", player);
    return 0;
}