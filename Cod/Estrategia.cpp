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

	sensores.lerValoresCalibrados();
	leds.pinar();
	
	Serial.println("EEMPROM - Estrategia");
}

void Estrategia::seguirLinha() {
	/* ?--
		Se os sensores centrais virem branco, avançarão.
		Caso contrário, quando um dos sensores ver preto,
		corrigir a trajetória.*/									

	if (sensores.branco_branco_branco_branco())						motores.avancar();

	else if (sensores.branco_preto_branco_branco())					motores.virarEsquerda();
	else if (sensores.branco_branco_preto_branco())					motores.virarDireita();
	else if (sensores.branco_preto_preto_branco()) {
		while(sensores.maisEsqViuBranco() && sensores.maisDirViuBranco()) {motores.avancar();}
		if (sensores.maisEsqViuPreto() && sensores.maisDirViuBranco()) {
			motores.virarEsquerda();
			delay(300);
		}
		else if (sensores.maisDirViuBranco() && sensores.maisDirViuPreto()) {
			motores.virarDireita();
			delay(300);
		}
	}
	else if (sensores.preto_preto_branco_branco()) {
		while(sensores.preto_preto_branco_branco()) { motores.avancar(); }
		while(sensores.dirViuBranco()) { motores.virarEsquerda(); } 
	}
	else if (sensores.branco_branco_preto_preto()) {
		while(sensores.branco_branco_preto_preto()) { motores.avancar(); }
		while(sensores.dirViuBranco()) { motores.virarDireita(); }  
	}
	else if (sensores.preto_preto_preto_branco()) {
		while(sensores.preto_preto_preto_branco()) { motores.avancar(); }
		while(sensores.dirViuBranco()) { motores.virarEsquerda(); } 	
	}
	else if (sensores.branco_preto_preto_preto()) {
		while(sensores.branco_preto_preto_preto()) { motores.avancar(); }
		while(sensores.dirViuBranco()) { motores.virarDireita(); } 
	} else {
		motores.parar(0);
	}

	/*else {
		while (1) {
			motores.parar(0);
			leds.sinalizarConfusao();	
		}
	} */
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

	motores.parar(200);
	motores.recuar(180);
	
	while (sensores.maisEsqViuBranco()){ motores.virarDireita(); }
	while (!sensores.preto_preto_preto_preto()) { robo.acionarMotores(0,-45);}
	delay(100);
	while (!sensores.branco_branco_branco_branco()) { motores.paraTras(); }
	motores.parar(400);
	while (robo.lerSensorSonarLateral() > 10) { motores.avancar(); }
	motores.parar(400);
	while (robo.lerSensorSonarLateral() < 10) { motores.avancar(); } 
	delay(400);
	motores.parar(400);
	motores.virarEsquerda();
	delay(540);
	while(1) { motores.parar(0); }
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