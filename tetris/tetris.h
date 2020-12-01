#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BG_WIDTH 18
#define BG_HEIGHT 24
#define NUM_TYPE 4
#define NUM_DIREC 4

int backGround[BG_HEIGHT][BG_WIDTH] = { 0 };

int shape_O_0[16] = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};

int shape_O_1[16] = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};

int shape_O_2[16] = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};

int shape_O_3[16] = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};

int shape_I_0[16] = {
    0, 1, 0, 0, 
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0
};

int shape_I_1[16] = {
    0, 0, 0, 0, 
    1, 1, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0
};

int shape_I_2[16] = {
    0, 0, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 1, 0
};

int shape_I_3[16] = {
    0, 0, 0, 0, 
    0, 0, 0, 0, 
    1, 1, 1, 1, 
    0, 0, 0, 0
};

int shape_T_0[16] = {
    0, 0, 0, 0,
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 0, 1, 0
};

int shape_T_1[16] = {
    0, 0, 0, 0,
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0
};

int shape_T_2[16] = {
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};

int shape_T_3[16] = {
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0
};

int shape_L_0[16] = {
    0, 0, 0, 0,
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0
};

int shape_L_1[16] = {
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0
};

int shape_L_2[16] = {
    0, 0, 0, 0,
    0, 1, 1, 1,
    0, 1, 0, 0,
    0, 0, 0, 0
};

int shape_L_3[16] = {
    0, 0, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 1, 0
};

int * block_type_O[4] = {
    shape_O_0,
    shape_O_1,
    shape_O_2,
    shape_O_3
};

int * block_type_I[4] = {
    shape_I_0,
    shape_I_1,
    shape_I_2,
    shape_I_3
};

int * block_type_T[4] = {
    shape_T_0,
    shape_T_1,
    shape_T_2,
    shape_T_3
};

int * block_type_L[4] = {
    shape_L_0,
    shape_L_1,
    shape_L_2,
    shape_L_3
};

int ** blocks[NUM_TYPE] = {
    block_type_O,
    block_type_I,
    block_type_T,
    block_type_L
};


int curr_x = 7;
int curr_y = -3;

int curr_type = 1;
int curr_dire = 2;

int * curr_block;

#endif
