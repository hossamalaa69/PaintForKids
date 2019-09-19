#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	id = ID;
	Corner1 = P1;
	Corner2 = P2;
}
CRectangle::CRectangle(){}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

float area(int x1, int y1, int x2, int y2, int x3, int y3) 
{ 
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0); 
}
bool CRectangle::check(int x, int y) 
{ 
	int x1 = Corner1.x , y1 = Corner1.y;
	int x2 = Corner2.x, y2 = Corner1.y;
	int x3 = Corner2.x, y3 = Corner2.y;
	int x4 = Corner1.x, y4 = Corner2.y;
    /* Calculate area of rectangle ABCD */
    float A = area(x1, y1, x2, y2, x3, y3) + area(x1, y1, x4, y4, x3, y3); 
  
    /* Calculate area of triangle PAB */
    float A1 = area(x, y, x1, y1, x2, y2); 
  
    /* Calculate area of triangle PBC */
    float A2 = area(x, y, x2, y2, x3, y3); 
  
    /* Calculate area of triangle PCD */
    float A3 = area(x, y, x3, y3, x4, y4); 
  
    /* Calculate area of triangle PAD */
    float A4 = area(x, y, x1, y1, x4, y4); 
  
    /* Check if sum of A1, A2, A3 and A4  
       is same as A */
    return (A == A1 + A2 + A3 + A4); 
} 

void CRectangle::PrintInfo(Output* pOut)
{
	string info = "Rectangle : id = " + to_string(id) 
		+ ", corner1(" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ") , corner2(" 
		+ to_string(Corner2.x) + "," + to_string(Corner2.y) + ") , color = "
		+ StringColor(FigGfxInfo.DrawClr) ;
	pOut->PrintMessage(info);
}

void CRectangle::Save(ofstream &OutFile)
{
	string filled = (FigGfxInfo.isFilled)? StringColor(FigGfxInfo.FillClr) : "NO_FILL";
	OutFile << "RECT    " + to_string(id) 
		+ "   " + to_string(Corner1.x) + "    " + to_string(Corner1.y) + "    " 
		+ "   " + to_string(Corner2.x) + "    " + to_string(Corner2.y) + "    " 
		+ StringColor(FigGfxInfo.DrawClr) + "     " +  filled + "\n";
}

string CRectangle::Type()
{
	return "RECTANGLE";
}

int CRectangle::GetCx ()
{
	int cx=((Corner1.x-Corner2.x))/2;
	return cx;
}
int CRectangle::GetCy ()
{
	int cy=((Corner1.y-Corner2.y))/2;
        return cy;
}

void CRectangle::Load(string filename,int pos) 
 {
	string STRING[200];
	ifstream file;
	file.open (filename);
	int i=0;
   if (file.is_open())
   {
        while(!file.eof()) // To get you all the lines.
        {
			
	        getline(file,STRING[i]); // Saves the line in STRING.
	        
			if (i==pos)
				break;
			i++;
        }
	file.close();
    }
   	std::string str =STRING[i] ;
	std::istringstream stm(str) ;
	string word ;
	string arr [10];
	int k=0; 
	while( stm >> word ) // read white-space delimited tokens one by one 
	{
	  arr[k]=word;
	  k++;
		// put word into array
	}
	this->id=stoi(arr[1]);
	this->Corner1.x=stoi(arr[2]);
	this->Corner1.y=stoi(arr[3]);
	this->Corner2.x=stoi(arr[4]);
	this->Corner2.y=stoi(arr[5]);
	color col;
	if (arr[6]=="BLUE")
		col=BLUE;
	else if (arr[6]=="RED")
		col=RED;
	else if (arr[6]=="BLACK")
		col=BLACK;
	else if (arr[6]=="WHITE")
		col=WHITE;
	else if (arr[6]=="GREEN")
		col=GREEN;
	this->ChngDrawClr(col);
	this->Selected=false;
	if (arr[7]=="NO_FILL")
	{
		this->notfilled();
	}
	else if (arr[7]=="BLUE")
	{
					col=BLUE;;
		    this->ChngFillClr(col);
	}
	else if (arr[7]=="BLACK")
	{			col=BLACK;
				    this->ChngFillClr(col);

	}
	else if (arr[7]=="WHITE")
		{		col=WHITE;
		    this->ChngFillClr(col);
        }
	else if (arr[7]=="GREEN")
	{
			col=GREEN;
		    this->ChngFillClr(col);
	}
	else 
	{
		    this->ChngFillClr(RED);
	}
 }