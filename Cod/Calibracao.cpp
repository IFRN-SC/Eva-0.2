#include "Calibracao.h"

//~~~~~~~~~~~~~~~~~~ CONSTRUTOR ~~~~~~~~~~~~~~~~~~//

Calibracao::Calibracao() { escolha = ' '; }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void Calibracao::run() { menuCalibracao(); }

//~~~~~~~~~~~~~~~~~~ MENU INICIAL ~~~~~~~~~~~~~~~~~~//

void Calibracao::menuCalibracao() {
	while(1) {
		
		Serial.println(F("\n[---| MENU CALIBRACAO |---]"));
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
				break;
		}
	}
	if ((escolha != 'D') && (escolha != 'd')) {

		cali.refletancia_mais_esq	= refletancia_lido_esq2.getSeparacao();
		cali.refletancia_esq 		= refletancia_lido_esq.getSeparacao();
		cali.refletancia_dir 		= refletancia_lido_dir.getSeparacao();
		cali.refletancia_mais_dir 	= refletancia_lido_dir2.getSeparacao();

		Serial.println(F("Calibracao salva com sucesso!"));
		robo.salvarCalibracao(cali);
	} else {
		Serial.println(F("Calibracao descartada."));
	}
}

//~~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR OS VALORES ~~~~~~~~~~~~~~~~~~~//

void Calibracao::menuFormaPegarValores() {
	while ((escolha != 'V') && (escolha != 'v')) {

		Serial.println();
		Serial.print(F("CALIBRAR "));
		Serial.println(tipo);
		Serial.println(F("DE QUE FORMA QUERES PEGAR OS VALORES?"));
		Serial.println();
		Serial.println(F("[S] TODOS OS SENSORES SIMULTANEAMENTE"));
		Serial.println(F("[U] UM POR UM"));
		Serial.println(F("[V] VOLTAR"));
		esperarParaLer();
		escolha = Serial.read();
		
		if ((escolha == 'S') || (escolha == 's'))	pegarSimultaneamente();
		else if ((escolha == 'U') || (escolha == 'u')) pegarUmPorUm();
	}
	escolha = ' ';
}


//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR SIMULTANEAMENTE ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarSimultaneamente() {
	Serial.println();
	Serial.print(F("CALIBRAR "));
	Serial.println(tipo);
	Serial.print(F("POSICIONE TODOS OS SENSORES PARA PEGAR O "));
	Serial.println(tipo);
	esperar_Posicionamento();

	//exit = false;
	while ((escolha != 'V') && (escolha != 'v')) {
		Serial.println();
		Serial.println(F("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n"));
		Serial.println(F("[V] VOLTAR"));
		esperarParaLer();
		escolha = Serial.read();

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
	escolha = ' ';
	menuCalibracao();
}

//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR UM POR UM ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarUmPorUm() {
	char sensor = ' '; // Uso temporário?

	Serial.println();
	Serial.print(F("PEGAR VALORES PARA ")); 
	Serial.println(tipo);
	
	while ((escolha != 'S') && (escolha != 's')) {

		Serial.println();
		Serial.println(F("ESCOLHA QUAL SENSOR QUERES PEGAR VALORES"));
		Serial.println(F("[E] maisEsq"));
		Serial.println(F("[e] Esq"));
		Serial.println(F("[d] Dir"));
		Serial.println(F("[D] maisDir"));
		Serial.println(F("[S] SALVAR"));
		esperarParaLer();
		escolha = Serial.read();
		
		while ( (escolha != 'V') && (escolha != 'v'))	{
			Serial.println(F("POSICIONE O SENSOR CORRETAMENTE..."));
			esperar_Posicionamento();
			
			Serial.println();
			Serial.println(F("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n"));
			Serial.println(F("[V] VOLTAR"));
			esperarParaLer();
			escolha = Serial.read();
	
			switch (sensor) {
				case 'E': 	
					if (tipo == "MINIMO BRANCO") {
						refletancia_lido_esq.setMinimoBranco(robo.lerSensorLinhaEsq());
					}
					else {
						refletancia_lido_esq.setMaximoPreto(robo.lerSensorLinhaEsq());
					}	
					Serial.println(F("\n(maisEsq)"));
					Serial.print(robo.lerSensorLinhaDir());				 
					break;					

				case 'e': // Pega valor do sensor Esq e descarta a leitura dos outros sensores.
					if (tipo == "MINIMO BRANCO") {
						refletancia_lido_esq.setMinimoBranco(robo.lerSensorLinhaEsq());
					}
					else {
						refletancia_lido_esq.setMaximoPreto(robo.lerSensorLinhaEsq());
					}
					Serial.println(F("\n(Esq)"));
					Serial.print(robo.lerSensorLinhaDir());					 
					break;
				
				case 'd': // Pega valor do sensor Dir e descarta a leitura dos outros sensores.
					if (tipo == "MINIMO BRANCO") {
						refletancia_lido_dir.setMinimoBranco(robo.lerSensorLinhaDir());
					}
					else {
						refletancia_lido_dir.setMaximoPreto(robo.lerSensorLinhaDir());		
					}
					Serial.println(F("\n(Dir)"));
					Serial.print(robo.lerSensorLinhaDir()); 						 
					break;
				
				case 'D': // Pega valor do sensor maisDir e descarta a leitura dos outros sensores.
					if (tipo == "MINIMO BRANCO") {
						refletancia_lido_dir2.setMinimoBranco(robo.lerSensorLinhaDir2());
					}
					else {
						refletancia_lido_dir2.setMaximoPreto(robo.lerSensorLinhaDir2());						
					}
					Serial.println(F("\n(maisDir)"));
					Serial.print(robo.lerSensorLinhaDir2());				
					break;
			}
			Serial.println();
		}
	}
	escolha = ' ';
	menuCalibracao();
}

//~~~~~~~~~~~~ FERRAMENTAS ~~~~~~~~~~~~~//


void Calibracao::esperar_Posicionamento() {
	Serial.println();
	Serial.println(F("INSIRA ALGO NO SERIAL QUANDO TODOS OS SENSORES ESTIVEREM POSICIONADOS CORRETAMENTE.\n"));
	Serial.println(F("(maisEsq)	---		(Esq)		---		(Dir)		---		(maisDir)\n"));
	while(1) {
		Serial.print(robo.lerSensorLinhaEsq2());
		Serial.print(F("		---		"));
		Serial.print(robo.lerSensorLinhaEsq());
		Serial.print(F("		---		"));
		Serial.print(robo.lerSensorLinhaDir());
		Serial.print(F("		---		"));
		Serial.print(robo.lerSensorLinhaDir2());
		Serial.println();
		delay(1000);

		if(Serial.available()) {
			Serial.read();
			break;
		}
	}
}

void Calibracao::esperarParaLer() {
	while(!Serial.available()) {}
}
