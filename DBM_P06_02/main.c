#include <stdio.h>
#include <immintrin.h>

int fi_media_floats(float *ptr_datos, unsigned int longitud_array, float *ptr_resultado);

int main(){
	double m1[4][4] =							// Matriz de ejemplo
	{
			{1.0,	2.0,	3.0,	4.0},
			{5.0,	6.0,	7.0,	8.0},
			{9.0,	10.0,	11.0,	12.0},
			{13.0,	14.0,	15.0,	16.0}
	};

	double res[4][4];							// Matriz de resultado

	fi_sumar_matrices_4x4_double(m1, m1, res);	// Sumamos la matriz m1 consigo misma, es decir, se multiplica por 2 en este ejemplo

	for(int i=0; i<4; i++){						// Muestra en pantalla la matriz resultado
		for(int j=0; j<4; j++){
			printf("%.2f\t", res[i][j]);
		}
		printf("\n");
	}

	return 0;
}

int fi_sumar_matrices_4x4_double(const double *ptr_matriz_1, const double *ptr_matriz_2, double *ptr_matriz_suma){
	if(ptr_matriz_1 == NULL || ptr_matriz_2 == NULL || ptr_matriz_suma == NULL){
		return 0;								// Devolvemos 0 en caso de que algún puntero sea nulo
	}else{
		__m256d a, b;							// Creamos las variables que usan las funciones intrínsecas de AVX

		for(int i = 0; i<4; i++){				// Vamos recorriendo la matriz sumando de fila en fila
			a = _mm256_load_pd(ptr_matriz_1 + (4 * i));
			b = _mm256_load_pd(ptr_matriz_2 + (4 * i));

			_mm256_store_pd(ptr_matriz_suma + (4 * i), _mm256_add_pd(a, b));	// Realizamos la suma y almacenamos el resultado
		}

		return 1;								// Devolvemos 1 al finalizar la función con éxito
	}
}
