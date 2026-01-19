#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MINE 1
#define EXPLORED 2
#define UNEXPLORED 0
#define MARQUED -1
#define BLANK ' '
#define MAX_SIZE 35
#define GAME_OVER 1
#define GAME_COMPLETED 2
#define GAME_ACTIVE 0

/******************************************     FUNCTION HEADERS     **********************************************/

int **createBoard(int size);
char **createShowBoard(int size);
void freeMatrix(int **pBoard, char **pShowBoard, int size);
void printBoard(int **pBoard, int size);
void printShowBoard(char **pShowBoard, int size);
void initalizeBoard(int **pBoard, int size, int mines);
void initializeShowBoard(char **pShowBoard, int size);
int randomGenerator(int a, int b);
int checkSurrounding(int **pBoard, int tempx, int tempy, int size);
int checkBoard(int **pBoard, int size);

/******************************************     MAIN     **********************************************/

int main()
{
    int size=2, mines=0, **pBoard = NULL, number, game_status=0, tempx, tempy;
    char **pShowBoard = NULL, temp_decision;
    printf("\n\n\t>> WELCOME TO THE MINE SWEEPER <<");
    
    /*Define board size*/
    do
    {
        if (size <= 1 || size > MAX_SIZE)
        {
            printf("\nPlease enter a valid input (2 / %d)", MAX_SIZE);
        }
        
        printf("\n\nType the board size: ");
        scanf("%d", &size);

    } while (size <= 1 || size > MAX_SIZE);
    
    /*Define number of mines*/
    do
    {
        if (mines >= size * size || mines < 0)
        {
            printf("\nPlease enter a valid number\n\n");
        }

        printf("Type the number of mines: ");
        scanf("%d", &mines);
    } while (mines >= size * size || mines < 0);
    
    
    /*Generación de semilla para números aleatorios*/
    srand(time(NULL));

    /*Creación de tableros*/
    if (!(pBoard = createBoard(size)))
    {
        printf("Error 00: Could not allocate memory");
    }    
    
    if (!(pShowBoard = createShowBoard(size)))
    {
        printf("Error 00: Could not allocate memory");
    } 

    initalizeBoard(pBoard, size, mines);
    initializeShowBoard(pShowBoard, size);
    printBoard(pBoard, size);
    
    /***********  Game Loop  *********/

    printf("\n\n");

    while(game_status == GAME_ACTIVE)
    {

        printShowBoard(pShowBoard, size); 
        printf("\n\n");

        do
        {
            printf("\nDo you want to (E)xplore or (M)ark a position?: ");
            scanf(" %c", &temp_decision);
        } while (temp_decision != 'E' && temp_decision != 'M');
        
        do
        {
            printf("Enter the row: ");
            scanf("%d", &tempx);
            printf("Enter the column: ");
            scanf("%d", &tempy);
            printf("\n");

            if (tempx < 1 || tempx > size || tempy < 1 || tempy > size)
            {
                printf("Given coordinates are out of range, try again\n");
                continue;
            }

            if (pBoard[tempx-1][tempy-1] == EXPLORED || pBoard[tempx-1][tempy-1] == MARQUED)
            {
                printf("That positions has already been explored, try again\n");
                continue;
            }

            break;
    
        } while (1);
        
        tempx--;
        tempy--;
        
        if (pBoard[tempx][tempy] == MINE && temp_decision == 'E')
        {
            game_status = GAME_OVER;
            break;
        }
        else if (pBoard[tempx][tempy] == UNEXPLORED && temp_decision == 'E')
        {
            pBoard[tempx][tempy] = EXPLORED;
            pShowBoard[tempx][tempy] = checkSurrounding(pBoard, tempx, tempy, size) + '0';
        }    
        else if (temp_decision == 'M' && pBoard[tempx][tempy] == MINE)
        {
            pBoard[tempx][tempy] = MARQUED;
            pShowBoard[tempx][tempy] = 'x';
        }    
        else if (temp_decision == 'M' && pBoard[tempx][tempy] == UNEXPLORED)
        {
            game_status = GAME_OVER;  
            break;
        }
        
        if (checkBoard(pBoard, size) == 1)
        {
            game_status = GAME_COMPLETED;
            break;
        }
    }
    
    if (game_status == GAME_OVER)
    {
        printf("\033[031mGAME OVER\033[0m");
        freeMatrix(pBoard, pShowBoard, size);
        return 0;
    }
    
    printf("\033[032mGAME COMPLETED\033[0m");
    freeMatrix(pBoard, pShowBoard, size);
    return 0;
}

/******************************************     FUNCTION IMPLEMENTATION     **********************************************/

void freeMatrix(int **pBoard, char **pShowBoard, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (pBoard[i])
        {
            free(pBoard[i]);
        }
        if (pShowBoard[i])
        {
            free(pShowBoard[i]);
        }
        
    }
    free(pBoard);
    free(pShowBoard);
    
}

/***********  Create the board  *********/

int **createBoard(int size)
{
    /*Pointer array*/
    int **pBoard = NULL;
    if (!(pBoard = (int**)malloc(size * sizeof(int*))))
    {
        return NULL;
    }

    /*Int array*/
    for (int i = 0; i < size; i++)
    {
        if (!(pBoard[i] = (int*)malloc(size * sizeof(int))))
        {
            for (int j = 0; j < i; j++) 
            {
                free(pBoard[j]); 
            }
            free(pBoard);  
            return NULL;
        }
    }

    return pBoard;
}

char **createShowBoard(int size)
{
    /*Pointer array*/
    char **pShowBoard = NULL;
    if (!(pShowBoard = (char**)malloc(size * sizeof(char*))))
    {
        return NULL;
    }

    /*Int array*/
    for (int i = 0; i < size; i++)
    {
        if (!(pShowBoard[i] = (char*)malloc(size * sizeof(char))))
        {
            for (int j = 0; j < i; j++) 
            {
                free(pShowBoard[j]); 
            }
            free(pShowBoard);  
            return NULL;
        }
    }

    return pShowBoard;
}

/***********  Printing  *********/

void printShowBoard(char **pShowBoard, int size)
{
    for (int p = 0; p < size; p++)
    {
        if (p < 9)
        {
            printf(" 0%d ", p+1);
        }
        else
        {
            printf(" %d ", p+1);
        }
    }
    
    printf("\n");
    
    for (int r = 0; r < size; r++)
    {
        printf("----");
    }

    printf("-\n");

    for (int i = 0; i < size; i++)
    {
        for (int q = 0; q < size; q++)
        {
            if (pShowBoard[i][q] == 'x')
            {
                printf("| \033[31m%c\033[0m ", pShowBoard[i][q]);
            }
            else
            {
                printf("| \033[32m%c\033[0m ", pShowBoard[i][q]);
            }
        } 
    
        if (i > 8)
        {
        printf("|  %d\n", i+1);
        }
        else if (i <= 8)
        {
        printf("|  0%d\n", i+1);
        }

        for (int r = 0; r < size; r++)
        {
            printf("----");
        }

        printf("-\n");
    }
}

void printBoard(int **pBoard, int size)
{
    printf("\n\n");

    for (int p = 0; p < size; p++)
    {
        if (p < 9)
        {
            printf(" 0%d ", p+1);
        }
        else
        {
            printf(" %d ", p+1);
        }
    }
    
    printf("\n");
    
    for (int r = 0; r < size; r++)
    {
        printf("----");
    }

    printf("-\n");

    for (int i = 0; i < size; i++)
    {
        for (int q = 0; q < size; q++)
        {
            printf("| %d ", pBoard[i][q]);
        } 
    
        if (i > 8)
        {
        printf("|  %d\n", i+1);
        }
        else if (i <= 8)
        {
        printf("|  0%d\n", i+1);
        }

        for (int r = 0; r < size; r++)
        {
            printf("----");
        }

        printf("-\n");
    }
}

/***********  Init  *********/

void initalizeBoard(int **pBoard, int size, int mines)
{
    int tempx, tempy;
    /*Start to 0*/
    for (int i = 0; i < size; i++)
    {
        for (int q = 0; q < size; q++)
        {
            pBoard[i][q] = 0;
        }
    }

    /*Randomly distribute mines*/
    for (int i = 0; i < mines;)
    {
        tempx = randomGenerator(0, size-1);
        tempy = randomGenerator(0, size-1);
        if (pBoard[tempx][tempy] == 0)
        {
            pBoard[tempx][tempy] = MINE;
            i++;
        }
    }
}

void initializeShowBoard(char **pShowBoard, int size)
{
    /*Put board to white*/
    for (int i = 0; i < size; i++)
    {
        for (int q = 0; q < size; q++)
        {
            pShowBoard[i][q] = BLANK;
        }
    }
}

/***********  Random numbers  *********/

int randomGenerator(int a, int b)
{
    int temp = a, result;
    if (a == b)
    {
        return a;
    }
    if (a > b)
    {
        a = b;
        b = temp;
    }

    result = a + rand() % (b - a + 1);
    
    return result;
}

/***********  Mine sweeping   *********/

int checkSurrounding(int **pBoard, int tempx, int tempy, int size)
{
    int counter = 0;

    if (tempx + 1 < size && pBoard[tempx + 1][tempy]) counter++;
    if (tempx - 1 >= 0 && pBoard[tempx - 1][tempy]) counter++;
    if (tempy + 1 < size && pBoard[tempx][tempy + 1]) counter++;
    if (tempy - 1 >= 0 && pBoard[tempx][tempy - 1]) counter++;
    if (tempx + 1 < size && tempy + 1 < size && pBoard[tempx + 1][tempy + 1]) counter++;
    if (tempx - 1 >= 0 && tempy - 1 >= 0 && pBoard[tempx - 1][tempy - 1]) counter++;
    if (tempx + 1 < size && tempy - 1 >= 0 && pBoard[tempx + 1][tempy - 1]) counter++;
    if (tempx - 1 >= 0 && tempy + 1 < size && pBoard[tempx - 1][tempy + 1]) counter++;

    return counter;
}

/***********  Check game status   *********/

int checkBoard(int **pBoard, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int q = 0; q < size; q++)
        {
            if (pBoard[i][q] == UNEXPLORED)
            {
                return 0;
            }
        }
    }
    
    return 1;
}

