//
// Created by stormnight on 9/3/19.
//

#include <unistd.h>

long GetTotalSystemMemory()
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);

    return pages * page_size;
}