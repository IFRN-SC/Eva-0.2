#ifndef LEDS_H
#define LEDS_H

/* 
//---------------- PINAGEM - LEDS --------------------//
 
Futuro uso para comunicação dos sensores de refletância
#define LED_maisEsq 9
#define LED_Esq 10
#define LED_Dir 11
#define LED_maisDir 12
//-----------------------------------------------------// 
*/

class Leds {
public:
	void pinar(){
		
		/*
		pinMode(LED_maisEsq, OUTPUT);		
		pinMode(LED_Esq, OUTPUT);
		pinMode(LED_Dir, OUTPUT);
		pinMode(LED_maisDir, OUTPUT);
		*/ 

		pinMode(10, OUTPUT);
		pinMode(11, OUTPUT);
	}

	/*
	void piscar(int led){
		switch (led) {
			case 1: // maisEsq viu preto.
				digitalWrite(LED_maisEsq, HIGH);
				delay(300);
				digitalWrite(LED_maisEsq, LOW);
				break;
			case 2:
				digitalWrite(LED_Esq, HIGH);
				delay(500);
				digitalWrite(LED_Esq, LOW);
				break;
			case 3:
				digitalWrite(LED_Dir, HIGH);
				delay(500);
				digitalWrite(LED_Dir, LOW);
				break;
			case 4:
				digitalWrite(LED_maisDir, HIGH);
				delay(500);
				digitalWrite(LED_maisDir, LOW);
				break;
		}
	}*/

	void sinalizarConfusao() {
		while(1) {
			digitalWrite(10, HIGH);
			delay(300);
			digitalWrite(11, LOW);
			delay(300);
		}
	}
};

#endif
