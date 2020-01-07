#include <stdio.h>
#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_length)
{
    size_t i;
    const char* temp_address;
    const char* start_address = cluster_start_locations[0];
    const char* end_address = cluster_start_locations[0] + cluster_lengths[0] - 1;
    size_t layer = 0;
    const char* longest_cluster_start_address;
    const char* temp_safe_start_address;
    size_t temp_safe_length = 0;
    size_t longest_length = 0;

    for (i = 0; i < cluster_count; i++) {
        if (start_address > cluster_start_locations[i]) {
            start_address = cluster_start_locations[i];
        }

        if (end_address < cluster_start_locations[i] + cluster_lengths[i] - 1) {
            end_address = cluster_start_locations[i] + cluster_lengths[i] - 1;
        }
    }

    for (temp_address = start_address; temp_address < end_address + 1; temp_address++) {
        for (i = 0; i < cluster_count; i++) {
            if (temp_address >= cluster_start_locations[i] && temp_address <= cluster_start_locations[i] + cluster_lengths[i] - 1) {
                layer++;
            }
        }

        if (layer % 2 != 0) {
            if (temp_safe_length == 0) {
                temp_safe_start_address = temp_address;
            }
            temp_safe_length++;
        } else {
            temp_safe_length = 0;
        }

        if (temp_safe_length >= longest_length) {
            longest_length = temp_safe_length;
            longest_cluster_start_address = temp_safe_start_address;
        }

        layer = 0;
    }

    *out_longest_length = longest_length;

    return longest_cluster_start_address;
}

int get_travel_time(const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    size_t i;
    const char* temp_address;
    const char* start_address = cluster_start_locations[0];
    const char* end_address = cluster_start_locations[0] + cluster_lengths[0] - 1;
    size_t layer = 0;
    size_t safe_zone_count = 0;
    size_t danger_zone_count = 0;
    double travel_time;

    for (i = 0; i < cluster_count; i++) {
        if (start_address > cluster_start_locations[i]) {
            start_address = cluster_start_locations[i];
        }

        if (end_address < cluster_start_locations[i] + cluster_lengths[i] - 1) {
            end_address = cluster_start_locations[i] + cluster_lengths[i] - 1;
        }
    }

    for (temp_address = start_address; temp_address < end_address + 1; temp_address++) {
        for (i = 0; i < cluster_count; i++) {
            if (temp_address >= cluster_start_locations[i] && temp_address <= cluster_start_locations[i] + cluster_lengths[i] - 1) {
                layer++;
            }
        }

        if (layer % 2 != 0) {
            safe_zone_count++;
        } else {
            danger_zone_count++;
        }

        layer = 0;
    }

    travel_time = (double)(safe_zone_count * 6 + danger_zone_count * 12) / 60;

    return (int)(travel_time + 0.5);
}
