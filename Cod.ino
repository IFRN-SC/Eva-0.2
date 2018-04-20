#include "Estrategia.h"

Estrategia estrategia;
/*
  Serão usadas funções deste objeto para
  a calibração e controle estratégico do robô no 
  void loop().
*/

void setup(){
	Serial.begin(9600); 
	// ^    ^ A priori, somente deves saber que isto habilita o uso do Serial
	robo.configurar(false); // Habilita ou desalibita a garra
	//estrategia.calibrar(false);
	/* ^         ^  
	  Determina se será feita a calibracao
	  da separação-branco-preto.
	*/
}

void loop(){
	estrategia.run();
}