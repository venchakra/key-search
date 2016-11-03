#include "search.h"
#include <cstdio>
#include <cassert>

SearchResult
SearchHelper(const int * const items,
             const int key,
             const SearchType type,
             int* const index,
             int start,
             int end,
             int step)
{
    switch (type) {
    case LessThan:
        {
            if (items[start] >= key) {
                return NotFound;
            }

            int idx = start;
            while ((idx != end+step) && (items[idx] < key)) {
                *index = idx;
                idx+=step;
            }

            return FoundLess;
        }

    case LessThanEquals:
        {
            if (items[start] > key) {
                return NotFound;
            }

            int idx = start;
            while ((idx != end+step) && (items[idx] <= key)) {
                *index = idx;
                idx+=step;
            }

            if (items[*index] == key) {
                return FoundExact;
            }

            return FoundLess;
        }

    case Equals:
        { 
            int idx = start;
            while ((idx != end+step) && (items[idx] != key)) {
                idx+=step;
            }

            if (items[idx] == key) {
                *index = idx;
                return FoundExact;
            }

            return NotFound;
        }

    case GreaterThanEquals:
        {
            int idx = start;
            while ((idx != end) && (items[idx] < key)) {
                idx+=step;
            }

            if (items[idx] < key) {
                return NotFound;
            }

            *index = idx;

            if (items[idx] == key) {
                return FoundExact;
            }

            return FoundGreater;
        }

    case GreaterThan:
        {
            int idx = start;
            while ((idx != end) && (items[idx] <= key)) {
                idx+=step;
            }

            if (items[idx] <= key) {
                return NotFound;
            }

            *index = idx;
            return FoundGreater;
        }

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

    switch (ascending) {
    case 0:
        // Descending sorted array
        return SearchHelper(items, key, type, index, (n_items-1), 0, -1);
    default:
        // Ascending sorted array
        return SearchHelper(items, key, type, index, 0, (n_items-1), 1);
    }
}
