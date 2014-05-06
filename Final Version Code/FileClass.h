#ifndef FILE_PARSER_CLASS_IS_INCLUDED
#define FILE_PARSER_CLASS_IS_INCLUDED

#include <stdio.h>

class FileClass
{
protected:
    FILE *fp;
public:
    FileClass();
    ~FileClass();

    int open(char fn[],char mode[]);  // Return 1:Success 0:Fail
	FILE *getFp(void);
    void close(void);
};

#endif