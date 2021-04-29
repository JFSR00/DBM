#include <stdio.h>
#include <immintrin.h>

int fi_media_floats(float *ptr_datos, unsigned int longitud_array, float *ptr_resultado);

int main(){
	float m1[17] __attribute__ ((aligned (32))) =	// Matriz de ejemplo
	{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0 };

	float res __attribute__ ((aligned (32)));	// Variable del resultado

	fi_media_floats(m1, 17, &res);				// Calculamos la media de la matriz de ejemplo, el resultado debe ser 9

	printf("%.2f\t", res);						// Muestra en pantalla el resultado de la operación

	return 0;
}

int fi_media_floats(float *ptr_datos, unsigned int longitud_array, float *ptr_resultado){
	if(ptr_datos == NULL || ptr_resultado == NULL || longitud_array == 0){
		return 0;								// Devolvemos 0 en caso de que algún puntero sea nulo o la longitud 0
	}else{
		__m256 inter, v;						// inter servirá para el cálculo de la media, v contendrá la suma de
												// todos los elementos del array
		__m128 resultado;						// res contendrá el resultado de la media

		unsigned int n_bloques = longitud_array / 8;
		unsigned int resto = longitud_array % 8;

		float res;

		v = _mm256_set1_ps(0.0);			// Ponemos a 0 la variable media

		while(n_bloques > 0){					// Caso para más de 8 elementos
			v = _mm256_add_ps(v, _mm256_load_ps(ptr_datos));
			n_bloques--;
			ptr_datos += 8;
		}

		v = _mm256_hadd_ps(v, v);
		v = _mm256_hadd_ps(v, v);
		//media = _mm256_hadd_ps(media, media);

		inter = _mm256_permute2f128_ps(v, v, 1);
		inter = _mm256_add_ps(inter, v);

		resultado = _mm256_castps256_ps128(inter);

		_mm_store_ss(&res, resultado);

		while(resto > 0){						// Caso para menos de 8 elementos
			res += *ptr_datos;
			ptr_datos++;
			resto--;
		}

		*ptr_resultado = res / longitud_array;

		return 1;								// Devolvemos 1 al finalizar la función con éxito
	}
}
