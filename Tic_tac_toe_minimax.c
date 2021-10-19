#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PLAYER 1
#define BOT -1

void display_logo();
int difficulty_selection();
void player_turn(int (*board)[3]);
void bot_turn(int (*board)[3], int);
void board_state(int (*board)[3], int);
int check_winner(int (*board)[3]);
void display_result(int);

int max(int, int);
int min(int, int);
int move_left(int (*board)[3]);
int minimax(int (*board)[3], int);
void bestmove(int (*board)[3]);

// Player is X Bot is O
int main(void)
{
    int game_on = 1;

    display_logo();
    while (game_on)
    {
        int board[3][3] = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};

        int turn = 1;
        int winner = 0;
        char game_should_continue[10];
        int is_hard = difficulty_selection();

        while (winner == 0 && move_left(board) != 0)
        {
            board_state(board, turn);
            if (turn % 2 == 1)
                player_turn(board);
            else if (turn % 2 == 0)
            {
                bot_turn(board, is_hard);
                sleep(1);
            }

            winner = check_winner(board);
            turn++;
        }
        board_state(board, --turn);

        display_result(winner);

        printf("\n\nDo you want to continue? (y/n):\n> ");
        scanf("%s", game_should_continue);
        while (getchar() != '\n')
        {
        }

        if (strcmp(game_should_continue, "y") != 0)
        {
            game_on = 0;
        }
    }

    return 0;
}

void display_logo()
{
    printf("%s\n%s\n%s\n%s\n%s\n%s\n\n",
           " _______ _        _______           _______",
           "|__   __(_)      |__   __|         |__   __|",
           "   | |   _  ___     | | __ _  ___     | | ___   ___",
           "   | |  | |/ __|    | |/ _` |/ __|    | |/ _ \\ / _ \\",
           "   | |  | | (__     | | (_| | (__     | | (_) |  __/",
           "   |_|  |_|\\___|    |_|\\__,_|\\___|    |_|\\___/ \\___|");
    printf("\t\tWelcome to Tic Tac Toe\n");
    printf("\t\tPlayer: 'X' | Bot: 'O'\n");
}

int difficulty_selection()
{
    char difficulty[100];
    printf("\nChoose Your Difficulty (Easy/Hard):\n> ");

    scanf("%s", difficulty);
    while ((strcmp(difficulty, "Easy") != 0) && (strcmp(difficulty, "Hard") != 0))
    {
        printf("Invalid Input. Please re-enter:\n> ");
        scanf("%s", difficulty);
    }

    if (strcmp(difficulty, "Hard") == 0)
        return 1;
    return 0;
}

void player_turn(int (*board)[3])
{
    int row, col;

    printf("Its Player's turn.\nInsert row follow by column:\n> ");
    while ((scanf("%d %d", &row, &col) != 2) || (row > 3 || row < 1) || (col > 3 || col < 1) || board[--row][--col] != 0)
    {
        while (getchar() != '\n')
        {
        }

        printf("It is not valid. Please re-enter: ");
    }
    board[row][col] = PLAYER;
}

void bot_turn(int (*board)[3], int hard)
{
    int row, col;
    if (hard == 1)
        bestmove(board);
    else
    {
        do
        {
            srand(time(NULL));
            int random_num = rand() % 8 + 0;
            row = random_num % 3;
            col = random_num / 3;

        } while (board[row][col] != 0);
        board[row][col] = BOT;
    }
}

void board_state(int (*board)[3], int turn)
{

    char board_c[3][3];
    system("cls");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                board_c[i][j] = ' ';
            else if (board[i][j] == 1)
                board_c[i][j] = 'X';
            else if (board[i][j] == -1)
                board_c[i][j] = 'O';
        }

    printf("\n      Round: %d", turn);

    printf("\n\n     1   2   3\n");
    for (int row = 0; row < 3; row++)
    {
        printf("   +---+---+---+ \n");
        printf(" %d | %c | %c | %c | \n", row + 1, board_c[row][0], board_c[row][1], board_c[row][2]);
    }
    printf("   +---+---+---+ \n\n");

    if (turn % 2 == 0)
        printf("   Bot's Turn ... ");
}

int check_winner(int (*board)[3])
{
    if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && (board[0][0] != 0))
        return board[0][0];

    else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && (board[0][2] != 0))
        return board[0][2];

    for (int i = 0; i < 3; i++)
        if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) && (board[i][0] != 0))
            return board[i][0];

    for (int i = 0; i < 3; i++)
        if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) && (board[0][i] != 0))
            return board[0][i];

    return 0;
}

void display_result(int winner)
{
    if (winner == PLAYER)
        printf("Congratulation you won!");
    else if (winner == BOT)
        printf("You lost!");
    else
        printf("Its a Draw!");
}

int max(int num1, int num2)
{
    return (num1 > num2) ? num1 : num2;
}

int min(int num1, int num2)
{
    return (num1 > num2) ? num2 : num1;
}

int move_left(int (*board)[3])
{
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[j][i] == 0)
                return 1;
        }
    }
    return 0;
}

int minimax(int (*board)[3], int Max_Min)
{
    int score = check_winner(board);

    if (score == PLAYER)
        return PLAYER;
    else if (score == BOT)
        return BOT;
    else if (move_left(board) == 0)
        return 0;

    if (Max_Min == PLAYER)
    {
        int best_score = -10;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == 0)
                {
                    board[i][j] = PLAYER;
                    best_score = max(best_score, minimax(board, BOT));
                    board[i][j] = 0;
                }
            }
        }
        return best_score;
    }
    else if (Max_Min == BOT)
    {
        int best_score = 10;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == 0)
                {
                    board[i][j] = BOT;
                    best_score = min(best_score, minimax(board, PLAYER));
                    board[i][j] = 0;
                }
            }
        }
        return best_score;
    }
    return 0;
}

void bestmove(int (*board)[3])
{
    int min_score = 10;
    int best_row, best_col, position = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = BOT;
                int score = minimax(board, PLAYER);
                board[i][j] = 0;

                if (min_score > score)
                {
                    best_row = i;
                    best_col = j;
                    min_score = score;
                }
            }
        }
    }
    board[best_row][best_col] = BOT;
}
