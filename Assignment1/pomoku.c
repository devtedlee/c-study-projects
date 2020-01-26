#include "pomoku.h"
 
static int g_black_score;
static int g_white_score;
static color_t* g_board[MAX_BOARD_SIZE];
static color_t g_board_array[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
static size_t g_curr_row_size;
static size_t g_curr_col_size;
 
void init_game(void)
{
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
 
    g_black_score = 0;
    g_white_score = 0;
    g_curr_row_size = 15;
    g_curr_col_size = 15;
 
    for (; j < MAX_BOARD_SIZE; j++) {
        for (; k < MAX_BOARD_SIZE; k++) {
            g_board_array[j][k] = COLOR_EMPTY;
        }
        k = 0;
    }
 
    for (; i<MAX_BOARD_SIZE; i++)
    {
        g_board[i] = g_board_array[i];
    }
 
    
}
 
size_t get_row_count(void)
{
    return g_curr_row_size;
}
 
size_t get_column_count(void)
{
    return g_curr_col_size;
}
 
int get_score(const color_t color)
{
    if (color == COLOR_BLACK)
    {
        return g_black_score;
    }
    
    else if (color == COLOR_WHITE)
    {
        return g_white_score;
    }
    
    return -1;
}
 
int get_color(const size_t row, const size_t col)
{
    if ((row >= g_curr_row_size) || (col >= g_curr_col_size))
    {
        return -1;
    }
 
    if (g_board[row][col] == COLOR_BLACK)
    {
        return COLOR_BLACK;
    }
 
    else if (g_board[row][col] == COLOR_WHITE)
    {
        return COLOR_WHITE;
    }
    
    
    return -1;
}
 
 
int is_placeable(const size_t row, const size_t col)
{
    if (row >= g_curr_row_size || col >= g_curr_col_size || g_board[row][col] == COLOR_BLACK || g_board[row][col] == COLOR_WHITE)
    {
        return FALSE;
    }
 
    return TRUE;
}
 
int place_stone(const color_t color, const size_t row, const size_t col)
{
    
    int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int x = 0;
    int y = 0;
    int new_x = 0;
    int new_y = 0;
    int recur_dx = 0;
    int recur_dy = 0;
    int increase_score = 0;
    int stone_number = 0;
    size_t i = 0;
    size_t x_length = 4;
 
    if (is_placeable(row, col) == FALSE)
    {
        return FALSE;
    }
    
    g_board[row][col] = color;
    
    for (; i<x_length; i++){
        x = col + dx[i];
        y = row - dy[i];
        if (check_range(x, y) == TRUE) {
            if (g_board[y][x] == color) {
                recur_dx = x - col;
                recur_dy = y - row;
                stone_number = 1;
				
                while (TRUE) {
 
                    if (x < 0 || x >= (int)g_curr_col_size || y < 0 || y >= (int)g_curr_row_size) {
                        break;
                    }
                    
                    if (g_board[y][x] != color) {
                        break;
                    }
 
                    stone_number++;
                    x = x + recur_dx;
                    y = y + recur_dy;
 
                    if (stone_number >= 5) {
                        increase_score++;
                    }
                }
				
               
            }
 
        }
 
        x = col + dx[i + 4];
        y = row - dy[i + 4];
        if (check_range(x, y) == TRUE) {
            if (g_board[y][x] == color) {
                recur_dx = x - col;
                recur_dy = y - row;
                if (stone_number == 0) {
                    stone_number = 1;
                }
 
                while (TRUE) {
 
                    if (x < 0 || x >= (int)g_curr_col_size || y < 0 || y >= (int)g_curr_row_size) {
                        break;
                    }
                   
                    if (g_board[y][x] != color) {
                        break;
                    }
 
                    x = x + recur_dx;
                    y = y + recur_dy;
 
                    stone_number++;
 
                    if (stone_number >= 5) {
                        increase_score++;
                    }
                }
            }
        }
        
        if (color == COLOR_BLACK) {
            g_black_score += increase_score;
        }
        else {
            g_white_score += increase_score;
        }
 
        stone_number = 0;
        increase_score = 0;
    }
    
    return TRUE;
}
 
/* special moves */
 
int insert_row(const color_t color, const size_t row)
{
    
    size_t i = 0;
    size_t j = 0;
    
    color_t* temp_ptr = NULL;
 
    if (row > g_curr_row_size || g_curr_row_size >= MAX_BOARD_SIZE || check_score(color, 3) == FALSE) {
        return FALSE;
    }
    
    temp_ptr = g_board[g_curr_row_size];
 
    for (; i<(g_curr_row_size - row);i++) {
        g_board[g_curr_row_size - i] = g_board[g_curr_row_size - i - 1];
    }
 
    g_board[row] = temp_ptr;
 
    g_curr_row_size++;
 
    for (; j<g_curr_col_size; j++) {
        g_board[row][j] = COLOR_EMPTY;
    }
 
    reduce_score(color, 3);
    
    return TRUE;
}
 
int insert_column(const color_t color, const size_t col)
{
    
    size_t i = 0;
    size_t j = 0;
 
    if (col > g_curr_col_size || g_curr_col_size >= MAX_BOARD_SIZE || check_score(color, 3) == FALSE) {
        return FALSE;
    }
 
    for (; i<g_curr_row_size; i++) {
        for (; j<(g_curr_col_size - col); j++) {
            g_board[i][g_curr_col_size - j] = g_board[i][g_curr_col_size - j - 1];
        }
        j = 0;
        g_board[i][col] = COLOR_EMPTY;
    }
 
    g_curr_col_size++;
 
    reduce_score(color, 3);
    
    return TRUE;
}
 
 
int remove_row(const color_t color, const size_t row)
{
    
    size_t i = 0;
    color_t* temp_ptr = NULL;
 
    if (row >= g_curr_row_size || g_curr_row_size <= MIN_BOARD_SIZE || check_score(color, 3) == FALSE) {
        return FALSE;
    }
 
    temp_ptr = g_board[row];
 
    for (; i < (g_curr_row_size - row - 1); i++) {
        g_board[row + i] = g_board[row + 1 + i];
    }
 
    g_board[g_curr_row_size - 1] = temp_ptr;
 
    g_curr_row_size--;
 
    reduce_score(color, 3);
    
    return TRUE;
}
 
 
int remove_column(const color_t color, const size_t col)
{
    
    size_t i = 0;
    size_t j = 0;
 
    if (col >= g_curr_col_size || g_curr_col_size <= MIN_BOARD_SIZE || check_score(color, 3) == FALSE) {
        return FALSE;
    }
 
    for (; i<g_curr_row_size; i++) {
        for (; j < (g_curr_col_size - col - 1); j++) {
            g_board[i][col + j] = g_board[i][col + 1 + j];
        }
        j = 0;
    }
    
    g_curr_col_size--;
    reduce_score(color, 3);
 
    return TRUE;
    
}
 
 
int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    
    color_t* temp_ptr = NULL;
 
    if (row0 >= g_curr_row_size || row1 >= g_curr_row_size || check_score(color, 2) == FALSE) {
        return FALSE;
    }
 
    temp_ptr = g_board[row0];
    g_board[row0] = g_board[row1];
    g_board[row1] = temp_ptr;
 
    reduce_score(color, 2);
    
    return TRUE;
}
 
 
int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    color_t temp_arr[MAX_BOARD_SIZE] = {COLOR_EMPTY,};
 
    if (col0 >= g_curr_col_size || col1 >= g_curr_col_size || check_score(color, 2) == FALSE) {
        return FALSE;
    }
 
    for (; i<g_curr_row_size; i++) {
        temp_arr[i] = g_board[i][col0];
    }
 
    for (; j<g_curr_row_size; j++) {
        g_board[j][col0] = g_board[j][col1];
    }
 
    for (; k<g_curr_row_size; j++) {
        g_board[k][col1] = temp_arr[k];
    }
 
    reduce_score(color, 2);
    
    return TRUE;
}
 
 
 
int copy_row(const color_t color, const size_t src, const size_t dst)
{
    size_t i = 0;
 
    if (src >= g_curr_row_size || dst >= g_curr_row_size || check_score(color, 4) == FALSE) {
        return FALSE;
    }
 
    for (; i<g_curr_col_size; i++) {
        g_board[dst][i] = g_board[src][i];
    }
 
    reduce_score(color, 4);
 
    return TRUE;
}
 
 
 
int copy_column(const color_t color, const size_t src, const size_t dst)
{
    size_t i = 0;
 
    if (src >= g_curr_col_size || dst >= g_curr_col_size || check_score(color, 4) == FALSE) {
        return FALSE;
    }
 
    for (; i<g_curr_row_size; i++) {
        g_board[i][dst] = g_board[i][src];
    }
 
    reduce_score(color, 4);
 
    return TRUE;
}
 
 
int check_score(color_t color, int score)
{
    if (color == COLOR_BLACK) {
        if(g_black_score < score) {
            return FALSE;
        }
    }
 
    else if (color == COLOR_WHITE) {
        if(g_white_score < score) {
            return FALSE;
        }
    }
 
    else {
        return TRUE;
    }
 
    return TRUE;
}
 
void reduce_score(color_t color, int score)
{
    if (color == COLOR_BLACK) {
        g_black_score -= score;
    }
 
    else {
        g_white_score -= score;
    }
}
 
int check_range(int x, int y)
{
    if (x >= 0 && x < (int)g_curr_col_size && y >= 0 && y < (int)g_curr_row_size) {
        return TRUE;
    }
 
    else {
        return FALSE;
    }
 
 
}
 
int recursive_check_place_stone(color_t color, int row, int col, int dx, int dy, int* stone_number, int* new_score)
{
    int new_x = col + dx;
    int new_y = row + dy;
 
    (*stone_number)++;
 
    if ((*stone_number) >= 5) {
            (*new_score)++;
        }
 
    if (new_x < 0 || new_x >= (int)g_curr_col_size || new_y < 0 || new_y >= (int)g_curr_row_size) {
        return TRUE;
    }
    else if (g_board[new_y][new_x] == color ) {
        recursive_check_place_stone(color, new_y, new_x, dx, dy, stone_number, new_score);
    }
    else {
        return TRUE;
    }
    
    return TRUE;
}
