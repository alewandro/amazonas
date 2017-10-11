#ifndef ARCO_H
#define ARCO_H

//template <typename un_tipo_de_costo> 
	class Arco{
		public:
			Arco(const int d, const int c);  //const un_tipo_de_costo c
			
			virtual ~Arco();

			int Devolver_destino() const;
			int Devolver_costo() const;

		private:
			int destino;
			int costo;  //un_tipo_de_costo

};

#endif