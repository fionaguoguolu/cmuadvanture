#include "ParserClass.h"

ParserClass::ParserClass()
{
    str=NULL;
    nWord=0;
    wordTop=NULL;
    wordLength=NULL;
}

ParserClass::~ParserClass()
{
    CleanUp();
}

int ParserClass::ParseString(int maxNumWords)
{
    int i,state;

    state=0;
    nWord=0;
    for(i=0; str[i]!=0; i++)
    {
        switch(state)
        {
        case 0:
            if(str[i]!=' ' && str[i]!='\t' && str[i]!=',' && str[i]!='\n')
            {
                state=1;
                wordTop[nWord]=i;
                wordLength[nWord]=1;
                nWord++;
            }
            break;
        case 1:
            if(str[i]!=' ' && str[i]!='\t' && str[i]!=',' && str[i]!='\n')
            {
                wordLength[nWord-1]++;
            }
            else
            {
                state=0;
                if(nWord==maxNumWords)
                {
                    goto LOOPOUT;
                }
            }
            break;
        }
    }
LOOPOUT:
    return nWord;
}

void ParserClass::SafeStrCpy(char dst[],char src[],int nLetters,int nLimit) const
{
    int i,stopper;
    if(nLetters<nLimit)
    {
        stopper=nLetters;
    }
    else
    {
        stopper=nLimit;
    }

    for(i=0; i<stopper; i++)
    {
        dst[i]=src[i];
    }
    dst[stopper]=0;
}


void ParserClass::CleanUp(void)
{
    if(NULL!=str)
    {
        delete [] str;
        str=NULL;
    }
    if(NULL!=wordTop)
    {
        delete [] wordTop;
        wordTop=NULL;
    }
    if(NULL!=wordLength)
    {
        delete [] wordLength;
        wordLength=NULL;
    }
    nWord=0;
}

int ParserClass::SetStringAndParse(const char inputStr[])
{
    if(NULL!=inputStr)
    {
        CleanUp();

        int n=strlen(inputStr);
        str=new char [n+1];
        wordTop=new int [n];  // You can make it n/2 safely
        wordLength=new int [n];  // You can make it n/2 safely
        if(NULL!=str && NULL!=wordTop && NULL!=wordLength)
        {
            strcpy(str,inputStr);
            ParseString(n);
            return nWord;
        }
        else
        {
            CleanUp();
        }
    }
    return 0;
}

int ParserClass::GetNumWords(void) const
{
    return nWord;
}

void ParserClass::GetWord(char word[],int maxLength,int nthWord) const
{
    if(NULL!=word)
    {
        if(0<=nthWord && nthWord<nWord)
        {
            SafeStrCpy(word,str+wordTop[nthWord],wordLength[nthWord],maxLength);
        }
        else
        {
            word[0]=0;
        }
    }
}
