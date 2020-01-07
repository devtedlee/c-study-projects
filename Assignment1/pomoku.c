#include <stdio.h>
#include "pomoku.h"

const int BOARD_MIN_SIZE = 10;
const int BOARD_MAX_SIZE = 20;
space_t g_board[20][20] = { { 0, } };
size_t g_black_score = 0;
size_t g_white_score = 0;

void init_game(void)
{
    const int BOARD_DEFAULT_SIZE = 15;

    /*set empty 15X15 board*/
    reset_board(BOARD_DEFAULT_SIZE, BOARD_DEFAULT_SIZE);

    /*set players score to 0*/
    g_black_score = 0;
    g_white_score = 0;
}

size_t get_row_count(void)
{
    size_t i;

    for (i = 0; i < BOARD_MAX_SIZE; i++) {
        if (g_board[i][0] == SPACE_DEACTIVE) {
            break;
        }
    }

    return i;
}

size_t get_column_count(void)
{
    size_t i;

    for (i = 0; i < BOARD_MAX_SIZE; i++) {
        if (g_board[0][i] == SPACE_DEACTIVE) {
            break;
        }
    }

    return i;
}

int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK:
        return g_black_score;
    case COLOR_WHITE:
        return g_white_score;
    default:
        return -1;
    }
}

int get_color(const size_t row, const size_t col)
{
    space_t current_stone = g_board[row][col];

    switch (current_stone) {
    case SPACE_BLACK:
        return 0;
    case SPACE_WHITE:
        return 1;
    default:
        return -1;
    }
}

int is_placeable(const size_t row, const size_t col)
{
    space_t current_stone = g_board[row][col];

    switch (current_stone) {
    case SPACE_ACTIVE:
        return TRUE;
    default:
        return FALSE;
    }
}

int place_stone(const color_t color, const size_t row, const size_t col)
{
    int r;
    int c;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();
    size_t vertical_connection_count = 1;
    size_t horizontal_connection_count = 1;
    size_t main_diagonal_connection_count = 1;
    size_t anti_diagonal_connection_count = 1;

    if (row > row_size - 1 || col > col_size - 1) {
        return FALSE;
    }

    if (is_placeable(row, col) == TRUE) {
        g_board[row][col] = (space_t)color;
    } else {
        return FALSE;
    }

    for (r = (int)row - 1 ; r > -1; r--) {
        if (g_board[r][col] == (space_t)color) {
            vertical_connection_count++;
        } else {
            break;
        }
    }

    for (r = (int)row + 1 ; r < (int)row_size; r++) {
        if (g_board[r][col] == (space_t)color) {
            vertical_connection_count++;
        } else {
            break;
        }
    }
    
    for (c = (int)col - 1 ; c > -1; c--) {
        if (g_board[row][c] == (space_t)color) {
            horizontal_connection_count++;
        } else {
            break;
        }
    }
    
    for (c = (int)col + 1 ; c < (int)col_size; c++) {
        if (g_board[row][c] == (space_t)color) {
            horizontal_connection_count++;
        } else {
            break;
        }
    }
    
    for (r = (int)row - 1 ; r > -1; r--) {
        if (g_board[r][r] == (space_t)color) {
            main_diagonal_connection_count++;
        } else {
            break;
        }
    }

    for (r = (int)row + 1 ; r < (int)row_size; r++) {
        if (g_board[r][r] == (space_t)color) {
            main_diagonal_connection_count++;
        } else {
            break;
        }
    }

    c = (int)col + 1;
    for (r = (int)row - 1 ; r > -1 || c < (int)col_size; r--) {
        if (g_board[r][c] == (space_t)color) {
            anti_diagonal_connection_count++;
        } else {
            break;
        }
        
        c++;
    }

    c = (int)col - 1;
    for (r = (int)row + 1 ; r < (int)row_size || c > -1; r++) {
        if (g_board[r][c] == (space_t)color) {
            anti_diagonal_connection_count++;
        } else {
            break;
        }

        c--;
    }

    get_score_from_connection(color, vertical_connection_count);
    get_score_from_connection(color, horizontal_connection_count);
    get_score_from_connection(color, main_diagonal_connection_count);
    get_score_from_connection(color, anti_diagonal_connection_count);

    return TRUE;
}

int insert_row(const color_t color, const size_t row)
{
    int r;
    int c;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (row_size >= BOARD_MAX_SIZE || row > row_size) {
        return FALSE;
    }

    if (use_score(color, 3) == FALSE) {
        return FALSE;
    }

    for (r = row_size; r > (int)row - 1; r--) {
        for (c = col_size - 1; c > -1; c--) {
            if ((int)row == r) {
                g_board[r][c] = SPACE_ACTIVE;
            } else {
                g_board[r][c] = g_board[r - 1][c];
            }
        }
    }

    return TRUE;
}

int insert_column(const color_t color, const size_t col)
{
    int r;
    int c;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (col_size >= BOARD_MAX_SIZE || col > col_size) {
        return FALSE;
    }

    if (use_score(color, 3) == FALSE) {
        return FALSE;
    }

    for (c = col_size; c > (int)col - 1 ; c--) {
        for (r = row_size - 1; r > -1; r--) {
            if ((int)col == c) {
                g_board[r][c] = SPACE_ACTIVE;
            } else {
                g_board[r][c] = g_board[r][c - 1];
            }
        }
    }

    return TRUE;
}

int remove_row(const color_t color, const size_t row)
{
    size_t r;
    size_t c;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (row_size <= BOARD_MIN_SIZE || row >= row_size) {
        return FALSE;
    }

    if (use_score(color, 3) == FALSE) {
        return FALSE;
    }

    for (r = row; r < row_size; r++) {
        for (c = 0; c < col_size; c++) {
            if (r == row_size - 1) {
                g_board[r][c] = SPACE_DEACTIVE;
            } else {
                g_board[r][c] = g_board[r + 1][c];
            }
        }
    }

    return TRUE;
}

int remove_column(const color_t color, const size_t col)
{
    size_t r;
    size_t c;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (col_size <= BOARD_MIN_SIZE || col >= col_size) {
        return FALSE;
    }

    if (use_score(color, 3) == FALSE) {
        return FALSE;
    }
    
    for (c = col; c < col_size; c++) {
        for (r = 0; r < row_size; r++) {
            if (c == col_size - 1) {
                g_board[r][c] = SPACE_DEACTIVE;
            } else {
                g_board[r][c] = g_board[r][c + 1];
            }
        }
    }

    return TRUE;
}

int swap_rows(const color_t color, const size_t row_a0, size_t const row_b1)
{
    space_t temp_row0_value;
    size_t col;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (row_a0 > row_size - 1 || row_b1 > row_size - 1) {
        return FALSE;
    }

    if (use_score(color, 2) == FALSE) {
        return FALSE;
    }

    for (col = 0; col < col_size; col++) {
        temp_row0_value = g_board[row_a0][col];
        g_board[row_a0][col] = g_board[row_b1][col];
        g_board[row_b1][col] = temp_row0_value;
    }

    return TRUE;
}

int swap_columns(const color_t color, const size_t col_a0, const size_t col_b1)
{
    space_t temp_col0_value;
    size_t row;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (col_a0 > col_size - 1 || col_b1 > col_size - 1) {
        return FALSE;
    }

    if (use_score(color, 2) == FALSE) {
        return FALSE;
    }

    for (row = 0; row < row_size; row++) {
        temp_col0_value = g_board[row][col_a0];
        g_board[row][col_a0] = g_board[row][col_b1];
        g_board[row][col_b1] = temp_col0_value;
    }

    return TRUE;
}

int copy_row(const color_t color, const size_t src, const size_t dest)
{
    size_t col;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (src == dest || src > row_size - 1 || dest > row_size - 1) {
        return FALSE;
    }

    if (use_score(color, 4) == FALSE) {
        return FALSE;
    }

    for (col = 0; col < col_size; col++) {
        g_board[dest][col] = g_board[src][col];
    }

    return TRUE;
}

int copy_column(const color_t color, const size_t src, const size_t dest)
{
    size_t row;
    size_t row_size = get_row_count();
    size_t col_size = get_column_count();

    if (src == dest || src > col_size - 1 || dest > col_size - 1) {
        return FALSE;
    }

    if (use_score(color, 4) == FALSE) {
        return FALSE;
    }

    for (row = 0; row < row_size; row++) {
        g_board[row][dest] = g_board[row][src];
    }

    return TRUE;
}

void reset_board(const size_t active_row_size, const size_t active_col_size)
{
    size_t row;
    size_t col;

    for (row = 0; row < BOARD_MAX_SIZE; row++) {
        for (col = 0; col < BOARD_MAX_SIZE; col++) {
            if (row < active_row_size && col < active_col_size) {
                g_board[row][col] = SPACE_ACTIVE;
            } else {
                g_board[row][col] = SPACE_DEACTIVE;
            }
        }
    }
}

int use_score(const color_t color, const size_t score)
{
    switch (color) {
    case COLOR_BLACK:
        if (g_black_score >= score) {
            g_black_score -= score;
        } else {
            return FALSE;
        }
        break;
    case COLOR_WHITE:
        if (g_white_score >= score) {
            g_white_score -= score;
        } else {
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

void get_score_from_connection(const color_t color, const size_t connetion_count)
{
    const size_t SCORE_BASELINE = 4;

    if (connetion_count > SCORE_BASELINE) {
        if (color == COLOR_BLACK) {
            g_black_score += connetion_count - SCORE_BASELINE;
        } else if (color == COLOR_WHITE) {
            g_white_score += connetion_count - SCORE_BASELINE;
        }
    }
}
