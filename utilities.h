
#ifndef utilities_h
#define utilities_h
// utilities.h

const int MINWORDLEN = 4;
const int MAXWORDLEN = 6;

int loadWords(char words[][MAXWORDLEN+1], int maxWords);
int randInt(int min, int max);

#endif /* utilities_h */
