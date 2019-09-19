#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\AddEllipseAction.h"
#include "Actions\AddRhombusAction.h"
#include "Actions\SelectAction.h"
#include "Actions\SwitchToPlayAction.h"
#include "Actions\SwitchToDrawAction.h"
#include "Actions\SaveAction.h"
#include "Actions\SaveTypeAction.h"
#include "Actions\delfigAction.h"
#include "GUI\UI_Info.h"
#include "Actions\LoadAction.h"
#include "Figures\CFigure.h"
#include "Figures\CEllipse.h"
#include "Figures\CLine.h"
#include "Figures\CRectangle.h"
#include "Figures\CRhombus.h"
#include "Figures\CTri.h"
#include "Actions\BringFrontAction.h"
#include "Actions\SendBackAction.h"
#include "Actions\VoiceAction.h"
#include "Actions\CopyFigAction.h"
#include "Actions\CutAction.h"
#include "Actions\PasteAction.h"
#include "Actions\ChngDrawAction.h"
#include "Actions\ChngFillAction.h"
#include "Actions\TypeAction.h"
#include "Actions\ColourAction.h"
#include <time.h>
#define MAXSPACE 25
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	SelectedFig = NULL;
	Clipboard=NULL;
	Voice = false;
	FigCount = 0;
	count=0; 
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		case DRAW_LINE:
			///create AddLineAction here
			pAct = new AddLineAction(this);
			break;
		case DRAW_ELLIPSE:
			pAct = new AddEllipseAction(this);
			break;
		case DRAW_RHOMBUS:
			pAct = new AddRhombusAction(this);
			break;
		case DRAW_TRI:
			pAct = new AddTriAction(this);
			break;
		case SELECT:
			pAct = new SelectAction(this);
			break;
		case DRAWING_AREA:
			if (SelectedFig != NULL)
			{
				SelectedFig->SetSelected(false);
				SelectedFig = NULL;
			}
			pOut->ClearStatusBar();
			break;
		case TO_PLAY:
			pAct = new SwitchToPlayAction(this);
			break;
		case TO_DRAW:
			pAct = new SwitchToDrawAction(this);
			break;
		case DEL:
			pAct=new delfigAction (this);
			break;
		case COPY:
			pAct=new CopyFigAction(this);
			break;
		case CUT:
			pAct=new CutAction(this);
			break;
		case PASTE:
			pAct=new PasteAction(this);
			break;
		case LOAD:
			pAct= new LoadAction (this);
			break;
		case SAVE:
			pAct = new SaveAction(this);
			break;
		case SAVE_BY_TYPE:
			pAct = new SaveTypeAction(this);
			break;
		case CHNG_DRAW_CLR:
			pAct = new ChngDrawAction(this);
			break;
		case CHNG_FILL_CLR:
			pAct = new ChngFillAction(this);
			break;
		case BK:
			pAct = new SendBackAction(this);
			break;
		case FT:
			pAct = new BringFrontAction(this);
			break;
		case VC:
			pAct = new VoiceAction(this);
			break;
		case PICK_TYPE:
			pAct = new TypeAction(this);
			break;
		case PICK_COLOR:
			pAct = new ColourAction(this);
			break;
		case EXIT:
			break;
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	for (int i = FigCount - 1; i >= 0; i--)
		if(FigList[i]->check(x, y))
			return FigList[i];
		
	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}
void ApplicationManager::deletallfig()
{
	for (int i = FigCount - 1; i >= 0; i--)
		{
			delete FigList[i];
			FigList[i]=NULL;
			FigCount--;
		}	
}
void ApplicationManager::SelectFig(CFigure* pFig)
{
	SelectedFig = pFig;
}

CFigure *ApplicationManager::GetSelected()
{
	return SelectedFig;
}

void ApplicationManager::setVoice(bool b)
{
	Voice = b;
}

bool ApplicationManager::getVoice()
{
	return Voice;
}

void ApplicationManager::SaveAll(ofstream &OutFile)
{
	OutFile << StringColor(UI.DrawColor) + "    "  + StringColor(UI.FillColor) + "\n";
	OutFile << to_string(FigCount) + "\n";
	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(OutFile);
	}
}

CFigure* ApplicationManager::GetRandomFigure(ActionType act) const
{

	CFigure* RandomFig;
	int randomindex;
	GfxInfo info;
	if(act==PICK_TYPE)
	{
		if(FigCount==0)
			return NULL;
		randomindex=rand()%FigCount;
		RandomFig=FigList[randomindex];
		return RandomFig;
	}

	if(act==PICK_COLOR)
	{
		if(FigCount==0)
			return NULL;
		int i;
		for( i=0;i<FigCount;i++)
		{
			info = FigList[i]->GetGfx();
			if(info.isFilled==true)
				break;
		}
		if(i==FigCount)		//this means that there is no Filled shapes in the Figlist
			return NULL;
		do
		{
		randomindex=rand()%FigCount;
		RandomFig=FigList[randomindex];
		info = FigList[randomindex]->GetGfx();
		if(info.isFilled)
			return RandomFig;
		}while(true);
		
	}
}

int ApplicationManager:: RandomFigureCount(ActionType act,CFigure* Rand)
{
	int Nu=0;
	if(act==PICK_TYPE)
	{
		for(int i=0; i<FigCount ;i++)
			if(FigList[i]->Type() == Rand->Type())
				Nu++;
		return Nu;
	}
	if(act==PICK_COLOR)
	{
		for(int j=0;j<FigCount;j++)
		{
			if((FigList[j]->GetGfx().FillClr==Rand->GetGfx().FillClr) && FigList[j]->GetGfx().isFilled)
				Nu++;
		}
		return Nu;
	}
	return Nu;
}


void ApplicationManager::LoadAll(ifstream &file,string filename)
{
	Output* pOut =GetOutput();
	Input* pIn = GetInput();
	string STRING[200];
	int i=0;
	bool empty=false; 
        while(!file.eof()) // To get you all the lines.
        {
			
			getline(file,STRING[i]); // Saves the line in STRING.
			if (i<2)
			{
				i++;
				continue;
			}
			if(STRING[2]=="")
			{
				pOut->PrintMessage("this file is empty    press ENTER to contiue");
				pIn->GetSrting(pOut);
				pOut->ClearStatusBar();
				empty=true;
				break;
			}
		 if (!empty)
		 {
			 deletallfig();
			 pOut->ClearDrawArea();
			 empty=true;
		 }
		   if (STRING[i].find("LINE")!=-1)
				{
				fig[count]=new CLine;
				fig[count]->Load(filename,i);
				AddFigure(fig[count]);
				count++;

		   }
		   else if(STRING[i].find("RECT")!=-1)
			{
				fig[count]=new CRectangle;
				fig[count]->Load(filename,i);
				AddFigure(fig[count]);
				count++;
		   }
		  else if(STRING[i].find("TRIANG")!=-1)
		   {
				fig[count]=new CTri;
				fig[count]->Load(filename,i);
				AddFigure(fig[count]);
				count++;
		   }
	
		  else if(STRING[i].find("ELLIPSE")!=-1)
			{	
				fig[count] = new CEllipse;
	 			fig[count]->Load(filename,i);
				AddFigure(fig[count]);
				count++;
			 }
		  else if(STRING[i].find("RHOMBUS")!=-1)
	     	{
				fig[count] = new CRhombus;
	   			fig[count]->Load(filename,i);
				AddFigure(fig[count]);
				count++;
	}	                                          
		i++;
		 }	

}

void ApplicationManager::SaveType(ofstream &OutFile, string type)
{
	int typecount = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if(FigList[i]->Type() == type)
			typecount++;
	}
	OutFile << StringColor(UI.DrawColor) + "    "  + StringColor(UI.FillColor) + "\n";
	OutFile << to_string(typecount) + "\n";
	for (int i = 0; i < FigCount; i++)
	{
		if(FigList[i]->Type() == type)
			FigList[i]->Save(OutFile);
	}
}


void ApplicationManager::copyfigure(CFigure* cfig)
{
		for (int i = 0; i < FigCount; i++)
		if(FigList[i] == cfig)                 //receiving figure from CopyClass
		{	Clipboard = FigList[i];  break; }   //Store figure in ClipBoard
}

void ApplicationManager::cutfigure(CFigure* cfig)
{

       for (int i = 0; i < FigCount; i++)
		if(FigList[i] == cfig)                  //receiving figure from CopyClass
      {	
		Clipboard = FigList[i];                 //Store figure in ClipBoard
        cfig->setgfxold(cfig->GetGfx());        //storing all GFX info. of figure before changing color to GREY 
        FigList[i]->ChngFillClr(GREY);          //Changing FillColor to Grey 
		FigList[i]->ChngDrawClr(GREY);         //Changing DrawColor to Grey
         break; 
      }
}

void ApplicationManager::pastefigure(CFigure* cfig)
{
	Point P1;                                                              //centre point of the paste figure           
	pOut->PrintMessage("Please, click new cerntre point of figure to paste it"); //invoke user to click the point
	pIn->GetPointClicked(P1.x, P1.y);                                           
	int xc=P1.x;                                                                   //x coordinate of new centre                                                 
	int yc=P1.y;                                                                   //y coordinate of new centre
	
if(dynamic_cast<CEllipse*>(cfig))                                           //checking type of figure
{  
	if(cfig->GetColor()==GREY)                                             //check if figure is in cut order
	{cfig->setgfx(cfig->getgfxold());                                     //get old GFX info before changing color to Grey
	CEllipse *c=new CEllipse(P1,cfig->GetGfx()); 
	AddFigure(c); delfigure(cfig); Clipboard=NULL;}                       //creating the new figure and deleting the old one
	else { CEllipse *c=new CEllipse(P1,cfig->GetGfx()); AddFigure(c); }  //if figure is copied
}
else if(dynamic_cast<CTri*>(cfig))                                      //same on other figures
{
	if(cfig->GetColor()==GREY) {cfig->setgfx(cfig->getgfxold()); int cxx=cfig->GetCx(); int cyy=cfig->GetCy(); 
	int deltax,deltay; deltax=xc-cxx; deltay=yc-cyy; Point t1,t2,t3; t1=cfig->GetP1(); t2=cfig->GetP2(); t3=cfig->GetP3();
	t1.x+=deltax; t2.x+=deltax; t3.x+=deltax; t1.y+=deltay; t2.y+=deltay; t3.y+=deltay;
	CTri *t=new CTri(t1,t2,t3,cfig->GetGfx()); AddFigure(t); delfigure(cfig); Clipboard=NULL;}
	else {int cxx=cfig->GetCx(); int cyy=cfig->GetCy(); int deltax,deltay;
	deltax=xc-cxx; deltay=yc-cyy; Point t1,t2,t3; t1=cfig->GetP1(); t2=cfig->GetP2(); t3=cfig->GetP3();
	t1.x+=deltax; t2.x+=deltax; t3.x+=deltax; t1.y+=deltay; t2.y+=deltay; t3.y+=deltay;
	CTri *t=new CTri(t1,t2,t3,cfig->GetGfx()); AddFigure(t);}
}
else if(dynamic_cast<CLine*>(cfig))  
{
	 if(cfig->GetColor()==GREY) { cfig->setgfx(cfig->getgfxold()); int cxx=cfig->GetCx(); int cyy=cfig->GetCy();
	int p1x=xc+cxx; int p1y=yc+cyy; int p2x=xc-cxx; int p2y=yc-cyy; Point Pl1,Pl2; Pl1.x=p1x; Pl1.y=p1y;
	Pl2.x=p2x; Pl2.y=p2y; CLine *l=new CLine(Pl1,Pl2,cfig->GetGfx()); AddFigure(l); delfigure(cfig); Clipboard=NULL;}
  else {int cxx=cfig->GetCx(); int cyy=cfig->GetCy();
	int p1x=xc+cxx; int p1y=yc+cyy; int p2x=xc-cxx; int p2y=yc-cyy; Point Pl1,Pl2; Pl1.x=p1x; Pl1.y=p1y;
	Pl2.x=p2x; Pl2.y=p2y; CLine *l=new CLine(Pl1,Pl2,cfig->GetGfx()); AddFigure(l); }
}
	else if(dynamic_cast<CRectangle*>(cfig)) 
{ 
	if(cfig->GetColor()==GREY) {cfig->setgfx(cfig->getgfxold()); int cxx=cfig->GetCx(); int cyy=cfig->GetCy(); 
	int p1x=xc+cxx; int p1y=yc+cyy; int p2x=xc-cxx; int p2y=yc-cyy; Point Pl1,Pl2; Pl1.x=p1x; Pl1.y=p1y; Pl2.x=p2x;
	Pl2.y=p2y; CRectangle *r=new CRectangle(Pl1,Pl2,cfig->GetGfx()); AddFigure(r); delfigure(cfig); Clipboard=NULL;}
	else { int cxx=cfig->GetCx(); int cyy=cfig->GetCy(); int p1x=xc+cxx; int p1y=yc+cyy; int p2x=xc-cxx; 
	int p2y=yc-cyy; Point Pl1,Pl2; Pl1.x=p1x; Pl1.y=p1y; Pl2.x=p2x;
	Pl2.y=p2y; CRectangle *r=new CRectangle(Pl1,Pl2,cfig->GetGfx()); AddFigure(r);}
}
	else if(dynamic_cast<CRhombus*>(cfig)) 
 {
	if(cfig->GetColor()==GREY) { cfig->setgfx(cfig->getgfxold()); CRhombus *rh=new CRhombus(P1,cfig->GetGfx()); 
	AddFigure(rh); delfigure(cfig); Clipboard=NULL; }
	else
	{  CRhombus *rh=new CRhombus(P1,cfig->GetGfx());  AddFigure(rh);}
		  
 }

}


CFigure* ApplicationManager::GetClipboard() {return Clipboard; } 
void ApplicationManager::delfigure(CFigure * dFig)
{
	int i;
	for (i=FigCount-1; i >= 0; i--)
	{
		if(FigList[i]==dFig)
		{
			
			delete FigList[i];
			FigList[i]=NULL;
			break;
		}
	}
	for (i; i <FigCount-1; i++)
	{
		FigList[i]=FigList[i+1];
	}
	FigList[FigCount - 1] = NULL;
	FigCount--;

}
void ApplicationManager::SendBack(CFigure* pfigure)
{
	CFigure* temp = NULL;
	for (int i = 0; i < FigCount; i++)
	{
		if(FigList[i] == pfigure)
		{
			temp = FigList[i];
			for(i; i > 0; i--)
			FigList[i] = FigList[i-1];
			FigList[0] = temp;
			temp = NULL;
			break;
		}
	}
}

void ApplicationManager::BringFront(CFigure* pfigure)
{
	CFigure* temp = NULL;
	for (int i = 0; i < FigCount; i++)
	{
		if(FigList[i] == pfigure)
		{
			temp = FigList[i];
			for(i; i < FigCount - 1; i++)
				FigList[i] = FigList[i+1];
			FigList[FigCount-1] = temp;
			temp = NULL;
			break;
		}
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	Output * pOut = GetOutput();
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	        
	delete pIn;
	delete pOut;
	
}
