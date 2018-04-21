#include "Calibracao.h"

Calibracao::Calibracao() {
	escolha = ' ';
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
	while((escolha != 'S') || (escolha != 'S')) {
		
		Serial.println();
		Serial.println("[--+ MENU CALIBRACAO +--]");
		Serial.println("O QUE DESEJAS SENHOR?");
		Serial.println("[B] MINIMO BRANCO.");
		Serial.println("[P] MAXIMO PRETO.");
		Serial.println("[S] SALVAR.");
		esperarParaLer();
		escolha = Serial.read();

		switch (escolha) {
			case 'B':
			case 'b':
				menuFormaPegarValores('B');
				break;
			case 'P':
			case 'p':
				menuFormaPegarValores('P');
				break;
		}
	}	
}

//~~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR OS VALORES ~~~~~~~~~~~~~~~~~~~//

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
		
		if (escolha == 'S') pegarSimultaneamente(tipo);
		//else if (escolha == 'U') pegarUmPorUm(tipo);
	}
}

void Calibracao::pegarSimultaneamente(char tipo){
	escolha = ' ';
	Serial.println();
	Serial.println("CALIBRAR "+ tipoCompleto);
	Serial.println("POSICIONE TODOS OS SENSORES PARA PEGAR O " + tipoCompleto);
	
	while ((escolha != 'S') || (escolha != 'S')) {
		Serial.println("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n");
		Serial.println("[S] SALVAR VALORES");
		esperarParaLer();
		escolha = Serial.read();
		
		if ((escolha != 'S') || (escolha != 'S')) continue;
			
		if (tipo == 'B') calculeMinimoBranco(
			robo.lerSensorLinhaEsq2(),robo.lerSensorLinhaEsq()
			robo.lerSensorLinhaDir(),robo.lerSensorLinhaDir2()							   	
		);
		else calculeMaximoPreto(
			robo.lerSensorLinhaEsq2(),robo.lerSensorLinhaEsq()
			robo.lerSensorLinhaDir(),robo.lerSensorLinhaDir2()							   	
		);
	}
}




/*
void Calibracao::pegarUmPorUm(char tipo) {
	while((escolha != 'S') || (escolha != 'S')) {
		Serial.println();
		Serial.println("PEGAR VALORES PARA" + tipoCompleto);
		Serial.println("ESCOLHA QUAL SENSOR QUERES PEGAR O VALOR");
		Serial.println("[E] maisEsq");
		Serial.println("[e] Esq");
		Serial.println("[d] Dir");
		Serial.println("[D] maisDir");
		Serial.println("[S] SALVAR");
		esperarParaLer();
		escolha = Serial.read();

		switch (escolha) {
			case 'E':
				break;
			case 'e':
				break;
			case 'd':
				break;
			case 'D':
				break;
		}
	}
}
*/

void Calibracao::calculeMinimoBranco (float valorEsq2,float valorEsq,float valorDir,float valorDir2) {
	if (valorEsq2 < minimoBrancoEsq2)	minimoBrancoEsq2 = valorEsq2;
	if (valorEsq < minimoBrancoEsq) 	minimoBrancoEsq = valorEsq;
	if (valorDir < minimoBrancoDir) 	minimoBrancoDir = valorDir;
	if (valorDir2 < minimoBrancoDir2) 	minimoBrancoDir2 = valorDir2;
}
void Calibracao::calculeMaximoPreto(float valorEsq2,float valorEsq,float valorDir,float valorDir2){
	if (valorEsq2 < maximoPretoEsq2)	maximoPretoEsq2 = valorEsq2;
	if (valorEsq < maximoPretoEsq)		maximoPretoEsq = valorEsq;
	if (valorDir < maximoPretoDir)		maximoPretoDir = valorDir;
	if (valorDir2 < maximoPretoDir2) 	maximoPretoDir2 = valorDir2;
}


void Calibracao::esperarParaLer(){
	while(!Serial.available()){}
}
