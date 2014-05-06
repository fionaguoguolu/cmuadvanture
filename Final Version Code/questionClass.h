#ifndef YYQUESTION_IS_INCLUDED
#define YYQUESTION_IS_INCLUDED

class QuestionClass
{
private:
	const char *qn;
	const char *ans;

	void CopyStringSection(const int startIndex, const int endIndex, const char from[], char to[]);
	void Initialize(void);
	void CleanUp(void);

public:
	QuestionClass(void);
	~QuestionClass(void);
	
	void Set(const char *question, const char *answer);
	void PrintQn(void);
	bool CheckAnswer(const char* ansString);
	const char* GetAnswer(void);
};


#endif

