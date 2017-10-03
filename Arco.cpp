#include "Arco.h"

	// template <typename un_tipo_de_costo> 
		Arco::Arco(const int d, const int c){	//Arco<un_tipo_de_costo>::
			destino= d;
			costo= c;

	}

	// template <typename un_tipo> 
		Arco::~Arco(){
	}


	// template <typename un_tipo_de_costo> 
		int Arco::Devolver_destino() const{
			return destino;
	}

	// template <typename un_tipo_de_costo> 
		int Arco::Devolver_costo() const{
			return costo;
	}
