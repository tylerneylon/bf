// bf.c
//
// A brainf*ck interpreter.
//
// Not written for efficiency, by the way.
//
// I use ints as my boolean type because
// it's more honest about what the machine is
// doing with types. Also C didn't originally
// have a built-in boolean type.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*******************************************\
  Globals.
\*******************************************/

// For now we have a fixed allowed src size of 1MB.
char src[1024 * 1024];
int srclen = 0;
int curinst = 0;

// Data size fixed at 1MB.
char data[1024 * 1024];
int curdata = 0;


/*******************************************\
  Debug tools.
\*******************************************/

int stepsdone = 0;

void printstate() {
  const char *plural = (stepsdone == 1 ? "" : "s");
  fprintf(stderr, "--- %d step%s done ---\n", stepsdone++, plural);
  fprintf(stderr, "Source point:\n");
  for (int i = 0; i < srclen; ++i) fputc(src[i], stderr);
  fprintf(stderr, "\n");
  for (int i = 0; i < curinst; ++i) fputc(' ', stderr);
  fprintf(stderr, "^\n");
  fprintf(stderr, "Data:\n");
  const int numdata = 20;
  for (int i = 0; i < numdata; ++i) {
    fprintf(stderr, i ? ", " : "  ");
    fprintf(stderr, "%3d", data[i]);
  }
  fprintf(stderr, ", ... \n");
  if (curdata < numdata) {
    for (int i = 0; i < curdata; ++i) {
      fprintf(stderr, "     ");
    }
    fprintf(stderr, "    ^\n");
  } else {
    fprintf(stderr, " (data pointer is %d)\n", curdata);
  }
}


/*******************************************\
  File & execution functions.
\*******************************************/

void readfile(char *filename) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Couldn't open file '%s'\n", filename);
    exit(1);
  }
  int c;
  while ((c = fgetc(fp)) != EOF) {
    if (strchr("+-<>,.[]", c)) src[srclen++] = c;
  }
}

// Expects dir to be -1 for backwards, 1 for forwards.
void jump(int dir) {
  int bracketdepth = 1;
  char inwardchar = (dir == 1 ? '[' : ']');
  char outwardchar = (dir == 1 ? ']' : '[');
  while (curinst < srclen) {
    curinst += dir;
    char inst = src[curinst];
    if (inst == inwardchar) bracketdepth++;
    if (inst == outwardchar) {
      bracketdepth--;
      if (bracketdepth == 0) return;
    }
  }
}

// Returns 0 when no more instructions remain.
int step(int debugmode) {
  if (debugmode) printstate();
  switch (src[curinst]) {
    case '+':
      data[curdata]++;
      break;
    case '-':
      data[curdata]--;
      break;
    case '<':
      if (curdata > 0) curdata--;
      break;
    case '>':
      curdata++;
      break;
    case '.':
      putchar(data[curdata]);
      break;
    case ',':
      {
        int inchar = getchar();
        if (inchar == EOF) inchar = 0;
        data[curdata] = inchar;
      }
      break;
    case '[':
      if (data[curdata] == 0) jump(1);
      break;
    case ']':
      if (data[curdata]) jump(-1);
      break;
  }
  curinst++;
  return (curinst < srclen);
}


/*******************************************\
  Main.
\*******************************************/

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage:\n");
    printf(" %s <bf_filename>\t\tExecute <bf_filename>\n", argv[0]);
    printf(" %s -d <bf_filename>\t\tExecute with debug info on stderr\n", argv[0]);
    exit(2);
  }
  int debugmode = 0;
  char *filename = argv[1];

  if (strcmp(argv[1], "-d") == 0) {
    debugmode = 1;
    filename = argv[2];
  }

  memset(data, 0, sizeof(data));
  readfile(filename);
  while (step(debugmode));

  return 0;
}
