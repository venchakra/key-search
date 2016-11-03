/* Search an array of sorted numbers.
*
* items    : An array of sorted ints, with no duplicates
* n_items  : Number of elements in the items array
* ascending: non-zero if the array is sorted in ascending order
* key      : the key to search for
* type     : the type of match to find
*
* This function finds the element in the array
* that best fits the search criteria. It returns
* the match type and the index of the matching item.
*
* LessThan
* --------
*  Finds the largest item which is less than the key.
*  It returns FoundLess if a match is found, NotFound
*  if no match is found.
*
* LessThanEquals
* --------------
*  Finds the item which is equal to the key, or the
*  largest item which is less than the key. Returns
*  FoundExact if an item that exactly matches the key
*  is found, FoundLess if a non-exact match is found
*  and NotFound if no match is found.
*
* Equals
* ------
*  Finds an item which is equal to the key. Returns
*  FoundExact if an item if found, NotFound otherwise.
*
* GreaterThanEquals
* -----------------
*  Finds the item which is equal to the key, or the
*  smallest item which is greater than the key. Returns
*  FoundExact if an item that exactly matches the key
*  is found, FoundGreater if a non-exact match is found
*  and NotFound if no match is found.
*
* GreaterThan
* -----------
*  Finds the smallest item which is greater than the
*  key. Returns FoundGreater if a match if found, NotFound
*  if no match is found.
*
* Examples
* --------
*  Given the input array [0, 2, 4, 6, 8] (ascending order)
*
*  +-----+-------------------+--------------+-------+
*  | Key | Type              | Returns      | Index |
*  +-----+-------------------+--------------+-------+
*  | -1  | LessThanEquals    | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  0  | LessThan          | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  0  | Equals            | FoundExact   | 0     |
*  +-----+-------------------+--------------+-------+
*  |  1  | Equals            | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThanEquals | FoundExact   | 1     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThan       | FoundGreater | 2     |
*  +-----+-------------------+--------------+-------+
*
*  Given the input array [8, 6, 4, 2, 0] (descending order)
*
*  +-----+-------------------+--------------+-------+
*  | Key | Type              | Returns      | Index |
*  +-----+-------------------+--------------+-------+
*  | -1  | LessThan          | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*  |  4  | LessThanEquals    | FoundExact   | 2     |
*  +-----+-------------------+--------------+-------+
*  |  8  | Equals            | FoundExact   | 0     |
*  +-----+-------------------+--------------+-------+
*  |  5  | GreaterThanEquals | FoundGreater | 1     |
*  +-----+-------------------+--------------+-------+
*  |  2  | GreaterThanEquals | FoundExact   | 3     |
*  +-----+-------------------+--------------+-------+
*  |  9  | GreaterThan       | NotFound     | X     |
*  +-----+-------------------+--------------+-------+
*
* Assumptions
* -----------
*  The items are sorted
*  Items will be non-NULL
*  There are no duplicate items
*  n_items will be > 0
*/

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
