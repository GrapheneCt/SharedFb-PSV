#include <psp2/gxt.h> 

#include "graphics.h"

int main( void )
{
	initGraphics();

	while (1) {
			drawDisplay();
	}

	return 0;
}