#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "textsring.h"

GenericCharArray::GenericCharArray()
{
    temp=new int[21];
    lng=0;
    dat=NULL;
}

GenericCharArray::~GenericCharArray()
{
    CleanUp();
}

void GenericCharArray::CleanUp(void)
{
    lng=0;
    if(NULL!=dat)
    {
        delete [] dat;
        dat=NULL;
    }
    if(NULL!=temp)
    {
        delete [] temp;
        temp=NULL;
    }
    
}

void GenericCharArray::Resize(int newLng)
{
    if(0<newLng)
    {
        char *newDat=new char [newLng];
        if(NULL!=newDat)
        {
            int i;
            for(i=0; i<newLng && i<lng; i++)
            {
                newDat[i]=dat[i];
            }
            if(NULL!=dat)
            {
                delete [] dat;
            }
            lng=newLng;
            dat=newDat;
        }
    }
    else
    {
        CleanUp();
    }
}

int GenericCharArray::GetSize(void) const
{
    return lng;
}

char *GenericCharArray::GetPointer(void)
{
    return dat;
}

const char *GenericCharArray::GetPointer(void) const
{
    return dat;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TextStringC::TextStringC()
{
    
}

TextStringC::TextStringC(const char from[])
{
    Set(from);
}

TextStringC::TextStringC(const TextStringC &from)
{
    Set(from.GetPointer());
}

TextStringC::~TextStringC()
{
    CleanUp();
}

void TextStringC::Set(const char from[])
{
    if(NULL!=from)
    {
        CleanUp();

        const int n=strlen(from);
        Resize(n+1);
        if(GetSize()==n+1)
        {
            strcpy(GetPointer(),from);
        }
    }
}

void TextStringC::Add(const char from[])
{
    if(NULL!=from)
    {
        const int nCurrent=Strlen();
        const int nFrom=strlen(from);

        Resize(nCurrent+nFrom+1);
        if(GetSize()==nCurrent+nFrom+1)
        {
            strcpy(GetPointer()+nCurrent,from);
        }
    }
}

void TextStringC::Add(const char c)
{
    const int nCurrent=Strlen();

    Resize(nCurrent+2);
    if(GetSize()==nCurrent+2)
    {
        char *str=GetPointer();
        str[nCurrent]=c;
        str[nCurrent+1]=0;
    }
}

void TextStringC::BackSpace(void)
{
    char *str=GetPointer();
    if(NULL!=str)
    {
        int n=Strlen();
        if(0<n)
        {
            str[n-1]=0;
        }
    }
}

void TextStringC::DeleteLastControlCode(void)
{
    int n;
    char *str=GetPointer();
    for(n=strlen(str)-1; 0<=n; n--)
    {
        if(0!=isprint(str[n]))
        {
            break;
        }
        str[n]=0;
    }
}

const char *TextStringC::Fgets(FILE *fp)
{
    if(NULL!=fp)
    {
        CleanUp();

        int firstLine=1;
        const int nBuf=256;
        char buf[nBuf+1];

        buf[nBuf]=0;
        for(;;)
        {
            if(NULL==fgets(buf,nBuf,fp))
            {
                if(0!=firstLine)
                {
                    return NULL;
                }
                else
                {
                    break;
                }
            }
            else
            {
                firstLine=0;
                Add(buf);

                int nChar=strlen(buf);
                if(buf[nChar-1]=='\n' || buf[nChar-1]=='\a')
                {
                    break;
                }
            }
        }

        DeleteLastControlCode();
        return GetPointer();
    }
    return NULL;
}

char *TextStringC::GetPointer(void)
{
    char *str=GenericCharArray::GetPointer();
    if(NULL!=str)
    {
        return str;
    }
    else
    {
        return "";
    }
}

const char *TextStringC::GetPointer(void) const
{
    const char *str=GenericCharArray::GetPointer();
    if(NULL!=str)
    {
        return str;
    }
    else
    {
        return "";
    }
}

const int TextStringC::Strlen(void) const
{
    return strlen(GetPointer());
}

void TextStringC::Print(void) const
{
    printf("%s\n",GetPointer());
}

const TextStringC &TextStringC::operator=(const TextStringC &from)
{
    Set(from.GetPointer());
    return *this;
}


int TextStringC::check (void)
{
    char *temp;
    temp = GetPointer();
    
    for (int i=0;i<21;i++)
    {
        if (temp[i]=='X'||temp[i]=='x'||temp[i]=='/'||temp[i]==' '||temp[i]=='-'||temp[i]=='0'||temp[i]=='1'||temp[i]=='2'||temp[i]=='3'||temp[i]=='4'||temp[i]=='5'||temp[i]=='6'||temp[i]=='7'||temp[i]=='8'||temp[i]=='9')
        {
            continue;
        }else
            return 1;
        
    }
    return 0; 
}

int *TextStringC::transfer(void)
{
    
    int *temp;
    char *tempstr;
    temp= new int[21];
    tempstr = GetPointer();
    for( int i=0;i<21;i++)
    {
        if (tempstr[i]=='0'||tempstr[i]=='1'||tempstr[i]=='2'||tempstr[i]=='3'||tempstr[i]=='4'||tempstr[i]=='5'||tempstr[i]=='6'||tempstr[i]=='7'||tempstr[i]=='8'||tempstr[i]=='9')
        {
            temp[i]=tempstr[i]-'0';
        }else if (tempstr[i]=='X'||tempstr[i]=='x')
        {
            temp[i]=10;
        }else if (tempstr[i]==' ')
        {
            temp[i]=0;
        }else if (tempstr[i]=='-')
        {
            temp[i]=0;
        }else if (tempstr[i]=='/')
        {
            temp[i]=10-temp[i-1];
        };
        
    }
    
    return temp;
}

void TextStringC::Getscore(void)
{
    
    
    
    
}



