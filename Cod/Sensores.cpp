#include "Sensores.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~ SONARES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

bool Sensores::sonarViuObstaculo(int DISTANCIA_OBSTACULO) {
	return (robo.lerSensorSonarFrontal() <= DISTANCIA_OBSTACULO);
}

bool Sensores::sonarLateralViuRampa(int DISTANCIA_RAMPA) {
	if (robo.lerSensorSonarLateral() <= DISTANCIA_RAMPA) { // ! NEW
		robo.acionarMotores(0,0); // ! NEW
		delay(300); // ! NEW
		if (robo.lerSensorSonarLateral() <= DISTANCIA_RAMPA) { // ! NEW
			leds.piscar(10); // ! NEW
			return true; // ! NEW
		} // ! NEW
		else { // ! NEW
			leds.piscar(11); // ! NEW
			return false; // ! NEW
		}

		//return (robo.lerSensorSonarLateral() <= DISTANCIA_RAMPA);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~ CASOS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//------------------------------------------------------------------
// Caso "Todos" ----------------------------------------------------
bool Sensores::branco_branco_branco_branco() {
	return(
		maisEsqViuBranco() &&
		esqViuBranco() &&
		dirViuBranco() &&
		maisDirViuBranco()
	);
}

bool Sensores::preto_preto_preto_preto() {
	return(
		maisEsqViuPreto() &&
		esqViuPreto() &&
		dirViuPreto() &&
		maisDirViuPreto()
	);
}

//------------------------------------------------------------------
// Caso "Internos" -------------------------------------------------
bool Sensores::branco_preto_branco_branco() {
	return(
		maisEsqViuBranco() &&
		esqViuPreto() &&
		dirViuBranco() &&
		maisDirViuBranco()
	);
}

bool Sensores::branco_branco_preto_branco() {
	return(
		maisEsqViuBranco() &&
		esqViuBranco() &&
		dirViuPreto() &&
		maisDirViuBranco()
	);
}

//------------------------------------------------------------------
// Caso "Externos" -------------------------------------------------
bool Sensores::preto_branco_branco_branco() {
	return(
		maisEsqViuPreto() &&
		maisEsqViuPreto() &&
		maisEsqViuPreto() &&
		maisEsqViuPreto() &&
		esqViuBranco() &&
		dirViuBranco() &&
		maisDirViuBranco()
	);
}

bool Sensores::branco_branco_branco_preto() {
	return(
		maisEsqViuBranco() &&
		esqViuBranco() &&
		dirViuBranco() &&
		maisDirViuPreto()
	);
}

//------------------------------------------------------------------
// Caso "Duplo" ----------------------------------------------------
bool Sensores::preto_preto_branco_branco() {
	return(
		maisEsqViuPreto() &&
		esqViuPreto() &&
		dirViuBranco() &&
		maisDirViuBranco()
	);
}

bool Sensores::branco_branco_preto_preto() {
	return(
		maisEsqViuBranco() &&
		esqViuBranco() &&
		dirViuPreto() &&
		maisDirViuPreto()
	);
}

//--------------------------------------------------------------------
// Caso "Triplo" -----------------------------------------------------
bool Sensores::preto_preto_preto_branco() {
	return(
		maisEsqViuPreto() &&
		esqViuPreto() &&
		dirViuPreto() &&
		maisDirViuBranco()
	);
}

bool Sensores::branco_preto_preto_preto() {
	return(
		maisEsqViuBranco() &&
		esqViuPreto() &&
		dirViuPreto() &&
		maisDirViuPreto()
	);
}

//--------------------------------------------------------------------
// Caso "Alternados" -------------------------------------------------
bool Sensores::preto_branco_preto_branco() {
	return(
		maisEsqViuPreto() &&
		esqViuBranco() &&
		dirViuPreto() &&
		maisDirViuBranco()
	);
}

bool Sensores::branco_preto_branco_preto() {
	return(
		maisEsqViuBranco() &&
		esqViuPreto() &&
		dirViuBranco() &&
		maisDirViuPreto()
	);
}

//--------------------------------------------------------------------
// Caso "Internos brancos" -------------------------------------------
bool Sensores::preto_preto_branco_preto() {
	return(
		maisEsqViuPreto() &&
		esqViuPreto() &&
		dirViuBranco() &&
		maisDirViuPreto()
	);
}

bool Sensores::preto_branco_preto_preto() {
	return(
		maisEsqViuPreto() &&
		esqViuBranco() &&
		dirViuPreto() &&
		maisDirViuPreto()
	);
}

//-------------------------------------------------------------------
// Caso "Duplo preto" -----------------------------------------------
bool Sensores::branco_preto_preto_branco() {
	return(
		maisEsqViuBranco() &&
		esqViuPreto() &&
		dirViuPreto() &&
		maisDirViuBranco()
	);
}

bool Sensores::preto_branco_branco_preto() {
	return(
		maisEsqViuPreto() &&
		esqViuBranco() &&
		dirViuBranco() &&
		maisDirViuPreto()
	);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~-	 INDIVIDUAIS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

bool Sensores::maisEsqViuBranco() {
	return (robo.lerSensorLinhaEsq2() > refletancia_esq2.getSeparacao()); 
}

bool Sensores::maisEsqViuPreto() {
	return (robo.lerSensorLinhaEsq2() <= refletancia_esq2.getSeparacao());  
}

bool Sensores::esqViuBranco() {
	return (robo.lerSensorLinhaEsq() > refletancia_esq.getSeparacao()); 
}

bool Sensores::esqViuPreto() {
	return (robo.lerSensorLinhaEsq() <= refletancia_esq.getSeparacao());  
}

bool Sensores::dirViuBranco() {
	return (robo.lerSensorLinhaDir() > refletancia_dir.getSeparacao());  	
}

bool Sensores::dirViuPreto() {
	return (robo.lerSensorLinhaDir() <= refletancia_dir.getSeparacao());  		
}

bool Sensores::maisDirViuBranco() {
	return (robo.lerSensorLinhaDir2() > refletancia_dir2.getSeparacao());  	
}   

bool Sensores::maisDirViuPreto() {
	return (robo.lerSensorLinhaDir2() <= refletancia_dir2.getSeparacao());  
} 