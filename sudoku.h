//
// Created by Lenovo on 2021/6/13.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <random>
#include <string.h>
#include <memory.h>
#include <stack>
#include <windows.h>

#define EXIT 0
#define PRINT 1
#define GENERATE 2
#define INPUT_TAB 3
#define SOLVE 4
#define HINT 5
#define INPUT_NUMBER 6
#define RESTART 7
#define SAVE 8
#define SHOW 9
#define BACK 10
#define OVER 11


typedef int* Pos;


typedef struct SudokuStruct {
    int currTab[9][9];
    int initTab[9][9];
    bool isInitSolvable;
    bool isCurrSolvable;
    //bool isLegal;
} Sudoku;

typedef struct fileStruct {
    int ID;
    char name[30];
    int time[5];
    Sudoku sudoku;
    struct fileStruct* next;
} sudokuFile;
#define LIBRARY 8
int libraryTab[LIBRARY][81] = {
        {2, 1, 6, 3, 5, 7, 4, 8, 9, 3, 4, 8, 1, 2, 9, 7, 5, 6, 5, 9, 7, 6, 8, 4, 3, 1, 2, 9, 2, 1, 5, 7, 6, 8, 4, 3, 4,
         6, 3, 9, 1, 8, 5, 2, 7, 8, 7, 5, 2, 4, 3, 9, 6, 1, 1, 3, 4, 8, 9, 2,
         6, 7, 5, 6, 8, 2, 7, 3, 5, 1, 9, 4, 7, 5, 9, 4, 6, 1, 2, 3, 8},
        {1, 2, 3, 4, 5, 6, 7, 9, 8, 4, 7, 5, 8, 1, 9, 2, 6, 3, 8, 9, 6, 3, 2, 7, 4, 1, 5, 2, 1, 4, 5, 6, 3, 8, 7, 9, 5,
         3, 7, 1, 9, 8, 6, 2, 4, 6, 8, 9, 2, 7, 4, 5, 3, 1, 9, 4, 1, 6, 8, 2,
         3, 5, 7, 3, 5, 2, 7, 4, 1, 9, 8, 6, 7, 6, 8, 9, 3, 5, 1, 4, 2},
        {2, 1, 4, 5, 7, 8, 3, 9, 6, 9, 3, 6, 1, 4, 2, 7, 5, 8, 5, 7, 8, 3, 6, 9, 4, 1, 2, 3, 4, 7, 6, 8, 1, 5, 2, 9, 8,
         2, 5, 4, 9, 7, 6, 3, 1, 1, 6, 9, 2, 3, 5, 8, 4, 7, 6, 9, 3, 7, 2, 4,
         1, 8, 5, 4, 8, 1, 9, 5, 6, 2, 7, 3, 7, 5, 2, 8, 1, 3, 9, 6, 4},
        {1, 3, 7, 4, 6, 8, 2, 5, 9, 5, 8, 9, 1, 3, 2, 7, 4, 6, 2, 4, 6, 7, 9, 5, 8, 1, 3, 8, 2, 4, 3, 1, 6, 5, 9, 7, 3,
         6, 5, 9, 2, 7, 4, 8, 1, 9, 7, 1, 5, 8, 4, 6, 3, 2, 6, 5, 3, 8, 7, 1,
         9, 2, 4, 4, 1, 2, 6, 5, 9, 3, 7, 8, 7, 9, 8, 2, 4, 3, 1, 6, 5},
        {3, 1, 4, 2, 5, 9, 7, 6, 8, 5, 9, 8, 1, 7, 6, 4, 3, 2, 6, 7, 2, 8, 4, 3, 9, 1, 5, 1, 4, 3, 5, 9, 7, 2, 8, 6, 8,
         6, 9, 4, 1, 2, 5, 7, 3, 2, 5, 7, 6, 3, 8, 1, 9, 4, 9, 3, 5, 7, 8, 4,
         6, 2, 1, 7, 2, 1, 3, 6, 5, 8, 4, 9, 4, 8, 6, 9, 2, 1, 3, 5, 7},
        {2, 1, 3, 4, 7, 9, 8, 6, 5, 7, 5, 6, 2, 3, 8, 1, 9, 4, 8, 4, 9, 5, 6, 1, 2, 3, 7, 9, 6, 5, 8, 2, 3, 4, 7, 1, 3,
         2, 7, 9, 1, 4, 6, 5, 8, 1, 8, 4, 6, 5, 7, 9, 2, 3, 5, 9, 8, 7, 4, 6,
         3, 1, 2, 6, 7, 1, 3, 8, 2, 5, 4, 9, 4, 3, 2, 1, 9, 5, 7, 8, 6},
        {2, 1, 6, 3, 4, 7, 8, 9, 5, 4, 5, 9, 8, 2, 6, 3, 7, 1, 3, 8, 7, 5, 1, 9, 4, 2, 6, 7, 2, 3, 4, 5, 1, 6, 8, 9, 1,
         6, 5, 7, 9, 8, 2, 4, 3, 8, 9, 4, 2, 6, 3, 5, 1, 7, 9, 7, 8, 6, 3, 2,
         1, 5, 4, 5, 3, 1, 9, 8, 4, 7, 6, 2, 6, 4, 2, 1, 7, 5, 9, 3, 8},
        {1, 4, 2, 3, 6, 7, 8, 5, 9, 8, 5, 3, 4, 1, 9, 2, 6, 7, 6, 7, 9, 2, 5, 8, 4, 3, 1, 3, 2, 8, 6, 7, 1, 5, 9, 4, 9,
         1, 4, 5, 2, 3, 7, 8, 6, 7, 6, 5, 8, 9, 4, 1, 2, 3, 2, 8, 7, 9, 4, 6,
         3, 1, 5, 4, 3, 6, 1, 8, 5, 9, 7, 2, 5, 9, 1, 7, 3, 2, 6, 4, 8},

};

void pos(int x, int y);

void welcome();

char Decide();


int oneStepForward(Sudoku* S);

int stringProceed(Sudoku* S);

void orderReceive(Sudoku* S, int order, int* number);

void print(int table[][9]);

void randomInit(Sudoku* S);

void getPos(int* line);

void swapRow(int Tab[][9], int row1, int row2);

void swapCol(int Tab[][9], int col1, int col2);


int inputTab(Sudoku* S);

bool isSolvable(const Sudoku* S);

bool oneSolution(Sudoku* S, int pos);

int hint(Sudoku* S);

int inputNum(Sudoku* S, int row, int col, int number);

int save(Sudoku* S);

int show(Sudoku* S);

sudokuFile* creatAccount(sudokuFile* head, char* fileName);

int add(Sudoku* S, sudokuFile* head, char* fileName, char* newName);

int getTime(int* tm);

int read(sudokuFile* head);

int isSearch(Sudoku* S, sudokuFile* head, int id);

void freeList(sudokuFile* head);

bool nameCmp(char* newName, sudokuFile* head);

bool isLegal(Sudoku* S);

bool isFull(Sudoku* S);

int back(Sudoku* S);

int isOver(Sudoku* S);


#endif //SUDOKU_SUDOKU_H
