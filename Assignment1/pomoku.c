#include <stdio.h>
#include "pomoku.h"
 
static int s_board[20][20];
static size_t s_board_row;
static size_t s_board_col;
 
static int s_score_black;
static int s_score_white;
 
void init_game(void)
{
    int* field;
    for (field = s_board[0]; field <= &s_board[19][19];) {
        *field++ = -1;
    }
    s_board_row = 15;
    s_board_col = 15;
    s_score_black = 0;
    s_score_white = 0;
 
    return;
}
 
size_t get_row_count(void)
{
    return s_board_row;
}
 
size_t get_column_count(void)
{
    return s_board_col;
}
 
int get_score(const color_t color)
{
    switch (color) {
    case COLOR_BLACK:
        return s_score_black;
    case COLOR_WHITE:
        return s_score_white;
    default:
        return -1;
    }
}
 
int get_color(const size_t row, const size_t col)
{
    return s_board[row][col];
}
 
int is_placeable(const size_t row, const size_t col)
{
    if (row >= s_board_row) {
        return FALSE;
    }
    if (col >= s_board_col) {
        return FALSE;
    }
    if (s_board[row][col] == -1) {
        return TRUE;
    } else {
        return FALSE;
    }
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
    
    s_board[row][col] = color;
    
    for (; i<x_length; i++){
        x = col + dx[i];
        y = row - dy[i];
        if (check_range(x, y) == TRUE) {
            if (s_board[y][x] == color) {
                recur_dx = x - col;
                recur_dy = y - row;
                stone_number = 1;
				
                while (TRUE) {
 
                    if (x < 0 || x >= (int)s_board_col || y < 0 || y >= (int)s_board_row) {
                        break;
                    }
                    
                    if (s_board[y][x] != color) {
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
            if (s_board[y][x] == color) {
                recur_dx = x - col;
                recur_dy = y - row;
                if (stone_number == 0) {
                    stone_number = 1;
                }
 
                while (TRUE) {
 
                    if (x < 0 || x >= (int)s_board_col || y < 0 || y >= (int)s_board_row) {
                        break;
                    }
                   
                    if (s_board[y][x] != color) {
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
            s_score_black += increase_score;
        }
        else {
            s_score_white += increase_score;
        }
 
        stone_number = 0;
        increase_score = 0;
    }
    
    return TRUE;
}
 
/* special moves */
int insert_row(const color_t color, const size_t row)
{
    int* field;
    int i;
    int j;
    if (s_board_row >= 20) {
        return FALSE;
    }
    if (row > s_board_row) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 3) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 3) {
        return FALSE;
    }
    for (i = s_board_row - 1; i >= (int)row; --i) {
        field = s_board[i];
        for (j = 0; j < 20; ++j) {
            *(field + j + 20) = *(field + j);
        }
    }
    /* 현재 보드판의 끝에 새로 추가할 경우, 위의 복사 반복문이 진행되지 않으므로, field를 for문 마지막 형태로 직적 대입. */
    for (field = s_board[row]; field <= &s_board[row][19];) {
        *field++ = -1;
    }
    ++s_board_row;
    if (color == COLOR_BLACK) {
        s_score_black -= 3;
    } else {
        s_score_white -= 3;
    }
    return TRUE;
}
 
int insert_column(const color_t color, const size_t col)
{
    int* field;
    int i;
    int j;
    if (s_board_col >= 20) {
        return FALSE;
    }
    if (col > s_board_col) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 3) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 3) {
        return FALSE;
    }
    for (i = 0; i < 20; ++i) {
        field = s_board[i];
        for (j = s_board_col - 1; j >= (int)col; --j) {
            *(field + j + 1) = *(field + j);
        }
    }
    /* 현재 보드판의 끝에 새로 추가할 경우, 위의 복사 반복문이 진행되지 않으므로, field를 for문 마지막 형태로 직적 대입. */
    for (field = s_board[19] + col; field >= &s_board[0][col]; field -= 20) {
        *field = -1;
    }
    ++s_board_col;
    if (color == COLOR_BLACK) {
        s_score_black -= 3;
    } else {
        s_score_white -= 3;
    }
    return TRUE;
}
 
int remove_row(const color_t color, const size_t row)
{
    int* field;
    size_t i;
    size_t j;
    if (s_board_row <= 10) {
        return FALSE;
    }
    if (row >= s_board_row) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 3) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 3) {
        return FALSE;
    }
    for (i = row; i < 19; ++i) {
        field = s_board[i];
        for (j = 0; j < 20; ++j) {
            *(field + j) = *(field + j + 20);
        }
    }
    for (field = s_board[19]; field <= &s_board[19][19];) {
        *field++ = -1;
    }
    --s_board_row;
    if (color == COLOR_BLACK) {
        s_score_black -= 3;
    } else {
        s_score_white -= 3;
    }
    return TRUE;
}
 
int remove_column(const color_t color, const size_t col)
{
    int* field;
    size_t i;
    size_t j;
    if (s_board_col <= 10) {
        return FALSE;
    }
    if (col >= s_board_col) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 3) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 3) {
        return FALSE;
    }
    for (i = 0; i < 20; ++i) {
        field = s_board[i];
        for (j = col; j < 19; ++j) {
            *(field + j) = *(field + j + 1);
        }
    }
    for (field += 19; field <= &s_board[0][19]; field -= 20) {
        *field = -1;
    }
    --s_board_col;
    if (color == COLOR_BLACK) {
        s_score_black -= 3;
    } else {
        s_score_white -= 3;
    }
    return TRUE;
}
 
int swap_rows(const color_t color, const size_t row0, const size_t row1)
{
    size_t i;
    int temp;
    if (row0 >= s_board_row) {
        return FALSE;
    }
    if (row1 >= s_board_row) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 2) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 2) {
        return FALSE;
    }
    for (i = 0; i < 20; ++i) {
        temp = s_board[row0][i];
        s_board[row0][i] = s_board[row1][i];
        s_board[row1][i] = temp;
    }
    if (color == COLOR_BLACK) {
        s_score_black -= 2;
    } else {
        s_score_white -= 2;
    }
    return TRUE;
}
 
int swap_columns(const color_t color, const size_t col0, const size_t col1)
{
    int* field0;
    int* field1;
    size_t i;
    int temp[20];
    if (col0 >= s_board_col) {
        return FALSE;
    }
    if (col1 >= s_board_col) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 2) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 2) {
        return FALSE;
    }
    field0 = &s_board[0][col0];
    for (i = 0; i < 20; ++i) {
        *(temp + i) = *(field0 + i * 20);
    }
    field1 = &s_board[0][col1];
    for (i = 0; i < 20; ++i) {
        *(field0 + i * 20) = *(field1 + i * 20);
    }
    for (i = 0; i < 20; ++i) {
        *(field1 + i * 20) = *(temp + i);
    }
    if (color == COLOR_BLACK) {
        s_score_black -= 2;
    } else {
        s_score_white -= 2;
    }
    return TRUE;
}
 
int copy_row(const color_t color, const size_t src, const size_t dst)
{
    size_t i;
    if (src >= s_board_row) {
        return FALSE;
    }
    if (dst >= s_board_row) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 4) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 4) {
        return FALSE;
    }
    for (i = 0; i < 20; ++i) {
        s_board[dst][i] = s_board[src][i];
    }
    if (color == COLOR_BLACK) {
        s_score_black -= 4;
    } else {
        s_score_white -= 4;
    }
    return TRUE;
}
 
int copy_column(const color_t color, const size_t src, const size_t dst)
{
    int* field_src;
    int* field_dst;
    size_t i;
    if (src >= s_board_col) {
        return FALSE;
    }
    if (dst >= s_board_col) {
        return FALSE;
    }
    if (color == COLOR_BLACK && s_score_black < 4) {
        return FALSE;
    }
    if (color == COLOR_WHITE && s_score_white < 4) {
        return FALSE;
    }
    field_src = &s_board[0][src];
    field_dst = &s_board[0][dst];
    for (i = 0; i < 20; ++i) {
        *(field_dst + i * 20) = *(field_src + i * 20);
    }
    if (color == COLOR_BLACK) {
        s_score_black -= 4;
    } else {
        s_score_white -= 4;
    }
    return TRUE;
}
 
/* custom function */
void add_score(const color_t color, const size_t row, const size_t col)
{
    size_t score_add = 0;
    size_t count;
    size_t i;
    size_t is_break0;
    size_t is_break1;
    int now_row;
    int now_col;
 
    /* 세로줄 확인 */
    count = 1;
    is_break0 = FALSE;
    is_break1 = FALSE;
    for (i = 1; i < 20; ++i) {
        if (is_break0 == FALSE) {
            now_row = row - i;
            if (now_row >= 0) {
                if (s_board[now_row][col] == color) {
                    ++count;
                } else {
                    is_break0 = TRUE;
                }
            } else {
                is_break0 = TRUE;
            }
        }
        if (is_break1 == FALSE) {
            now_row = row + i;
            if (now_row < 20) {
                if (s_board[now_row][col] == color) {
                    ++count;
                } else {
                    is_break1 = TRUE;
                }
            } else {
                is_break1 = TRUE;
            }
        }
        if (is_break0 == TRUE && is_break1 == TRUE) {
            break;
        }
    }
    if (count >= 5) {
        score_add += (count - 4);
    }
 
    /* 가로줄 확인 */
    count = 1;
    is_break0 = FALSE;
    is_break1 = FALSE;
    for (i = 1; i < 20; ++i) {
        if (is_break0 == FALSE) {
            now_col = col - i;
            if (now_col >= 0) {
                if (s_board[row][now_col] == color) {
                    ++count;
                } else {
                    is_break0 = TRUE;
                }
            } else {
                is_break0 = TRUE;
            }
        }
        if (is_break1 == FALSE) {
            now_col = col + i;
            if (now_col < 20) {
                if (s_board[row][now_col] == color) {
                    ++count;
                } else {
                    is_break1 = TRUE;
                }
            } else {
                is_break1 = TRUE;
            }
        }
        if (is_break0 == TRUE && is_break1 == TRUE) {
            break;
        }
    }
    if (count >= 5) {
        score_add += (count - 4);
    }
 
    /* 대각선 11시 to 5시 방향 확인 */
    count = 1;
    is_break0 = FALSE;
    is_break1 = FALSE;
    for (i = 1; i < 20; ++i) {
        if (is_break0 == FALSE) {
            now_row = row - i;
            now_col = col - i;
            if (now_row >= 0 && now_col >= 0) {
                if (s_board[now_row][now_col] == color) {
                    ++count;
                } else {
                    is_break0 = TRUE;
                }
            } else {
                is_break0 = TRUE;
            }
        }
        if (is_break1 == FALSE) {
            now_row = row + i;
            now_col = col + i;
            if (now_row < 20 && now_col < 20) {
                if (s_board[now_row][now_col] == color) {
                    ++count;
                } else {
                    is_break1 = TRUE;
                }
            } else {
                is_break1 = TRUE;
            }
        }
        if (is_break0 == TRUE && is_break1 == TRUE) {
            break;
        }
    }
    if (count >= 5) {
        score_add += (count - 4);
    }
 
    /* 대각선 1시 to 7시 방향 확인 */
    count = 1;
    is_break0 = FALSE;
    is_break1 = FALSE;
    for (i = 1; i < 20; ++i) {
        if (is_break0 == FALSE) {
            now_row = row - i;
            now_col = col + i;
            if (now_row >= 0 && now_col < 20) {
                if (s_board[now_row][now_col] == color) {
                    ++count;
                } else {
                    is_break0 = TRUE;
                }
            } else {
                is_break0 = TRUE;
            }
        }
        if (is_break1 == FALSE) {
            now_row = row + i;
            now_col = col - i;
            if (now_row < 20 && now_col >= 0) {
                if (s_board[now_row][now_col] == color) {
                    ++count;
                } else {
                    is_break1 = TRUE;
                }
            } else {
                is_break1 = TRUE;
            }
        }
        if (is_break0 == TRUE && is_break1 == TRUE) {
            break;
        }
    }
    if (count >= 5) {
        score_add += (count - 4);
    }
 
    if (color == COLOR_BLACK) {
        s_score_black += score_add;
    } else {
        s_score_white += score_add;
    }
 
    return;
}
 
void print_board(void)
{
    size_t i;
    size_t j;
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Now board ~ rows: %d, cols: %d\n", s_board_row, s_board_col);
    printf("Now score ~ Black: %d, White: %d\n", s_score_black, s_score_white);
    printf("    ");
    for (i = 0; i < 20; ++i) {
        printf("%3d ", i);
        if (i == s_board_col - 1) {
            printf(" | ");
        }
    }
    printf("row\n");
    for (i = 0; i < 20; ++i) {
        printf("%3d ", i);
        for (j = 0; j < 20; ++j) {
            printf("[%2d]", s_board[i][j]);
            if (j == s_board_col - 1) {
                printf(" | ");
            }
        }
        printf("\n");
        if (i == s_board_row - 1) {
            printf("----");
            for (j = 0; j < 20; ++j) {
                printf("----");
                if (j == s_board_col - 1) {
                    printf("-+-");
                }
            }
            printf("\n");
        }
    }
    printf("col\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
 
    return;
}
