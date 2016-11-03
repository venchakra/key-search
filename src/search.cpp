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
    switch (type) {
    case LessThan:
        if (items[startIndex] >= key) {
            return NotFound;
        }

        while ((startIndex != endIndex+step) && (items[startIndex] < key)) {
            *index = startIndex;
            startIndex += step;
        }

        return FoundLess;

    case LessThanEquals:
        if (items[startIndex] > key) {
            return NotFound;
        }

        while ((startIndex != endIndex+step) && (items[startIndex] <= key)) {
            *index = startIndex;
            startIndex += step;
        }

        if (items[*index] == key) {
            return FoundExact;
        }

        return FoundLess;

    case Equals:
        while ((startIndex != endIndex+step) && (items[startIndex] != key)) {
            startIndex += step;
        }

        if (items[startIndex] == key) {
            *index = startIndex;
            return FoundExact;
        }

        return NotFound;

    case GreaterThanEquals:
        while ((startIndex != endIndex) && (items[startIndex] < key)) {
            startIndex += step;
        }

        if (items[startIndex] < key) {
            return NotFound;
        }

        *index = startIndex;

        if (items[startIndex] == key) {
            return FoundExact;
        }

        return FoundGreater;

    case GreaterThan:
        while ((startIndex != endIndex) && (items[startIndex] <= key)) {
            startIndex += step;
        }

        if (items[startIndex] <= key) {
            return NotFound;
        }

        *index = startIndex;
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
