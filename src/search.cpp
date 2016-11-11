#include "search.h"
#include <cassert>
#include <cstdio>

SearchResult
Search(const int * const items,
       const int n_items,
       const int ascending,
       const int key,
       const SearchType type,
       int* const index)
{
    assert(NULL != index);

    int startIndex = 0;
    int endIndex = (n_items-1);
    int step = 1;
    SearchResult result = NotFound;

    if (!ascending) {
        // Descending sorted array (switch start and end indexes so that we
        // always examine the array in ascending order)
        startIndex = (n_items-1);
        endIndex = 0;
        step = -1;
    }

    for (; startIndex != (endIndex+step); startIndex += step) {
        if ((LessThan == type) && (items[startIndex] < key)) {
            *index = startIndex;
            result = FoundLess;
        } else if ((LessThanEquals == type) && (items[startIndex] <= key)) {
            *index = startIndex;
            result = (items[startIndex] == key) ? FoundExact : FoundLess;
        } else if ((Equals == type) && (items[startIndex] == key)) {
            *index = startIndex;
            result = FoundExact;
            break;
        } else if ((GreaterThanEquals == type) && (items[startIndex] >= key)) {
            *index = startIndex;
            result = (items[startIndex] == key) ? FoundExact : FoundGreater;
            break;
        } else if ((GreaterThan == type) && (items[startIndex] > key)) {
            *index = startIndex;
            result = FoundGreater;
            break;
        }
    }

    return result;
}
