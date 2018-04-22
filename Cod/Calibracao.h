#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware.h>
#include "Sensores.h"

class Calibracao {
public:
	void run();
	Calibracao();
private:

	calibracao_dados cali;

	Sensores
	refletancia_lido_esq2, 
	refletancia_lido_esq,
	refletancia_lido_dir, 
	refletancia_lido_dir2;

	//~~~~~~~  MENU CALIBRACAO ~~~~~~~//
	
	void menuCalibracao();
	/* ?--
		Função inicial. É nela que decidiremos
		como será feita a calibração.*/
	void esperarParaLer();
	/* ?--
		Função ferramenta - 
		Usada para esperar a leitura do Serial.*/
	void esperar_Posicionamento();
	/* ?--
		Função ferramenta.
		Usada para esperar o posicionamento correto
		do(s) sensor(es).*/

	// Variáveis usadas para controlar o fluxo nos menus.
	char escolha; 
	bool save;
	bool exit;

	String tipo; // Usada para determinar se será lido branco ou preto.
	
	//~~~ FORMA DE PEGAR OS VALORES ~~~//
	
	void menuFormaPegarValores();
	void pegarUmPorUm();
	void pegarSimultaneamente();
};

#endif