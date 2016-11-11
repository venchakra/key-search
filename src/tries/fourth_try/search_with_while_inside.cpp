#include "search.h"
#include <cstdio>
#include <cassert>

#define INIT_IDX (-5)

SearchResult
SearchHelper(const int * const items,
             const int key,
             const SearchType type,
             int* const index,
             int startIndex,
             int endIndex,
             int step)
{
    int target = INIT_IDX;

    switch (type) {
    case LessThan:
        while (startIndex != endIndex+step) {
            if (items[startIndex] >= key) {
                break;
            }

            target = startIndex;
            startIndex += step;
        }

        if (target == INIT_IDX) {
            return NotFound;
        }

        *index = target;

        return FoundLess;

    case LessThanEquals:
        while (startIndex != endIndex+step) {
            if (items[startIndex] > key) {
                break;
            }

            target = startIndex;
            startIndex += step;
        }

        if (target == INIT_IDX) {
            return NotFound;
        }

        *index = target;

        if (items[target] == key) {
            return FoundExact;
        }

        return FoundLess;

    case Equals:
        while (startIndex != endIndex+step) {
            if (items[startIndex] > key) {
                break;
            }

            target = startIndex;
            startIndex += step;
        }

        if ((target == INIT_IDX) || (items[target] != key)) {
            return NotFound;
        }

        *index = target;

        return FoundExact;

    case GreaterThanEquals:
        while (startIndex != endIndex+step) {
            if (items[startIndex] >= key) {
                target = startIndex;
                break;
            }

            startIndex += step;
        }

        if ((target == INIT_IDX) || (target == endIndex+step)) {
            return NotFound;
        }

        *index = target;

        if (items[target] == key) {
            return FoundExact;
        }

        return FoundGreater;

    case GreaterThan:
        while (startIndex != endIndex+step) {
            if (items[startIndex] > key) {
                target = startIndex;
                break;
            }

            startIndex += step;
        }

        if ((target == INIT_IDX) || (target == endIndex+step)) {
            return NotFound;
        }

        *index = target;

        return FoundGreater;

    default:
        // Error
        printf("Error in search type\n");
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
