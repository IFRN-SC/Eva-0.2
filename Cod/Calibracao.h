#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware.h>
#include "Sensores_Refletancia.h"

class Calibracao {
public:
	
	void run();
	Calibracao();

	void lerValoresCalibrados();

private:	

	calibracao_dados cali;

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

protected:
	Sensores_Refletancia
	refletancia_esq2, 
	refletancia_esq,
	refletancia_dir, 
	refletancia_dir2;
};

#endif