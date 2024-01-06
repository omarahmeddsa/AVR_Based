#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_int.h"
#include <avr/io.h>
/*******************************************************
function impelemntation
this function takes port no and pin number and direction mood
and output void
 ********************************************************/
void DIO_vSetPinDir(u8 A_u8PortNo, u8 A_u8PinNo, u8 A_u8Dir) {
	/*
	 * switch case for the wanted direction of this pin
	 */
	switch(A_u8Dir) {
	/*
	 * if it's output mood go here
	 */
	case DIO_OUTPUT:
		/*
		 * switch to see which port to deal with
		 * then set the pin number in this port
		 */
		switch(A_u8PortNo) {
		case DIO_PORTA:
			SET_BIT(DDRA, A_u8PinNo);
			break;

		case DIO_PORTB:
			SET_BIT(DDRB, A_u8PinNo);
			break;

		case DIO_PORTC:
			SET_BIT(DDRC, A_u8PinNo);
			break;

		case DIO_PORTD:
			SET_BIT(DDRD, A_u8PinNo);
			break;

		}
		break;
		/*
		 * in case of input mood clear the pin number in this specific register
		 */
		case DIO_INPUT:
			switch(A_u8PortNo) {
			case DIO_PORTA:
				CLR_BIT(DDRA, A_u8PinNo);
				break;

			case DIO_PORTB:
				CLR_BIT(DDRB, A_u8PinNo);
				break;

			case DIO_PORTC:
				CLR_BIT(DDRC, A_u8PinNo);
				break;

			case DIO_PORTD:
				CLR_BIT(DDRD, A_u8PinNo);
				break;
			}
			break;
	}
}
/*******************************************************
function implementation
this dunction take port numver and pin number and the tis pin
to the value of high or loww
 ********************************************************/

void DIO_vSetPinVal(u8 A_u8PortNo, u8 A_u8PinNo, u8 A_u8Val) {
	/*
	 * switch case to see this value is high or low
	 */
	switch(A_u8Val) {
	/*
	 * in case of high set the pin number to high in this register
	 */
	case DIO_HIGH:
		switch(A_u8PortNo) {
		case DIO_PORTA:
			SET_BIT(PORTA, A_u8PinNo);
			break;

		case DIO_PORTB:
			SET_BIT(PORTB, A_u8PinNo);
			break;

		case DIO_PORTC:
			SET_BIT(PORTC, A_u8PinNo);
			break;

		case DIO_PORTD:
			SET_BIT(PORTD, A_u8PinNo);
			break;

		}
		break;
		/*
		 * in case of low clae the pin number of this port in this register
		 */
		case DIO_LOW:
			switch(A_u8PortNo) {
			case DIO_PORTA:
				CLR_BIT(PORTA, A_u8PinNo);
				break;

			case DIO_PORTB:
				CLR_BIT(PORTB, A_u8PinNo);
				break;

			case DIO_PORTC:
				CLR_BIT(PORTC, A_u8PinNo);
				break;

			case DIO_PORTD:
				CLR_BIT(PORTD, A_u8PinNo);
				break;
			}
			break;
	}
}
/*******************************************************
function implementation
this function takes port number and pin number then return back
the value of this pin number in PIN register
 ********************************************************/

u8 DIO_u8GetPinVal(u8 A_u8PortNo, u8 A_u8PinNo) {
	/*
	 * local ariable to store the value of the pin
	 */
	u8 L_u8PinVal = 0;
	/*
	 * switch over port number to know which port to deal with
	 */
	switch(A_u8PortNo) {
	/*
	 * set pin of this specific port
	 */
	case DIO_PORTA: L_u8PinVal = GET_BIT(PINA, A_u8PinNo); break;
	case DIO_PORTB: L_u8PinVal = GET_BIT(PINB, A_u8PinNo); break;
	case DIO_PORTC: L_u8PinVal = GET_BIT(PINC, A_u8PinNo); break;
	case DIO_PORTD: L_u8PinVal = GET_BIT(PIND, A_u8PinNo); break;
	}
	/*
	 * return vvalue of the pin
	 */
	return L_u8PinVal;
}
/*******************************************************
function implemenatation
this function takes the port numbber and direction moode of this port
and set the whole port
********************************************************/
void DIO_vSetPortDir(u8 A_u8PortNo, u8 A_u8Dir) {
	/*
	 * siwtch over the ports to see which port to deal with
	 */
	switch(A_u8PortNo) {
	/*
	 * set whole port values in this specific port to direction mood
	 */
	case DIO_PORTA:
		DDRA = A_u8Dir;
		break;

	case DIO_PORTB:
		DDRB = A_u8Dir;
		break;

	case DIO_PORTC:
		DDRC = A_u8Dir;
		break;

	case DIO_PORTD:
		DDRD = A_u8Dir;
		break;
	}
}
/*******************************************************
function implemenation
set the whole port value with this speceifc value that we
wanted
********************************************************/
void DIO_vSetPortVal(u8 A_u8PortNo, u8 A_u8Val) {
	/*
	 * switch over port numbers
	 */
	switch(A_u8PortNo) {
	/*
	 * set whole port with the value provided
	 */
	case DIO_PORTA:
		PORTA = A_u8Val;
		break;

	case DIO_PORTB:
		PORTB = A_u8Val;
		break;

	case DIO_PORTC:
		PORTC = A_u8Val;
		break;

	case DIO_PORTD:
		PORTD = A_u8Val;
		break;

	}

}
/*******************************************************
function implemenatation
this function takes the wanted port number
********************************************************/
u8 DIO_u8GetPortVal(u8 A_u8PortNo) {
	/*
	 * local variable to store the value
	 */
	u8 L_u8PortVal = 0;
	/*
	 * switch over all ports to the specefic port
	 */
	switch(A_u8PortNo) {
	/*
	 * store the value of PINA to the local variable
	 */
	case DIO_PORTA:
		L_u8PortVal = PINA;
		break;

	case DIO_PORTB:
		L_u8PortVal = PINB;
		break;

	case DIO_PORTC:
		L_u8PortVal = PINC;
		break;

	case DIO_PORTD:
		L_u8PortVal = PIND;
		break;

	}
	/*
	 * return the port value
	 */
	return L_u8PortVal;
}

