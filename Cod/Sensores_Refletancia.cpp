#include "Sensores_Refletancia.h"

void Sensores_Refletancia::setMinimoBranco(float valor_lido) {
	if (valor_lido < minimoBranco) minimoBranco = valor_lido;
}

void Sensores_Refletancia::setMaximoPreto(float valor_lido) {
	if (valor_lido > maximoPreto) maximoPreto = valor_lido; 
}

void Sensores_Refletancia::calculeMedia(float minimoBranco,float maximoPreto) {
	media = ((minimoBranco + maximoPreto)/6);
}

float Sensores::getSeparacao() { return media; }