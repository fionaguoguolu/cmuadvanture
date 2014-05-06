//
//  StringParser.h
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/14.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#ifndef __TEST__StringParser__
#define __TEST__StringParser__

#include <iostream>
class StringParser
{
protected:
    char *str;
    
    int nWord;
    int *wordTop,*wordLength;
    
    int ParseString(int &nWord,int wordTop[],int wordLength[],char str[],int maxNumWords);
    void SafeStrCpy(char dst[],char src[],int nLetters,int nLimit) const;
    
public:
    StringParser();
    ~StringParser();
    
    void CleanUp(void);
    int SetStringAndParse(const char str[]);
    int GetNumWords(void) const;
    void GetWord(char word[],int maxLength,int nthWord) const;
};


#endif /* defined(__TEST__StringParser__) */
