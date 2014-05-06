#ifndef CAD_HW_H_IS_INCLUDED
#define CAD_HW_H_IS_INCLUDED



class CADCLASS; template <class T> 
class DoublyLinkedListItem; class Lines;

class Lines
{
public:
	int x,y;
};
class CADCLASS
{	
public:
	YsRawPngDecoder BackgroundPng[3],AnswerPng[3],PenPng,EraserPng,CheckPng;
	DoublyLinkedListItem<Lines> *newline,*ptr;
	int level,MapX[800],MapY[600];
	static const int Draw=0,Erase=1,ShowWinStats=2, //For LineState
		Uncalled=0,Calling=1,Proceed=2;  //For ConfirmationWindow
	int n[3],LineState,ConfirmationWindow;  //n:number of lines
	int lb,mb,rb,mx,my;
	int idx,MouseEvent,MouseClick,ShowAnswer,terminate;
	int WinInfo[12]; //0:score;1:#of wrong;2:tot#;3:redundent
	DoublyLinkedListItem<Lines> **head,**tail;
	
	CADCLASS();
	~CADCLASS();
	int CADMain();
	int ReadBackground();
	void DrawBackground();
	int CheckWinLevel();
	void CheckMouseEvent();
	void AddLines();
	void DrawLines();
	void EraseLines();
	double CalculateDistance(double x1,double y1,double x2,double y2);
	void PreventLeak();
	void DrawStats();
	void DeleteLineMember();
	void CleanUp();
};
template <class T>
class DoublyLinkedListItem
{
public:
    T lines;
    DoublyLinkedListItem<T> *prev,*next;
    DoublyLinkedListItem();
	~DoublyLinkedListItem();
};

template <class T>
DoublyLinkedListItem<T>::DoublyLinkedListItem()
{
    prev=NULL;
    next=NULL;
}
template <class T>
DoublyLinkedListItem<T>::~DoublyLinkedListItem()
{
	prev=NULL;
	next=NULL;
}
#endif