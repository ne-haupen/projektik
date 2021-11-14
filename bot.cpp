#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "visual.h"
#include "logic.h"

#define COMP 'O'
int count(char board[26][26], int size)
{
    int counting = 0;
    for (int x = 0; x < size; ++x)
        for (int y = 0; y < size; ++y)
            if (board[x][y] !='*')
                ++counting;
    return counting;
}

void first_move(char board[26][26], int size, int move[2]) {
    int x, y;
    int ch = 0;
    bool done = false;
    for (int a = 0; done ==false; a++) {
        for (int b = 0; done == false; b++) {
            if (board[a][b] != '*') {
                done = true;
            }else
                ch++;
        }
        if (done == true) {
            break;
        }
    }
    int moves[] = { -1, 0, 1 };
    srand(time(0));
    x = ch / size;
    if (ch % size - 1 >= 0)
        y = ch % size - 1;
    else y = 0;
    int sx = x;
    int sy = y;
    done = false;

    while (done == false) {
        x += moves[rand() % 3];
        y += moves[rand() % 3];
        if ((x >= 0) && (y >= 0)) {
            if (!((x == sx) && (y == sy))) {
                done = true;
            }
        }
        else {
            x = sx;
            y = sy;
        }
    }
    move[0] = x;
    move[1] = y;
    return;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int check_win_s(char gamee[26][26], int size) {
    int count = 0;
    int winc = win_value(size);
    for (int n = 0; n < size; n++) {
        for (int k = 0; k < size; k++) {
            if (gamee[n][k] != '*') {
                count++;
                if (check_surrounding(n, k, gamee[n][k], gamee, winc) == 1) {
                    if (gamee[n][k] == 'X')
                        return 1;
                    else
                        return 2;
                }
            }
        }
    }
    if (count == size * size) {
        return -1;
    }
    return 0;
}
int moves_left(char board[26][26], int focus[2], int needed, int size) {
    int count=0;
    int x_check, y_check;
    for (int a = 0; a < needed; a++) {
        for (int b = 0; b < needed; b++) {
            x_check =focus[0] - ((needed - 1) / 2) + a;
            y_check = focus[1] - ((needed - 1) / 2) + b;
            if (x_check >= 0 && y_check >= 0) {
                if (board[x_check][y_check] == '*') {
                    count++;
                }
            }
        }
    }
    return count;
}

void get_focus(char board[26][26], int size, int needed, int focus[2]) {
    int counts[2] = { 0, 0 };
    int char_count = 0;
    for (int a = 0; a < size; a++) {
        for (int b = 0; b < size; b++) {
            if (board[a][b] != '*') {
                counts[0] += a;
                counts[1] += b;
                char_count++;
            }
        }
    }
    counts[0] /= char_count;
    counts[1] /= char_count;
    while(moves_left(board, counts, needed, size) == 0) {
        int b_size;
        if (size % 2 == 1) {
            b_size = (size+1)/2;
            if (counts[1] == b_size && counts[0] == b_size) {
                counts[0]--;
                counts[1]--;
            }
        }
        else {
            b_size = size/2;
        }
        for (int n = 0; n < 2; n++) {
            if (counts[n] < b_size) {
                counts[n]++;
            }if (counts[n] > b_size) {
                counts[n]--;
            }
        }
    }
    focus[0] = counts[0];
    focus[1] = counts[1];
    return;

}

int minimax(char board[26][26], int depth, bool isMax, int size, int focus[2], int needed)
{
    int score = check_win_s(board, size);
    int sx, sy;
    sx = focus[0] - (needed/2);
    sy = focus[1] - (needed / 2);
    // If Maximizer has won the game return his/her
    // evaluated score
    if (score == 1)
        return -10;
    if (score == 2)
        return 10;
    if (score == -1)
        return 0;
    if (isMax)
    {
        int best = -1000;
        for (int i = sx; i < sx+needed; i++)
        {
            for (int j = sy; j < sy+needed; j++)
            {
                if (board[i][j] == '*')
                {
                    board[i][j] = 'O';
                    best = max(best,
                        minimax(board, depth + 1, !isMax, size, focus, needed));
                    board[i][j] = '*';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = sx; i < sx+needed; i++)
        {
            for (int j = sy; j < sy+needed; j++)
            {
                if (board[i][j] == '*')
                {
                    board[i][j] = 'X';
                    best = min(best,
                        minimax(board, depth + 1, !isMax, size, focus, needed));
                    board[i][j] = '*';
                }
            }
        }
        return best;
    }
}

void computer_move(char board[26][26], int size, int needed, int move[2])
{
    int game_focus[2];
    if ((count(board, size)) == 1) {
        first_move(board, size, move);
        return;
    }
    get_focus(board, size, needed, game_focus);
    int sx, sy, move_x, move_y;
    int bestVal = -1000;
    sy = game_focus[1] - (needed / 2);
    sx = game_focus[0] - (needed / 2);
    while ((sx - ((needed+1) / 2)) < 0) {
        sx++;
    }
    while ((sy - ((needed+1) / 2)) < 0) {
        sy++;
    }
    for (int i = sx; i < sx + needed; i++)
    {
        for (int j = sy; j < sy + needed; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = 'X';
                int moveVal = minimax(board, 0, false, size, game_focus, needed);
                board[i][j] = '*';
                if (moveVal > bestVal)
                {
                    move_x = i;
                    move_y = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    move[0] = move_x;
    move[1] = move_y;
    return;
}