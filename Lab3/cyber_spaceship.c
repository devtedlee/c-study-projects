#include <stdio.h>
#include "cyber_spaceship.h"
#define CAB_LENGTH (100)

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    int check_cab[CAB_LENGTH] = {0, }; /* 배열에 홀짝으로 판단한다. */
    char* max_address_p = NULL;
    char* index_p = NULL;
    int max_length = -1; /* length길이가 이미 0이므로 비교하기 위해선 int로 선언 후 마이너스, size_t */
    int temp = 0;
    int index_temp = 0;
    int i;
    int arr_index = 0;
    *out_longest_safe_area_length = 0; /* 함수를 부를때마다 초기화를 해주자 안전하게 */
    
    if (cab_length == 0) {
        return NULL;
    }
    if (cluster_count == 0) {
        *out_longest_safe_area_length = cab_length;
        return cab_start_location;
    }
    for (i = 0; i < cluster_count; i++) {
        /* const변수를 읽어올때 타입을 이렇게 변환 해주어야 경고가 나지 않는다. */
        for (index_p = (char*)cluster_start_locations[i]; index_p < cluster_start_locations[i] + cluster_lengths[i]; index_p++) {
            arr_index = (int)(index_p - cab_start_location);
            check_cab[arr_index]++;
            /* 클러스터시작위치 - cab시작위치 = 인덱스가 나오고 이것을 배열에 저장한다. */
        }
    }
    for (i = 0; i < cab_length; i++) {
        if (check_cab[i] % 2 == 0) {
            temp++;
        } else if (check_cab[i] % 2 != 0) {
            temp = 0;
        }
        if (max_length <= temp) {
            max_length = temp;
            index_temp = i; /* 최대값의 마지막 인덱스를 찾는다. 이주소에서 길이를 빼면 최대길이의 시작주소가 나온다. */
        }
    }
    /* for문 끝나고 최종적 최대길이를 넣어준다. */
    *out_longest_safe_area_length = (size_t)max_length;
    /* 시작주소+(최대값마지막주소-최대값길이) + 1을 해야지 인덱스 갯수가 정확히 나오기 때문이다. */
    max_address_p = (char*)cab_start_location + (index_temp - max_length + 1); /* const변수를 읽어올때 타입을 이렇게 변환 해주어야 경고가 나지 않는다. */
    if (*out_longest_safe_area_length == 0) {
        max_address_p = NULL;
    }
    
    return max_address_p;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    const char* start_address = cab_start_location;
    const char* end_address = cab_start_location + cab_length - 1;
    const char* temp_start_address;
    size_t layer = 0;
    size_t safe_zone_count = 0;
    size_t danger_zone_count = 0;
    double travel_time;

    for (temp_start_address = start_address; temp_start_address < end_address + 1; ++temp_start_address) {
        size_t i;
        for (i = 0; i < cluster_count; ++i) {
            if (temp_start_address >= cluster_start_locations[i] && temp_start_address <= cluster_start_locations[i] + cluster_lengths[i] - 1) {
                ++layer;
            }
        }

        if (layer % 2 == 0) {
            ++safe_zone_count;
        } else {
            ++danger_zone_count;
        }

        layer = 0;
    }

    travel_time = (double)(safe_zone_count * 6 + danger_zone_count * 12) / 60;

    return (int)(travel_time + 0.5);
}
