//==============================================================================
// Name        : <blocks/stdio.h>
// Author      : Karim DRIDI
// Version     : 0.1
// Copyright   : Private
// Description : Block macros
//==============================================================================
#ifndef BLOCKS_STDIO_H_
#define BLOCKS_STDIO_H_

#include "blocks.h"
#include <stdio.h>

#define block_fclose(_file, _sblock, _fblock) {                                \
  FILE **__block_fclose_file = (FILE **) (&(_file));                           \
  block_if((*__block_fclose_file != NULL),                                     \
    block_if((fclose(*__block_fclose_file) == 0),                              \
      block_compose(block_assign(*__block_fclose_file, NULL), _sblock),        \
      _fblock                                                                  \
    ),                                                                         \
    _fblock                                                                    \
  )                                                                            \
}

#define block_fclose_quietly(_file, _block)                                    \
  block_fclose(_file, _block, block_empty())

#define block_fopen(_result, _path, _mode, _sblock, _fblock) {                 \
  FILE *_result = fopen((_path), (_mode));                                     \
  block_if((_result == NULL), _fblock, _sblock)                                \
}

#define block_fopen_quietly(_result, _path, _mode, _block)                     \
  block_fopen(_result, _path, _mode, _block, block_empty())

#define block_fdopen(_result, _fd, _mode, _sblock, _fblock) {                  \
  FILE *_result = fdopen((_fd), (_mode));                                      \
  block_if((_result == NULL), _fblock, _sblock)                                \
}

#define block_fdopen_quietly(_result, _fd, _mode, _block)                      \
  block_fdopen(_result, _fd, _mode, _block, block_empty())

#define block_freopen(_result, _path, _mode, _stream, _sblock, _fblock) {      \
  FILE *_result = freopen((_path), (_mode), (_stream));                        \
  block_if((_result == NULL), _fblock, _sblock)                                \
}

#define block_freopen_quietly(_result, _path, _mode, _stream, _block)          \
  block_freopen(_result, _path, _mode, _stream, _block, block_empty())

#define block_fseek(_stream, _offset, _whence, _sblock, _fblock)               \
  block_if((fseek((_stream), (_offset), (_whence)) != -1), _sblock, _fblock)

#define block_fseek_quietly(_stream, _offset, _whence, _block)                 \
  block_fseek(_stream, _offset, _whence, _block, block_empty())

#define block_fgetpos(_stream, _pos, _sblock, _fblock)                         \
  block_if((fgetpos((_stream), (_pos)) != -1), _sblock, _fblock)

#define block_fgetpos_quietly(_stream, _pos, _block)                           \
  block_fgetpos(_stream, _pos, _block, block_empty())

#define block_fsetpos(_stream, _pos, _sblock, _fblock)                         \
  block_if((fsetpos((_stream), (_pos)) != -1), _sblock, _fblock)

#define block_fsetpos_quietly(_stream, _pos, _block)                           \
  block_fsetpos(_stream, _pos, _block, block_empty())

#define block_ftell(_result, _stream, _sblock, _fblock) {                      \
  long _result = ftell((_stream));                                             \
  block_if((_result != -1), _sblock, _fblock)                                  \
}

#define block_ftell_quietly(_result, _stream, _block)                          \
  block_ftell(_result, _stream, _block, block_empty())

#define block_fread(_ptr, _size, _nmemb, _stream, _sblock, _fblock) {          \
  size_t __block_fread_nmemb = (size_t) (_nmemb);                              \
  size_t __block_fread_result =                                                \
    fread((_ptr), (_size), __block_fread_nmemb, (_stream));                    \
  block_if((__block_fread_result != __block_fread_nmemb), _sblock, _fblock)    \
}

#define block_fread_quietly(_ptr, _size, _nmemb, _stream, _block)              \
  block_fread(_ptr, _size, _nmemb, _stream, _block, block_empty())

#define block_fwrite(_ptr, _size, _nmemb, _stream, _sblock, _fblock) {         \
  size_t __block_fwrite_nmemb = (size_t) (_nmemb);                             \
  size_t __block_fwrite_result =                                               \
    fwrite((_ptr), (_size), (__block_fwrite_nmemb), (_stream));                \
  block_if((__block_fwrite_result != __block_fwrite_nmemb),                    \
    _sblock, _fblock)                                                          \
}

#define block_fwrite_quietly(_ptr, _size, _nmemb, _stream, _block)             \
  block_fwrite(_ptr, _size, _nmemb, _stream, _block, block_empty())

#endif /* BLOCKS_STDIO_H_ */
