#ifndef LEDS_H
#define LEDS_H

/* 
//---------------- 		  LEDS 	    --------------------//
 
Futuro uso para comunicação dos sensores de refletância
#define LED_maisEsq 1
#define LED_Esq 	2
#define LED_Dir 	3
#define LED_maisDir 4

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

	void ligar(int led) { digitalWrite(led,HIGH); }
	void desligar(int led) { digitalWrite(led,LOW); }


	void piscar(int led){
		digitalWrite(led,HIGH);
		delay(400);
		digitalWrite(led,LOW);
	}

	void sinalizarConfusao() {
		while(1) {
			digitalWrite(10, !digitalRead(10));
			delay(300);
			digitalWrite(11, !digitalRead(11));
			delay(300);
		}
	}
};

#endif
