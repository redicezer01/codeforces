#include <stdio.h>
#include <stddef.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <string.h>
 
/**
 * Pool: pool of small objects
 * Format: [data, ptr], ptr - shift in bytes from base
 * Pool returns NOT pointers to objects, but shift from begin field
 * In was done for automatic capacity increase, because 'realloc'
 * can change address of pointer
 */
 
struct Pool {
    char* begin;
    char* end;
    char* tail;
    size_t elementSizeInBytes;
};
 
int PoolInit(struct Pool* pool, size_t elementSizeInBytes, size_t count);
void PoolDestroy(struct Pool* pool);
int PoolIsEmpty(struct Pool* pool);
size_t PoolGetShift(struct Pool* pool);
#define PoolGet(pool, shift) (pool->begin + shift)
void PoolReleaseShift(struct Pool* pool, size_t shift);
 
/**
 * This is simple implementation of Hashtable ADT
 * In uses lists for collisions
 * It has constant capacity, but uses Pool, so
 * can contain "unlimited" amount of a data
 *
 * Format (with pool) [[[key, value], next], prev]
 */
 
struct Hashtable {
    size_t (*hash_func)(char*);
    int (*equals_func)(char*, char*);
    void*(*key_copy_func)(void*, const void*, size_t);
    void*(*value_copy_func)(void*, const void*, size_t);
    size_t* begin;
    size_t* end;
    size_t keySizeInBytes;
    size_t valueSizeInBytes;
    size_t elementSizeInBytes;
    struct Pool pool;
    size_t count;
};
 
int HashtableInit(struct Hashtable* table, size_t keySizeInBytes,
        size_t valueSizeInBytes, size_t count, size_t(*hash_func)(char*),
        int(*equals_func)(char*, char*), void*(*key_copy_func)(void*,
                const void*, size_t), void*(*value_copy_func)(void*,
                const void*, size_t));
void HashtableDestroy(struct Hashtable* table);
void HashtableTravel(struct Hashtable* table, void(*travel_func)(char*, void*),
        void* userData);
char* HashtableGet(struct Hashtable* table, char* key);
#define HashtableGetKey(table, iterator) (iterator)
#define HashtableGetValue(table, iterator) (iterator + (table)->keySizeInBytes)
int HashtablePut(struct Hashtable* table, char* key, char* value);
int HashtableRemove(struct Hashtable* table, char* key);
 
size_t hash(char* data) {
    size_t r = 0;
    for (; *data != '\0'; ++data)
        r = 31 * r + (*data - 'a') + 1;
    return r;
}
 
int equal(char* l, char* r) {
    return strcmp(l, r) == 0;
}
 
 
int main() {
    int n, v;
    char s[34];
    char *it;
    struct Hashtable table;
    
    HashtableInit(&table, sizeof(s), sizeof(int), 98317, hash, equal, memcpy, memcpy);
    scanf("%d", &n);
    while (n-- > 0) {
        scanf("%s", s);
        it = HashtableGet(&table, s);
        if (!it) {
            printf("OK\n");
            v = 1;
            HashtablePut(&table, s, (char*)&v);
        } else {
            v = *((int*) (it + sizeof(s)));
            printf("%s%d\n", it, v);
            *((int*) (it + sizeof(s))) = v + 1;
        }
    }
    HashtableDestroy(&table);
    return 0;
}
 
 
#define POOL_ALIGN 4
 
#define Data(x, elementSizeInBytes) (x)
#define Prev(x, elementSizeInBytes) (x + elementSizeInBytes)
 
int PoolInit(struct Pool* pool, size_t elementSizeInBytes, size_t count) {
    char *begin, *end, *it;
    size_t bufSize;
    size_t step, shift;
 
    assert(pool);
    assert(elementSizeInBytes);
    assert(count);
 
    step = elementSizeInBytes + sizeof(ptrdiff_t);
    bufSize = step * count;
    bufSize += (POOL_ALIGN - (bufSize + POOL_ALIGN) % POOL_ALIGN) % POOL_ALIGN;
 
    begin = (char*) realloc(NULL, bufSize);
    if (!begin)
        return -4;
 
    end = begin + bufSize;
    *((ptrdiff_t*) Prev(begin, elementSizeInBytes)) = (ptrdiff_t) (-1);
    for (it = begin + step, shift = 0; it < end; it += step, shift += step) {
        *((ptrdiff_t*) Prev(it, elementSizeInBytes)) = (ptrdiff_t) shift;
    }
 
    memset(pool, 0, sizeof(struct Pool));
    pool->begin = begin;
    pool->end = end;
    pool->tail = end - step;
    pool->elementSizeInBytes = elementSizeInBytes;
    return 0;
}
 
void PoolDestroy(struct Pool* pool) {
    assert(pool);
    if (pool->begin)
        free(pool->begin);
    memset(pool, 0, sizeof(struct Pool));
}
 
int PoolIsEmpty(struct Pool* pool) {
    assert(pool);
    return pool->tail < pool->begin;
}
 
size_t PoolGetShift(struct Pool* pool) {
    size_t result;
    size_t oldSize, newSize;
    char *newBuf, *it;
    size_t shift, step, elementSizeInBytes;
 
    if (PoolIsEmpty(pool)) {
        /* try to realloc */
        oldSize = pool->end - pool->begin;
        newSize = oldSize * 2;
        newBuf = (char*) realloc(pool->begin, newSize);
        if (!newBuf)
            return (size_t) (-4);
 
        elementSizeInBytes = pool->elementSizeInBytes;
        step = elementSizeInBytes + sizeof(ptrdiff_t);
        *((ptrdiff_t*) Prev(newBuf + oldSize, elementSizeInBytes))
                = (ptrdiff_t) (-1);
        for (it = newBuf + step + oldSize, shift = oldSize; shift < newSize; it
                += step, shift += step) {
            *((ptrdiff_t*) Prev(it, elementSizeInBytes)) = (ptrdiff_t) shift;
        }
        pool->begin = newBuf;
        pool->end = newBuf + newSize;
        pool->tail = newBuf + newSize - step;
    }
 
    result = pool->tail - pool->begin;
    pool->tail = pool->begin
            + *((ptrdiff_t*) Prev(pool->tail, pool->elementSizeInBytes));
    return result;
 
}
 
void PoolReleaseShift(struct Pool* pool, size_t shift) {
    assert(pool);
 
    *((ptrdiff_t*) Prev(pool->begin + shift, pool->elementSizeInBytes))
            = (ptrdiff_t) (pool->tail - pool->begin);
    pool->tail = pool->begin + shift;
}
 
int HashtableInit(struct Hashtable* table, size_t keySizeInBytes,
        size_t valueSizeInBytes, size_t count, size_t(*hash_func)(char*),
        int(*equals_func)(char*, char*), void*(*key_copy_func)(void*,
                const void*, size_t), void*(*value_copy_func)(void*,
                const void*, size_t)) {
    size_t elementSizeInBytes;
    size_t *begin;
    struct Pool pool;
 
    assert(table);
    assert(keySizeInBytes);
    /* valueSizeInBytes can be zero to support HashSet */
    assert(count);
    assert(hash_func);
    assert(equals_func);
    assert(key_copy_func);
 
    elementSizeInBytes = keySizeInBytes + valueSizeInBytes;
 
    begin = (size_t*) malloc(count * sizeof(size_t));
    if (!begin)
        return -4;
 
    /**
     * We don't make pool size the same as table size,
     * because it takes only a few (~10) realloc to
     * hold all values for all cases in practice
     */
 
    if (PoolInit(&pool, elementSizeInBytes + sizeof(ptrdiff_t), 128) < 0) {
        free(begin);
        return -4;
    }
 
    memset(begin, 0xFF, count * sizeof(size_t));
    table->begin = begin;
    table->end = begin + count;
    table->elementSizeInBytes = elementSizeInBytes;
    table->keySizeInBytes = keySizeInBytes;
    table->valueSizeInBytes = valueSizeInBytes;
    table->hash_func = hash_func;
    table->equals_func = equals_func;
    table->key_copy_func = key_copy_func;
    table->value_copy_func = value_copy_func;
    table->pool = pool;
 
    return 0;
}
 
void HashtableDestroy(struct Hashtable* table) {
    assert(table);
 
    PoolDestroy(&table->pool);
    if (table->begin)
        free(table->begin);
 
    memset(table, 0, sizeof(struct Hashtable));
}
 
/**
 * travel_func([key, value], user data)
 */
 
#define Next(it, shift) *((size_t*) (it + shift))
 
void HashtableTravel(struct Hashtable* table, void(*travel_func)(char*, void*),
        void* userData) {
    size_t *it, *end;
    size_t it2;
    size_t shift;
    char *data;
    struct Pool* pool;
 
    assert(table);
    assert(travel_func);
 
    end = table->end;
    pool = &table->pool;
    shift = table->elementSizeInBytes;
 
    for (it = table->begin; it < end; ++it) {
        it2 = *it;
        while (it2 != (size_t) (-1)) {
            data = PoolGet(pool, it2);
            (*travel_func)(data, userData);
            it2 = Next(data, shift);
        }
    }
}
 
char* HashtableGet(struct Hashtable* table, char* key) {
    size_t shift;
    size_t it2;
    char *data;
    struct Pool* pool;
    int (*equals_func)(char*, char*);
 
    assert(table);
    assert(key);
 
    equals_func = table->equals_func;
    pool = &table->pool;
    shift = table->elementSizeInBytes;
    it2 = *(table->begin + (*(table->hash_func))(key) % (table->end
            - table->begin));
    while (it2 != (size_t) (-1)) {
        data = PoolGet(pool, it2);
        if ((*equals_func)(key, data)) {
            return data;
        }
        it2 = Next(data, shift);
    }
 
    return NULL;
}
 
enum {
    _S_num_primes = 28
};
 
static const unsigned long __stl_prime_list[_S_num_primes] = { 53ul, 97ul,
        193ul, 389ul, 769ul, 1543ul, 3079ul, 6151ul, 12289ul, 24593ul, 49157ul,
        98317ul, 196613ul, 393241ul, 786433ul, 1572869ul, 3145739ul, 6291469ul,
        12582917ul, 25165843ul, 50331653ul, 100663319ul, 201326611ul,
        402653189ul, 805306457ul, 1610612741ul, 3221225473ul, 4294967291ul };
 
static unsigned long* lower_bound(unsigned long* begin, unsigned long* end,
        unsigned long val) {
    unsigned long *mid;
 
    while (begin < end) {
        mid = begin + ((end - begin) >> 1);
        if (*mid < val)
            begin = mid + 1;
        else
            end = mid;
    }
    return begin;
}
 
static int HashtableRehash(struct Hashtable* table) {
    size_t oldSize, newSize;
    unsigned long* pos;
    size_t* newBuf;
    size_t *it, *end, *newIt;
    size_t it2, tmp;
    size_t shift;
    char *data;
    struct Pool* pool;
    size_t (*hash_func)(char*);
 
    /* obtain new size */
    oldSize = table->end - table->begin;
    pos = lower_bound((unsigned long*) __stl_prime_list,
            (unsigned long*) (__stl_prime_list + _S_num_primes),
            (unsigned long) oldSize);
    newSize = (pos == __stl_prime_list + _S_num_primes) ? *(__stl_prime_list
            + _S_num_primes - 1) : *pos;
 
    /* alloc memory */
    newBuf = (size_t*) malloc(newSize * sizeof(size_t));
    if (!newBuf)
        return -4;
 
    memset(newBuf, 0xFF, newSize * sizeof(size_t));
 
    /* iterate old hashtable and fill new */
    hash_func = table->hash_func;
    pool = &table->pool;
    shift = table->elementSizeInBytes;
    end = table->end;
    for (it = table->begin; it < end; ++it) {
        it2 = *it;
        while (it2 != (size_t) (-1)) {
            data = PoolGet(pool, it2);
            tmp = it2;
            it2 = Next(data, shift);
            newIt = newBuf + (*hash_func)(data) % newSize;
            Next(data, shift) = *newIt;
            *newIt = tmp;
        }
    }
    free(table->begin);
    table->begin = newBuf;
    table->end = newBuf + newSize;
    return 0;
}
 
int HashtablePut(struct Hashtable* table, char* key, char* value) {
    size_t shift;
    size_t *it;
    size_t it2;
    char *data;
    size_t poolShift;
    struct Pool* pool;
    int (*equals_func)(char*, char*);
    void*(*key_copy_func)(void*, const void*, size_t);
    void*(*value_copy_func)(void*, const void*, size_t);
 
    assert(table);
    assert(key);
    assert(value || (table->valueSizeInBytes == 0));
 
    key_copy_func = table->key_copy_func;
    value_copy_func = table->value_copy_func;
    equals_func = table->equals_func;
    pool = &(table->pool);
    shift = table->elementSizeInBytes;
    it = table->begin + (*(table->hash_func))(key)
            % (table->end - table->begin);
 
    it2 = *it;
    while (it2 != (size_t) (-1)) {
        data = PoolGet(pool, it2);
        if ((*equals_func)(key, data)) {
            /* exists */
            if (table->valueSizeInBytes > 0)
                (*value_copy_func)(data + table->keySizeInBytes, value,
                        table->valueSizeInBytes);
            return 0;
        }
        it2 = Next(data, shift);
    }
    poolShift = PoolGetShift(pool);
    if (poolShift == (size_t) (-4))
        return -4;
 
    table->count++;
    data = PoolGet(pool, poolShift);
    Next(data, shift) = *it;
    (*key_copy_func)(data, key, table->keySizeInBytes);
    if (table->valueSizeInBytes > 0)
        (*value_copy_func)(data + table->keySizeInBytes, value,
                table->valueSizeInBytes);
    *it = poolShift;
 
    if ((table->count / 4) * 3 > (table->end - table->begin)) {
        //return HashtableRehash(table);
    }
    return 0;
}
 
int HashtableRemove(struct Hashtable* table, char* key) {
    size_t shift;
    size_t *it;
    size_t it2;
    char *data, *data_prev;
    struct Pool* pool;
    int (*equals_func)(char*, char*);
 
    assert(table);
    assert(key);
 
    equals_func = table->equals_func;
    pool = &(table->pool);
    shift = table->elementSizeInBytes;
    it = table->begin + (*(table->hash_func))(key)
            % (table->end - table->begin);
 
    if (*it == (size_t) (-1))
        return -1;
 
    it2 = *it;
    data_prev = NULL;
    while (it2 != (size_t) (-1)) {
        data = PoolGet(pool, it2);
        if ((*equals_func)(key, data)) {
            /* found */
            table->count--;
            PoolReleaseShift(pool, it2);
            if (!data_prev) {
                *it = Next(data, shift);
            } else {
                Next(data_prev, shift) = Next(data, shift);
            }
            return 0;
        }
        data_prev = data;
        it2 = Next(data, shift);
    }
    return -1;
}
