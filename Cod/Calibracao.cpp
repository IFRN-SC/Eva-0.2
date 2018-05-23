#include "Calibracao.h"

//~~~~~~~~~~~~~~~~~~ CONSTRUTOR ~~~~~~~~~~~~~~~~~~//

Calibracao::Calibracao() { escolha = ' '; }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void Calibracao::run() { menuCalibracao(); }

//~~~~~~~~~~~~~~~~~~ MENU INICIAL ~~~~~~~~~~~~~~~~~~//

void Calibracao::menuCalibracao() {
	while (((escolha != 'S') && (escolha != 'D')) && ((escolha != 's') && (escolha != 'd'))) {
		
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
		}
	}

	if ((escolha != 'D') && (escolha != 'd')) {

		refletancia_esq2.calculeMedia();
		refletancia_esq.calculeMedia();
		refletancia_dir.calculeMedia();
		refletancia_dir2.calculeMedia();
		
		cali.refletancia_mais_esq	= refletancia_esq2.getSeparacao();
		cali.refletancia_esq 		= refletancia_esq.getSeparacao();
		cali.refletancia_dir 		= refletancia_dir.getSeparacao();
		cali.refletancia_mais_dir 	= refletancia_dir2.getSeparacao();
  
		robo.salvarCalibracao(cali);
		Serial.println(F("Calibracao salva com sucesso!"));
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

		if ((escolha != 'V') && (escolha != 'v')) {
			if (tipo == "MINIMO BRANCO"){
				refletancia_esq2.setMinimoBranco(robo.lerSensorLinhaEsq2());
				refletancia_esq.setMinimoBranco(robo.lerSensorLinhaEsq());
				refletancia_dir.setMinimoBranco(robo.lerSensorLinhaDir());
				refletancia_dir2.setMinimoBranco(robo.lerSensorLinhaDir2());
			}
			else {
				refletancia_esq2.setMaximoPreto(robo.lerSensorLinhaEsq2());
				refletancia_esq.setMaximoPreto(robo.lerSensorLinhaEsq());
				refletancia_dir.setMaximoPreto(robo.lerSensorLinhaDir());
				refletancia_dir2.setMaximoPreto(robo.lerSensorLinhaDir2());
			}

			Serial.println(F("\n(maisEsq)	---		(Esq)		---		(Dir)		---		(maisDir)\n"));
			Serial.print(robo.lerSensorLinhaEsq2());
			Serial.print(F("		---		"));
			Serial.print(robo.lerSensorLinhaEsq());
			Serial.print(F("		---		"));
			Serial.print(robo.lerSensorLinhaDir());
			Serial.print(F("		---		"));
			Serial.print(robo.lerSensorLinhaDir2());
			Serial.println();
		}
	}
}

//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR UM POR UM ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarUmPorUm() {
	char sensor = ' '; // Uso temporário?

	Serial.println();
	Serial.print(F("PEGAR VALORES PARA ")); 
	Serial.println(tipo);

	while ((escolha != 'V') && (escolha != 'v')) {

		Serial.println();
		Serial.println(F("ESCOLHA QUAL SENSOR QUERES PEGAR VALORES"));
		Serial.println(F("[E] maisEsq"));
		Serial.println(F("[e] Esq"));
		Serial.println(F("[d] Dir"));
		Serial.println(F("[D] maisDir"));
		Serial.println(F("[V] VOLTAR"));
		esperarParaLer();
		escolha = Serial.read();
		sensor = escolha;

		while ((escolha != 'V') && (escolha != 'v'))	{
			Serial.println(F("POSICIONE O SENSOR CORRETAMENTE..."));
			esperar_Posicionamento();
			
			Serial.println();
			Serial.println(F("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n"));
			Serial.println(F("[V] VOLTAR"));
			esperarParaLer();
			escolha = Serial.read();
	
			switch (sensor) {
				case 'E':  // Pega SOMENTE o valor do sensor esq2 e descarta a leitura dos outros sensores. 	
					if (tipo == "MINIMO BRANCO") {
						refletancia_esq.setMinimoBranco(robo.lerSensorLinhaEsq2());
					}
					else {
						refletancia_esq.setMaximoPreto(robo.lerSensorLinhaEsq2());
					}	
					escolha = ' ';				 
					Serial.println(F("\n(esq2)"));
					Serial.print(robo.lerSensorLinhaEsq2());
					Serial.println();
					break;					

				case 'e': // Pega SOMENTE o valor do sensor Esq e descarta a leitura dos outros sensores.
					if (tipo == "MINIMO BRANCO") {
						refletancia_esq.setMinimoBranco(robo.lerSensorLinhaEsq());
					}
					else {
						refletancia_esq.setMaximoPreto(robo.lerSensorLinhaEsq());
					}
					escolha = ' ';
					Serial.println(F("\n(Esq)"));
					Serial.print(robo.lerSensorLinhaEsq());	
					Serial.println();				 
					break;
				
				case 'd': // Pega SOMENTE o  valor do sensor Dir e descarta a leitura dos outros sensores.
					if (tipo == "MINIMO BRANCO") {
						refletancia_dir.setMinimoBranco(robo.lerSensorLinhaDir());
					}
					else {
						refletancia_dir.setMaximoPreto(robo.lerSensorLinhaDir());		
					}
					escolha = ' ';
					Serial.println(F("\n(Dir)"));
					Serial.print(robo.lerSensorLinhaDir()); 
					Serial.println();						 
					break;
				
				case 'D': // Pega SOMENTE o  valor do sensor dir2 e descarta a leitura dos outros sensores.
					if (tipo == "MINIMO BRANCO") {
						refletancia_dir2.setMinimoBranco(robo.lerSensorLinhaDir2());
					}
					else {
						refletancia_dir2.setMaximoPreto(robo.lerSensorLinhaDir2());						
					}
					escolha = ' ';
					Serial.println(F("\n(dir2)"));
					Serial.print(robo.lerSensorLinhaDir2());
					Serial.println();				
					break;
			}
			Serial.println();
		}
	}
}


void Calibracao::lerValoresCalibrados(){
	robo.lerCalibracao(cali);

	refletancia_esq2.setMedia(cali.refletancia_mais_esq);
	refletancia_esq.setMedia(cali.refletancia_esq);
	refletancia_dir.setMedia(cali.refletancia_dir);
	refletancia_dir2.setMedia(cali.refletancia_mais_dir);

	Serial.println("EEMPROM");
	Serial.println(cali.refletancia_mais_esq);
	Serial.println(cali.refletancia_esq);
	Serial.println(cali.refletancia_dir);
	Serial.println(cali.refletancia_mais_dir);

	Serial.println("GET_SEPARACAO");
	Serial.println(refletancia_esq2.getSeparacao());
	Serial.println(refletancia_esq.getSeparacao());
	Serial.println(refletancia_dir.getSeparacao());
	Serial.println(refletancia_dir2.getSeparacao());
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
