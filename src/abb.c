#include "abb.h"
#include "abb_estructura_privada.h"

// typedef struct nodo {
// 	void *elemento;
// 	struct nodo *izq;
// 	struct nodo *der;
// } nodo_t;

// struct abb {
// 	size_t nodos;
// 	nodo_t *raiz;
// 	int (*comparador)(void*, void*);
// };

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
	if (abb == NULL || abb->raiz == NULL)
		return false;

	nodo_t *nodo = abb->raiz;
	nodo_t *padre = NULL;

	while (nodo != NULL) {
		int comparacion = abb->comparador(buscado, nodo->elemento);

		if (comparacion == 0) {
			break;
		} else if (comparacion < 0) {
			padre = nodo;
			nodo = nodo->izq;
		} else {
			padre = nodo;
			nodo = nodo->der;
		}
	}

	if (nodo == NULL)
		return false;

	if (encontrado != NULL)
		*encontrado = nodo->elemento;

	if (padre == NULL) {
		if (nodo->izq == NULL) {
			abb->raiz = nodo->der;
		} else if (nodo->der == NULL) {
			abb->raiz = nodo->izq;
		} else {
			nodo_t *reemplazo = nodo->der;
			nodo_t *padre_reemplazo = nodo;

			while (reemplazo->izq != NULL) {
				padre_reemplazo = reemplazo;
				reemplazo = reemplazo->izq;
			}

			nodo->elemento = reemplazo->elemento;

			if (padre_reemplazo == nodo) {
				nodo->der = reemplazo->der;
			} else {
				padre_reemplazo->izq = reemplazo->der;
			}
		}
	} else {
		if (nodo->izq == NULL) {
			if (padre->izq == nodo) {
				padre->izq = nodo->der;
			} else {
				padre->der = nodo->der;
			}
		} else if (nodo->der == NULL) {
			if (padre->izq == nodo) {
				padre->izq = nodo->izq;
			} else {
				padre->der = nodo->izq;
			}
		} else {
			nodo_t *reemplazo = nodo->der;
			nodo_t *padre_reemplazo = nodo;

			while (reemplazo->izq != NULL) {
				padre_reemplazo = reemplazo;
				reemplazo = reemplazo->izq;
			}

			nodo->elemento = reemplazo->elemento;

			if (padre_reemplazo == nodo) {
				nodo->der = reemplazo->der;
			} else {
				padre_reemplazo->izq = reemplazo->der;
			}
		}
	}

	free(nodo);

	abb->nodos--;

	return true;
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

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	return 0;
}

size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	return 0;
}

size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	return 0;
}

size_t abb_vectorizar_inorden(abb_t *abb, void **vector, size_t tamaño)
{
	return 0;
}

size_t abb_vectorizar_preorden(abb_t *abb, void **vector, size_t tamaño)
{
	return 0;
}

size_t abb_vectorizar_postorden(abb_t *abb, void **vector, size_t tamaño)
{
	return 0;
}
