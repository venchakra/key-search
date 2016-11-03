#include "search.h"
#include <cstdio>
#include <cassert>

static SearchResult
SearchLessThan(const int * const items,
               const int key,
               int* const index,
               const int start,
               const int end,
               const int step)
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

static SearchResult
SearchLessThanEquals(const int * const items,
                     const int key,
                     int* const index,
                     const int start,
                     const int end,
                     const int step)
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

static SearchResult
SearchEquals(const int * const items,
             const int key,
             int* const index,
             const int start,
             const int end,
             const int step)
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

static SearchResult
SearchGreaterThanEquals(const int * const items,
                        const int key,
                        int* const index,
                        const int start,
                        const int end,
                        const int step)
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

static SearchResult
SearchGreaterThan(const int * const items,
                  const int key,
                  int* const index,
                  const int start,
                  const int end,
                  const int step)
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
        return SearchLessThan(items, key, index, start, end, step);
    case LessThanEquals:
        return SearchLessThanEquals(items, key, index, start, end, step);
    case Equals:
        return SearchEquals(items, key, index, start, end, step);
    case GreaterThanEquals:
        return SearchGreaterThanEquals(items, key, index, start, end, step);
    case GreaterThan:
        return SearchGreaterThan(items, key, index, start, end, step);
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
