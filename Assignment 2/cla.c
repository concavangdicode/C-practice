// How to use command-line arguments, by example

#include <stdio.h>

// We will explain a declaration like "char *argv[]" later
int main(int argc, char *argv[]) {

  // Assume we would like a single command-line argument containing a filename
  if (argc != 2) {
    // Error:
    fprintf(stderr, "Expected usage: %s filename\n", argv[0]);

    // Just for fun, here's what they did enter (note where the array ends):
    // printf("argc: %d\n", argc);
    // for (int i = 0; i < argc; i++) {
    //   printf("argv[%d]: %s\n", i, argv[i]);
    // }
  } else {
    // OK:
    printf("You entered '%s' as a filename.\n", argv[1]);
    
    // Now you can open the selected file with fopen(argv[1], "r")
    // ...
  }
  
  return 0;
}