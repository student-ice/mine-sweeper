#include "game.h"

void menu()
{
    printf("******************************************\n");
    printf("********** 1. play    0. exit ************\n");
    printf("******************************************\n");
}

void enterGame()
{
    int input = 0;
    do
    {
        menu();
        printf("请选择:>");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            startGame();
            break;
        case 0:
            printf("退出游戏\n");
            break;
        default:
            printf("输入的是无效数字\n");
            break;
        }
    } while (input);
}

void startGame()
{
    // 字符二维数组
    char data[ROWS][COLS];
    char show[ROWS][COLS];
    // 初始化二维数组
    init(data, ROWS, COLS, '0');
    init(show, ROWS, COLS, '*');

    // display(data, ROW, COL);
    display(show, ROW, COL);

    setMine(data, ROW, COL);
    // display(data, ROW, COL);

    // 排雷
    findMine(show, data, ROW, COL);
}

void init(char array[ROWS][COLS], int row, int col, char c)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            array[i][j] = c;
        }
    }
}

void display(char array[ROWS][COLS], int row, int col)
{
    int i, j;
    printf("  ");
    // 打印列号
    for (i = 1; i <= col; i++)
    {
        // 列号
        printf(" %d ", i);
    }
    printf("\n");
    for (i = 1; i <= row; i++)
    {
        // 行号
        printf("%d ", i);
        for (j = 1; j <= col; j++)
        {
            printf(" %c ", array[i][j]);
        }
        printf("\n");
    }
}

void setMine(char array[ROWS][COLS], int row, int col)
{
    int x, y, i;
    for (i = 0; i < COUNT; i++)
    {
        x = rand() % COL + 1;
        y = rand() % ROW + 1;
        if (array[x][y] == '1')
        {
            i--;
        }
        else
        {
            array[x][y] = '1';
        }
    }
}

void findMine(char show[ROWS][COLS], char data[ROWS][COLS], int row, int col)
{
    int x, y, i = 0;
    while (1)
    {
        printf("请输入排查雷的坐标:>");
        scanf("%d %d", &x, &y);
        if (x >= 1 && x <= row && y >= 1 && y <= col)
        {
            // 坐标合法
            if (data[x][y] == '1')
            {
                i++;
                if (i == 1)
                {
                    printf("你已经被炸死了，还有最后一次机会！！！\n");
                    continue;
                    ;
                }
                // 展示数据
                display(show, row, col);
                // 你被炸死了游戏结束
                printf("你被炸死了，游戏结束\n");
                break;
            }
            else
            {
                // 递归探索
                recurveSearch(show, data, row, col, x, y);
                display(show, row, col);
                if (isWin(show, data, row, col))
                {
                    break;
                }
            }
        }
        else
        {
            printf("输入的坐标非法，请重新输入\n");
        }
    }
    if (i != 2)
        printf("恭喜你，排雷成功\n");
}

void recurveSearch(char show[ROWS][COLS], char data[ROWS][COLS], int row, int col, int x, int y)
{
    // 递归条件:
    //  1. 遇到了空白格
    //  2. 当前格子外围有地雷
    if (show[x][y] == ' ')
    {
        return;
    }
    else if (getMineCount(data, x, y))
    {
        show[x][y] = getMineCount(data, x, y) + '0';
        return;
    }
    show[x][y] = ' ';
    recurveSearch(show, data, row, col, x - 1, y - 1);
    recurveSearch(show, data, row, col, x - 1, y);
    recurveSearch(show, data, row, col, x - 1, y + 1);
    recurveSearch(show, data, row, col, x, y - 1);
    recurveSearch(show, data, row, col, x, y + 1);
    recurveSearch(show, data, row, col, x + 1, y - 1);
    recurveSearch(show, data, row, col, x + 1, y);
    recurveSearch(show, data, row, col, x + 1, y + 1);
}

int getMineCount(char data[ROWS][COLS], int x, int y)
{
    int res = data[x - 1][y - 1] + data[x - 1][y] + data[x - 1][y + 1] +
              data[x][y - 1] + data[x][y + 1] +
              data[x + 1][y - 1] + data[x + 1][y] + data[x + 1][y + 1] - 8 * '0';
    return res;
}

bool isWin(char show[ROWS][COLS], char data[ROWS][COLS], int row, int col)
{
    int i, j;
    for (i = 1; i <= row; i++)
    {
        for (j = 1; j <= col; j++)
        {
            if (show[i][j] != '*' && data[i][j] == '0' || data[i][j] == '1')
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}