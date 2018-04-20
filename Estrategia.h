#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

//#include "Setup.h"
#include "Sonares.h"
#include "Sensores.h"
#include "Obstaculo.h"
#include "Motores.h"


class Estrategia {
public:
	
	void run();
private:

	void seguirLinha();
	void curvas();
	void viuObstaculo();
	//void passarVerde();

	Sonares sonar;
	Sensores sensores;
	Obstaculo obstaculo;
	Motores motores;
};

#endif
