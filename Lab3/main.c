#include <assert.h>
#include <stdio.h>
#include "cyber_spaceship.h"

#define CAB_LENGTH (50)

void NoCluster()
{
    char cab[CAB_LENGTH];
    const char* cab_start_address = cab;

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    int time_in_mins;
    
    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, NULL, NULL, 0, out_longest_safe_area_length_p);
    
    assert(out_longest_safe_area_length == 50);
    assert(longest_safe_cluster_start_address == cab_start_address + 0);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, NULL, NULL, 0);
    assert(time_in_mins == 5);
}

void Cluster()
{
    char cab[CAB_LENGTH];
    const char* cab_start_address = cab;

    const char* cluster_start_addresses[1];
    size_t cluster_lengths[1];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    int time_in_mins;

    cluster_start_addresses[0] = &cab[8];

    cluster_lengths[0] = 10U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 1, out_longest_safe_area_length_p);
        
    assert(out_longest_safe_area_length == 32);
    assert(longest_safe_cluster_start_address == cab_start_address + 18);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 1);
    assert(time_in_mins == 6);
}

void ClustersNoOverlap()
{
    char cab[CAB_LENGTH];
    const char* cab_start_address = cab;

    const char* cluster_start_addresses[2];
    size_t cluster_lengths[2];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;
    
    int time_in_mins;
    
    cluster_start_addresses[0] = &cab[3];
    cluster_start_addresses[1] = &cab[18];
    
    cluster_lengths[0] = 10U;
    cluster_lengths[1] = 22U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 2, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 10);
    assert(longest_safe_cluster_start_address == cab_start_address + 40);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 2);

    assert(time_in_mins == 8);
}

void ClustersPartialOverlap()
{
    char cab[CAB_LENGTH];
    const char* cab_start_address = cab;

    const char* cluster_start_addresses[2];
    size_t cluster_lengths[2];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    int time_in_mins;

    cluster_start_addresses[0] = &cab[10];
    cluster_start_addresses[1] = &cab[2];

    cluster_lengths[0] = 30U;
    cluster_lengths[1] = 36U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 2, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 28);
    assert(longest_safe_cluster_start_address == cab_start_address + 10);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 2);

    assert(time_in_mins == 6);
}

void ClustersFullOverlap()
{
    char cab[CAB_LENGTH];
    const char* cab_start_address = cab;

    const char* cluster_start_addresses[2];
    size_t cluster_lengths[2];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    int time_in_mins;

    cluster_start_addresses[0] = &cab[2];
    cluster_start_addresses[1] = &cab[2];

    cluster_lengths[0] = 29U;
    cluster_lengths[1] = 29U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 2, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 50);
    assert(longest_safe_cluster_start_address == cab_start_address + 0);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 2);

    assert(time_in_mins == 5);
}

void MultipleClustersNoOverlap()
{
    char cab[CAB_LENGTH];
    const char* cab_start_address = cab;

    const char* cluster_start_addresses[5];
    size_t cluster_lengths[5];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    int time_in_mins;

    cluster_start_addresses[0] = &cab[8];
    cluster_start_addresses[1] = &cab[1];
    cluster_start_addresses[2] = &cab[13];
    cluster_start_addresses[3] = &cab[33];
    cluster_start_addresses[4] = &cab[38];

    cluster_lengths[0] = 3U;
    cluster_lengths[1] = 2U;
    cluster_lengths[2] = 10U;
    cluster_lengths[3] = 4U;
    cluster_lengths[4] = 9U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 10);
    assert(longest_safe_cluster_start_address == cab_start_address + 23);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5);

    assert(time_in_mins == 8);
}

void MultipleClustersOverlap()
{
    char cab[CAB_LENGTH];
    const char* cab_start_address = cab;

    const char* cluster_start_addresses[5];
    size_t cluster_lengths[5];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;

    int time_in_mins;

    cluster_start_addresses[0] = &cab[8];
    cluster_start_addresses[1] = &cab[1];
    cluster_start_addresses[2] = &cab[13];
    cluster_start_addresses[3] = &cab[33];
    cluster_start_addresses[4] = &cab[38];

    cluster_lengths[0] = 10U;
    cluster_lengths[1] = 22U;
    cluster_lengths[2] = 10U;
    cluster_lengths[3] = 13U;
    cluster_lengths[4] = 10U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 15);
    assert(longest_safe_cluster_start_address == cab_start_address + 18);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5);

    assert(time_in_mins == 7);
}


int main(void)
{
    NoCluster();
    Cluster();
    ClustersNoOverlap();
    ClustersPartialOverlap();
    ClustersFullOverlap();
    MultipleClustersNoOverlap();
    MultipleClustersOverlap();
    return 0;
}
