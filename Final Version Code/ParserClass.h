#ifndef PARSER_CLASS_IS_INCLUDED
#define PARSER_CLASS_IS_INCLUDED

#include <string.h>

class ParserClass
{
protected:
    char *str;

    int nWord;
    int *wordTop,*wordLength;

    int ParseString(int maxNumWords);
    void SafeStrCpy(char dst[],char src[],int nLetters,int nLimit) const;

public:
    ParserClass();
    ~ParserClass();

    void CleanUp(void);
    int SetStringAndParse(const char str[]);
    int GetNumWords(void) const;
    void GetWord(char word[],int maxLength,int nthWord) const;
};

#endif