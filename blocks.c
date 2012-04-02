//============================================================================
// Name        : blocks.cpp
// Author      : Karim DRIDI
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <blocks/blocks.h>

int check_block_empty(int value) {
  block_empty();
  return value;
}

int check_block_compose(int value) {
  int result = value - 2;
  block_compose( {result++;}, {result++;});
  return result;
}

int check_block_if(int value) {
  int result = 0;
  int is_even = value % 2;
  if (is_even) {
    result = value - 2;
  } else {
    result = value - 1;
  }
  block_if(is_even, {result += 2;}, {result += 1;});
  return result;
}

int check_block_if_true(int value) {
  int result = 0;
  int is_even = value % 2;
  if (is_even) {
    result = value - 2;
  } else {
    result = value - 1;
  }
  block_if_true(is_even, {result += 1;});
  return result + 1;
}

int check_block_assign(int value) {
  int result = -1;
  block_assign(result, check_block_if_true(value));
  return result;
}

int check_block_return(int value) {
  int offset = 10;
  block_return(int, result, check_block_assign(value - offset), {
    result += check_block_if_true(offset);
  });
}

int check_block_fclose(int value) {
  int offset = 5;
  int result = value - offset;
  FILE *file = NULL;
  FILE **file_ptr = &file;
  block_fclose(*file_ptr, {
    result -= offset;
  }, {
    result += offset;
  });
  return result;
}

int check_block_fclose_quietly(int value) {
  int offset = 5;
  int result = value;
  FILE *file = NULL;
  FILE **file_ptr = &file;
  block_fclose_quietly(*file_ptr, {
    result -= offset;
  });
  return result;
}

int main(void) {
  int result = EXIT_SUCCESS;

#define run(function) {                                                        \
  int local_result = EXIT_SUCCESS;                                             \
  for (int i = __LINE__ - 10; i < __LINE__; i++) {                             \
    int expected = i + 1;                                                      \
    int actual = i;                                                            \
    block_if_true((expected != function(++actual)), {                          \
      block_warn(">>>>>>  Failure: " #function);                               \
      local_result = EXIT_FAILURE;                                             \
      break;                                                                   \
    });                                                                        \
  }                                                                            \
  if(local_result == EXIT_FAILURE) {                                           \
    result = EXIT_FAILURE;                                                     \
  } else {                                                                     \
    block_info("        Success: " #function);                                 \
  }                                                                            \
}

  run(check_block_empty);
  run(check_block_compose);
  run(check_block_if);
  run(check_block_if_true);
  run(check_block_assign);
  run(check_block_return);
  run(check_block_fclose);
  run(check_block_fclose_quietly);

#undef run

  return result;
}
