#include "Sensores_Refletancia.h"

Sensores_Refletancia::Sensores_Refletancia() {
	minimoBranco = 101;
	maximoPreto = 0;
	media = 0;
}

void Sensores_Refletancia::setMinimoBranco(float valor_lido) {
	if (valor_lido < minimoBranco) minimoBranco = valor_lido;
}

void Sensores_Refletancia::setMaximoPreto(float valor_lido) {
	if (valor_lido > maximoPreto) maximoPreto = valor_lido;
}

void Sensores_Refletancia::calculeMedia() {
	media = ((minimoBranco + maximoPreto)/2);
}

void Sensores_Refletancia::setMedia(float valor_media) {
	media = valor_media;
}

float Sensores_Refletancia::getSeparacao() { return media; }