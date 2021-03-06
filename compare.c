#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_WORD_SIZE 128

int resetptr(unsigned char * ptr) {
    unsigned char *nullb = "\000\000\000\000\000\000\000\000\000"
                           "\000\000\000\000\000\000\000\000\000"
                           "\000\000\000\000\000\000\000\000\000"
                           "\000\000\000\000\000\000\000\000\000"
                           "\000\000\000\000\000\000\000\000\000"
                           "\000\000\000\000\000\000\000\000\000"
                           "\000\000\000\000\000\000\000\000\000"
                           "\000\000\000\000\000\000\000\000\000";
    memcpy(ptr, nullb, MAX_WORD_SIZE);
}

int main( int argc, char **argv)
{
   unsigned char *file1 = argv[1];
   unsigned char *file2 = argv[2];

   unsigned char words[2096][MAX_WORD_SIZE];
   unsigned char words2[2096][MAX_WORD_SIZE];
   unsigned int index;
   int fp1 = open(file1, O_RDONLY);
   unsigned char cursor = 0x00;
   unsigned char *current = (unsigned char *) malloc(sizeof(unsigned char) * MAX_WORD_SIZE);
   resetptr(current);
    int row = 0;
   int total = 0;
   int s = 0;
   while(0 != read(fp1, &cursor, 1)) {
     switch (cursor) {
        case 0xa:
           memcpy(&words[row], &current, s);
           resetptr(current);
             row++;
           s = 0;
           break;
        case 0x00:
           break;
        default:
           current[s++] = cursor;
             if (s >= MAX_WORD_SIZE) {
                 dprintf(2, "reaching buffer limit\n");
             }
           break;
     }
   }

   free(current);
   close(fp1);
   int word_length = index;
    index = 0;
   //qsort (words, 134, sizeof (const char *), compare);
   //qsort (words2, 4096, sizeof (const char *), compare);
   int fp2 = open(file2, O_RDONLY);
   s = 0;
   cursor = 0x00;
   row = 0;
   resetptr(current);
   while(0 != read(fp2, &cursor, 1)) {
        switch (cursor) {
           case 0xa:
               memcpy(&words2[row], &current, s);
                resetptr(current);
                row++;
                s = 0;
              break;
           case 0x00:
              break;
           default:
              current[s++] = cursor;
                if (s >= MAX_WORD_SIZE) {
                    dprintf(2, "reaching buffer limit\n");
                }
              break;
        }
   }
    int word2_length = index;
   close(fp2);
   int match = 0;
   for (int x = 0; x < word_length; x++) {
        for (int y = 0; y < word2_length; y++) {
            if (memcmp(words[x], words2[y], 1) == 0) {
                match++;
            }
        }
   }

   printf("matches %d from\n",  match);
}
