#include "FileClass.h"

FileClass::FileClass()
{
    fp=NULL;
}
FileClass::~FileClass()
{
    if(fp!=NULL)
    {
        fclose(fp);
        fp=NULL;
    }
}
int FileClass::open(char fn[],char mode[])
{
    if(fp==NULL)
    {
        fp=fopen(fn,mode);
        if(fp!=NULL)
        {
            return 1;
        }
    }
    return 0;
}
FILE *FileClass::getFp(void)
{
    return fp;
}
void FileClass::close(void)
{
    if(fp!=NULL)
    {
        fclose(fp);
        fp=NULL;
    }
}