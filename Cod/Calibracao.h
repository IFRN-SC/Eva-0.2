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
	
	float minimoEsq2;
	float minimoEsq;
	float minimoDir;
	float minimoDir2;

	void menuCalibracao();
	void esperarParaLer();

	void minimoBranco();
	void maximoPreto();
	
	void calculeMinimo(int valorEsq2,int valorEsq,int valorDir,int valorDir2);
	
	char escolha;
};

#endif