#ifndef POMOKU_H
#define POMOKU_H
 
#include <stddef.h>
 
#define TRUE (1)
#define FALSE (0)
 
#define MAX_BOARD_SIZE 20
#define MIN_BOARD_SIZE 10
 
typedef enum color {
    COLOR_BLACK,
	COLOR_WHITE,
	COLOR_EMPTY
} color_t;
 
void init_game(void);
 
size_t get_row_count(void);
 
size_t get_column_count(void);
 
int get_score(const color_t color);
 
int get_color(const size_t row, const size_t col);
 
int is_placeable(const size_t row, const size_t col);
 
int place_stone(const color_t color, const size_t row, const size_t col);
 
/* special moves */
int insert_row(const color_t color, const size_t row);
 
int insert_column(const color_t color, const size_t col);
 
int remove_row(const color_t color, const size_t row);
 
int remove_column(const color_t color, const size_t col);
 
int swap_rows(const color_t color, const size_t row0, const size_t row1);
 
int swap_columns(const color_t color, const size_t col0, const size_t col1);
 
int copy_row(const color_t color, const size_t src, const size_t dst);
 
int copy_column(const color_t color, const size_t src, const size_t dst);
 
int check_score(color_t color, int score);
 
void reduce_score(color_t color, int score);
 
int recursive_check_place_stone(color_t color, int row, int col, int dx, int dy, int* stone_number, int* new_score);
 
int check_range(int x, int y);
 
#endif /* POMOKU_H */
