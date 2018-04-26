#ifndef SENSORES_REFLETANCIA
#define SENSORES_REFLETANCIA

#include <robo_hardware.h>

class Sensores_Refletancia {
public:

	void setMinimoBranco(float valor_lido);
	void setMaximoPreto(float valor_lido);
	void setMedia(float minimoBranco, float maximoPreto);

	float getSeparacao();

private:

	float minimoBranco;
	/* ?--
		Variável que guardará o mínimo
		valor lido para branco de cada sensor de refletância.*/
	float maximoPreto;
	/* ?--
		Variável que guardará o máximo
		valores lido para branco de cada sensor de refletância.*/
	float media;
	/* ?--
		Variáveis que guardam a média
		de branco_preto para todos os sensores.*/
};

#endif