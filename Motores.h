#ifndef MOTORES_H
#define MOTORES_H

//#include "Setup.h"
#include <robo_hardware.h>

#define VEL 40

class Motores {
public:
	//~~~~~~~~~~~~ Funções de movimentação básica ~~~~~~~~~~~~~~~~~~//
	
	void avancar() { robo.acionarMotores(VEL,VEL); }
	void virarEsquerda() { robo.acionarMotores(VEL,VEL *(-1)); }
	void virarDireita() { robo.acionarMotores(VEL *(-1),VEL); }

	void virarEixoEsq() { robo.acionarMotores(0,VEL); }
	void virarEixoDir() { robo.acionarMotores(VEL,0); }

	void parar(int tempo) {
		robo.acionarMotores(0,0); 
		delay(tempo);
	}
	void recuar(int tempo) {
		robo.acionarMotores(VEL * (-1),VEL * (-1));
		delay(tempo);
	}
};

#endif