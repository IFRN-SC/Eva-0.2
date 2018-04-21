#include "Calibracao.h"

Calibracao::Calibracao() {
	escolha = ' ';
	tipoCompleto = " ";
	
	minimoBrancoEsq2 = NULLBRANCO;
	minimoBrancoEsq = NULLBRANCO;
	minimoBrancoDir = NULLBRANCO;
	minimoBrancoDir2 = NULLBRANCO;
	
	maximoPretoEsq2 = NULLPRETO;
	maximoPretoEsq = NULLPRETO;
	maximoPretoDir = NULLPRETO;
	maximoPretoDir2 = NULLPRETO;
}

void Calibracao::run(){
	menuCalibracao();
}

void Calibracao::menuCalibracao(){
	while((escolha != 'S') || (escolha != 's')) {
		
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
	
	while (((escolha != 'S') && (escolha != 's')) && ((escolha != 'U') && (escolha != 'u'))) {
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
	
	while ((escolha != 'V') || (escolha != 'v')) {
		Serial.println("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n");
		Serial.println("[V] VOLTAR");
		esperarParaLer();
		escolha = Serial.read();
		
		if ((escolha != 'V') || (escolha != 'v')) continue;
			
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


void Calibracao::pegarUmPorUm(char tipo) {
	while((escolha != 'S') || (escolha != 's')) {
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
				if (tipo == 'B') calculeMinimoBranco( robo.lerSensorLinhaEsq2() ,NULLBRANCO ,NULLBRANCO ,NULLBRANCO);
				else 			  calculeMaximoPreto( robo.lerSensorLinhaEsq2() ,NULLPRETO,NULLPRETO,NULLPRETO);
				break;
			case 'e':
				if (tipo == 'B') calculeMinimoBranco(NULLBRANCO, robo.lerSensorLinhaEsq() ,NULLBRANCO,NULLBRANCO);
				else 			   calculeMaximoPreto(NULLPRETO, robo.lerSensorLinhaEsq() ,NULLPRETO,NULLPRETO);
				break;
			case 'd':
				if (tipo == 'B') calculeMinimoBranco(NULLBRANCO,NULLBRANCO, robo.lerSensorLinhaDir() ,NULLBRANCO);
				else                calculeMaximoPreto(NULLPRETO,NULLPRETO, robo.lerSensorLinhaDir() ,NULLPRETO);
				break;
			case 'D':
				if (tipo == 'B') calculeMinimoBranco(NULLBRANCO,NULLBRANCO,NULLBRANCO, robo.lerSensorLinhaDir() );
				else                 calculeMaximoPreto(NULLPRETO,NULLPRETO,NULLPRETO, robo.lerSensorLinhaDir() );
				break;
		}
	}
}

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
