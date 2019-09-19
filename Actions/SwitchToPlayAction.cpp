#include "SwitchToPlayAction.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager *pApp):Action(pApp)
{
}

void SwitchToPlayAction::ReadActionParameters()
{
}

void SwitchToPlayAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ofstream outFile;
	outFile.open("Graph.txt");
	pManager->SaveAll(outFile);
	outFile.close();
	pOut->ClearToolBar();
	pOut->CreatePlayToolBar();
}

SwitchToPlayAction::~SwitchToPlayAction(void)
{
}
