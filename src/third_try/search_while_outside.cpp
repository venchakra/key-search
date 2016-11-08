#include "search.h"
#include <cstdio>
#include <cassert>

SearchResult
SearchHelper(const int * const items,
             const int key,
             const SearchType type,
             int* const index,
             int startIndex,
             int endIndex,
             int step)
{
    int target = -5;

    while (startIndex != endIndex+step) {
        switch (type) {
        case LessThan:
            if (items[startIndex] >= key) {
                goto done;
            }

            target = startIndex;
            break;

        case LessThanEquals:
        case Equals:
            if (items[startIndex] > key) {
                goto done;
            }

            target = startIndex;
            break;

        case GreaterThanEquals:
            if (items[startIndex] >= key) {
                target = startIndex;
                goto done;
            }

            break;

        case GreaterThan:
            if (items[startIndex] > key) {
                target = startIndex;
                goto done;
            }

            break;

        default:
            // Error
            printf("Error in search type\n");
            return NotFound;
        }

        startIndex += step;
    } // end while loop

 done:
    switch (type) {
    case LessThan:
        if (target == -5) {
            return NotFound;
        }

        *index = target;

        return FoundLess;

    case LessThanEquals:
        if (target == -5) {
            return NotFound;
        }

        *index = target;

        if (items[target] == key) {
            return FoundExact;
        }

        return FoundLess;

    case Equals:
        if ((target == -5) || (items[target] != key)) {
            return NotFound;
        }

        *index = target;

        return FoundExact;

    case GreaterThanEquals:
        if ((target == -5) || (target == endIndex+step)) {
            return NotFound;
        }

        *index = target;

        if (items[target] == key) {
            return FoundExact;
        }

        return FoundGreater;

    case GreaterThan:
        if ((target == -5) || (target == endIndex+step)) {
            return NotFound;
        }

        *index = target;

        return FoundGreater;

    default:
        return NotFound;
    }
}

SearchResult
Search(const int * const items,
       const int n_items,
       const int ascending,
       const int key,
       const SearchType type,
       int* const index)
{
    assert(NULL != items);
    assert(NULL != index);
    assert(n_items > 0);

    if (ascending) {
        // Ascending sorted array
        return SearchHelper(items, key, type, index, 0, (n_items-1), 1);
    }

    // Descending sorted array (we always examine the array in ascending order)
    return SearchHelper(items, key, type, index, (n_items-1), 0, -1);
}
