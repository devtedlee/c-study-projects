#ifndef CYBER_SPACESHIP_H
#define CYBER_SPACESHIP_H

const char* get_longest_safe_zone_or_null(const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_length);

int get_travel_time(const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count);

#endif /* CYBER_SPACESHIP */
