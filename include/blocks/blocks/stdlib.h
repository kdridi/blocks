//==============================================================================
// Name        : <blocks/stlib.h>
// Author      : Karim DRIDI
// Version     : 0.1
// Copyright   : Private
// Description : Block macros
//==============================================================================

#ifndef BLOCKS_STDLIB_H_
#define BLOCKS_STDLIB_H_

#include "blocks.h"
#include <stdlib.h>

#define block_calloc(_result, _nmemb, _size, _sblock, _fblock) {               \
  void *_result = calloc((_nmemb), (_size));                                   \
  block_if((_result != NULL), _sblock, _fblock)                                \
}

#define block_calloc_quietly(_result, _nmemb, _size, _block)                   \
  block_calloc(_result, _nmemb, _size, _block, block_empty())

#define block_malloc(_result, _size, _sblock, _fblock) {                       \
  void *_result = malloc((_size));                                             \
  block_if((_result != NULL), _sblock, _fblock)                                \
}

#define block_malloc_quietly(_result, _size, _block)                           \
  block_malloc(_result, _size, _block, block_empty())

#define block_free(_ptr, _block) {                                             \
  void **__blk_fptr = (void **) (&(_ptr));                                     \
  block_if_true((*__blk_fptr != NULL),                                         \
    block_compose(free(*__blk_fptr), block_assign(*__blk_fptr, NULL))          \
  )                                                                            \
}

#define block_realloc(_result, _ptr, _size, _sblock, _fblock) {                \
  void *_result = realloc((_ptr), (_size));                                    \
  block_if((_result != NULL), _sblock, _fblock)                                \
}

#define block_realloc_quietly(_result, _ptr, _size, block)                     \
  block_realloc(_result, _ptr, _size, block, block_empty())

#define block_mkstemp(_template, _sblock, _fblock)                             \
  block_if((mkstemp((_template)) == -1), _fblock, _sblock)

#define block_mkstemp_quietly(_template, _block)                               \
  block_mkstemp(_template, _block, block_empty())

#define block_mkostemp(_template, _flags, _sblock, _fblock)                    \
  block_if((mkostemp((_template), (_flags)) == -1), _fblock, _sblock)

#define block_mkostemp_quietly(_template, _flags, _block)                      \
  block_mkostemp(_template, _flags, _block, block_empty())

#endif /* BLOCKS_STDLIB_H_ */
