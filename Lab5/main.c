#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "receipter.h"

int main(void)
{
    time_t time = 1569472997;

    assert(TRUE == add_item("Magarita", 12.45222));
    assert(TRUE == add_item("Sharkfin soup", 500.12254));
    assert(TRUE == add_item("Kingcrab dip", 125.9999));
    assert(TRUE == add_item("Deep fried scallops", 7.36));
    assert(TRUE == add_item("Tacoyaki", 6.898));
    assert(TRUE == add_item("Salmon sashimi", 16.54));
    assert(TRUE == add_item("Tuna sashimi", 15.42));
    assert(TRUE == add_item("Unagi soup", 25.485));
    assert(TRUE == add_item("Nestea ice tea", 5.99));
    assert(TRUE == add_item("Chocolate brownie fudge", 8.99));

    assert(FALSE == add_item("This won't get added lol", 2.5555555555));

    add_tip(20.55);

    add_message("Thanks for dining with us! Thanks for dining with us! Thanks for dining with us!");

    assert(TRUE == print_receipt("receipt0.txt", time));

    assert(TRUE == add_item("Raw sea cucumber", 34.266));
    assert(TRUE == add_item("Pan fried Mackerel", 16.58));
    assert(TRUE == add_item("Pepsi", 5.99));

    assert(TRUE == print_receipt("receipt1.txt", time));

    assert(FALSE == print_receipt("receipt2.txt", time));
    
    assert(0);
    return 0;
}
