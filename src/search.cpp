#include "search.h"
#include <cstdio>
#include <cassert>

static SearchResult
SearchLessThan(const int * const items,
               const int n_items,
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
                     const int n_items,
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
             const int n_items,
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
                        const int n_items,
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
                  const int n_items,
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
        switch (type) {
        case LessThan:
            return SearchLessThan(items, n_items, key, index, (n_items-1), 0, -1);
        case LessThanEquals:
            return SearchLessThanEquals(items, n_items, key, index, (n_items-1), 0, -1);
        case Equals:
            return SearchEquals(items, n_items, key, index, (n_items-1), 0, -1);
        case GreaterThanEquals:
            return SearchGreaterThanEquals(items, n_items, key, index, (n_items-1), 0, -1);
        case GreaterThan:
            return SearchGreaterThan(items, n_items, key, index, (n_items-1), 0, -1);
        default:
            // Error
            printf("Error in search type\n");
            return NotFound;
        }
    default:
        // Ascending sorted array
        switch (type) {
        case LessThan:
            return SearchLessThan(items, n_items, key, index, 0, (n_items-1), 1);
        case LessThanEquals:
            return SearchLessThanEquals(items, n_items, key, index, 0, (n_items-1), 1);
        case Equals:
            return SearchEquals(items, n_items, key, index, 0, (n_items-1), 1);
        case GreaterThanEquals:
            return SearchGreaterThanEquals(items, n_items, key, index, 0, (n_items-1), 1);
        case GreaterThan:
            return SearchGreaterThan(items, n_items, key, index, 0, (n_items-1), 1);
        default:
            // Error
            printf("Error in search type\n");
            return NotFound;
        }
    }
}
