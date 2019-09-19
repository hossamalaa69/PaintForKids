#pragma once
#include "Action.h"
#include <iostream>
#include <fstream>
using namespace std;

class LoadAction:public Action
{
private:
	
	string filename;
	int count;
	ifstream file;
public:
	LoadAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
	
	~LoadAction();
};
