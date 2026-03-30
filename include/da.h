#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    size_t count;
    size_t capacity;
} Header;

#define ARR_INIT_CAP 256

#define dapush(da, x)                                                                       \
    do                                                                                      \
    {                                                                                       \
        if ((da) == NULL)                                                                   \
        {                                                                                   \
            Header *header = malloc(sizeof(*(da)) * ARR_INIT_CAP + sizeof(Header));         \
            if (header == NULL)                                                             \
            {                                                                               \
                fprintf(stderr, "dapush: malloc failed\n");                                 \
                abort();                                                                    \
            }                                                                               \
            header->count = 0;                                                              \
            header->capacity = ARR_INIT_CAP;                                                \
            (da) = (void *)(header + 1);                                                    \
        }                                                                                   \
        Header *header = (Header *)(da) - 1;                                                \
        if (header->count >= header->capacity)                                              \
        {                                                                                   \
            size_t new_cap = header->capacity * 2;                                          \
            Header *new_header = realloc(header, sizeof(*(da)) * new_cap + sizeof(Header)); \
            if (new_header == NULL)                                                         \
            {                                                                               \
                fprintf(stderr, "dapush: realloc failed\n");                                \
                abort();                                                                    \
            }                                                                               \
            new_header->capacity = new_cap;                                                 \
            header = new_header;                                                            \
            (da) = (void *)(header + 1);                                                    \
        }                                                                                   \
        (da)[header->count++] = (x);                                                        \
    } while (0)

#define dapop(da) ((da)[--((Header *)(da) - 1)->count])

#define daresv(da, n)                                                                       \
    do                                                                                      \
    {                                                                                       \
        if ((da) == NULL)                                                                   \
        {                                                                                   \
            Header *header = malloc(sizeof(*(da)) * (n) + sizeof(Header));                  \
            if (header == NULL)                                                             \
            {                                                                               \
                fprintf(stderr, "dareserve: malloc failed\n");                              \
                abort();                                                                    \
            }                                                                               \
            header->count = 0;                                                              \
            header->capacity = (n);                                                         \
            (da) = (void *)(header + 1);                                                    \
        }                                                                                   \
        else                                                                                \
        {                                                                                   \
            Header *header = (Header *)(da) - 1;                                            \
            if ((n) > header->capacity)                                                     \
            {                                                                               \
                Header *new_header = realloc(header, sizeof(*(da)) * (n) + sizeof(Header)); \
                if (new_header == NULL)                                                     \
                {                                                                           \
                    fprintf(stderr, "dareserve: realloc failed\n");                         \
                    abort();                                                                \
                }                                                                           \
                new_header->capacity = (n);                                                 \
                (da) = (void *)(new_header + 1);                                            \
            }                                                                               \
        }                                                                                   \
    } while (0)

#define dalen(da) ((da) == NULL ? 0 : ((Header *)(da) - 1)->count)

#define daclr(da) ((da) == NULL ? (void)0 : (void)(((Header *)(da) - 1)->count = 0))

#define dafree(da) ((da) == NULL ? (void)0 : free((Header *)(da) - 1))