#include "pa2m.h"
#include "src/abb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	*elemento1 = 21;
	abb_insertar(abb, elemento1);
	int *elemento2 = malloc(sizeof(int));
	*elemento2 = 54;
	abb_insertar(abb, elemento2);
	int *elemento3 = malloc(sizeof(int));
	*elemento3 = 32;
	abb_insertar(abb, elemento3);
	int *elemento4 = malloc(sizeof(int));
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 3;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);
	size_t cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en inorden el ABB");
	abb_destruir_todo(abb, destructor);
}

void iterarInordenBorrandoUnElemento()
{
	abb_t *abb = abb_crear(comparador_enteros);

	// Inserción de elementos
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
	*elemento4 = 10;
	abb_insertar(abb, elemento4);
	int *elemento5 = malloc(sizeof(int));
	*elemento5 = 3;
	abb_insertar(abb, elemento5);
	int *elemento6 = malloc(sizeof(int));
	*elemento6 = 15;
	abb_insertar(abb, elemento6);

	size_t cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 6, "Se puede iterar en inorden el ABB");

	pa2m_afirmar(abb_quitar(abb, elemento4, NULL),
		     "Se puede eliminar un elemento del ABB");

	cantidad = abb_iterar_inorden(abb, imprimir_elemento, NULL);
	printf("\n");
	pa2m_afirmar(cantidad == 5, "Se puede iterar en inorden el ABB");

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

	return pa2m_mostrar_reporte();
}
