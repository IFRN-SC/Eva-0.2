#include "Estrategia.h"

void Estrategia::run() {
 	/* !-- Se o sonar frontal retornar um valor menor ou igual
 		   ao valor de DISTANCIA_OBSTACULO, o robô começará
 		   a desviar do obstáculo.
 		   Se não, somente seguirá a linha.
 	*/
	if (sensores.sonarViuObstaculo(DISTANCIA_OBSTACULO))	desviarObstaculo();
	else	seguirLinha();
}

void Estrategia::calibrar(bool value) {
	/* !-- Verifica se queremos calibrar os valores. Passado 4 segundos,
		se não insirirmos algo no Serial, o robô irá continuar com os valores
		salvos na EEPROM.
	*/
	Serial.println("INSIRA ALGUMA COISA PARA CALIBRAR");
	for (int i=10; i>=0; i--) {
		Serial.println("Tentativa " + i);
		delay(400);
		if (Serial.available()) {
			Serial.read();
			calibracao.run();
		}
	}
}

void Estrategia::seguirLinha() {
	/* Se todos virem branco ou preto, motores avançam.
	*/													
	if (sensores.esqViuBranco() && sensores.dirViuBranco())				motores.avancar();
	else if (sensores.esqViuPreto() && sensores.dirViuBranco())			motores.virarEsquerda();
	else if (sensores.esqViuBranco() && sensores.dirViuPreto()) 		motores.virarDireita();
	// ?? Testes virarEixo's
	else if (sensores.preto_preto_branco_branco())						motores.virarEixoEsq();
	else if (sensores.branco_branco_preto_preto()) 						motores.virarEixoEsq();
	/*
	else {
		motores.parar(500);
		while(1){
			motores.virarEsquerda();
			delay(500);
			motores.virarDireita();
			delay(500);
		}
	}
	
	else {
		passarVerde();	
	}
	*/
}

/*
void Estrategia::passarVerde(int lado) {
	switch (lado){
		case 'L': // Esquerda
			if (!sensores.branco_branco_branco_branco() &&
				!sensores.preto_preto_preto_preto()) 
			{
				while(!sensores.preto_preto_preto_preto()){
					motores.virarEixoEsq();
				}
			}
			break;
		case 'R':
	}
}
*/

void Estrategia::impulso() {
	while (sensores.branco_branco_branco_branco()
		  || 
		  sensores.preto_preto_preto_preto()
		  && 
		  (!sensores.sonarViuObstaculo(DISTANCIA_OBSTACULO))) 
	{
		robo.acionarMotores(60,60);	
	}
	motores.parar(500);
}

void Estrategia::desviarObstaculo(){
	
	//piscarLeds();
	
	bool pelaDireita; // Se o robô está indo realmente pela direita.

	motores.parar(150);
	motores.recuar(180);
	
	while (!sensores.maisDirViuPreto()){
		robo.acionarMotores(0,VEL * (-1));
	}

	/**** Verificar melhor lado para ir ****/

	if (sensores.sonarViuObstaculo(3 * DISTANCIA_OBSTACULO)){  // Se é melhor ir para a direita
		pelaDireita = true;
		alinharObstaculo('R'); // Right - Direita
	} 
	else {	// Se é melhor ir para a esquerda

		while (!sensores.maisDirViuPreto()){
			robo.acionarMotores(0,VEL);
		}

		alinharObstaculo('L'); // Left - Esquerda
	}

	motores.parar(1000);
	
	motores.avancar();


	// ENROLADA EXPONENCIAL
	
	if(pelaDireita){
		for (int i=10; i!=0; --i){
			robo.acionarMotores((VEL * (i/100)),VEL);
			delay(200);	
		}
	} 
	else {
		for (int i=10; i!=0; --i){
			robo.acionarMotores(VEL,(VEL * (i/100)));
			delay(200);	
		}
	}
	
	motores.avancar();
}

void Estrategia::alinharObstaculo(char lado){
	switch (lado){
		case 'R':
			while (obstaculoDesalinhado()) {
				robo.acionarMotores((VEL * 0.10) * (-1),VEL * (-1)); 
				/*  ^				^				^	 		^  
					Motor contrário recua com 10% de VEL.
				*/
			}
			break;
		case 'L':
			while (obstaculoDesalinhado()) {
				robo.acionarMotores(VEL * (-1),(VEL * 0.10) * (-1)); 
				/*  ^				^				^	 		^  
					Motor contrário recua com 10% de VEL.
				*/
			}
			break;
	}
	
}

bool Estrategia::obstaculoDesalinhado(){
	return (sensores.branco_branco_branco_branco());
}