#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "distractionClass.h"
#include "fssimplewindow.h"
#include "keepAwake.h"
#include "questionClass.h"
#include "textInput.h"
#include "ysglfontdata.h"
#include "yspng.h"



TextString::TextString() : str(NULL)
{
}
/*
TextString::TextString(const char from[]) : str(NULL)
{
    Set(from);
}

TextString::TextString(const TextString &from) : str(NULL)
{
    Set(from.GetPointer());
}
*/
TextString::~TextString()
{
    CleanUp();
}

void TextString::CleanUp()
{
    if(NULL!=str)
    {
        delete [] str;
        str=NULL;
    }
}

void TextString::Set(const char from[])
{
    if(NULL!=from)
    {
        CleanUp();

        const int n=strlen(from);
        str=new char [n+1];
        if(NULL!=str)
        {
            strcpy(str,from);
        }
    }
}

void TextString::Add(const char from[])
{
    if(NULL!=from)
    {
        const int nCurrent=Strlen();
        const int nFrom=strlen(from);

        char *newStr=new char [nCurrent+nFrom+1];
        if(NULL!=newStr)
        {
            strcpy(newStr,GetPointer());
            strcpy(newStr+nCurrent,from);
            if(NULL!=str)
            {
                delete [] str;
            }
            str=newStr;
        }
    }
}

void TextString::Add(const char c)
{
    const int nCurrent=Strlen();

    char *newStr=new char [nCurrent+2];
    if(NULL!=newStr)
    {
        strcpy(newStr,GetPointer());
        newStr[nCurrent]=c;
        newStr[nCurrent+1]=0;
        if(NULL!=str)
        {
            delete [] str;
        }
        str=newStr;
    }
}

void TextString::BackSpace(void)
{
    if(NULL!=str)
    {
        int n=Strlen();
        if(0<n)
        {
            str[n-1]=0;
        }
    }
}

void TextString::DeleteLastControlCode(void)
{
    int n;
    for(n=strlen(str)-1; 0<=n; n--)
    {
        if(0!=isprint(str[n]))
        {
            break;
        }
        str[n]=0;
    }
}
/*
const char *TextString::Fgets(FILE *fp)
{
    if(NULL!=fp)
    {
        CleanUp();

        int firstLine=1;
        const int nBuf=8;
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
        return str;
    }
    return NULL;
}
*/
const char *TextString::GetPointer(void) const
{
    if(NULL!=str)
    {
        return str;
    }
    else
    {
        return "";
    }
}

const int TextString::Strlen(void) const
{
    return strlen(GetPointer());
}

void TextString::Print(void) const
{
    if(NULL!=str)
    {
        printf("%s\n",str);
    }
}

const TextString &TextString::operator=(const TextString &from)
{
    Set(from.GetPointer());
    return *this;
}
/*
void TextInput::SetCaption(const char newCaption[])
{
    caption.Set(newCaption);
}

void TextInput::SetDefaultText(const char defTxt[])
{
    str.Set(defTxt);
}*/

const char *TextInput::GetString(void) const
{
    return str.GetPointer();
}

void TextInput::Draw(void)
{
    glColor3ub(255,255,255);
    /*glRasterPos2d(50,450);
    YsGlDrawFontBitmap20x32(caption.GetPointer());
    glColor3ub(255,255,255);
    */
	glRasterPos2d(50,500);
    YsGlDrawFontBitmap20x32(str.GetPointer());
   
	switch(time(NULL)%2)
    {
    case 0:
        YsGlDrawFontBitmap20x32("_");
        break;
    case 1:
        YsGlDrawFontBitmap20x32("|");
        break;
    }
}

void TextInput::Input(char key)
{
    if (key == '\b')
	{
		str.BackSpace();
	}

    if(0!=key && 0!=isprint(key))
    {
        str.Add(key);
    }

}

void TextInput::Clear(void)
{
	if (str.GetPointer() != NULL)
	{
		str.CleanUp();
	}
}
