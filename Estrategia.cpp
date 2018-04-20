#include "Estrategia.h"

void Estrategia::run() {
	if (sonar.viuObstaculo(DISTANCIA_OBSTACULO)) {
		obstaculo.iniciar(DISTANCIA_OBSTACULO);
		/*
			A partir de qual DISTANCIA_OBSTACULO devo
		  	começar a desviar?
		*/
	} 
	else {
		seguirLinha();
	}
}

void Estrategia::seguirLinha() {
	if(sensor.dirViuPreto()) {
		motores.virarEsquerda();
	} 
	else if(sensor.esqViuPreto()) {
		motores.virarDireita();
	}
	else if(sensores.todosBrancos() ||
			sensores.todosPretos()
			)
	{
		motores.emFrente();
	} else {
		motores.parar(500);
		while(1){
			motores.virarEsquerda();
			delay(500);
			motores.virarDireita();
			delay(500);
		}
	}
	/*else {
		curvas();	
	}*/
}
/*
void Estrategia::curvas() {
	if(sensores.preto_preto_branco_branco()) {
		motores.virarEsquerda();
	}
	else if (sensores.branco_branco_preto_preto()){
		motores.virarDireita();
	}
	else {
		passarVerde();
	}
}
*/
/*
void Estrategia::passarVerde() {
	if (sensor.esqViuPreto()){
		while (!sensores.todosPretos()){
			motores.emFrente();
		}

	}
}*/
