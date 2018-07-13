#include <cvirte.h>		
#include <userint.h>
#include "Enviroment.h"

static int enviroment;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((enviroment = LoadPanel (0, "Enviroment.uir", ENVIROMENT)) < 0)
		return -1;
	DisplayPanel (enviroment);
	RunUserInterface ();
	DiscardPanel (enviroment);
	return 0;
}
