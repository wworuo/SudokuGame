#include "sudoku.h"


#define NAME "sudoku.dat"
#define HARD 17
#define NORMAL 35
#define EASY 50


using namespace std;
static std::default_random_engine e(time(0));


stack<Pos> st;
int level = HARD;
char decision = 'y';
bool welCome = true;


#pragma warning(disable:4996)

int main() {
    while (decision == 'y') {
        welcome();
        Sudoku* S = (Sudoku*)malloc(sizeof(Sudoku));
        memset(S->currTab, 0, 81 * sizeof(int));
        memset(S->initTab, 0, 81 * sizeof(int));
        S->isCurrSolvable = true;
        S->isInitSolvable = true;
        while (stringProceed(S) != 0) {
            system("pause");
            system("cls");
            pos(52, 1);
            printf("Current Sudoku");
            for (int i = 0; i < 9; i++) {
                pos(50, i + 3);
                for (int j = 0; j < 9; j++) {
                    printf("%d ", S->currTab[i][j]);
                }
            }
            pos(50, 13);
            printf("Usage");
            pos(50, 14);
            printf("\"exit\":exit the game\n");
            pos(50, 15);
            printf("\"print\":print current sudoku\n");
            pos(50, 16);
            printf("\"input\":input a sudoku you want to play or solve\n");
            pos(50, 17);
            printf("\"generate\":generate a sudoku you can play\n");
            pos(50, 18);
            printf("\"solve\":solve the current sudoku \n");
            pos(50, 19);
            printf("\"put x y n\":put n into the line x, column y\n");
            pos(50, 20);
            printf("\"hint\":hint the next step\n");
            pos(50, 21);
            printf("\"back\":back to last step\n");
            pos(50, 22);
            printf("\"over\":judge if the game is over\n");
            pos(50, 23);
            printf("\"save\":save the sudoku's state in \"sudoku.dat\"\n");
            pos(50, 24);
            printf("\"show\":show all game's name and load someone\n");
            pos(0, 0);
            printf("Order:\n");
        }
        free(S);
        system("pause");
        system("cls");
        decision = Decide();
        system("cls");
    }
    pos(60, 5);
    printf("Goodbye!");
    Sleep(5000);

    return 0;
}

void pos(int x, int y) {
    COORD pos; //创建坐标数组
    HANDLE output;//创建位置
    pos.X = x;
    pos.Y = y;
    output = GetStdHandle(STD_OUTPUT_HANDLE);//标准输出
    SetConsoleCursorPosition(output, pos);//决定光标位置
}

void welcome() {
    int i;
    if (welCome) {
        welCome = false;
        pos(0, 0);
        printf("Welcome to my sudoku world!\n");
        GetAsyncKeyState(VK_RETURN);
        for (i = 0; i <= 2500; i += 100) {
            Sleep(100);
            if (GetAsyncKeyState(VK_RETURN))
                break;
        }
        pos(0, 2);
        printf("You can solve the sudoku or play the sudoku game:\n");
        for (i = 0; i <= 2500; i += 100) {
            Sleep(100);
            if (GetAsyncKeyState(VK_RETURN))
                break;
        }
        GetAsyncKeyState(VK_RETURN);
        pos(0, 3);
        printf("usages include:\n");
        printf("\"exit\":exit the game\n");
        printf("\"print\":print current sudoku\n");
        printf("\"input\":input a sudoku you want to play or solve\n");
        printf("\"generate\":generate a sudoku you can play\n");
        printf("\"solve\":solve the current sudoku \n");
        printf("\"put x y n\":put n into the line x, column y\n");
        printf("\"hint\":hint the next step\n");
        printf("\"back\":back to last step\n");
        printf("\"over\":judge if the game is over\n");
        printf("\"save\":save the sudoku's state in \"sudoku.dat\"\n");
        printf("\"show\":show all game's name and load someone\n");
        for (i = 0; i <= 5000; i += 100) {
            Sleep(100);
            if (GetAsyncKeyState(VK_RETURN))
                break;
        }
        system("pause");
        system("cls");
    }
    pos(0, 0);
    GetAsyncKeyState(VK_RETURN);
    printf("Now please choose the level of game if you want to play by pressing the keyboard:\n");
    for (i = 0; i <= 2500; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    printf("\"F1\" Hard   \"F2\" Normal   \"F3\" Easy\n");
    for (i = 0; i <= 2500; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    printf("Order:Level Choice:\n");
    while (1) {
        if (GetAsyncKeyState(VK_F1)) {
            printf("HARD MODE\n");
            level = HARD;
            break;
        }
        else if (GetAsyncKeyState(VK_F2)) {
            printf("NORMAL MODE\n");
            level = NORMAL;
            break;
        }
        else if (GetAsyncKeyState(VK_F3)) {
            printf("EASY MODE\n");
            level = EASY;
            break;
        }
    }
    system("pause");
    system("cls");
    pos(0, 0);
    printf("Order:\n");
    pos(40, 1);
    printf("Usage");
    pos(40, 2);
    printf("\"exit\":exit the game\n");
    pos(40, 3);
    printf("\"print\":print current sudoku\n");
    pos(40, 4);
    printf("\"input\":input a sudoku you want to play or solve\n");
    pos(40, 5);
    printf("\"generate\":generate a sudoku you can play\n");
    pos(40, 6);
    printf("\"solve\":solve the current sudoku \n");
    pos(40, 7);
    printf("\"put x y n\":put n into the line x, column y\n");
    pos(40, 8);
    printf("\"hint\":hint the next step\n");
    pos(40, 9);
    printf("\"back\":back to last step\n");
    pos(40, 10);
    printf("\"over\":judge if the game is over\n");
    pos(40, 11);
    printf("\"save\":save the sudoku's state in \"sudoku.dat\"\n");
    pos(40, 12);
    printf("\"show\":show all game's name and load someone\n");
    pos(0, 1);
}

char Decide() {
    int i;
    char d;
    pos(0, 3);
    printf("Do you want to play again?");
    for (i = 0; i <= 1500; i += 100) {
        Sleep(100);
        if (GetAsyncKeyState(VK_RETURN))
            break;
    }
    pos(0, 5);
    printf("input \"YES\" to continue     or input \"NO\" to exit\n");
    pos(0, 7);
    while (isspace(d = getchar())) continue;
    while (getchar() != '\n') continue;
    if (isupper(d))
        d = tolower(d);
    return d;
}

//get the character stream from scream
int stringProceed(Sudoku* S) {
    char c;
    char string[99];
    memset(string, 0, sizeof string);
    int number[3] = { 0 };
    int i = 0;
    scanf("%s", string);
    while ((c = getchar()) != '\n') {
        if (isdigit(c) || c == '-') {
            ungetc(c, stdin);
            scanf("%d", &number[i]);
            i++;
        }
    }
    if (!strcmp(string, "exit"))
        return EXIT;
    if (!strcmp(string, "print")) {
        orderReceive(S, PRINT, number);
        return PRINT;
    }
    if (!strcmp(string, "generate")) {
        orderReceive(S, GENERATE, number);
        return GENERATE;
    }
    if (!strcmp(string, "input")) {
        orderReceive(S, INPUT_TAB, number);
        return INPUT_TAB;
    }
    if (!strcmp(string, "solve")) {
        orderReceive(S, SOLVE, number);
        return SOLVE;
    }
    if (!strcmp(string, "hint")) {
        orderReceive(S, HINT, number);
        return HINT;
    }
    if (!strcmp(string, "put")) {
        orderReceive(S, INPUT_NUMBER, number);
        return INPUT_NUMBER;
    }
    if (!strcmp(string, "save")) {
        orderReceive(S, SAVE, number);
        return SAVE;
    }
    if (!strcmp(string, "show")) {
        orderReceive(S, SHOW, number);
        return SHOW;
    }
    if (!strcmp(string, "back")) {
        orderReceive(S, BACK, number);
        return BACK;
    }
    if (!strcmp(string, "over")) {
        orderReceive(S, OVER, number);
        return OVER;
    }
    printf("Error!\n");
    return 1;
}

/*
 * it includes all orders from player
 */
void orderReceive(Sudoku* S, int order, int* number) {
    switch (order) {
    case PRINT:
        printf("current sudoku state is\n");
        print(S->currTab);
        break;
    case GENERATE:
        printf("generated sudoku is\n");
        randomInit(S);
        print(S->initTab);
        break;
    case INPUT_TAB:
        printf("Please input a sudoku:\n");
        if (inputTab(S)) {
            printf("accept your input\n");
            print(S->initTab);
        }
        else {
            printf("illegal input\n");
        }
        break;
    case SOLVE:
        bool solvable;
        solvable = oneSolution(S, 0);//S->currentTab has been changed
        if (solvable) {
            printf("sudoku before solution is\n");
            print(S->initTab);
            printf("one possible solution is\n");
            print(S->currTab);
        }
        else
            printf("sudoku cannot be solved\n");
        break;
    case HINT:
        pos(52, 1);
        printf("Last Sudoku      ");
        pos(0, 3);
        printf("before hint, sudoku is\n");
        print(S->currTab);
        int hintSituation;
        hintSituation = hint(S);
        if (hintSituation == 2) {
            printf("\nGame is over!\nYou can put \"over\" to end the game\n");
        }
        else if (hintSituation == 1) {
            printf("now it is\n");
            print(S->currTab);
        }
        else if (hintSituation == 0) {
            printf("\nsudoku cannot be solved.\n");
        }
        break;
    case INPUT_NUMBER:
        int inputNumberState;
        inputNumberState = inputNum(S, number[0], number[1], number[2]);
        if (inputNumberState == 1) {
            pos(52, 1);
            printf("Last Sudoku       ");
            pos(0, 3);
            printf("now sudoku is.\n");
            print(S->currTab);
        }
        else if (inputNumberState == 2)
            printf("ERROR illegal location\n");
        else if (inputNumberState == 3)
            printf("ERROR data range exceed\n");
        else if (inputNumberState == 4)
            printf("ERROR the number is under data range\n");
        else if (inputNumberState == 5)
            printf("ERROR there are already a number in this position\n");
        break;
    case SAVE:
        if (save(S))
            printf("your game state has been recorded successfully\n");;
        break;
    case SHOW:
        show(S);
        break;
    case BACK:
        if (back(S)) {
            printf("the last sudoku is:\n");
            print(S->currTab);
        }
        else
            printf("you cannot back.\n");
        break;
    case OVER:
        int over = isOver(S);
        if (over == 0) {
            printf("Game is not over \nMaybe you have made some mistakes\n");
        }
        else if (over == 1) {
            printf("Congratulations!\nYou win and this sudoku is not solvable!\n");
            printf("\nPlease input \"exit\" to end the game\n");
        }
        else if (over == 2) {
            printf("Congratulations!\nYou win!\n");
            printf("\nPlease input \"exit\" to end the game\n");
        }
        break;
    }

}

//print a current sudoku
void print(int table[][9]) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}



//
/*read a sudoku table and initialize it
 * if the sudoku table is legal,store the table in currTab and initTab,
 * and judge if it is solvable
 * return1
 * if the table is illegal ,
 * return 0
 * */
int inputTab(Sudoku* S) {
    Sudoku temp;
    bool solvable, legal;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            scanf("%d", &(temp.currTab[i][j]));
    }
    legal = isLegal(&temp);
    if (!legal)
        return 0;
    else {
        solvable = isSolvable(&temp);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                S->currTab[i][j] = temp.currTab[i][j];
                S->initTab[i][j] = temp.currTab[i][j];
            }
        }
        S->isCurrSolvable = solvable;
        S->isInitSolvable = solvable;
        return 1;
    }
}

void randomInit(Sudoku* S) {
    std::uniform_int_distribution<int> r(0, 80);
    bool judgeSolvable;
    int randNum = r(e) % LIBRARY;
    int Tab[9][9];
    int i, j, k = 0;
    int count = 0;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++) {
            Tab[i][j] = libraryTab[randNum][k++];
        }
    while (count < 81 - level) {
        i = r(e) / 9;
        j = r(e) % 9;
        if (Tab[i][j] != 0) {
            Tab[i][j] = 0;
            count++;
        }
    }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++) {
            S->initTab[i][j] = Tab[i][j];
            S->currTab[i][j] = Tab[i][j];
        }
}

/* check if this sudoku CurrentTab can be solved
 * Do not change anything!
 * return true if found solution, return false if no solution
 * */
bool isSolvable(const Sudoku* S) {
    int i, j;
    bool solvable;
    Sudoku temp;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            temp.currTab[i][j] = S->currTab[i][j];
        }
    }
    solvable = oneSolution(&temp, 0);
    return solvable;
}

/* solve a sudoku and Change its CurrentTab!!!!!!
 * give one of its solutions
 * input a sudoku,and a position which n can express
 * return true if it is can reach last position,return false if it cannot
 */
bool oneSolution(Sudoku* S, int pos) {
    bool key = false;
    bool flag;
    int i = pos / 9;
    int j = pos % 9;
    if (S->currTab[i][j] != 0) {//已有原始数据
        if (pos == 80)
            key = true;
        else
            key = oneSolution(S, pos + 1);
    }
    else {
        for (int k = 1; k <= 9; ++k) {
            S->currTab[i][j] = k;
            flag = isLegal(S);
            if (flag) {
                if (pos == 80)
                    key = true;
                else
                    key = oneSolution(S, pos + 1);
            }
            if (key)
                break;
            else
                S->currTab[i][j] = 0;
        }
    }
    return key;
}

/*
 * if currently solvable, update currTab (one step forward), return 1;
 * if currently unsolvable, return 0.
 *
 */
int oneStepForward(Sudoku* S) {
    int* position = (int*)malloc(3 * sizeof(int));
    int i, j;
    bool solvable;
    Sudoku temp;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j) {
            temp.currTab[i][j] = S->currTab[i][j];
        }
    }
    solvable = oneSolution(&temp, 0);//oneSolution will change the temp.currTab situation
    if (solvable) {
        for (i = 0; i < 9; ++i) {
            for (j = 0; j < 9; ++j) {
                if (temp.currTab[i][j] == S->currTab[i][j])
                    continue;
                else
                    break;
            }
            if (temp.currTab[i][j] == S->currTab[i][j])
                continue;
            else
                break;
        }
        position[0] = i + 1;
        position[1] = j + 1;
        position[2] = S->currTab[i][j];
        st.push(position);
        S->currTab[i][j] = temp.currTab[i][j];
        return 1;
    }
    else
        return 0;
}


/*
 * if currently over,do not change table and remind player
 * return 2
 * if currently solvable,change the currTab,and give its next step
 * return1
 * if unsolvable,do not change table and remind the player
 * return 0
 */
int hint(Sudoku* S) {
    int solvable;
    bool full = isFull(S);
    if (full)
        return 2;
    else {
        solvable = oneStepForward(S);
        if (solvable)
            return 1;
        else
            return 0;
    }
}

/*
 *  update currTab,not update isCurrSolvable
 *  return 0 if some position has the same number,output information
 *  return 1 if input legal.
 *  return 2 if illegal location
 *  return 3 if data range exceed
 *  return 4 if the number is under data range
 *  return 5 if there are already a number in this position
 */
int inputNum(Sudoku* S, int row, int col, int number) {
    int* position = (int*)malloc(3 * sizeof(int));
    int rowOffset = (row - 1) / 3, colOffset = (col - 1) / 3;
    if (row > 9 || col > 9) {
        return 2;
    }
    else if (number > 9) {
        return 3;
    }
    else if (number < 0) {
        return 4;
    }
    else if (S->currTab[row - 1][col - 1] != 0) {
        return 5;
    }
    for (int i = 0; i < 9; ++i) {
        if (S->currTab[row - 1][i] == number) {
            printf("ERROR line illegal\nThe line %d column %d has the same number\n", row, i + 1);
            return 0;
        }
        if (S->currTab[i][col - 1] == number) {
            printf("ERROR line illegal\nThe line %d column %d has the same number\n", i + 1, col);
            return 0;
        }
        if (row == col) {
            if (S->currTab[i][i] == number) {
                printf("ERROR cross illegal\nThe line %d column %d has the same number\n", i + 1, i + 1);
                return 0;
            }
        }
        if ((row + col) == 10) {
            if (S->currTab[9 - i][i] == number) {
                printf("ERROR cross illegal\nThe line %d column %d has the same number\n", 10 - i, i + 1);
                return 0;
            }
        }
    }
    /*3x3 sub table check*/
    for (int i = rowOffset*3; i < rowOffset*3 + 3; ++i) {
        for (int j = colOffset*3; j < colOffset*3 + 3; ++j) {
            if (S->currTab[i][j] == number) {
                printf("ERROR 3x3 illegal\n3x3 sub table has the same number\n", i + 1, i + 1);
                return 0;
            }
        }

    }
    position[0] = row;
    position[1] = col;
    position[2] = S->currTab[row - 1][col - 1];
    st.push(position);
    S->currTab[row - 1][col - 1] = number;
    return 1;
}


/*
 *creat a account.dat
 *input a file's name,and save it
 * saving successful, return 1,
 * saving failed , return 0
 */
int save(Sudoku* S) {
    char newName[20];
    char fileName[20] = NAME;
    sudokuFile* head = NULL;
    head = creatAccount(head, fileName);
    printf("input your game record name\n");
    gets_s(newName, 20);
    while (!nameCmp(newName, head)) {
        printf("This name has existed\n");
        printf("input your game record name again\n");
        gets_s(newName, 20);
    }
    add(S, head, fileName, newName);
    freeList(head);
    return 1;
}

/*
 *it will show the text.dat's content
 * read the sudoku's ID and load the game if you have saved
 */
int show(Sudoku* S) {
    int id;
    int isReach;
    char fileName[20] = NAME;
    sudokuFile* head = NULL;
    head = creatAccount(head, fileName);
    read(head);
    scanf("%d", &id);
    while (!(isReach = isSearch(S, head, id))) {
        printf("Can't find it,try again!\n");
        scanf("%d", &id);
    }
    printf("last time sudoku is\n");
    print(S->currTab);
    freeList(head);
    return 1;
}

/*
 * print the content of text.dat
 */
int read(sudokuFile* head) {
    sudokuFile* p;
    p = head;
    while (p) {
        if (p->ID == 0)
            printf("%d-%s\n", p->ID, p->name);
        else
            printf("%d-%s-%d.%d.%d.%d:%d\n", p->ID, p->name, p->time[0], p->time[1], p->time[2], p->time[3],
                p->time[4]);
        p = p->next;
    }
    return 1;
}

/*
 * judge if have the ID that text.dat have saved
 */
int isSearch(Sudoku* S, sudokuFile* head, int id) {
    sudokuFile* p;
    p = head;
    while (p) {
        if (id == p->ID) {
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    S->currTab[i][j] = p->sudoku.currTab[i][j];
                    S->initTab[i][j] = p->sudoku.initTab[i][j];
                }
            }
            S->isCurrSolvable = p->sudoku.isCurrSolvable;
            S->isInitSolvable = p->sudoku.isInitSolvable;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

/*
 *
 * if the account has existed, read it and creat a file struct list
 * if the account do not exist, creat a account and creat a file struct list
 */
sudokuFile* creatAccount(sudokuFile* head, char* fileName) {
    int flag = 1;
    sudokuFile a;
    sudokuFile* p1, * p2 = &a;
    FILE* fp;
    if (!(fp = fopen(fileName, "rb"))) {
        head = (sudokuFile*)malloc(sizeof(sudokuFile));
        head->ID = 0;
        memset(head->name, 0, sizeof(head->name));
        strcpy(head->name, "new game");
        getTime(head->time);
        Sudoku S;
        memset(S.currTab, 0, 81 * sizeof(int));
        memset(S.initTab, 0, 81 * sizeof(int));
        S.isCurrSolvable = true;
        S.isInitSolvable = true;
        head->sudoku = S;
        head->next = NULL;
        fp = fopen(fileName, "wb");
        fwrite(head, sizeof(sudokuFile), 1, fp);
        fclose(fp);
    }
    else {
        do {
            p1 = (sudokuFile*)malloc(sizeof(sudokuFile));
            fread(p1, sizeof(sudokuFile), 1, fp);
            if (flag) {
                head = p1;
                flag = 0;
            }
            else
                p2->next = p1;
            p2 = p1;
        } while (p1->next);
        p2->next = NULL;
        fclose(fp);
    }
    return head;
}


int getTime(int* tm) {
    time_t now;
    struct tm* tm_now;
    time(&now);
    tm_now = localtime(&now);
    tm[0] = tm_now->tm_year + 1900;
    tm[1] = tm_now->tm_mon + 1;
    tm[2] = tm_now->tm_mday;
    tm[3] = tm_now->tm_hour;
    tm[4] = tm_now->tm_min;
    return 0;
}

/*
 * if have the same name return false
 */
bool nameCmp(char* newName, sudokuFile* head) {
    sudokuFile* p = head;
    while (p) {
        if (!strcmp(newName, p->name))
            return false;
        else
            p = p->next;
    }
    return true;
}

/*
 * add the status in to the file
 */
int add(Sudoku* S, sudokuFile* head, char* fileName, char* newName) {
    FILE* fp;
    sudokuFile* p = head;
    sudokuFile* newFile = (sudokuFile*)malloc(sizeof(sudokuFile));
    memset(newFile->name, 0, sizeof(newFile->name));
    strcpy(newFile->name, newName);
    getTime(newFile->time);
    newFile->sudoku = *S;
    newFile->next = NULL;
    while (p->next)
        p = p->next;
    newFile->ID = p->ID + 1;
    p->next = newFile;
    p = head;
    if (!(fp = fopen(fileName, "wb"))) {
        printf("Cannot open the %s file.\n", fileName);
        exit(1);
    }
    while (p) {
        fwrite(p, sizeof(sudokuFile), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

void freeList(sudokuFile* head) {
    sudokuFile* p1 = head;
    sudokuFile* p2 = head->next;
    while (p1->next) {
        free(p1);
        p1 = p2;
        p2 = p2->next;
    }
    free(p1);
}

/* TEST PASSED
 * if currently legal, return 1.
 * if currently illegal, return 0.
 * DO NOT change isCurrSolvable & isInitSolvable
 * LINE, ROW, CROSS, 3x3, >17
 * */
bool isLegal(Sudoku* S) {
    int tag[9];
    int i, j;
    memset(tag, 0, 9 * sizeof(int));
    /*element range check*/
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (S->currTab[i][j] < 0 || S->currTab[i][j] > 9)
                return false;
        }
    }

    memset(tag, 0, 9 * sizeof(int));
    /*line check*/
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (S->currTab[i][j] > 0) {
                if (tag[S->currTab[i][j] - 1] == 1)
                    return false;
                tag[S->currTab[i][j] - 1] = 1;
            }
        }
        memset(tag, 0, 9 * sizeof(int));
    }

    /*row check*/
    for (j = 0; j < 9; j++) {
        memset(tag, 0, 9 * sizeof(int));
        for (i = 0; i < 9; i++) {
            if (S->currTab[i][j] > 0) {
                if (tag[S->currTab[i][j] - 1] == 1)
                    return false;
                tag[S->currTab[i][j] - 1] = 1;
            }
        }
    }

    /*cross check*/
    memset(tag, 0, 9 * sizeof(int));
    for (i = 0; i < 9; i++) {
        if (S->currTab[i][i] > 0) {
            if (tag[S->currTab[i][i] - 1] == 1)
                return false;
            tag[S->currTab[i][i] - 1] = 1;
        }
    }
    memset(tag, 0, 9 * sizeof(int));
    for (i = 0; i < 9; i++) {
        if (S->currTab[i][8 - i] > 0) {
            if (tag[S->currTab[i][8 - i] - 1] == 1)
                return false;
            tag[S->currTab[i][8 - i] - 1] = 1;
        }
    }
    /*element number check*/
    int count = 0;
    for (j = 0; j < 9; j++) {
        for (i = 0; i < 9; i++) {
            if (S->currTab[i][j] > 0)
                count++;
        }
    }
    if (count < 17)
        return false;

    /*3x3 sub table check*/
    int rowOffset, colOffset;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            memset(tag, 0, 9 * sizeof(int));
            for (rowOffset = 0; rowOffset < 3; rowOffset++) {
                for (colOffset = 0; colOffset < 3; colOffset++) {
                    if (S->currTab[3 * i + rowOffset][3 * j + colOffset] > 0) {
                        if (tag[S->currTab[3 * i + rowOffset][3 * j + colOffset] - 1] == 1)
                            return false;
                        tag[S->currTab[3 * i + rowOffset][3 * j + colOffset] - 1] = 1;
                    }
                }
            }
        }
    }
    return true;
}


/*
 * TODO
 * if cannot solvable
 * if current table has been solved,return 1;
 * if current table need solving ,return 0;
 */
bool isFull(Sudoku* S) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (S->currTab[i][j] == 0)
                return false;
            else
                continue;
        }
    }
    return true;
}

/*Back to last step
 *
 * if the stack is empty means coming back to the initial situation
 * else the currentTab come back to the last step
 */
int back(Sudoku* S) {
    int* position;
    if (st.empty())
        return 0;
    else {
        position = st.top();
        S->currTab[position[0] - 1][position[1] - 1] = position[2];

        free(position);
        st.pop();
        return 1;
    }
}

/* update isCurrSolvable
 * Judge if the game is over
 * game is not over
 * return 0.player judged wrongly
 *
 * game over case:
 * return 1.the initial sudoku is unsolvable
 * return 2.the sudoku is full and current sudoku is solvable
 *
 */
int isOver(Sudoku* S) {
    bool judgeSolvable = isSolvable(S);
    S->isCurrSolvable = judgeSolvable;
    if (!judgeSolvable) {//current Sudoku is unsolvable
        if (!S->isInitSolvable)
            return 1;
        else
            return 0;
    }
    else {
        if (isFull(S))
            return 2;
        else
            return 0;
    }
}


