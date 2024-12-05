#include <stdio.h>

#include "Dis65.h"

CDis65::CDis65()
{
}

CDis65::~CDis65()
{
}

bool CDis65::Create()
{
	return false;
}

int CDis65::Run()
{
	return 0;
}

//--------------------------------
// main
//--------------------------------

int main(int argc, char* argv[])
{
	CDis65 Disasembler;

	Disasembler.Create();
	Disasembler.Run();
	return 0;
}