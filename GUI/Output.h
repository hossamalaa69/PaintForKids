#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateColorToolBar() const; //creates Color mode toolbar & menu
	void CreateResizeToolBar() const;  //creates Resize mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar


	Input* CreateInput() const; //creates a pointer to the Input object
	void ClearToolBar() const;  //Clears the tool bar
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	
	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;  //Draw a rectangle
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo,bool selected=false) const;  //Draw a Line
	void DrawTrinagle(Point P1, Point P2,Point P3, GfxInfo TriGfxInfo,bool selected=false) const;  //Draw a Triangle
	void DrawEllipes(Point P1, GfxInfo ElipseGfxInfo,bool selected=false) const;  //Draw a Triangle
	void DrawRhombus(Point P1, GfxInfo RhomnusGfxInfo,bool selected=false) const;  //Draw a Rhombus
	
	
	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width

	
	~Output();
};

#endif