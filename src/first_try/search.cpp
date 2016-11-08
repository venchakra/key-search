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

    if (items[end] < key) {
        *index = end;
        return FoundLess;
    }

    int idx = start;
    while ((idx != end) && (items[idx] < key)) {
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

    if (items[start] == key) {
        *index = start;
        return FoundExact;
    }

    if (items[end] < key) {
        *index = end;
        return FoundLess;
    }

    if (items[end] == key) {
        *index = end;
        return FoundExact;
    }

    int idx = start;
    while ((idx != end) && (items[idx] <= key)) {
        *index = idx;
        idx+=step;
    }

    if (items[(*index)] == key) {
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
    if ((items[start] > key) || (items[end] < key)) {
        return NotFound;
    }

    for (int idx = start; idx != (end+step); idx+=step) {
        if (items[idx] == key) {
            *index = idx;
            return FoundExact;
        } else if (items[idx] > key) {
            break;
        }
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
    if (items[start] > key) {
        *index = start;
        return FoundGreater;
    }

    if (items[start] == key) {
        *index = start;
        return FoundExact;
    }

    if (items[end] < key) {
        return NotFound;
    }

    if (items[end] == key) {
        *index = end;
        return FoundExact;
    }

    int idx = start+step;
    while ((idx != end) && (items[idx] < key)) {
        idx+=step;
    }

    *index = idx;

    if (items[(*index)] == key) {
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
    if (items[start] > key) {
        *index = start;
        return FoundGreater;
    }

    if (items[end] <= key) {
        return NotFound;
    }

    int idx = start+step;
    while ((idx != end) && (items[idx] <= key)) {
        idx+=step;
    }

    *index = idx;
    return FoundGreater;
}

static SearchResult
SearchDescending(const int * const items,
                 const int n_items,
                 const int key,
                 const SearchType type,
                 int* const index)
{
    if (type == LessThan) {
        return SearchLessThan(items, n_items, key, index, (n_items-1), 0, -1);
    } else if (type == LessThanEquals) {
        return SearchLessThanEquals(items, n_items, key, index, (n_items-1), 0, -1);
    } else if (type == Equals) {
        return SearchEquals(items, n_items, key, index, (n_items-1), 0, -1);
    } else if (type == GreaterThanEquals) {
        return SearchGreaterThanEquals(items, n_items, key, index, (n_items-1), 0, -1);
    } else if (type == GreaterThan) {
        return SearchGreaterThan(items, n_items, key, index, (n_items-1), 0, -1);
    } else {
        // Error
        printf("Error in search type\n");
        return NotFound;
    }
}

static SearchResult
SearchAscending(const int * const items,
                const int n_items,
                const int key,
                const SearchType type,
                int* const index)
{
    if (type == LessThan) {
        return SearchLessThan(items, n_items, key, index, 0, (n_items-1), 1);
    } else if (type == LessThanEquals) {
        return SearchLessThanEquals(items, n_items, key, index, 0, (n_items-1), 1);
    } else if (type == Equals) {
        return SearchEquals(items, n_items, key, index, 0, (n_items-1), 1);
    } else if (type == GreaterThanEquals) {
        return SearchGreaterThanEquals(items, n_items, key, index, 0, (n_items-1), 1);
    } else if (type == GreaterThan) {
        return SearchGreaterThan(items, n_items, key, index, 0, (n_items-1), 1);
    } else {
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
    if (NULL == index) {
        return NotFound;
    }

    assert(NULL != items);
    assert(n_items > 0);

    if (ascending != 0) {
        return SearchAscending(items, n_items, key, type, index);
    } else {
        return SearchDescending(items, n_items, key, type, index);
    }
}
