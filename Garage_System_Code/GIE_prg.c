#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GIE_int.h"
/*******************************************************
function implelemntation
set the pin of global interrupt to high to enable it
********************************************************/
void GIE_vEnable(void) {
	SET_BIT(SREG, 7);
}
/*******************************************************
function implelemntation
clear the pin of global interrupt to low to disable it
********************************************************/

void GIE_vDisable(void) {
	CLR_BIT(SREG, 7);
}

