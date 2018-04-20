#include "Calibracao.h"

Calibracao::Calibracao() {
	escolha = " ";
	tipoCompleto = " ";
	
	minimoBrancoEsq2 = 100;
	minimoBrancoEsq = 100;
	minimoBrancoDir = 100;
	minimoBrancoDir2 = 100;
	
	maximoPretoEsq2 = 0;
	maximoPretoEsq = 0;
	maximoPretoDir = 0;
	maximoPretoDir2 = 0;
}

void Calibracao::run(){
	menuCalibracao();
}

void Calibracao::menuCalibracao(){
	while(escolha != "S") {
		Serial.println();
		Serial.println("[--+ MENU CALIBRACAO +--]");
		Serial.println("O QUE DESEJAS SENHOR?");
		Serial.println("[B] MINIMO BRANCO.");
		Serial.println("[P] MAXIMO PRETO.");
		Serial.println("[S] SALVAR.");
		esperarParaLer();
		escolha = Serial.read();
		escolha = escolha.toUpperCase().charAt(0);
		

		switch (escolha) {
			case 'B':
				menuFormaPegarValores('B');
				break;
			case 'P':
				menuFormaPegarValores('P');
				break;
		}
	}	
	escolha = ' ';
}


void Calibracao::menuFormaPegarValores(char tipo){
	if (tipo == 'B') tipoCompleto = "MINIMO BRANCO";
	else tipoCompleto = "MAXIMO PRETO";
	
	while ((escolha != 'S') && (escolha != 'U')){
		Serial.println();
		Serial.println("CALIBRAR "+ tipoCompleto);
		Serial.println("DE QUE FORMA QUERES PEGAR OS VALORES?");
		Serial.println("[S] TODOS OS SENSORES SIMULTANEAMENTE");
		Serial.println("[U] UM POR UM");
		esperarParaLer();
		escolha = Serial.read();
		
		if (escolha == 'S') pegarSimultaneamente(tipo);SMAR
		else if (escolha == 'U') pegarUmPorUm(tipo);
	}
}



void Calibracao::calculeMinimoBranco(int valorEsq2,int valorEsq,int valorDir,int valorDir2){
	if (valorEsq2 < minimoBrancoEsq2)	minimoBrancoEsq2 = valorEsq2;
	if (valorEsq < minimoBrancoEsq)	minimoBrancoEsq = valorEsq;
	if (valorDir < minimoBrancoDir)	minimoBrancoDir = valorDir;
	if (valorDir2 < minimoBrancoDir2) minimoBrancoDir2 = valorDir2;
}
void Calibracao::calculeMaximoPreto(int valorEsq2,int valorEsq,int valorDir,int valorDir2){
	if (valorEsq2 < maximoPretoEsq2)	maximoPretoEsq2 = valorEsq2;
	if (valorEsq < maximoPretoEsq)	maximoPretoEsq = valorEsq;
	if (valorDir < maximoPretoDir)	maximoPretoDir = valorDir;
	if (valorDir2 < maximoPretoDir2) maximoPretoDir2 = valorDir2;
}


void Calibracao::esperarParaLer(){
	while(!Serial.available()){}
}
