// 五子棋游戏

#include <stdio.h>

// 定义棋盘大小
#define BOARD_SIZE 15

// 初始化棋盘
void initBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// 打印棋盘
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("  ");
    for (int j = 0; j < BOARD_SIZE; j++) {
        printf("%d ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// 检查是否有获胜情况
int checkWin(char player, char board[BOARD_SIZE][BOARD_SIZE]) {
    // 检查水平方向
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j <= BOARD_SIZE - 5; j++) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player &&
                board[i][j + 3] == player && board[i][j + 4] == player) {
                return 1;
            }
        }
    }

    // 检查垂直方向
    for (int j = 0; j < BOARD_SIZE; j++) {
        for (int i = 0; i <= BOARD_SIZE - 5; i++) {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player &&
                board[i + 3][j] == player && board[i + 4][j] == player) {
                return 1;
            }
        }
    }
    
    // 检查主对角线方向
    for (int i = 0, j = 0; i <= BOARD_SIZE - 5; i++, j++) {
        if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player &&
            board[i + 3][j + 3] == player && board[i + 4][j + 4] == player) {
            return 1;
        }
    }
    
    // 检查副对角线方向
    for (int i = 4, j = 0; i < BOARD_SIZE; i++, j++) {
        if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player &&
            board[i - 3][j + 3] == player && board[i - 4][j + 4] == player) {
            return 1;
        }
    }

    return 0;
}

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    initBoard(board); 
    char player = 'X'; 
    int game_over = 0; 

    while (!game_over) {
        printBoard(board);
        int row, col;
        printf("Player %c, enter your move (row and column): ", player);
        scanf("%d %d", &row, &col);

        row--;
        col--;

        // 检查输入是否有效(越界？重叠？)
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = player; // 更新棋盘状态
        game_over = checkWin(player, board); // 检查是否获胜
        
        // 如果无人获胜，切换玩家
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