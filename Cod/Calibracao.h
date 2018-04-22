#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware.h>

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
	
	float mediaEsq2;
	float mediaEsq;
	float mediaDir;
	float mediaDir2;
	/* ?--
		Variáveis que guardam a média
		de branco_preto para todos os sensores.*/
	
private:
	
	float minimoBrancoEsq2;
	float minimoBrancoEsq;
	float minimoBrancoDir;
	float minimoBrancoDir2;
	/* ?--
		Variáveis que guardarão o mínimo
		valor lido para branco de cada sensor de refletância.*/
	
	float maximoPretoEsq2;
	float maximoPretoEsq;
	float maximoPretoDir;
	float maximoPretoDir2;
	/* ?--
		Variáveis que guardarão o máximo
		valores lido para branco de cada sensor de refletância.*/

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

	char escolha; // Usada para controlar o fluxo nos menus.
	String tipo; // Usada para determinar se será lido branco ou preto.
	
	//~~~ FORMA DE PEGAR OS VALORES ~~~//
	
	void menuFormaPegarValores();
	void pegarUmPorUm();
	void pegarSimultaneamente();
	
	void calculeMinimoBranco(float valorEsq2,float valorEsq,float valorDir,float valorDir2);
	void calculeMaximoPreto(float valorEsq2,float valorEsq,float valorDir,float valorDir2);
	
};

#endif