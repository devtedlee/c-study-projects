/*
모든 테스트 케이스 통과 시 실제 포목 게임을 체험할 수 있습니다.
단, 본인 코드에 문제가 있을 시 게임에서 버그나 툴다운이 발생할 수 있습니다.
pomoku.h에서 #include <windows.h> 추가 후
#define TRUE (1)
#define FALSE (0)
부분 주석처리 해야 컴파일 됩니다.
빌드봇 채점 시 pomoku.h는 원상복귀 시키고
main.c는 게임 구현 관련 코드를 주석처리 하거나
기존에 쓰던 main.c를 써주세요.
*/
#include <assert.h>

#include <stdio.h>
#include <conio.h>
#include <string.h>

#include "pomoku.h"

typedef enum DIRECTION { DIRECTION_EAST, DIRECTION_WEST, DIRECTION_SOUTH, DIRECTION_NORTH } direction_t;

void test_init_game(void);
void test_horizontal_chain(void);
void test_combined_chains(void);
void test_swap_row(void);
void test_insert_row(void);
void test_remove_row(void);
void test_copy_row(void);
void test_copy_col(void);
void test_place_stone_combined(void);
void test_place_stone_combined2(void);

void game_start(void);
void goto_xy(const size_t x, const size_t y);
void goto_row_col(const size_t row, const size_t col);
void draw_board(void);
void draw_stone(const color_t color);
void update_state(const color_t color, const size_t x, const size_t y);

void init_game_and_test(void);
void score_test(void);

int main(void)
{
    test_init_game();

    assert(is_placeable(0, 0) == TRUE);
    assert(is_placeable(14, 14) == TRUE);
    assert(is_placeable(15, 15) == FALSE);

    assert(place_stone(COLOR_BLACK, 0, 0) == TRUE);
    assert(is_placeable(0, 0) == FALSE);
    assert(get_color(0, 0) == 0);
    assert(place_stone(COLOR_WHITE, 0, 0) == FALSE);
    assert(place_stone(COLOR_BLACK, 0, 0) == FALSE);

    test_horizontal_chain();
    test_combined_chains();

    test_swap_row();
    test_insert_row();
    test_remove_row();
    test_copy_row();
    test_copy_col();

    score_test();

    test_place_stone_combined();
    test_place_stone_combined2();

    return 0;
}

void test_init_game(void)
{
    init_game();

    assert(get_row_count() == 15);
    assert(get_column_count() == 15);
    assert(get_score(5) == -1);
    assert(get_score(COLOR_BLACK) == 0);
    assert(get_score(COLOR_WHITE) == 0);
}

void test_horizontal_chain(void)
{
    test_init_game();

    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);

    assert(get_score(COLOR_BLACK) == 1);

    place_stone(COLOR_BLACK, 0, 5);
    assert(get_score(COLOR_BLACK) == 3);

    place_stone(COLOR_BLACK, 0, 7);
    assert(get_score(COLOR_BLACK) == 3);

    place_stone(COLOR_BLACK, 0, 6);
    assert(get_score(COLOR_BLACK) == 7);

    assert(get_score(COLOR_WHITE) == 0);
}

void test_combined_chains(void)
{
    test_init_game();

    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 4);
    place_stone(COLOR_BLACK, 0, 5);

    place_stone(COLOR_BLACK, 1, 3);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 3);

    assert(get_score(COLOR_BLACK) == 0);

    place_stone(COLOR_BLACK, 0, 3);

    assert(get_score(COLOR_BLACK) == 3);
}

void test_swap_row(void)
{
    size_t i;

    test_init_game();

    for (i = 0; i < 6; i++) {
        place_stone(COLOR_BLACK, 0, i);
    }

    assert(get_score(COLOR_BLACK) == 3);

    assert(swap_rows(COLOR_BLACK, 0, 4) == TRUE);
    assert(get_score(COLOR_BLACK) == 1);

    for (i = 0; i < 6; i++) {
        assert(is_placeable(0, i) == TRUE);
        assert(is_placeable(4, i) == FALSE);
    }
}

void test_insert_row(void)
{
    size_t i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);

    assert(get_score(COLOR_BLACK) == 3);

    assert(insert_row(COLOR_BLACK, 2) == TRUE);
    assert(get_score(COLOR_BLACK) == 0);
    assert(insert_row(COLOR_BLACK, 2) == FALSE);
    assert(get_row_count() == 16);

    for (i = 0; i < 6; i++) {
        assert(is_placeable(2, i) == TRUE);
        assert(get_color(3, i) == COLOR_BLACK);
        assert(is_placeable(3, i) == FALSE);
    }

    place_stone(COLOR_WHITE, 4, 0);
    place_stone(COLOR_WHITE, 4, 1);
    place_stone(COLOR_WHITE, 4, 2);
    place_stone(COLOR_WHITE, 4, 3);
    place_stone(COLOR_WHITE, 4, 4);
    place_stone(COLOR_WHITE, 4, 5);

    assert(get_score(COLOR_WHITE) == 3);

    assert(insert_row(COLOR_WHITE, 4) == TRUE);
    assert(get_score(COLOR_WHITE) == 0);
    assert(insert_row(COLOR_WHITE, 4) == FALSE);
    assert(get_row_count() == 17);

    for (i = 0; i < 6; i++) {
        assert(is_placeable(4, i) == TRUE);
        assert(get_color(5, i) == COLOR_WHITE);
        assert(is_placeable(5, i) == FALSE);
    }

    place_stone(COLOR_WHITE, 16, 0);
    place_stone(COLOR_WHITE, 16, 1);
    place_stone(COLOR_WHITE, 16, 2);
    place_stone(COLOR_WHITE, 16, 3);
    place_stone(COLOR_WHITE, 16, 4);
    place_stone(COLOR_WHITE, 16, 5);

    assert(get_score(COLOR_WHITE) == 3);

    assert(insert_row(COLOR_WHITE, 17) == TRUE);
    assert(get_score(COLOR_WHITE) == 0);
    assert(insert_row(COLOR_WHITE, 17) == FALSE);
    assert(get_row_count() == 18);

    for (i = 0; i < 6; i++) {
        assert(is_placeable(16, i) == FALSE);
        assert(get_color(16, i) == COLOR_WHITE);
        assert(is_placeable(17, i) == TRUE);
    }

    place_stone(COLOR_WHITE, 17, 0);
    place_stone(COLOR_WHITE, 17, 1);
    place_stone(COLOR_WHITE, 17, 2);
    place_stone(COLOR_WHITE, 17, 3);
    place_stone(COLOR_WHITE, 17, 4);
    place_stone(COLOR_WHITE, 17, 5);

    assert(get_score(COLOR_WHITE) == 3);

    assert(insert_row(COLOR_WHITE, 18) == TRUE);
    assert(get_score(COLOR_WHITE) == 0);
    assert(insert_row(COLOR_WHITE, 18) == FALSE);
    assert(get_row_count() == 19);

    for (i = 0; i < 6; i++) {
        assert(is_placeable(17, i) == FALSE);
        assert(get_color(17, i) == COLOR_WHITE);
        assert(is_placeable(18, i) == TRUE);
    }

    place_stone(COLOR_WHITE, 18, 0);
    place_stone(COLOR_WHITE, 18, 1);
    place_stone(COLOR_WHITE, 18, 2);
    place_stone(COLOR_WHITE, 18, 3);
    place_stone(COLOR_WHITE, 18, 4);
    place_stone(COLOR_WHITE, 18, 5);

    assert(get_score(COLOR_WHITE) == 3);

    assert(insert_row(COLOR_WHITE, 19) == TRUE);
    assert(get_score(COLOR_WHITE) == 0);
    assert(insert_row(COLOR_WHITE, 19) == FALSE);
    assert(get_row_count() == 20);

    for (i = 0; i < 6; i++) {
        assert(is_placeable(18, i) == FALSE);
        assert(get_color(18, i) == COLOR_WHITE);
        assert(is_placeable(19, i) == TRUE);
    }

    place_stone(COLOR_WHITE, 19, 0);
    place_stone(COLOR_WHITE, 19, 1);
    place_stone(COLOR_WHITE, 19, 2);
    place_stone(COLOR_WHITE, 19, 3);
    place_stone(COLOR_WHITE, 19, 4);
    place_stone(COLOR_WHITE, 19, 5);

    assert(get_score(COLOR_WHITE) == 3);

    assert(insert_row(COLOR_WHITE, 20) == FALSE);
    assert(get_score(COLOR_WHITE) == 3);
    assert(get_row_count() == 20);

}

void test_remove_row(void)
{
    size_t i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);

    assert(get_score(COLOR_BLACK) == 3);
    assert(remove_row(COLOR_BLACK, 2) == TRUE);
    assert(get_score(COLOR_BLACK) == 0);

    for (i = 0; i < get_column_count(); i++) {
        assert(is_placeable(2, i) == TRUE);
    }
}

void test_copy_row(void)
{
    size_t i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);
    place_stone(COLOR_BLACK, 2, 6);

    place_stone(COLOR_WHITE, 2, 7);
    place_stone(COLOR_WHITE, 2, 8);

    assert(get_score(COLOR_BLACK) == 6);
    assert(copy_row(COLOR_BLACK, 2, 4) == TRUE);
    assert(get_score(COLOR_BLACK) == 2);

    for (i = 0; i < get_column_count(); i++) {
        assert(get_color(4, i) == get_color(2, i));
    }
}

void test_copy_col(void)
{
    size_t i;

    test_init_game();

    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 1, 0);
    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 3, 0);
    place_stone(COLOR_BLACK, 4, 0);
    place_stone(COLOR_BLACK, 5, 0);
    place_stone(COLOR_BLACK, 6, 0);

    place_stone(COLOR_WHITE, 7, 0);
    place_stone(COLOR_WHITE, 8, 0);

    assert(get_score(COLOR_BLACK) == 6);
    assert(copy_column(COLOR_BLACK, 0, 4) == TRUE);
    assert(get_score(COLOR_BLACK) == 2);

    for (i = 0; i < get_row_count(); i++) {
        assert(get_color(i, 4) == get_color(i, 0));
    }
}

void init_game_and_test(void)
{
    init_game();
 
    assert(15 == get_row_count());
    assert(15 == get_column_count());
 
    assert(0 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
}
 
void score_test(void)
{
    /* hori */
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 5);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 6);
 
    assert(6 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 1, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 4);
 
    assert(7 == get_score(COLOR_BLACK));
 
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 14);
    place_stone(COLOR_BLACK, 0, 13);
    place_stone(COLOR_BLACK, 0, 12);
    place_stone(COLOR_BLACK, 0, 11);
    place_stone(COLOR_BLACK, 0, 10);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 9);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 8);
 
    assert(6 == get_score(COLOR_BLACK));
 
    /* verti */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 0);
    place_stone(COLOR_WHITE, 2, 0);
    place_stone(COLOR_WHITE, 3, 0);
    place_stone(COLOR_WHITE, 4, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 0);
    place_stone(COLOR_WHITE, 12, 0);
    place_stone(COLOR_WHITE, 11, 0);
    place_stone(COLOR_WHITE, 10, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* left-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 1);
    place_stone(COLOR_WHITE, 2, 2);
    place_stone(COLOR_WHITE, 3, 3);
    place_stone(COLOR_WHITE, 4, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 14);
    place_stone(COLOR_WHITE, 13, 13);
    place_stone(COLOR_WHITE, 12, 12);
    place_stone(COLOR_WHITE, 11, 11);
    place_stone(COLOR_WHITE, 10, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 9);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 8);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* right-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 1);
    place_stone(COLOR_WHITE, 12, 2);
    place_stone(COLOR_WHITE, 11, 3);
    place_stone(COLOR_WHITE, 10, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 14);
    place_stone(COLOR_WHITE, 1, 13);
    place_stone(COLOR_WHITE, 2, 12);
    place_stone(COLOR_WHITE, 3, 11);
    place_stone(COLOR_WHITE, 4, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 9);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 8);
 
    assert(6 == get_score(COLOR_WHITE));


    /* C08_ChainsInMultipleDirections */
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 1, 0);
    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 3, 0);
    place_stone(COLOR_BLACK, 4, 0);
    place_stone(COLOR_BLACK, 5, 0);
 
    assert(3 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_BLACK, 5, 1);
    place_stone(COLOR_BLACK, 5, 2);
    place_stone(COLOR_BLACK, 5, 3);
    place_stone(COLOR_BLACK, 5, 4);
    place_stone(COLOR_BLACK, 5, 5);
    place_stone(COLOR_BLACK, 5, 6);
 
    assert(9 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_BLACK, 6, 7);
    place_stone(COLOR_BLACK, 7, 8);
    place_stone(COLOR_BLACK, 8, 9);
    place_stone(COLOR_BLACK, 9, 10);
    place_stone(COLOR_BLACK, 10, 11);
 
    assert(12 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
 
    assert(FALSE == place_stone(COLOR_BLACK, 0, 15));
    assert(FALSE == place_stone(COLOR_BLACK, 15, 0));
    assert(FALSE == place_stone(COLOR_BLACK, 15, 15));
    assert(FALSE == place_stone(COLOR_WHITE, 0, 15));
    assert(FALSE == place_stone(COLOR_WHITE, 15, 0));
    assert(FALSE == place_stone(COLOR_WHITE, 15, 15));
 
    place_stone(COLOR_BLACK, 11, 11);
    place_stone(COLOR_BLACK, 12, 11);
    place_stone(COLOR_BLACK, 13, 11);
    place_stone(COLOR_BLACK, 14, 11);
 
    assert(13 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_BLACK, 14, 10);
    place_stone(COLOR_BLACK, 14, 12);
    place_stone(COLOR_BLACK, 14, 13);
    place_stone(COLOR_BLACK, 14, 14);
 
    assert(14 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
 
    init_game_and_test();
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 0);
    place_stone(COLOR_WHITE, 2, 0);
    place_stone(COLOR_WHITE, 3, 0);
    place_stone(COLOR_WHITE, 4, 0); /* 1 */
    place_stone(COLOR_WHITE, 5, 0); /* 2 */
    place_stone(COLOR_WHITE, 6, 0); /* 3 */
    place_stone(COLOR_WHITE, 7, 0);
    place_stone(COLOR_WHITE, 8, 0);
    place_stone(COLOR_WHITE, 9, 0);
    place_stone(COLOR_WHITE, 10, 0);
    place_stone(COLOR_WHITE, 11, 0);
    place_stone(COLOR_WHITE, 12, 0);
    place_stone(COLOR_WHITE, 13, 0);
    place_stone(COLOR_WHITE, 14, 0);
 
    assert(66 == get_score(COLOR_WHITE));
    assert(0 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_WHITE, 5, 0);
    place_stone(COLOR_WHITE, 5, 1);
    place_stone(COLOR_WHITE, 5, 2);
    place_stone(COLOR_WHITE, 5, 3);
    place_stone(COLOR_WHITE, 5, 4);
    place_stone(COLOR_WHITE, 5, 5);
    place_stone(COLOR_WHITE, 5, 6);
    place_stone(COLOR_WHITE, 5, 7);
    place_stone(COLOR_WHITE, 5, 8);
    place_stone(COLOR_WHITE, 5, 9);
    place_stone(COLOR_WHITE, 5, 10);
    place_stone(COLOR_WHITE, 5, 11);
    place_stone(COLOR_WHITE, 5, 12);
    place_stone(COLOR_WHITE, 5, 13);
    place_stone(COLOR_WHITE, 5, 14);
 
    assert(132 == get_score(COLOR_WHITE));
    assert(0 == get_score(COLOR_BLACK));
}

void test_place_stone_combined(void)
{
    unsigned int i;
    unsigned int j;
    const unsigned int MAX = 100u;
    int score = 0;

    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
        if (i >= 4) {
            score += i - 3;
        }
    }
    assert(get_score(COLOR_BLACK) == score);
    assert(insert_row(COLOR_BLACK, 21) == FALSE);
    assert(insert_row(COLOR_BLACK, 20) == FALSE);
    assert(insert_row(COLOR_BLACK, 19) == FALSE);
    assert(insert_row(COLOR_BLACK, 18) == FALSE);
    assert(insert_row(COLOR_BLACK, 17) == FALSE);
    assert(insert_row(COLOR_BLACK, 16) == FALSE);
    assert(insert_row(COLOR_BLACK, 15) == TRUE);
    assert(insert_row(COLOR_BLACK, 16) == TRUE);
    assert(insert_row(COLOR_BLACK, 17) == TRUE);
    assert(insert_row(COLOR_BLACK, 18) == TRUE);
    assert(insert_row(COLOR_BLACK, 19) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(insert_row(COLOR_BLACK, i) == FALSE);
    }
    assert(get_score(COLOR_BLACK) == score - 3 * 5);
    for (i = 1; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 1 && i < 20 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(insert_column(COLOR_WHITE, 21) == FALSE);
    assert(insert_column(COLOR_WHITE, 20) == FALSE);
    assert(insert_column(COLOR_WHITE, 19) == FALSE);
    assert(insert_column(COLOR_WHITE, 18) == FALSE);
    assert(insert_column(COLOR_WHITE, 17) == FALSE);
    assert(insert_column(COLOR_WHITE, 16) == FALSE);
    assert(insert_column(COLOR_WHITE, 15) == TRUE);
    assert(insert_column(COLOR_WHITE, 16) == TRUE);
    assert(insert_column(COLOR_WHITE, 17) == TRUE);
    assert(insert_column(COLOR_WHITE, 18) == TRUE);
    assert(insert_column(COLOR_WHITE, 19) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(insert_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 1; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 1 && j < 20) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
    }
    assert(remove_row(COLOR_BLACK, 21) == FALSE);
    assert(remove_row(COLOR_BLACK, 20) == FALSE);
    assert(remove_row(COLOR_BLACK, 19) == FALSE);
    assert(remove_row(COLOR_BLACK, 18) == FALSE);
    assert(remove_row(COLOR_BLACK, 17) == FALSE);
    assert(remove_row(COLOR_BLACK, 16) == FALSE);
    assert(remove_row(COLOR_BLACK, 15) == FALSE);
    assert(remove_row(COLOR_BLACK, 14) == TRUE);
    assert(remove_row(COLOR_BLACK, 14) == FALSE);
    assert(remove_row(COLOR_BLACK, 13) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 12) == FALSE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == FALSE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_row(COLOR_BLACK, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 10 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }

    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(remove_column(COLOR_WHITE, 21) == FALSE);
    assert(remove_column(COLOR_WHITE, 20) == FALSE);
    assert(remove_column(COLOR_WHITE, 19) == FALSE);
    assert(remove_column(COLOR_WHITE, 18) == FALSE);
    assert(remove_column(COLOR_WHITE, 17) == FALSE);
    assert(remove_column(COLOR_WHITE, 16) == FALSE);
    assert(remove_column(COLOR_WHITE, 15) == FALSE);
    assert(remove_column(COLOR_WHITE, 14) == TRUE);
    assert(remove_column(COLOR_WHITE, 14) == FALSE);
    assert(remove_column(COLOR_WHITE, 13) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 12) == FALSE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == FALSE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 10) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }
}

void test_place_stone_combined2(void)
{
    unsigned int i;
    unsigned int j;
    const unsigned int MAX = 100u;
    int score = 0;
 
    /* Place All Positions */
 
    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 2992);
 
    init_game();
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
            }
        }
    }
    assert(get_score(COLOR_WHITE) == 2992);
 
    init_game();
    assert(place_stone(COLOR_BLACK, -1, 0) == FALSE);
    assert(place_stone(COLOR_BLACK, 0, -1) == FALSE);
    assert(place_stone(COLOR_BLACK, -1, -1) == FALSE);
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (j % 2 == 0) {
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            } else {
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 528);
    assert(get_score(COLOR_WHITE) == 462);
 
        init_game();
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (i % 2 == 0) {
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
            } else {
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            }
        }
    }
    assert(get_score(COLOR_BLACK) == 462);
    assert(get_score(COLOR_WHITE) == 528);
 
    /* Test in Max Length */
 
    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
        if (i >= 4) {
            score += i - 3;
        }
    }
    assert(get_score(COLOR_BLACK) == score);
    assert(insert_row(COLOR_BLACK, 21) == FALSE);
    assert(insert_row(COLOR_BLACK, 20) == FALSE);
    assert(insert_row(COLOR_BLACK, 19) == FALSE);
    assert(insert_row(COLOR_BLACK, 18) == FALSE);
    assert(insert_row(COLOR_BLACK, 17) == FALSE);
    assert(insert_row(COLOR_BLACK, 16) == FALSE);
    assert(insert_row(COLOR_BLACK, 15) == TRUE);
    assert(insert_row(COLOR_BLACK, 16) == TRUE);
    assert(insert_row(COLOR_BLACK, 17) == TRUE);
    assert(insert_row(COLOR_BLACK, 18) == TRUE);
    assert(insert_row(COLOR_BLACK, 19) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(insert_row(COLOR_BLACK, i) == FALSE);
    }
    assert(get_score(COLOR_BLACK) == score - 3 * 5);
    for (i = 1; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 1 && i < 20 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }
 
    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(insert_column(COLOR_WHITE, 21) == FALSE);
    assert(insert_column(COLOR_WHITE, 20) == FALSE);
    assert(insert_column(COLOR_WHITE, 19) == FALSE);
    assert(insert_column(COLOR_WHITE, 18) == FALSE);
    assert(insert_column(COLOR_WHITE, 17) == FALSE);
    assert(insert_column(COLOR_WHITE, 16) == FALSE);
    assert(insert_column(COLOR_WHITE, 15) == TRUE);
    assert(insert_column(COLOR_WHITE, 16) == TRUE);
    assert(insert_column(COLOR_WHITE, 17) == TRUE);
    assert(insert_column(COLOR_WHITE, 18) == TRUE);
    assert(insert_column(COLOR_WHITE, 19) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(insert_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 1; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 1 && j < 20) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }
 
    /* Test in Min Length */
 
    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_BLACK, 0, i) == TRUE);
    }
    assert(remove_row(COLOR_BLACK, 21) == FALSE);
    assert(remove_row(COLOR_BLACK, 20) == FALSE);
    assert(remove_row(COLOR_BLACK, 19) == FALSE);
    assert(remove_row(COLOR_BLACK, 18) == FALSE);
    assert(remove_row(COLOR_BLACK, 17) == FALSE);
    assert(remove_row(COLOR_BLACK, 16) == FALSE);
    assert(remove_row(COLOR_BLACK, 15) == FALSE);
    assert(remove_row(COLOR_BLACK, 14) == TRUE);
    assert(remove_row(COLOR_BLACK, 14) == FALSE);
    assert(remove_row(COLOR_BLACK, 13) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 12) == FALSE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    assert(remove_row(COLOR_BLACK, 0) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_row(COLOR_BLACK, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 10 && j >= 0 && j < 15) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_BLACK, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_BLACK);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_BLACK, i, j) == FALSE);
            }
        }
    }
 
    init_game();
    for (i = 0; i < 15; i++) {
        assert(place_stone(COLOR_WHITE, i, 0) == TRUE);
    }
    assert(remove_column(COLOR_WHITE, 21) == FALSE);
    assert(remove_column(COLOR_WHITE, 20) == FALSE);
    assert(remove_column(COLOR_WHITE, 19) == FALSE);
    assert(remove_column(COLOR_WHITE, 18) == FALSE);
    assert(remove_column(COLOR_WHITE, 17) == FALSE);
    assert(remove_column(COLOR_WHITE, 16) == FALSE);
    assert(remove_column(COLOR_WHITE, 15) == FALSE);
    assert(remove_column(COLOR_WHITE, 14) == TRUE);
    assert(remove_column(COLOR_WHITE, 14) == FALSE);
    assert(remove_column(COLOR_WHITE, 13) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 12) == FALSE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    assert(remove_column(COLOR_WHITE, 0) == TRUE);
    for (i = 0; i <= MAX; i++) {
        assert(remove_column(COLOR_WHITE, i) == FALSE);
    }
    for (i = 0; i <= MAX; i++) {
        for (j = 0; j <= MAX; j++) {
            if (i >= 0 && i < 15 && j >= 0 && j < 10) {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == TRUE);
                assert(place_stone(COLOR_WHITE, i, j) == TRUE);
                assert(get_color(i, j) == COLOR_WHITE);
                assert(is_placeable(i, j) == FALSE);
            } else {
                assert(get_color(i, j) == -1);
                assert(is_placeable(i, j) == FALSE);
                assert(place_stone(COLOR_WHITE, i, j) == FALSE);
            }
        }
    }
}
 
void test_various_score(void)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int cnt = 0;
    unsigned int chain_count;
    direction_t dir = DIRECTION_EAST;
 
    /* Checker */
    init_game();
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        i = cnt / 15;
        j = cnt % 15;
        if (cnt % 2 == 0) {
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        }
    }
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        i = cnt / 15;
        j = cnt % 15;
        if (cnt % 2 == 1) {
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        }
    }
    assert(get_score(COLOR_BLACK) == 2162);
 
    /* Tornado Pattern */
    i = 0;
    j = 0;
    init_game();
    for (cnt = 0; cnt < 15 * 15; cnt++) {
        assert(place_stone(COLOR_BLACK, i, j) == TRUE);
        switch (dir) {
            case DIRECTION_EAST:
                if (is_placeable(i, j + 1) == FALSE) {
                    dir = DIRECTION_SOUTH;
                    i++;
                } else {
                    j++;
                }
                break;
            case DIRECTION_WEST:
                if (is_placeable(i, j - 1) == FALSE) {
                    dir = DIRECTION_NORTH;
                    i--;
                } else {
                    j--;
                }
                break;
            case DIRECTION_SOUTH:
                if (is_placeable(i + 1, j) == FALSE) {
                    dir = DIRECTION_WEST;
                    j--;
                } else {
                    i++;
                }
                break;
            case DIRECTION_NORTH:
                if (is_placeable(i - 1, j) == FALSE) {
                    dir = DIRECTION_EAST;
                    j++;
                } else {
                    i--;
                }
                break;
            default:
                assert(0);
        }
    }
    assert(get_score(COLOR_BLACK) == 1521);
 
    /* Horizontal + Vertical + Diagonals Combined Chains of 5 stones*/
    chain_count = 5;
    for (i = 0; i <= 15 - chain_count; i++) {
        for (j = 0; j <= 15 - chain_count; j++) {
            init_game();
            assert(place_stone(COLOR_BLACK, i+2, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+2) == TRUE);
            assert(get_score(COLOR_BLACK) == 4);
        }
    }
 
    /* Horizontal + Vertical + Diagonals Combained Chains of 9 stones*/
    chain_count = 9;
    for (i = 0; i <= 15 - chain_count; i++) {
        for (j = 0; j <= 15 - chain_count; j++) {
            init_game();
            assert(place_stone(COLOR_BLACK, i+4, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j+4) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i+8, j) == TRUE);
            assert(place_stone(COLOR_BLACK, i+7, j+1) == TRUE);
            assert(place_stone(COLOR_BLACK, i+6, j+2) == TRUE);
            assert(place_stone(COLOR_BLACK, i+5, j+3) == TRUE);
            assert(place_stone(COLOR_BLACK, i+3, j+5) == TRUE);
            assert(place_stone(COLOR_BLACK, i+2, j+6) == TRUE);
            assert(place_stone(COLOR_BLACK, i+1, j+7) == TRUE);
            assert(place_stone(COLOR_BLACK, i, j+8) == TRUE);
            assert(place_stone(COLOR_BLACK, i+4, j+4) == TRUE);
            assert(get_score(COLOR_BLACK) == 20);
        }
    }
}
