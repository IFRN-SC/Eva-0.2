#include "Calibracao.h"

//~~~~~~~~~~~~~~~~~~ CONSTRUTOR ~~~~~~~~~~~~~~~~~~//

Calibracao::Calibracao() {
	escolha = ' ';

	minimoBrancoEsq2 = NULLBRANCO;
	minimoBrancoEsq = NULLBRANCO;
	minimoBrancoDir = NULLBRANCO;
	minimoBrancoDir2 = NULLBRANCO;
	
	maximoPretoEsq2 = NULLPRETO;
	maximoPretoEsq = NULLPRETO;
	maximoPretoDir = NULLPRETO;
	maximoPretoDir2 = NULLPRETO;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void Calibracao::run() {
	menuCalibracao();
}

//~~~~~~~~~~~~~~~~~~ MENU INICIAL ~~~~~~~~~~~~~~~~~~//

void Calibracao::menuCalibracao() {
	while((escolha != 'S') || (escolha != 's')) {
		
		Serial.println();
		Serial.println("[---| MENU CALIBRACAO |---]");
		Serial.println("O QUE DESEJAS SENHOR?");
		Serial.println("[B] MINIMO BRANCO.");
		Serial.println("[P] MAXIMO PRETO.");
		Serial.println("[S] SALVAR.");
		esperarParaLer();
		escolha = Serial.read();

		switch (escolha) {
			case 'B':
			case 'b':
				tipo = "MINIMO BRANCO";
				menuFormaPegarValores();
				break;
			case 'P':
			case 'p':
				tipo = "MAXIMO PRETO";
				menuFormaPegarValores();
				break;
		}
	}	
}

//~~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR OS VALORES ~~~~~~~~~~~~~~~~~~~//

void Calibracao::menuFormaPegarValores() {
	while (((escolha != 'S') && (escolha != 's')) && ((escolha != 'U') && (escolha != 'u'))) {
		Serial.println();
		Serial.println("CALIBRAR " + tipo);
		Serial.println("DE QUE FORMA QUERES PEGAR OS VALORES?");
		Serial.println("[S] TODOS OS SENSORES SIMULTANEAMENTE");
		Serial.println("[U] UM POR UM");
		esperarParaLer();
		escolha = Serial.read();
		
		if (escolha == 'S') pegarSimultaneamente();
		else if (escolha == 'U') pegarUmPorUm();
	}
}


//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR SIMULTANEAMENTE ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarSimultaneamente() {
	escolha = ' ';
	Serial.println();
	Serial.println("CALIBRAR "+ tipo);
	Serial.println("POSICIONE TODOS OS SENSORES PARA PEGAR O " + tipo);
	esperar_Posicionamento();

	
	while ((escolha != 'V') || (escolha != 'v')) {
		Serial.println("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n");
		Serial.println("[V] VOLTAR");
		esperarParaLer();
		escolha = Serial.read();
		
		if ((escolha != 'V') || (escolha != 'v')) continue;
			
		if (tipo == "MINIMO BRANCO") calculeMinimoBranco(
			robo.lerSensorLinhaEsq2(),robo.lerSensorLinhaEsq(),
			robo.lerSensorLinhaDir(),robo.lerSensorLinhaDir2()							   	
		);
		else calculeMaximoPreto(
			robo.lerSensorLinhaEsq2(),robo.lerSensorLinhaEsq(),
			robo.lerSensorLinhaDir(),robo.lerSensorLinhaDir2()							   	
		);
	}
}

//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR UM POR UM ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarUmPorUm() {
	while((escolha != 'S') || (escolha != 's')) {
		Serial.println();
		Serial.println("PEGAR VALORES PARA" + tipo);
		Serial.println("POSICIONE O SENSOR CORRETAMENTE...");
		esperar_Posicionamento();

		Serial.println("ESCOLHA QUAL SENSOR QUERES PEGAR VALORES");
		Serial.println("[E] maisEsq");
		Serial.println("[e] Esq");
		Serial.println("[d] Dir");
		Serial.println("[D] maisDir");
		Serial.println("[S] SALVAR");
		esperarParaLer();
		escolha = Serial.read();

		switch (escolha) {
			case 'E': // Pega valor do sensor maisEsq e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") calculeMinimoBranco( robo.lerSensorLinhaEsq2() ,NULLBRANCO ,NULLBRANCO ,NULLBRANCO);
				else 			  calculeMaximoPreto( robo.lerSensorLinhaEsq2() ,NULLPRETO,NULLPRETO,NULLPRETO);
				break;
			case 'e': // Pega valor do sensor Esq e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") calculeMinimoBranco(NULLBRANCO, robo.lerSensorLinhaEsq() ,NULLBRANCO,NULLBRANCO);
				else 			   calculeMaximoPreto(NULLPRETO, robo.lerSensorLinhaEsq() ,NULLPRETO,NULLPRETO);
				break;
			case 'd': // Pega valor do sensor Dir e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") calculeMinimoBranco(NULLBRANCO,NULLBRANCO, robo.lerSensorLinhaDir() ,NULLBRANCO);
				else                calculeMaximoPreto(NULLPRETO,NULLPRETO, robo.lerSensorLinhaDir() ,NULLPRETO);
				break;
			case 'D': // Pega valor do sensor maisDir e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") calculeMinimoBranco(NULLBRANCO,NULLBRANCO,NULLBRANCO, robo.lerSensorLinhaDir() );
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



//~~~~~~~~~~~~ FERRAMENTAS ~~~~~~~~~~~~~//


void Calibracao::esperar_Posicionamento() {
	Serial.println();
	Serial.println("maisEsq		---		Esq 	---		Dir 	---		maisDir");
	while(!Serial.read()) {
		Serial.print(robo.lerSensorLinhaEsq2());
		Serial.print("		---		");
		Serial.print(robo.lerSensorLinhaEsq());
		Serial.print("		---		");
		Serial.print(robo.lerSensorLinhaDir());
		Serial.print("		---		");
		Serial.print(robo.lerSensorLinhaDir2());
		Serial.println();
		delay(500);
	}
}

void Calibracao::esperarParaLer() {
	while(!Serial.available()) {}
}
