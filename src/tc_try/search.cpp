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
    SearchResult result = NotFound;

    while (startIndex != endIndex+step) {
        switch (type) {
        case LessThan:
            if (items[startIndex] < key) {
                *index = startIndex;
                result = FoundLess;
            }

            break;

        case LessThanEquals:
            if (items[startIndex] <= key) {
                *index = startIndex;
                result = (items[startIndex] == key) ? FoundExact : FoundLess;
            }

            break;

        case Equals:
            if (items[startIndex] == key) {
                *index = startIndex;
                return FoundExact;
            }

            break;

        case GreaterThan:
            if (items[(endIndex - startIndex) * step] > key) {
                *index = (endIndex - startIndex) * step;
                result = FoundGreater;
                if (step > 0) {
                    return result;
                }
            }

            break;

        case GreaterThanEquals:
            if (items[(endIndex - startIndex) * step] >= key) {
                *index = (endIndex - startIndex) * step;
                result = (items[*index] == key) ? FoundExact : FoundGreater;
                if (step > 0) {
                    return result;
                }
            }

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
    assert(NULL != items);
    assert(NULL != index);
    assert(n_items > 0);

    if ((ascending && type <= Equals) || (!ascending && type > Equals)) {
        return SearchHelper(items, key, type, index, 0, (n_items-1), 1);
    }

    return SearchHelper(items, key, type, index, (n_items-1), 0, -1);
}
