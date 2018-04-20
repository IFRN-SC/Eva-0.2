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

	void menuCalibracao();
	void esperarParaLer();

	void minimoBranco();
	void maximoPreto();
	
	void calculeMinimo(int valorEsq2,int valorEsq,int valorDir,int valorDir2);
	
	char escolha;
};

#endif