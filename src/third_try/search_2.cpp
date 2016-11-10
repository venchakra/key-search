#include "search.h"
#include <cstdio>
#include <cassert>

static bool allowedResults[5][4] = {
    { /* 0 - LessThan */
        true,  /* NotFound */
        false, /* FoundExact */
        false, /* FoundGreater */
        true,  /* FoundLess */
    },
    { /* 1 - LessThanEquals */
        true,  /* NotFound */
        true,  /* FoundExact */
        false, /* FoundGreater */
        true,  /* FoundLess */
    },
    { /* 2 - Equals */
        true,  /* NotFound */
        true,  /* FoundExact */
        false, /* FoundGreater */
        false, /* FoundLess */
    },
    { /* 3 - GreaterThanEquals */
        true,  /* NotFound */
        true,  /* FoundExact */
        true,  /* FoundGreater */
        false, /* FoundLess */
    },
    { /* 4 - GreaterThan */
        true,  /* NotFound */
        false, /* FoundExact */
        true,  /* FoundGreater */
        false, /* FoundLess */
    }
};

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
        if ((LessThan == type) && (items[startIndex] < key)) {
            target = startIndex;
        } else if ((LessThanEquals == type) && (items[startIndex] <= key)) {
            target = startIndex;
        } else if ((Equals == type) && (items[startIndex] == key)) {
            target = startIndex;
            break;
        } else if ((GreaterThanEquals == type) && (items[startIndex] >= key)) {
            target = startIndex;
            break;
        } else if ((GreaterThan == type) && (items[startIndex] > key)) {
            target = startIndex;
            break;
        }

        startIndex += step;
    }

    if (target == -5) {
        return NotFound;
    }

    if ((items[target] == key) && (allowedResults[type][FoundExact])) {
        *index = target;
        return FoundExact;
    } else if ((items[target] < key) && (allowedResults[type][FoundLess])) {
        *index = target;
        return FoundLess;
    } else if ((items[target] > key) && (allowedResults[type][FoundGreater])) {
        *index = target;
        return FoundGreater;
    }

    return NotFound;
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
