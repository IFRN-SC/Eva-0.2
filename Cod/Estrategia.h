#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H
 
#include "Sensores.h"
/* !-- Serão usadas as funções que retornam verdadeiro
	   quando os sensores vizualiam preto.

	   Ex.: 
	   		1 - sensores.preto_branco_branco_branco() == true;
		 	2 - sensores.preto_branco_preto_branco() == false;

	   		1 - O sensor maisEsq viu preto.
	   		2 - Os sensores maisEsq e Dir não viram preto.
*/
#include "Motores.h"
/* !-- Serão usadas funções de movimentação básica do robô.
	   Ex.:
	   		1- motores.emFrente();
	   		2- motores.recuar();

	   		1 - Ordena que os motores façam o robô ir para frente
	   		com uma velocidade padrão (VEL).
			2 - Ordena que os motores façam o robô recuar
			com uma velocidade padrão (VEL).

			(VEL -> definida em Motores.h)
*/
#include "Calibracao.h"
/* !-- Será utilizada a função padrão de run().
	   na função calibrar() Estrategia.cpp::15;
*/

#define DISTANCIA_OBSTACULO 10
/* !-- Define a partir de qual valor retornado pelo
	   sonar frontal o robô irá considerar que há
	   um obstáculo em sua frente.
*/

class Estrategia {
public:
	void run();
	/* !--run > 
		Principal função da classe Estrategia.
		
		Serão tratada situações em que:

		- Sensores virem preto;
		- Sensores virem verde;
		- Sonar detectar obstáculos;
	*/
	void calibrar(bool value);
	/* !--calibrar >
		Função realizada para calibrar a partir dos
		sensores de refletância, o valor de SEPARACAO_BRANCO_PRETO.

		(SEPARACAO_BRANCO_PRETO -> Calibracao.h).
	*/
private:
	void seguirLinha();
	/* !--seguirLinha >
		Função que corrige a trajetória do robô
		caso alguns dos sensores virem preto.
	*/
	void desviarObstaculo();
	/* !--desviarObstaculo >
		Função que realiza a estratégia do desvio
		de obstáculos.
	*/

	void impulso(); // Funciona que impulsiona o robô
	
	//void passarVerde();

	Calibracao calibracao;
	Sensores sensores;
	Motores motores;
};
 
 #endif