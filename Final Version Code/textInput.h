#ifndef TEXTINPUTCLASS_H_IS_INCLUDED
#define TEXTINPUTCLASS_H_IS_INCLUDED

class TextString
{
protected:
    char *str;

public:
    TextString();
    //TextString(const char from[]);
    //TextString(const TextString &str);
    ~TextString();
    void CleanUp();
    void Set(const char from[]);
    void Add(const char from[]);
    void Add(const char c);
    void BackSpace(void);
    //const char *Fgets(FILE *fp);
    void DeleteLastControlCode(void);
    const char *GetPointer(void) const;
    const int Strlen(void) const;
    void Print(void) const;
    const TextString &operator=(const TextString &from);
};

class TextInput
{
protected:
    //TextString caption;
    TextString str;
public:
    //void SetCaption(const char newCaption[]);
    //void SetDefaultText(const char defTxt[]);
    const char *GetString(void) const;
    void Input(char key);
    void Draw(void);
	void Clear(void);
};

#endif