//==============================================================================
// Name        : <blocks.h>
// Author      : Karim DRIDI
// Version     : 0.1
// Copyright   : Private
// Description : Block macros
//==============================================================================

#ifndef BLOCKS_H
#define BLOCKS_H

#include "blocks/blocks.h"
#include "blocks/stdio.h"
#include "blocks/stdlib.h"

#define block_file_with_path(_result, _path, _mode, _block)                    \
  block_fopen_quietly(_result, _path, _mode,                                   \
    block_compose(_block, block_fclose_quietly(_result, block_empty()))        \
  )

#define block_file_length(_result, _file, _block)                              \
  FILE *__##_result##__file = (FILE *) (_file);                                \
  block_fseek_quietly(__##_result##__file, 0, SEEK_END,                        \
    block_ftell_quietly(_result, __##_result##__file, _block)                  \
  )

#define block_memory_with_size(_var, _size, _block)                            \
  block_malloc(_var, (_size),                                                  \
    block_compose(                                                             \
      _block, block_if_true((_var != NULL),                                    \
        block_free(_var, block_empty())                                        \
      )                                                                        \
    ), block_warning("block_malloc"))

#define block_memory_with_filename(_result, _path, _block) {                   \
  long _result##_length = 0;                                                   \
  char *_result##_data = NULL;                                                 \
  block_file_with_path(_result##_file, _path, "r",                             \
    block_file_length(_result##_file_length, _result##_file,                   \
      block_fseek(_result##_file, 0, SEEK_SET,                                 \
        block_memory_with_size(_result##_file_buffer, _result##_file_length,   \
          size_t _result##_fread = fread                                       \
          _result##_file_buffer, 1                                             \
          _result##_file_length, _result##_file);                              \
        block_if((_result##_file_length == _result##_fread), {                 \
          _result##_length = _result##_file_length;                            \
          _result##_data = _result##_file_buffer;                              \
          _result##_file_buffer = NULL;                                        \
        }, block_warning("block_fread"))                                       \
      ),                                                                       \
      block_warning("block_fseek")                                             \
    )                                                                          \
  )                                                                            \
}

#endif /* BLOCKS_H */
