#include "abb.h"
#include "abb_estructura_privada.h"

abb_t *abb_crear(int (*comparador)(void *, void *))
{
	if (comparador == NULL)
		return NULL;

	abb_t *abb = calloc(1, sizeof(abb_t));

	if (abb == NULL)
		return NULL;

	abb->comparador = comparador;

	return abb;
}

void abb_destruir(abb_t *abb)
{
	abb_destruir_todo(abb, NULL);
}

void nodo_destruir(nodo_t *nodo, void (*destructor)(void *))
{
	if (nodo == NULL)
		return;

	nodo_destruir(nodo->izq, destructor);
	nodo_destruir(nodo->der, destructor);

	if (destructor != NULL)
		destructor(nodo->elemento);

	free(nodo);
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	nodo_destruir(abb->raiz, destructor);

	free(abb);

	return;
}

nodo_t *nodo_crear(void *elemento)
{
	nodo_t *nodo = calloc(1, sizeof(nodo_t));

	if (nodo == NULL)
		return NULL;

	nodo->elemento = elemento;

	return nodo;
}

nodo_t *nodo_insertar(nodo_t *nodo, void *elemento,
		      int (*comparador)(void *, void *), bool *insertado)
{
	if (nodo == NULL) {
		*insertado = true;

		return nodo_crear(elemento);
	}

	int comparacion = comparador(elemento, nodo->elemento);

	if (comparacion > 0) {
		nodo->der = nodo_insertar(nodo->der, elemento, comparador,
					  insertado);
	} else {
		nodo->izq = nodo_insertar(nodo->izq, elemento, comparador,
					  insertado);
	}

	return nodo;
}

bool abb_insertar(abb_t *abb, void *elemento)
{
	if (abb == NULL)
		return false;

	bool insertado = false;
	abb->raiz =
		nodo_insertar(abb->raiz, elemento, abb->comparador, &insertado);

	if (insertado)
		abb->nodos++;

	return insertado;
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado)
{
	if (abb == NULL)
		return false;

	nodo_t *nodo = abb->raiz;
	nodo_t *padre = NULL;

	while (nodo != NULL) {
		int comparacion = abb->comparador(buscado, nodo->elemento);

		if (comparacion == 0) {
			if (encontrado != NULL)
				*encontrado = nodo->elemento;

			if (nodo->izq == NULL && nodo->der == NULL) {
				if (padre == NULL)
					abb->raiz = NULL;
				else if (padre->izq == nodo)
					padre->izq = NULL;
				else
					padre->der = NULL;

				free(nodo);
			} else if (nodo->izq == NULL) {
				if (padre == NULL)
					abb->raiz = nodo->der;
				else if (padre->izq == nodo)
					padre->izq = nodo->der;
				else
					padre->der = nodo->der;

				free(nodo);
			} else if (nodo->der == NULL) {
				if (padre == NULL)
					abb->raiz = nodo->izq;
				else if (padre->izq == nodo)
					padre->izq = nodo->izq;
				else
					padre->der = nodo->izq;

				free(nodo);
			} else {
				nodo_t *reemplazo = nodo->der;
				nodo_t *padre_reemplazo = nodo;

				while (reemplazo->izq != NULL) {
					padre_reemplazo = reemplazo;
					reemplazo = reemplazo->izq;
				}

				if (padre_reemplazo == nodo)
					padre_reemplazo->der = reemplazo->der;
				else
					padre_reemplazo->izq = reemplazo->der;

				nodo->elemento = reemplazo->elemento;

				free(reemplazo);
			}

			abb->nodos--;

			return true;
		}

		padre = nodo;

		if (comparacion > 0)
			nodo = nodo->der;
		else
			nodo = nodo->izq;
	}

	free(nodo);

	return false;
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (abb == NULL)
		return NULL;

	nodo_t *nodo = abb->raiz;

	while (nodo != NULL) {
		int comparacion = abb->comparador(elemento, nodo->elemento);

		if (comparacion == 0)
			return nodo->elemento;

		if (comparacion > 0)
			nodo = nodo->der;
		else
			nodo = nodo->izq;
	}

	return NULL;
}

size_t abb_cantidad(abb_t *abb)
{
	return abb->nodos;
}

size_t abb_iterar_inorden_r(nodo_t *nodo, bool (*f)(void *, void *), void *ctx,
			    size_t *contador)
{
	if (nodo == NULL)
		return 0;

	abb_iterar_inorden_r(nodo->izq, f, ctx, contador);

	if (f(nodo->elemento, ctx) == false)
		return (*contador)++;

	(*contador)++;

	abb_iterar_inorden_r(nodo->der, f, ctx, contador);

	return *contador;
}

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || abb->raiz == NULL)
		return 0;

	size_t contador = 0;

	return abb_iterar_inorden_r(abb->raiz, f, ctx, &contador);
}

size_t abb_iterar_preorden_r(nodo_t *nodo, bool (*f)(void *, void *), void *ctx,
			     size_t *contador)
{
	if (nodo == NULL)
		return 0;

	if (f(nodo->elemento, ctx) == false)
		return (*contador)++;

	(*contador)++;

	abb_iterar_preorden_r(nodo->izq, f, ctx, contador);
	abb_iterar_preorden_r(nodo->der, f, ctx, contador);

	return *contador;
}

size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || abb->raiz == NULL)
		return 0;

	size_t contador = 0;

	return abb_iterar_preorden_r(abb->raiz, f, ctx, &contador);
}

size_t abb_iterar_postorden_r(nodo_t *nodo, bool (*f)(void *, void *),
			      void *ctx, size_t *contador)
{
	if (nodo == NULL)
		return 0;

	abb_iterar_postorden_r(nodo->izq, f, ctx, contador);
	abb_iterar_postorden_r(nodo->der, f, ctx, contador);

	if (f(nodo->elemento, ctx) == false)
		return *(contador)++;

	(*contador)++;

	return *contador;
}

size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || abb->raiz == NULL)
		return 0;

	size_t contador = 0;

	return abb_iterar_postorden_r(abb->raiz, f, ctx, &contador);
}

size_t abb_vectorizar_inorden_r(nodo_t *nodo, void **vector, size_t tamaño,
				size_t *contador)
{
	if (nodo == NULL || *contador >= tamaño)
		return *contador;

	abb_vectorizar_inorden_r(nodo->izq, vector, tamaño, contador);

	if (*contador < tamaño) {
		vector[*contador] = nodo->elemento;
		(*contador)++;
	}

	abb_vectorizar_inorden_r(nodo->der, vector, tamaño, contador);

	return *contador;
}

size_t abb_vectorizar_inorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (abb == NULL || abb->raiz == NULL || vector == NULL)
		return 0;

	size_t contador = 0;
	abb_vectorizar_inorden_r(abb->raiz, vector, tamaño, &contador);
	return contador;
}

size_t abb_vectorizar_preorden_r(nodo_t *nodo, void **vector, size_t tamaño,
				 size_t *contador)
{
	if (nodo == NULL || *contador >= tamaño)
		return *contador;

	if (*contador < tamaño) {
		vector[*contador] = nodo->elemento;
		(*contador)++;
	}

	abb_vectorizar_preorden_r(nodo->izq, vector, tamaño, contador);
	abb_vectorizar_preorden_r(nodo->der, vector, tamaño, contador);

	return *contador;
}

size_t abb_vectorizar_preorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (abb == NULL || abb->raiz == NULL || vector == NULL)
		return 0;

	size_t contador = 0;
	abb_vectorizar_preorden_r(abb->raiz, vector, tamaño, &contador);
	return contador;
}

size_t abb_vectorizar_postorden_r(nodo_t *nodo, void **vector, size_t tamaño,
				  size_t *contador)
{
	if (nodo == NULL ||
	    *contador >= tamaño) // Si el nodo es NULL o ya llenamos el vector
		return *contador;

	// Recorre el subárbol izquierdo
	abb_vectorizar_postorden_r(nodo->izq, vector, tamaño, contador);
	// Recorre el subárbol derecho
	abb_vectorizar_postorden_r(nodo->der, vector, tamaño, contador);

	if (*contador < tamaño) {
		vector[*contador] =
			nodo->elemento; // Almacena el elemento en el vector
		(*contador)++;
	}

	return *contador;
}

size_t abb_vectorizar_postorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (abb == NULL || abb->raiz == NULL || vector == NULL || tamaño == 0)
		return 0;

	size_t contador = 0;

	return abb_vectorizar_postorden_r(abb->raiz, vector, tamaño, &contador);
}
