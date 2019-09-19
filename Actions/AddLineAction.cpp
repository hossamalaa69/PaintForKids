#include "AddLineAction.h"
#include "..\Figures\CLine.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <Windows.h>
#include <MMSystem.h>

AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{}

void AddLineAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (pManager->getVoice())
		PlaySound(TEXT("Line.wav"), NULL, SND_SYNC);

	pOut->PrintMessage("New Line: Click at first corner");
	
	//Read 1st corner and store in point P1
	do
	{
	pIn->GetPointClicked(P1.x, P1.y);
	}while  (P1.y<UI.ToolBarHeight);

	pOut->PrintMessage("New Line: Click at second corner");

	//Read 2nd corner and store in point P2
	do
	{
	pIn->GetPointClicked(P2.x, P2.y);
	}while  (P2.y<UI.ToolBarHeight);
	//get drawing colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	pOut->ClearStatusBar();

}

//Execute the action
void AddLineAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a Line with the parameters read from the user
	CLine *R=new CLine(P1, P2, RectGfxInfo);

	//Add the Line to the list of figures
	pManager->AddFigure(R);
}
