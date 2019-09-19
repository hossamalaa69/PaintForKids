#include "AddRhombusAction.h"
#include "..\Figures\CRhombus.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <Windows.h>
#include <MMSystem.h>

AddRhombusAction::AddRhombusAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRhombusAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (pManager->getVoice())
		PlaySound(TEXT("Rhombus.wav"), NULL, SND_SYNC);

	pOut->PrintMessage("New Rhombus: Click at center");
	
	//Read 1st corner and store in point P1
	do
	{
	pIn->GetPointClicked(P1.x, P1.y);
	}while  (P1.y<UI.ToolBarHeight+100||P1.y>UI.height-UI.StatusBarHeight-100||P1.x>UI.width-115||P1.x<UI.wx+100);
	RectGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRhombusAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a Rhombus with the parameters read from the user
	CRhombus *R=new CRhombus(P1,RectGfxInfo);

	//Add the Rhombus to the list of figures
	pManager->AddFigure(R);
}
