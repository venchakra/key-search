#include "search.h"

SearchResult
SearchHelper(const int * const items,
             const int key,
             const SearchType type,
             int* const index,
             int startIndex,
             int endIndex,
             int step)
{
    SearchResult result = NotFound;

    while (startIndex != endIndex+step) {
        if ((LessThan == type) && (items[startIndex] < key)) {
            *index = startIndex;
            result = FoundLess;
        } else if ((LessThanEquals == type) && (items[startIndex] <= key)) {
            *index = startIndex;
            result = (items[startIndex] == key ? FoundExact : FoundLess);
        } else if ((Equals == type) && (items[startIndex] == key)) {
            *index = startIndex;
            result = FoundExact;
            break;
        } else if ((GreaterThanEquals == type) && (items[startIndex] >= key)) {
            *index = startIndex;
            result = (items[startIndex] == key ? FoundExact : FoundGreater);
            break;
        } else if ((GreaterThan == type) && (items[startIndex] > key)) {
            *index = startIndex;
            result = FoundGreater;
            break;
        }

        startIndex += step;
    }

    return result;
}

SearchResult
Search(const int * const items,
       const int n_items,
       const int ascending,
       const int key,
       const SearchType type,
       int* const index)
{
    if (ascending) {
        // Ascending sorted array
        return SearchHelper(items, key, type, index, 0, (n_items-1), 1);
    }

    // Descending sorted array (switch start and end indexes so that we
    // examine the array in ascending order)
    return SearchHelper(items, key, type, index, (n_items-1), 0, -1);
}
