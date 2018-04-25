#include "Estrategia.h"

void Estrategia::run() {
 	/* ?--
		Se o sonar frontal retornar um valor menor ou igual
		ao valor de DISTANCIA_OBSTACULO, o robô começará
		a desviar do obstáculo.
		Se não, somente seguirá a linha.*/
	if (sensores.sonarViuObstaculo(DISTANCIA_OBSTACULO))	desviarObstaculo();
	else	seguirLinha();
}

void Estrategia::calibrar(bool value) {
	/* ?--
		Verifica se queremos calibrar os valores. Passado 4 segundos,
		se não insrirmos algo no Serial, o robô irá continuar com os valores
		salvos na EEPROM.*/
	Serial.println(F("INSIRA ALGUMA COISA PARA CALIBRAR"));
	for (int i=10; i>=0; i--) {
		Serial.print(F("Tentativa "));
		Serial.println(i);
		delay(400);
		if (Serial.available()) {
			Serial.read();
			Serial.println();
			calibracao.run();
			i = 11;
		}
	}

	robo.lerCalibracao(cali);
}

void Estrategia::seguirLinha() {
	/* ?--
		Se os sensores centrais virem branco, avançarão.
		Caso contrário, quando um dos sensores ver preto,
		corrigir a trajetória.*/											
	if (sensores.esqViuBranco() && sensores.dirViuBranco())				motores.avancar();
	else if (sensores.esqViuPreto() && sensores.dirViuBranco())			motores.virarEsquerda();
	else if (sensores.esqViuBranco() && sensores.dirViuPreto()) 		motores.virarDireita();

	// ?? Testes virarEixo's
	else if (sensores.preto_preto_branco_branco())						motores.virarEixoEsq();
	else if (sensores.branco_branco_preto_preto()) 						motores.virarEixoDir();

	/* ?? Se teste virarEixo's falhar:
	else if (sensores.preto_preto_branco_branco())						motores.virarEsquerda();
	else if (sensores.branco_branco_preto_preto()) 						motores.virarDireita();
	*/

	//else if (sensores.branco_preto_preto_branco())						passarVerde();
	else leds.sinalizarConfusao();
}

/*
void Estrategia::passarVerde(//int lado) {
	if (sensores.branco_preto_preto_branco()) {
		motores.parar(200);
		
		while(!sensores.maisDirViuPreto()) {
			motores.virarEixoEsq();	
		}
		
		while("!sensores.")
	}
}
*/

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


	// CURVA EXPONENCIAL
	
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

void Estrategia::alinharObstaculo(char lado) {
	if (lado == 'R') {
		while (obstaculoDesalinhado()) {
			robo.acionarMotores((VEL * 0.10) * (-1),VEL * (-1)); 
			// Motor contrário recua com 10% de VEL.
		}		
	}	
	else {
		while (obstaculoDesalinhado()) {
		robo.acionarMotores(VEL * (-1),(VEL * 0.10) * (-1));
		// Motor contrário recua com 10% de VEL.
		}	
	}
}

bool Estrategia::obstaculoDesalinhado(){
	return (sensores.branco_branco_branco_branco());
}