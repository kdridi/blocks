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

int check_block_empty(int argc, char *argv[], int value) {
  block_empty();
  return value;
}

int check_block_compose(int argc, char *argv[], int value) {
  int result = value - 2;
  block_compose( {result++;}, {result++;});
  return result;
}

int check_block_if(int argc, char *argv[], int value) {
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

int check_block_if_true(int argc, char *argv[], int value) {
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

int check_block_assign(int argc, char *argv[], int value) {
  int result = -1;
  block_assign(result, check_block_if_true(argc, argv, value));
  return result;
}

int check_block_return(int argc, char *argv[], int value) {
  int offset = 10;
  block_return(int, result, check_block_assign(argc, argv, value - offset), {
    result += check_block_if_true(argc, argv, offset);
  });
}

int check_block_fclose(int argc, char *argv[], int value) {
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

int check_block_fclose_quietly(int argc, char *argv[], int value) {
  int offset = 5;
  int result = value;
  FILE *file = NULL;
  FILE **file_ptr = &file;
  block_fclose_quietly(*file_ptr, {
    result -= offset;
  });
  return result;
}

int check_block_fopen(int argc, char *argv[], int value) {
  int result = value - argc;
  block_fopen(file, NULL, "rb", {
    result -= argc;
  }, {
    result += argc;
  });
  return result;
}


int check_block_fopen_quietly(int argc, char *argv[], int value) {
  int result = value - argc;
  block_fopen_quietly(file, NULL, "rb", {
    result += argc;
    block_warn("check_block_fopen_quietly: can't reach this part!");
  });
  block_fopen_quietly(file, argv[0], "rb",
    block_fclose_quietly(file, {
	  result += argc;
    });
  );
  return result;
}

#ifndef __STRICT_ANSI__

int check_block_fdopen(int argc, char *argv[], int value) {
  int result = value - argc;
  block_fdopen(file, 0, "rb", {
    result -= argc;
  }, {
    result += argc;
  });
  return result;
}

int check_block_fdopen_quietly(int argc, char *argv[], int value) {
  int result = value - argc;
  block_fdopen_quietly(file, 0, "rb", {
    result += argc;
    block_warn("check_block_fdopen_quietly: can't reach this part!");
  });
  return result + argc;
}

#endif


int check_block_freopen(int argc, char *argv[], int value) {
  int result = value - argc;
  block_file_with_path(file, argv[0], "rb", {
    block_freopen(file, argv[0], "rb", {
      result += argc;
    }, {
      result -= argc;
      block_warn("check_block_freopen: can't reach this part 01!");
    })
  })
  return result;
}

int check_block_freopen_quietly(int argc, char *argv[], int value) {
  int result = value - argc;
  block_file_with_path(file, argv[0], "rb", {
    block_freopen_quietly(file, argv[0], "rb", {
      result += argc;
    })
  })
  return result;
}

int check_block_file_length(int argc, char *argv[], int value) {
  int file_length = atoi(argv[1]);
  int result = value - file_length;
  block_file_with_path(file, argv[0], "rb", {
    block_file_length(length, file, {
      result += length;
    })
  })
  return result;
}

int main(int argc, char *argv[]) {
  int result = EXIT_SUCCESS;

  printf("size: %d\n", atoi(argv[1]));

#define run(function) {                                                        \
  int local_result = EXIT_SUCCESS;                                             \
  for (int i = __LINE__ - 10; i < __LINE__; i++) {                             \
    int expected = i + 1;                                                      \
    int actual = i;                                                            \
    block_if_true((expected != function(argc, argv, ++actual)), {              \
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
  run(check_block_fopen);
  run(check_block_fopen_quietly);
#ifndef __STRICT_ANSI__
  run(check_block_fdopen);
  run(check_block_fdopen_quietly);
#endif
  run(check_block_freopen);
  run(check_block_freopen_quietly);
  run(check_block_file_length);

#undef run

  return result;
}
