#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "tetris.h"

void getRandBlock() {
    curr_type = rand() % NUM_TYPE;
    curr_dire = rand() % NUM_DIREC;
    curr_block = blocks[curr_type][curr_dire];
    curr_x = 7;
    curr_y = -3;
    return;
}

int currentBlockCanMoveDown() {
    // from bottom-left to top-right
    for(int index = 0; index < 16; index++) {
        // ith row, jth col
        int i = index / 4;
        int j = index % 4;
        if(curr_block[4 * i + j] == 0) {
            continue;
        }
        if (curr_y + i + 1 >= 0 && backGround[curr_y + i + 1][curr_x + j] == 1) {
            return 0;
        }
        if (curr_y + i == BG_HEIGHT - 1) {
            return 0;
        }
    }
    // if (curr_y >= BG_HEIGHT - 1 - 3) return 1;
    return 1;
}

int isGameOver () {
    if(currentBlockCanMoveDown()) {
        return 0;
    }
    int result = 0;
    for (int i = 0; i < BG_WIDTH; i++) {
        result = result || backGround[0][i];
    }
    return result;
}

void refreshBackground() {
    system("clear");
    for (int i = 0; i < BG_HEIGHT; i++) {
        for (int j = 0; j < BG_WIDTH; j++) {
            int mergedBackground = backGround[i][j];
            // meet current block position
            if (j >= curr_x && j <= curr_x + 3 && i >= curr_y && i <= curr_y + 3) {
                mergedBackground = curr_block[(i - curr_y) * 4 + j - curr_x] || mergedBackground;
            }
            if (mergedBackground == 1) {
                printf("*");
                continue;
            }
            printf("-");
        }
        printf("\n");
    }
    printf("score: %d\n", score);
    return;
}

void renewBackground() {
    for (int index = 0; index < 16; index++) {
        if(curr_block[index] != 1){
            continue;
        }
        int i = index / 4;
        int j = index % 4;
        if(curr_y + i >= 0) {
            backGround[curr_y + i][curr_x + j] = 1;
        }
    }
    score += 1;
    return;
}

int wholeLineIsOne(int line) {
    for (int i = 0; i < BG_WIDTH; i++) {
        if (backGround[line][i] != 1) {
            return 0;
        }
    }
    return 1;
}

void moveDownBackgroundFrom (int line) {
    for (int k = line; k >= 0; k--) {
        for (int i = 0; i < BG_WIDTH; i++) {
            int replaceBg = 0;
            if(k != 0) {
                replaceBg = backGround[k - 1][i];
            }
            backGround[k][i] = replaceBg;
        }
    }
}

void clearLine() {
    for (int j = BG_HEIGHT - 1; j >= 0; j--) {
        int allOne = wholeLineIsOne(j);
        
        if(allOne == 0) {
            continue;
        }
        //if all one, remove this line
        moveDownBackgroundFrom(j);
        score += 10;
        // after exchange, the j-1 line become the j line
        j++;
    }
    return;
}

int blockOverlap(int row, int col) {
    // column out of range
    if(col < 0 || col >= BG_WIDTH || row >= BG_HEIGHT) {
        return 1;
    }
    // row not enter the background, skip
    if(row < 0) {
        return 0;
    }
    // already has a block
    if(backGround[row][col] == 1) {
        return 1;
    }
    return 0;
}

int canMoveHor(int moveRight) {
    int offset = moveRight ? 1 : -1;
    for(int index = 0; index < 16; index ++) {
        if(curr_block[index] == 0) {
            continue;
        }
        int i = index / 4;
        int j = index % 4;
        int predictCol = curr_x + j + offset;
        int predictRow = curr_y + i;
        // column out of range
        if(blockOverlap(predictRow, predictCol)) {
            return 0;
        }
    }
    return 1;
}

int canRotate(int isClockwise) {
    // clockwise
    int predictDirction = (curr_dire + 1) % 4;
    // conterclockwise
    if(!isClockwise) {
        predictDirction = (curr_dire + -1) % 4;
    }
    int* predictBlock = blocks[curr_type][predictDirction];
    for(int index = 0; index < 16; index ++) {
        if(predictBlock[index] == 0) {
            continue;
        }
        int i = index / 4;
        int j = index % 4;
        int predictCol = curr_x + j;
        int predictRow = curr_y + i;
        // column out of range
        if(blockOverlap(predictRow, predictCol)) {
            return 0;
        }
    }
    return 1;
}

void renewInfo(int thisKey) {
    switch (thisKey) {
        case 0:
            //move left
            if (canMoveHor(0)) curr_x = curr_x - 1;
            break;
        case 1:
            //move right
            if (canMoveHor(1)) curr_x = curr_x + 1;
            break;
        case 2:
            // change direction (up)
            if (!canRotate(1)) {
                break;
            }
            curr_dire = (curr_dire + 1) % 4;
            curr_block = blocks[curr_type][curr_dire];
            break;
        case 3:
            curr_y = curr_y + 1;
            break;
        default:
            return;
    }
    if(currentBlockCanMoveDown()) {
        curr_y = curr_y + 1;
    }
    return;
}

int main() {
    score = 0;
    int thisKey;
    curr_block = blocks[1][0];
    while (1) {
        refreshBackground();
        // if game over, jump out
        if(isGameOver()) {
            break;
        }
        scanf("%d", &thisKey);
        renewInfo(thisKey);
        // if the block can't move, put it into the background and get a new block
        if(!currentBlockCanMoveDown()) {
            renewBackground();
            clearLine();
            getRandBlock();
        }
    }
    return 0;
}

