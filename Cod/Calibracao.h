#ifndef CALIBRACAO_H
#define CALIBRACAO_H

#include <robo_hardware.h>

class Calibracao {
public:

	void run();
	float getSeparacao(){ return (media); }
	
	float media; 

	Calibracao();
	
private:
	
	float minimoBrancoEsq2;
	float minimoBrancoEsq;
	float minimoBrancoDir;
	float minimoBrancoDir2;
	
	float maximoPretoEsq2;
	float maximoPretoEsq;
	float maximoPretoDir;
	float maximoPretoDir2;
	
	float mediaEsq2;
	float mediaEsq;
	float mediaDir;
	float mediaDir2;

	//~~~~~~~  MENU CALIBRACAO ~~~~~~~//
	
	void menuCalibracao();
	void esperarParaLer();
	
	String tipoCompleto;
	char escolha;
	
	// FORMA DE PEGAR OS VALORES
	
	void menuFormaPegarValores(char tipo);
	void pegarUmPorUm(char tipo);
	void pegarSimultaneamente(char tipo);
	
	void calculeMinimoBranco(float valorEsq2,float valorEsq,float valorDir,float valorDir2);
	void calculeMaximoPreto(float valorEsq2,float valorEsq,float valorDir,float valorDir2);
	
};

#endif