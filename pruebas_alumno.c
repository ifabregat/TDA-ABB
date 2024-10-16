#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *abb_raiz(abb_t *abb)
{
	if (abb == NULL)
		return NULL;

	return abb->raiz->elemento;
}

int comparador_enteros(void *elemento1, void *elemento2)
{
	if (elemento1 == NULL || elemento2 == NULL)
		return 0;

	return *(int *)elemento1 - *(int *)elemento2;
}

void destructor(void *elemento)
{
	free(elemento);
}

void creacionComparadorNULL()
{
	abb_t *abb = abb_crear(NULL);
	pa2m_afirmar(abb == NULL, "No se puede crear un ABB sin comparador");
	free(abb);
}

void creacionComparadorValido()
{
	abb_t *abb = abb_crear(comparador_enteros);
	pa2m_afirmar(abb != NULL, "Se puede crear un ABB con comparador");
	free(abb);
}

void liberarSoloABB()
{
	abb_t *abb = abb_crear(comparador_enteros);
	abb_destruir(abb);
	pa2m_afirmar(true, "Se puede liberar solo el ABB");
}

void liberarABBYElementos()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento = malloc(sizeof(int));
	*elemento = 21;
	abb_insertar(abb, elemento);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 32;
	abb_insertar(abb, elemento3);
	abb_destruir_todo(abb, destructor);
	pa2m_afirmar(true, "Se puede liberar el ABB y sus elementos");
}

void agregarUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento = malloc(sizeof(int));
	*elemento = 21;
	pa2m_afirmar(abb_insertar(abb, elemento),
		     "Se puede insertar un elemento en el ABB");
	pa2m_afirmar(abb_cantidad(abb) == 1,
		     "La cantidad de elementos en el ABB es 1");
	abb_destruir_todo(abb, destructor);
}

void agregarVariosElementos()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento = malloc(sizeof(int));
	*elemento = 21;
	pa2m_afirmar(abb_insertar(abb, elemento),
		     "Se puede insertar un elemento en el ABB");
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	pa2m_afirmar(abb_insertar(abb, elemento2),
		     "Se puede insertar un segundo elemento en el ABB");
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 32;
	pa2m_afirmar(abb_insertar(abb, elemento3),
		     "Se puede insertar un tercer elemento en el ABB");
	pa2m_afirmar(abb_cantidad(abb) == 3,
		     "La cantidad de elementos en el ABB es 3");
	abb_destruir_todo(abb, destructor);
}

void buscarElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento = malloc(sizeof(int));
	*elemento = 21;
	abb_insertar(abb, elemento);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 32;
	abb_insertar(abb, elemento3);
	void *elemento_buscado = abb_obtener(abb, elemento2);
	pa2m_afirmar(*(int *)elemento_buscado == 54,
		     "Elemento encontrado en el ABB");
	abb_destruir_todo(abb, destructor);
}

void buscarOtroElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 21;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 32;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 70;
	void *elemento_buscado = abb_obtener(abb, elemento4);
	pa2m_afirmar(elemento_buscado == NULL,
		     "Elemento no encontrado en el ABB");
	abb_destruir_todo(abb, destructor);
	free(elemento4);
}

void eliminarElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 21;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 32;
	abb_insertar(abb, elemento3);
	void *elemento_eliminado;
	pa2m_afirmar(abb_quitar(abb, elemento2, &elemento_eliminado),
		     "Se puede eliminar un elemento del ABB");
	pa2m_afirmar(*(int *)elemento_eliminado == 54,
		     "El elemento eliminado es el correcto");
	pa2m_afirmar(abb_cantidad(abb) == 2,
		     "La cantidad de elementos en el ABB es 2");
	free(elemento_eliminado);
	abb_destruir_todo(abb, destructor);
}

void eliminarVariosElementos()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 21;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 32;
	abb_insertar(abb, elemento3);
	void *elemento_eliminado;
	pa2m_afirmar(abb_quitar(abb, elemento2, &elemento_eliminado),
		     "Se puede eliminar un elemento del ABB");
	pa2m_afirmar(*(int *)elemento_eliminado == 54,
		     "El elemento eliminado es el correcto");
	pa2m_afirmar(abb_cantidad(abb) == 2,
		     "La cantidad de elementos en el ABB es 2");
	free(elemento_eliminado);
	pa2m_afirmar(abb_quitar(abb, elemento1, &elemento_eliminado),
		     "Se puede eliminar un elemento del ABB");
	pa2m_afirmar(*(int *)elemento_eliminado == 21,
		     "El elemento eliminado es el correcto");
	pa2m_afirmar(abb_cantidad(abb) == 1,
		     "La cantidad de elementos en el ABB es 1");
	free(elemento_eliminado);
	pa2m_afirmar(abb_quitar(abb, elemento3, &elemento_eliminado),
		     "Se puede eliminar un elemento del ABB");
	pa2m_afirmar(*(int *)elemento_eliminado == 32,
		     "El elemento eliminado es el correcto");
	pa2m_afirmar(abb_cantidad(abb) == 0,
		     "La cantidad de elementos en el ABB es 0");
	free(elemento_eliminado);
	abb_destruir_todo(abb, destructor);
}

bool imprimir_elemento(void *elemento, void *ctx)
{
	printf("%i ", *(int *)elemento);
	return true;
}

void iterarInorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");

	printf("Cantidad: %lu\n", cantidad);

	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en inorden el ABB");
	abb_destruir_todo(abb, destructor);
}

void iterarInordenBorrandoUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en inorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en inorden el ABB");

	free(elemento4);

	abb_destruir_todo(abb, destructor);
}

void otraPruebaDeIteracionInorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en inorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento5, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en inorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento1, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 5, "Se puede iterar en inorden el ABB");

	free(elemento1);
	free(elemento5);
	abb_destruir_todo(abb, destructor);
}

void iterarPreorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);

	size_t cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	printf("Cantidad: %lu\n", cantidad);
	printf("\n");

	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);

	cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	printf("Cantidad: %lu\n", cantidad);
	printf("\n");

	printf("\n");

	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);

	cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	printf("Cantidad: %lu\n", cantidad);
	printf("\n");

	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");

	printf("Cantidad xd: %lu\n", cantidad);

	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en preorden el ABB");
	abb_destruir_todo(abb, destructor);
}

void iterarPreordenBorrandoUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en preorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en preorden el ABB");

	free(elemento4);

	abb_destruir_todo(abb, destructor);
}

void otraPruebaDeIteracionPreorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en preorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento5, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en preorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento1, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_preorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 5, "Se puede iterar en preorden el ABB");

	free(elemento1);
	free(elemento5);
	abb_destruir_todo(abb, destructor);
}

void iterarPostorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_postorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en postorden el ABB");
	abb_destruir_todo(abb, destructor);
}

void iterarPostordenBorrandoUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_postorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en postorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_postorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en postorden el ABB");

	free(elemento4);

	abb_destruir_todo(abb, destructor);
}

void otraPruebaDeIteracionPostorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	size_t cantidad = abb_iterar_postorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 7, "Se puede iterar en postorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento5, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_postorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en postorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento1, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_postorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 5, "Se puede iterar en postorden el ABB");

	free(elemento1);
	free(elemento5);
	abb_destruir_todo(abb, destructor);
}

void vectorInorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_inorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en inorden");
	pa2m_afirmar(*(int *)vector[0] == 10,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 15,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 20,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 30,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 50,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 60,
		     "El septimo elemento del vector es el correcto");
	abb_destruir_todo(abb, destructor);
}

void vectorInordenBorrandoUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_inorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en inorden");
	pa2m_afirmar(*(int *)vector[0] == 10,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 15,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 20,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 30,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 50,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 60,
		     "El septimo elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_inorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 6,
		     "Se puede guardar en un vector los elementos en inorden");

	pa2m_afirmar(*(int *)vector[0] == 15,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 30,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 50,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 54,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 60,
		     "El sexto elemento del vector es el correcto");

	free(elemento4);

	abb_destruir_todo(abb, destructor);
}

void otraPruebaDeVectorInorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_inorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en inorden");
	pa2m_afirmar(*(int *)vector[0] == 10,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 15,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 20,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 30,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 50,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 60,
		     "El septimo elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento5, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_inorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 6,
		     "Se puede guardar en un vector los elementos en inorden");

	pa2m_afirmar(*(int *)vector[0] == 10,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 15,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 20,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 50,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 54,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 60,
		     "El sexto elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento1, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_inorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 5,
		     "Se puede guardar en un vector los elementos en inorden");

	pa2m_afirmar(*(int *)vector[0] == 10,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 15,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 20,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 54,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 60,
		     "El quinto elemento del vector es el correcto");

	free(elemento1);
	free(elemento5);

	abb_destruir_todo(abb, destructor);
}

void vectorPreorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_preorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 50,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 10,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 15,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 30,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 60,
		     "El septimo elemento del vector es el correcto");
	abb_destruir_todo(abb, destructor);
}

void vectorPreordenBorrandoUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_preorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 50,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 10,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 15,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 30,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 60,
		     "El septimo elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_preorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 6,
		     "Se puede guardar en un vector los elementos en preorden");

	pa2m_afirmar(*(int *)vector[0] == 50,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 15,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 30,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 54,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 60,
		     "El sexto elemento del vector es el correcto");

	free(elemento4);

	abb_destruir_todo(abb, destructor);
}

void otraPruebaDeVectorPreorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_preorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 50,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 10,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 15,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 30,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 60,
		     "El septimo elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento5, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_preorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 6,
		     "Se puede guardar en un vector los elementos en preorden");

	pa2m_afirmar(*(int *)vector[0] == 50,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 10,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 15,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 54,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 60,
		     "El sexto elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_preorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 5,
		     "Se puede guardar en un vector los elementos en preorden");

	pa2m_afirmar(*(int *)vector[0] == 50,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 15,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 54,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 60,
		     "El quinto elemento del vector es el correcto");

	free(elemento4);
	free(elemento5);

	abb_destruir_todo(abb, destructor);
}

void vectorPostorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_postorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 15,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 10,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 30,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 20,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 60,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 50,
		     "El septimo elemento del vector es el correcto");
	abb_destruir_todo(abb, destructor);
}

void vectorPostordenBorrandoUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_postorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 15,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 10,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 30,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 20,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 60,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 50,
		     "El septimo elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_postorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 6,
		     "Se puede guardar en un vector los elementos en preorden");

	pa2m_afirmar(*(int *)vector[0] == 15,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 30,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 20,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 60,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 54,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 50,
		     "El sexto elemento del vector es el correcto");

	free(elemento4);

	abb_destruir_todo(abb, destructor);
}

void otraPruebaDeVectorPostorden()
{
	abb_t *abb = abb_crear(comparador_enteros);
	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	int *elemento7 = malloc(sizeof(int));
	*elemento7 = 60;
	abb_insertar(abb, elemento7);
	void *vector[7];
	size_t cantidad = abb_vectorizar_postorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 7,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 15,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 10,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 30,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 20,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 60,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 54,
		     "El sexto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[6] == 50,
		     "El septimo elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento5, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_postorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 6,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 15,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 10,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 20,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 60,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 54,
		     "El quinto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[5] == 50,
		     "El sexto elemento del vector es el correcto");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	printf("\n");

	cantidad = abb_vectorizar_postorden(abb, vector, 7);

	for (size_t i = 0; i < cantidad; i++)
		printf("%i ", *(int *)vector[i]);

	printf("\n");

	pa2m_afirmar(cantidad == 5,
		     "Se puede guardar en un vector los elementos en preorden");
	pa2m_afirmar(*(int *)vector[0] == 15,
		     "El primer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[1] == 20,
		     "El segundo elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[2] == 60,
		     "El tercer elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[3] == 54,
		     "El cuarto elemento del vector es el correcto");
	pa2m_afirmar(*(int *)vector[4] == 50,
		     "El quinto elemento del vector es el correcto");

	free(elemento4);
	free(elemento5);

	abb_destruir_todo(abb, destructor);
}

void error1()
{
	abb_t *abb = abb_crear(comparador_enteros);

	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);

	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);

	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);

	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);

	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);

	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);

	void *raiz = abb_obtener(abb, elemento1);
	pa2m_afirmar(raiz == elemento1, "La raíz del ABB es el elemento 50");

	void *elementoquitado = NULL;
	pa2m_afirmar(abb_quitar(abb, elemento1, &elementoquitado),
		     "Se puede eliminar un nodo con dos hijos del ABB");
	pa2m_afirmar(elementoquitado == elemento1,
		     "El elemento quitado es el esperado (50)");

	raiz = abb_obtener(abb, elemento5);
	pa2m_afirmar(raiz == elemento5,
		     "La nueva raíz es el predecesor inorden (30)");

	pa2m_afirmar(
		abb_obtener(abb, elemento3) == elemento3,
		"El hijo izquierdo de la nueva raíz es el nodo esperado (20)");
	pa2m_afirmar(
		abb_obtener(abb, elemento2) == elemento2,
		"El hijo derecho de la nueva raíz es el nodo esperado (54)");

	pa2m_afirmar(abb_quitar(abb, elemento5, &elementoquitado),
		     "Se puede eliminar el predecesor inorden");
	pa2m_afirmar(abb_obtener(abb, elemento3) == elemento3,
		     "La nueva raíz es el nodo 20 después de eliminar 30");

	pa2m_afirmar(abb_obtener(abb, elemento6) == elemento6,
		     "El hijo izquierdo de 20 es el nodo 15");

	free(elemento1);
	free(elemento5);
	abb_destruir_todo(abb, destructor);
}

void error2()
{
	abb_t *abb = NULL;

	pa2m_afirmar(abb_insertar(abb, NULL) == false,
		     "No se puede insertar un elemento en un ABB NULL");

	pa2m_afirmar(abb_cantidad(abb) == 0,
		     "La cantidad de elementos en un ABB NULL es 0");

	pa2m_afirmar(abb_quitar(abb, NULL, NULL) == false,
		     "No se puede eliminar un elemento de un ABB NULL");
}

void error3()
{
	abb_t *abb = NULL;

	abb_destruir(abb);
}

bool limitador(void *elemento, void *extra)
{
	int *limite = extra;

	(*limite)--;

	if (*limite > 0) {
		return true;
	}

	return false;
}

void error1_2()
{
	abb_t *abb = abb_crear(comparador_enteros);

	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);

	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);

	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);

	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);

	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);

	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);

	pa2m_afirmar(abb_cantidad(abb) == 6,
		     "La cantidad de elementos en el ABB es 6");

	int limite = 3;

	size_t iterados = abb_iterar_inorden(abb, limitador, &limite);

	printf("Iterados: %zu\n", iterados);

	pa2m_afirmar(iterados == 3, "Se iteraron 3 elementos");

	abb_destruir_todo(abb, destructor);
}

void error2_2()
{
	abb_t *abb = abb_crear(comparador_enteros);

	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);

	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);

	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);

	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);

	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);

	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);

	pa2m_afirmar(abb_cantidad(abb) == 6,
		     "La cantidad de elementos en el ABB es 6");

	int limite = 3;

	size_t iterados = abb_iterar_preorden(abb, limitador, &limite);

	printf("Iterados: %zu\n", iterados);

	pa2m_afirmar(iterados == 3, "Se iteraron 3 elementos");

	abb_destruir_todo(abb, destructor);
}

void error3_2()
{
	abb_t *abb = abb_crear(comparador_enteros);

	int *elemento1 = malloc(sizeof(int));
	*elemento1 = 50;
	abb_insertar(abb, elemento1);

	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);

	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 20;
	abb_insertar(abb, elemento3);

	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);

	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 30;
	abb_insertar(abb, elemento5);

	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);

	pa2m_afirmar(abb_cantidad(abb) == 6,
		     "La cantidad de elementos en el ABB es 6");

	int limite = 3;

	size_t iterados = abb_iterar_postorden(abb, limitador, &limite);

	printf("Iterados: %zu\n", iterados);

	pa2m_afirmar(iterados == 3, "Se iteraron 3 elementos");

	abb_destruir_todo(abb, destructor);
}

int main()
{
	pa2m_nuevo_grupo("Creacion ABB");
	creacionComparadorNULL();
	printf("\n");
	creacionComparadorValido();
	pa2m_nuevo_grupo("Liberacion de memoria");
	liberarSoloABB();
	printf("\n");
	liberarABBYElementos();
	pa2m_nuevo_grupo("Inserccion de elementos");
	agregarUnElemento();
	printf("\n");
	agregarVariosElementos();
	printf("\n");
	pa2m_nuevo_grupo("Busqueda de elementos");
	buscarElemento();
	printf("\n");
	buscarOtroElemento();
	pa2m_nuevo_grupo("Eliminacion de elementos");
	eliminarElemento();
	printf("\n");
	eliminarVariosElementos();
	pa2m_nuevo_grupo("Iteracion elementos INORDEN");
	iterarInorden();
	printf("\n");
	iterarInordenBorrandoUnElemento();
	printf("\n");
	otraPruebaDeIteracionInorden();
	pa2m_nuevo_grupo("Iteracion elementos PREORDEN");
	iterarPreorden();
	printf("\n");
	iterarPreordenBorrandoUnElemento();
	printf("\n");
	otraPruebaDeIteracionPreorden();
	pa2m_nuevo_grupo("Iteracion elementos POSTORDEN");
	iterarPostorden();
	printf("\n");
	iterarPostordenBorrandoUnElemento();
	printf("\n");
	otraPruebaDeIteracionPostorden();
	pa2m_nuevo_grupo("Vector de elementos en INORDEN");
	vectorInorden();
	printf("\n");
	vectorInordenBorrandoUnElemento();
	printf("\n");
	otraPruebaDeVectorInorden();
	pa2m_nuevo_grupo("Vector de elementos en PREORDEN");
	vectorPreorden();
	printf("\n");
	vectorPreordenBorrandoUnElemento();
	printf("\n");
	otraPruebaDeVectorPreorden();
	pa2m_nuevo_grupo("Vector de elementos en POSTORDEN");
	vectorPostorden();
	printf("\n");
	vectorPostordenBorrandoUnElemento();
	printf("\n");
	otraPruebaDeVectorPostorden();
	pa2m_nuevo_grupo("Pruebas no pasadas - PARTE 1");
	error1();
	printf("\n");
	error2();
	printf("\n");
	error3();
	pa2m_nuevo_grupo("Pruebas no pasadas - PARTE 2");
	error1_2();
	printf("\n");
	error2_2();
	printf("\n");
	error3_2();

	return pa2m_mostrar_reporte();
}
