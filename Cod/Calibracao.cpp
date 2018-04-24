#include "Calibracao.h"

//~~~~~~~~~~~~~~~~~~ CONSTRUTOR ~~~~~~~~~~~~~~~~~~//

Calibracao::Calibracao() {
	escolha = ' ';
	save = false;
	exit = false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void Calibracao::run() {
	menuCalibracao();
}

//~~~~~~~~~~~~~~~~~~ MENU INICIAL ~~~~~~~~~~~~~~~~~~//

void Calibracao::menuCalibracao() {
	while(!save) {
		
		Serial.println(F("[---| MENU CALIBRACAO |---]"));
		Serial.println(F("O QUE DESEJAS SENHOR?"));
		Serial.println(F("[B] MINIMO BRANCO."));
		Serial.println(F("[P] MAXIMO PRETO."));
		Serial.println(F("[S] SALVAR."));
		Serial.println(F("[D] DESCARTAR CALIBRACAO"));
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
			case 'S':
			case 's':
			case 'D':
			case 'd':
				//robo.salvarCalibracao(cali);
				save = true;
		}
	}
	if ((escolha != 'D') && (escolha != 'd')) {

		cali.refletancia_mais_esq	= refletancia_lido_esq2.getSeparacao();
		cali.refletancia_esq 		= refletancia_lido_esq.getSeparacao();
		cali.refletancia_dir 		= refletancia_lido_dir.getSeparacao();
		cali.refletancia_mais_dir 	= refletancia_lido_dir2.getSeparacao();

		robo.salvarCalibracao(cali);	
	}
}

//~~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR OS VALORES ~~~~~~~~~~~~~~~~~~~//

void Calibracao::menuFormaPegarValores() {
	while (!exit) {

		Serial.println();
		Serial.print(F("CALIBRAR "));
		Serial.println(tipo);
		Serial.println(F("DE QUE FORMA QUERES PEGAR OS VALORES?"));
		Serial.println(F("[S] TODOS OS SENSORES SIMULTANEAMENTE"));
		Serial.println(F("[U] UM POR UM"));
		Serial.println(F("[V] VOLTAR"));
		esperarParaLer();
		escolha = Serial.read();
		
		if (escolha == 'S') pegarSimultaneamente();
		else if (escolha == 'U') pegarUmPorUm();
		else if ((escolha == 'V') || (escolha == 'v')) exit = true;

	}
	exit = false;
}


//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR SIMULTANEAMENTE ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarSimultaneamente() {
	Serial.print(F("CALIBRAR "));
	Serial.println(tipo);
	Serial.print(F("POSICIONE TODOS OS SENSORES PARA PEGAR O "));
	Serial.println(tipo);
	esperar_Posicionamento();

	
	while (!exit) {
		Serial.println(F("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n"));
		Serial.println(F("[V] VOLTAR"));
		esperarParaLer();
		escolha = Serial.read();
		
		if ((escolha != 'V') || (escolha != 'v')) exit = true; break;
			
		if (tipo == "MINIMO BRANCO"){
			refletancia_lido_esq2.setMinimoBranco(robo.lerSensorLinhaEsq2());
			refletancia_lido_esq.setMinimoBranco(robo.lerSensorLinhaEsq());
			refletancia_lido_dir.setMinimoBranco(robo.lerSensorLinhaDir());
			refletancia_lido_dir2.setMinimoBranco(robo.lerSensorLinhaDir2());
		}
		else {
			refletancia_lido_esq2.setMaximoPreto(robo.lerSensorLinhaEsq2());
			refletancia_lido_esq.setMaximoPreto(robo.lerSensorLinhaEsq());
			refletancia_lido_dir.setMaximoPreto(robo.lerSensorLinhaDir());
			refletancia_lido_dir2.setMaximoPreto(robo.lerSensorLinhaDir2());
		}
	}
}

//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR UM POR UM ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarUmPorUm() {
	while((escolha != 'S') || (escolha != 's')) {
		Serial.print(F("PEGAR VALORES PARA")); 
		Serial.println(tipo);
		Serial.println(F("POSICIONE O SENSOR CORRETAMENTE..."));
		esperar_Posicionamento();

		Serial.println();
		Serial.println(F("ESCOLHA QUAL SENSOR QUERES PEGAR VALORES"));
		Serial.println(F("[E] maisEsq"));
		Serial.println(F("[e] Esq"));
		Serial.println(F("[d] Dir"));
		Serial.println(F("[D] maisDir"));
		Serial.println(F("[S] SALVAR"));
		esperarParaLer();
		escolha = Serial.read();

		switch (escolha) {
			case 'E': 
				if (tipo == "MINIMO BRANCO") refletancia_lido_esq2.setMinimoBranco(robo.lerSensorLinhaEsq2());
				else 						 refletancia_lido_esq2.setMaximoPreto(robo.lerSensorLinhaEsq2());
				break;
			case 'e': // Pega valor do sensor Esq e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") refletancia_lido_esq.setMinimoBranco(robo.lerSensorLinhaEsq());
				else 						 refletancia_lido_esq.setMaximoPreto(robo.lerSensorLinhaEsq());
				break;
			case 'd': // Pega valor do sensor Dir e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") refletancia_lido_dir.setMinimoBranco(robo.lerSensorLinhaDir());
				else 						 refletancia_lido_dir.setMaximoPreto(robo.lerSensorLinhaDir());
				break;
			case 'D': // Pega valor do sensor maisDir e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") refletancia_lido_dir2.setMinimoBranco(robo.lerSensorLinhaDir2());
				else 						 refletancia_lido_dir2.setMaximoPreto(robo.lerSensorLinhaDir2());
				break;
		}
	}
}

//~~~~~~~~~~~~ FERRAMENTAS ~~~~~~~~~~~~~//


void Calibracao::esperar_Posicionamento() {
	Serial.println(F("INSIRA ALGO NO SERIAL QUANDO TODOS OS SENSORES ESTIVEREM POSICIONADOS CORRETAMENTE."));
	Serial.println(F("maisEsq		---		Esq 	---		Dir 	---		maisDir"));
	while(!Serial.read()) {
		Serial.print(robo.lerSensorLinhaEsq2());
		Serial.print(F("		---		"));
		Serial.print(robo.lerSensorLinhaEsq());
		Serial.print(F("		---		"));
		Serial.print(robo.lerSensorLinhaDir());
		Serial.print(F("		---		"));
		Serial.print(robo.lerSensorLinhaDir2());
		Serial.println();
		delay(500);
	}
}

void Calibracao::esperarParaLer() {
	while(!Serial.available()) {}
}
