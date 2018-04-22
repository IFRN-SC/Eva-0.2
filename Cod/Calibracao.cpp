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
		
		Serial.println();
		Serial.println("[---| MENU CALIBRACAO |---]");
		Serial.println("O QUE DESEJAS SENHOR?");
		Serial.println("[B] MINIMO BRANCO.");
		Serial.println("[P] MAXIMO PRETO.");
		Serial.println("[S] SALVAR.");
		Serial.println("[D] DESCARTAR CALIBRACAO")
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

		cali.refletancia_mais_esq = refletancia_lido_esq2.getSeparacao();
		cali.refletancia_esq = refletancia_lido_esq.getSeparacao();
		cali.refletancia_dir = refletancia_lido_dir.getSeparacao();
		cali.refletancia_mais_dir = refletancia_lido_dir2.getSeparacao();

		robo.salvarCalibracao(cali);	
	}
}

//~~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR OS VALORES ~~~~~~~~~~~~~~~~~~~//

void Calibracao::menuFormaPegarValores() {
	while (!exit) {

		Serial.println();
		Serial.println("CALIBRAR " + tipo);
		Serial.println("DE QUE FORMA QUERES PEGAR OS VALORES?");
		Serial.println("[S] TODOS OS SENSORES SIMULTANEAMENTE");
		Serial.println("[U] UM POR UM");
		Serial.println("[V] VOLTAR");
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
	Serial.println();
	Serial.println("CALIBRAR "+ tipo);
	Serial.println("POSICIONE TODOS OS SENSORES PARA PEGAR O " + tipo);
	esperar_Posicionamento();

	
	while (!exit) {
		Serial.println("INSIRA ALGUMA COISA PARA PEGAR OS VALORES.\n");
		Serial.println("[V] VOLTAR");
		esperarParaLer();
		escolha = Serial.read();
		
		if ((escolha != 'V') || (escolha != 'v')) exit = true; break;
			
		if (tipo == "MINIMO BRANCO"){
			refletancia_lido_esq2.setMinimoBranco();
			refletancia_lido_esq.setMinimoBranco();
			refletancia_lido_dir.setMinimoBranco();
			refletancia_lido_dir2.setMinimoBranco();
		}
		else {
			refletancia_lido_esq2.setMaximoPreto();
			refletancia_lido_esq.setMaximoPreto();
			refletancia_lido_dir.setMaximoPreto();
			refletancia_lido_dir2.setMaximoPreto();
		}
	}
}

//~~~~~~~~~~~~~~~~~~ FORMA DE PEGAR UM POR UM ~~~~~~~~~~~~~~~~~~//

void Calibracao::pegarUmPorUm() {
	while((escolha != 'S') || (escolha != 's')) {
		Serial.println();
		Serial.println("PEGAR VALORES PARA" + tipo);
		Serial.println("POSICIONE O SENSOR CORRETAMENTE...");
		esperar_Posicionamento();

		Serial.println();
		Serial.println("ESCOLHA QUAL SENSOR QUERES PEGAR VALORES");
		Serial.println("[E] maisEsq");
		Serial.println("[e] Esq");
		Serial.println("[d] Dir");
		Serial.println("[D] maisDir");+
		Serial.println("[S] SALVAR");
		esperarParaLer();
		escolha = Serial.read();

		switch (escolha) {
			case 'E': 
				if (tipo == "MINIMO BRANCO") refletancia_lido_esq2.setMinimoBranco();
				else 						 refletancia_lido_esq2.setMaximoPreto();
				break;
			case 'e': // Pega valor do sensor Esq e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") refletancia_lido_esq.setMinimoBranco();
				else 						 refletancia_lido_esq.setMaximoPreto();
				break;
			case 'd': // Pega valor do sensor Dir e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") refletancia_lido_dir.setMinimoBranco();
				else 						 refletancia_lido_dir.setMaximoPreto();
				break;
			case 'D': // Pega valor do sensor maisDir e descarta a leitura dos outros sensores.
				if (tipo == "MINIMO BRANCO") refletancia_lido_dir2.setMinimoBranco();
				else 						 refletancia_lido_dir2.setMaximoPreto();
				break;
		}
	}
}

//~~~~~~~~~~~~ FERRAMENTAS ~~~~~~~~~~~~~//


void Calibracao::esperar_Posicionamento() {
	Serial.println("INSIRA ALGO NO SERIAL QUANDO TODOS OS SENSORES ESTIVEREM POSICIONADOS CORRETAMENTE.");
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
