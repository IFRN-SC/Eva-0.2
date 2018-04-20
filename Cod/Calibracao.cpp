#include "Calibracao.h"

Calibracao::Calibracao() {
	escolha = ' ';
	minimoEsq2 = 100;
	minimoEsq = 100;
	minimoDir = 100;
	minimoDir2 = 100;
	
	maximoPretoEsq2 = 0;
	maximoPretoEsq = 0;
	maximoPretoDir = 0;
	maximoPretoDir2 = 0;
}

void Calibracao::run(){
	menuCalibracao();
}

void Calibracao::menuCalibracao(){
	Serial.println():
	Serial.println("[--+ MENU CALIBRACAO +--]");
	Serial.println("O QUE DESEJAS SENHOR? ");
	Serial.println("[B] MINIMO BRANCO.");
	Serial.println("[P] MAXIMO PRETO.");
	Serial.println("[S] SALVAR.");
	esperarParaLer();
	escolha = Serial.read();

	switch (escolha) {
		case 'B':
			minimoBranco();
			break;
		case 'P':
			maximoPreto();
			break;
		case 'S':
		default:
			menuCalibracao();
	}
	escolha = ' ';
}


void Calibracao::minimoBranco(){
	while (1){
		Serial.println("CALIBRAR MINIMO BRANCO: ");
		Serial.println();
		Serial.println("POSICIONES OS SENSORES NO BRANCO!");
		Serial.println();
		Serial.println("INSIRA QUALQUER COISA PARA PEGAR OS VALORES");
		Serial.println("[S] VOLTAR");
		Serial.println();
		Serial.print("R = ");
		esperarParaLer();
		escolha = Serial.read();
		
		if (escolha == 'S') menuCalibracao();
		else calculeMinimo(robo.lerSensorLinhaEsq2(),robo.lerSensorLinhaEsq(),robo.lerSensorLinhaDir(),robo.lerSensorLinhaDir2);
	}
}


void Calibracao::maximoPreto(){}

void Calibracao::calculeMinimo(int valorEsq2,int valorEsq,int valorDir,int valorDir2){
	if (valorEsq2 < minimoEsq2) {
		minimoEsq2 = valorEsq2;
	}
	if (valorEsq < minimoEsq) {
		minimoEsq = valorEsq;
	}
	if (valorDir < minimoDir) {
		minimoDir = valorDir;
	}
	if (valorDir2 < minimoDir2) {
		minimoDir2 = valorDir2;
	}
}


void Calibracao::esperarParaLer(){
	while(!Serial.available()){}
}
