#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware.h>
#include "Sensores.h"

//_______________________
#define NULLPRETO 0.0	
#define NULLBRANCO 100.0
/* ?--
	CONSTANTES usadas para passar "valores nulos" para as funções
	de leitura: calculeMinimoBranco(x,x,x,x) && calculeMaximoPreto(x,x,x,x).

	Quando for selecionado a calibração individual ou "Um-Por-Um", só será
	necessário a obtenção dos valores para um sensor. E temos que passar
	quatro parâmetros nas funções de leitura, usaremos as CONSTANTES para
	descartar qualquer leitura. */


class Calibracao {
public:
	void run();
	Calibracao();
private:

	calibracao_dados cali;

	Sensores 
	refletancia_lido_esq2, 
	refletancia_lido_esq2,
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