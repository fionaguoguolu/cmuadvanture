//
//  textsring.h
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/16.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#ifndef TEST_textsring_h
#define TEST_textsring_h

class GenericCharArray
{
private:
    int lng;
    char *dat;
    
    GenericCharArray(const GenericCharArray &copyFrom){}
    const GenericCharArray &operator=(const GenericCharArray &copyFrom){return *this;}
public:
    int *temp;
    GenericCharArray();
    ~GenericCharArray();
    void CleanUp(void);
    
    void Resize(int newLng);
    int GetSize(void) const;
protected:
    char *GetPointer(void);
    const char *GetPointer(void) const;
};


class TextStringC : public GenericCharArray
{
public:
    TextStringC();
    TextStringC(const char from[]);
    TextStringC(const TextStringC &str);
    ~TextStringC();
    
    void Set(const char from[]);
    void Add(const char from[]);
    void Add(const char c);
    void BackSpace(void);
    const char *Fgets(FILE *fp);
    void DeleteLastControlCode(void);
    char *GetPointer(void);
    const char *GetPointer(void) const;
    const int Strlen(void) const;
    void Print(void) const;
    const TextStringC &operator=(const TextStringC &from);
    int check (void);
    int *transfer(void);
    void Getscore(void);
};



#endif
