//==============================================================================
// Name        : <blocks.h>
// Author      : Karim DRIDI
// Version     : 0.1
// Copyright   : Private
// Description : Block macros
//==============================================================================

#ifndef BLOCKS_H
#define BLOCKS_H

#include "blocks/stdio.h"
#include "blocks/stdlib.h"

#define block_file_with_path(_result, _path, _mode, _block)                    \
  block_fopen(_result, _path, _mode,                                           \
    block_compose(                                                             \
      _block, block_fclose(_result,                                            \
        block_assign(_result, NULL),                                           \
        block_warning("block_fclose")                                          \
      )                                                                        \
    ), block_warning("block_fopen"))

#define block_file_length(_result, _file, _block)                              \
  block_fseek(_file, 0, SEEK_END,                                              \
    block_ftell(_result, _file, _block, block_warning("block_ftell")),         \
    block_warning("block_fseek")                                               \
  )

#define block_memory_with_size(_var, _size, _block)                            \
  block_malloc(_var, (_size),                                                  \
    block_compose(                                                             \
      _block, block_if_true((_var != NULL),                                    \
      block_free(_var, block_empty())                                          \
    )                                                                          \
  ), block_warning("block_malloc"))

#define block_memory_with_filename(_result, _path, _block) {                   \
  long _result##_length = 0;                                                   \
  char *_result##_data = NULL;                                                 \
  block_file_with_path(_result##_file, _path, "r",                             \
    block_file_length(_result##_file_length, _result##_file,                 \
      block_fseek(_result##_file, 0, SEEK_SET,                               \
        block_memory_with_size(_result##_file_buffer, _result##_file_length, \
          size_t _result##_fread = fread                                     \
          _result##_file_buffer, 1                                           \
          _result##_file_length, _result##_file);                            \
        block_if((_result##_file_length == _result##_fread), {               \
          _result##_length = _result##_file_length;                          \
          _result##_data = _result##_file_buffer;                            \
          _result##_file_buffer = NULL;                                      \
        }, block_warning("block_fread"))                                   \
      ),                                                                  \
      block_warning("block_fseek")                                           \
    )                                                                      \
  )                                                                        \
}

block_if_true((_result##_data != NULL), {                                      \
    _block                                                                     \
    block_free(_result##_data, block_assign(_result##_length, 0))              \
    })                                                                         \
}

#endif /* BLOCKS_H */
