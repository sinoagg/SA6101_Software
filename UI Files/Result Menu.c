#include <cvirte.h>		
#include <userint.h>
#include "Result Menu.h"

static int resultmenu;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((resultmenu = LoadPanel (0, "Result Menu.uir", RESULTMENU)) < 0)
		return -1;
	DisplayPanel (resultmenu);
	RunUserInterface ();
	DiscardPanel (resultmenu);
	return 0;
}
