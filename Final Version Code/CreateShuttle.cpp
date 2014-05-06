//
//  CreateShuttle.cpp
//  TEST
//
//  Created by Hsu Tsung Chun on 12/11/13.
//  Copyright (c) 2012年 Hsu Tsung Chun. All rights reserved.
//

#include "CreateShuttle.h"

CreateShuttle::CreateShuttle()
{
	node=NULL;
    
}

CreateShuttle::~CreateShuttle()
{
    
}
void CreateShuttle::move(int,const int & step)
{
    int Xchange=(node+step)->x;
    int Ychange=(node+step)->y;
    
    busfront.Decode("busfront1.PNG");
    busfront.Flip();
    busside.Decode("busside.PNG");
    busside.Flip();
    
    if ((node+step)->z==0)
    {
        //直的
        glRasterPos2d(Xchange,(double)(busfront.hei-1)+Ychange);
        glDrawPixels(busfront.wid,busfront.hei,GL_RGBA,GL_UNSIGNED_BYTE,busfront.rgba);
    }else if ((node+step)->z==1)
    {
        //橫的
        glRasterPos2d(Xchange,(double)(busside.hei-1)+Ychange);
        glDrawPixels(busside.wid,busside.hei,GL_RGBA,GL_UNSIGNED_BYTE,busside.rgba);
    }
    

    
    /*
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
    if ((node+step)->z==0)
    {
        //直的
        glVertex2i(Xchange,Ychange);
        glVertex2i(Xchange+20,Ychange);
        glVertex2i(Xchange+20,Ychange-40);
        glVertex2i(Xchange,Ychange-40);
    }else if ((node+step)->z==1)
    {
        //橫的
        glVertex2i(Xchange,Ychange);
        glVertex2i(Xchange+40,Ychange);
        glVertex2i(Xchange+40,Ychange-20);
        glVertex2i(Xchange,Ychange-20);
    }
    glEnd();
     */
    
}

int CreateShuttle::checkhome(const int & step)
{
    int X=(node+step)->x;
    int Y=(node+step)->y;
    if (X>675 && X<800 && Y<600 && Y>490)
        return 1;
    
	return 0;

}

void CreateShuttle::action(int key,int & step, int & state)
{
    
    move(key,step);
    switch (state)
    {
        case 1:
            move(key,step);
            step++;
            if(checkhome(step)==1)
            {
                state=2;
            }
            break;
        case 0:
            move(key,step);
            step++;
            if(checkhome(step)==1)
            {
                state=3;
            }
            break;
        case 3:
            move(key,step);
            
            
    }
}
void CreateShuttle::Set(void)
{




}
void CreateShuttle::CleanUp(void)
{
	if(NULL!=node)
	{
		delete [] node;
		node=NULL;
	}
}
void CreateShuttle::AllocNode(int n)
{
	if(NULL!=node)
	{
		delete [] node;
		node=NULL;
	}
	nNode=n;
	node=new Node2D[n];
}
int CreateShuttle::Writefile(FILE *fp,char *str)
{
    //FILE *fp=fopen("123.txt","w");
    
    //fprintf(fp,"%s","Number 300\n");
    fprintf(fp,"%s",str);
             


	return 0;
    
}

int CreateShuttle::Readfile(const char fn[])
{
    FILE *fp=fopen(fn,"r");
    if(NULL!=fp)
    {
        CleanUp();
        int nNodeRead=0;
        StringParser parser;
        
        char str[256];
        while (NULL!=fgets(str,255,fp))
        {
            parser.SetStringAndParse(str);
            if(0<parser.GetNumWords())
			{
				char word[256],param[256];
				parser.GetWord(word,255,0);
                
				if(0==strcmp("N",word) && 4<=parser.GetNumWords())
				{
					double x,y,z;
					parser.GetWord(param,255,2);
					x=atof(param);
					parser.GetWord(param,255,3);
					y=atof(param);
                     parser.GetWord(param,255,1);
					z=atof(param);
                    
					if(nNodeRead<nNode)
					{
                        node[nNodeRead].x=x;
                        node[nNodeRead].y=y;
                        node[nNodeRead].z=z;
                        //cout<<"nNodeRead is "<< nNodeRead<<endl<<node[nNodeRead].z<<" "<<node[nNodeRead].x<<" ";
                        //cout<<node[nNodeRead].y<<endl;
                        ++nNodeRead;
					}
                    

				}
                 else if(0==strcmp("Number",word))
				{
					parser.GetWord(param,255,1);
					const int n=atoi(param);
					//printf("NNode=%d\n",n);
					AllocNode(n);
				}

			}
		}
        
        
        
        
        
		//printf("NNode %d Read %d\n",nNode,nNodeRead);
        
		fclose(fp);
		return 1;
	}
	return 0;
}