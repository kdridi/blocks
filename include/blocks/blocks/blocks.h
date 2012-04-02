//==============================================================================
// Name        : <blocks/blocks.h>
// Author      : Karim DRIDI
// Version     : 0.1
// Copyright   : Private
// Description : Block macros
//==============================================================================

#ifndef BLOCKS_BLOCKS_H
#define BLOCKS_BLOCKS_H

#define block_empty() {                                                        \
}

#define block_compose(_block1, _block2) {                                      \
  _block1                                                                      \
  _block2                                                                      \
}

#define block_if(_condition, _tblock, _fblock) {                               \
  if(_condition)                                                               \
    _tblock                                                                    \
  else                                                                         \
    _fblock                                                                    \
}

#define block_if_true(_condition, _block)                                      \
  block_if(_condition, _block, block_empty())

#define block_assign(_variable, _value) {                                      \
  (_variable) = (_value);                                                      \
}

#define block_return(_type, _result, _default, _block) {                       \
  _type _result = (_default);                                                  \
  _block                                                                       \
  return _result;                                                              \
}

#define block_warn(_message) {                                                 \
  fprintf(stderr, "WARN[%s][%d]: %s\n", __FILE__, __LINE__, (_message));       \
}

#define block_info(_message) {                                                 \
  fprintf(stderr, "INFO[%s][%d]: %s\n", __FILE__, __LINE__, (_message));       \
}

#endif /* BLOCKS_BLOCKS_ */
