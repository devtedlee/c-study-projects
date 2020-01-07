#ifndef POMOKU_H
#define POMOKU_H

#define TRUE (1)
#define FALSE (0)

typedef enum color {
    COLOR_BLACK = 1,
    COLOR_WHITE = 2
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

int swap_rows(const color_t color, const size_t row_a0, size_t const row_b1);

int swap_columns(const color_t color, const size_t col_a0, const size_t col_b1);

int copy_row(const color_t color, const size_t src, const size_t dest);

int copy_column(const color_t color, const size_t src, const size_t dest);

/* custom code */
typedef enum space {
    SPACE_DEACTIVE = -1,
    SPACE_ACTIVE = 0,
    SPACE_BLACK = 1,
    SPACE_WHITE = 2
} space_t;

void reset_board(const size_t active_row_size, const size_t active_col_size);

int use_score(const color_t color, const size_t score);

void get_score_from_connection(const color_t color, const size_t connetion_count);

#endif /* POMOKU_H */
