#include "led.h"


int main(){

	vLEDInit();


	while(1) {

		vLEDOn();
		for(int i=0;i<90000;i++){};
		vLEDOff();
		for(int i=0;i<90000;i++){};
	}

}
