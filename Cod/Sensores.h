#ifndef SENSORES_H
#define SENSORES_H

#include <robo_hardware.h>
#include "Calibracao.h"

class Sensores: public Calibracao {
public:

	//~~~~~~~~~~~ SONAR ~~~~~~~~~~~//

	bool sonarViuObstaculo(int DISTANCIA_OBSTACULO);
	/* ?--
		Função usada para verificar
	   se o sonar frontal viu ou não um obstáculo.
	   A "distância" entre o robô e o obstáculo é 
	   definida na classe Estrategia.h -*/

	//~~~~~~~~~ SENSORES DE REFLETÂNCIA ~~~~~~~~~//

	// Caso "Todos"

	bool branco_branco_branco_branco();
	bool preto_preto_preto_preto();

	// Caso "Internos"

	bool branco_preto_branco_branco();
	bool branco_branco_preto_branco();

	// Caso "Externos"

	bool preto_branco_branco_branco();
	bool branco_branco_branco_preto();

	// Caso "Duplo"

	bool preto_preto_branco_branco();
	bool branco_branco_preto_preto();

	// Caso "Triplo"

	bool preto_preto_preto_branco();
	bool branco_preto_preto_preto();

	// Caso "Alternados"

	bool preto_branco_preto_branco();
	bool branco_preto_branco_preto();

	// Caso "Interno branco"

	bool preto_branco_preto_preto();
	bool preto_preto_branco_preto();

	// Caso "Duplo preto"

	bool preto_branco_branco_preto();
	bool branco_preto_preto_branco();

	// Funções individuais

	bool maisEsqViuBranco();
	bool maisEsqViuPreto();
	bool esqViuBranco();
	bool esqViuPreto();
	bool dirViuBranco();
	bool dirViuPreto();
	bool maisDirViuBranco();
	bool maisDirViuPreto();




	//~~~~~~~~~~~ CALIBRAÇÃO DOS SENSORES ~~~~~~~~~~~//

	/*
	void setMinimoBranco(float valor_lido);
	void setMaximoPreto(float valor_lido);
	void calculeMedia(float minimoBranco,float maximoPreto);
	float getSeparacao();
	*/

private:

	//calibracao_dados separacao;

	//~~~~~~~~~~~ CALIBRAÇÃO DOS SENSORES ~~~~~~~~~~~//

	//float minimoBranco;
	/* ?--
		Variável que guardará o mínimo
		valor lido para branco de cada sensor de refletância.*/
	//float maximoPreto;
	/* ?--
		Variável que guardará o máximo
		valores lido para branco de cada sensor de refletância.*/
	//float media;
	/* ?--
		Variáveis que guardam a média
		de branco_preto para todos os sensores.*/

};

#endif