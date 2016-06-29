#ifndef _SEARCH_H_
#define _SEARCH_H_

typedef enum {
    LessThan = 0,
    LessThanEquals = 1,
    Equals = 2,
    GreaterThanEquals = 3,
    GreaterThan = 4
} SearchType;

typedef enum {
    NotFound,
    FoundExact,
    FoundGreater,
    FoundLess
} SearchResult;

SearchResult Search(
    const int * const items,
    const int n_items,
    const int ascending,
    const int key,
    const SearchType type,
    int* const index);

#endif // _SEARCH_H_
