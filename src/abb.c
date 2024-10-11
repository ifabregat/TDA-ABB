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

	// Busca el nodo mediante el comparador
	while (nodo != NULL) {
		int comparacion = abb->comparador(buscado, nodo->elemento);

		if (comparacion == 0) {
			break; // Nodo encontrado
		} else if (comparacion < 0) {
			padre = nodo;
			nodo = nodo->izq;
		} else {
			padre = nodo;
			nodo = nodo->der;
		}
	}

	// Si no se encontró el nodo
	if (nodo == NULL)
		return false;

	// Se guarda el elemento eliminado
	if (encontrado != NULL)
		*encontrado = nodo->elemento;

	// Nodo a eliminar es la raíz
	if (padre == NULL) {
		// Caso 1: La raíz no tiene hijos
		if (nodo->izq == NULL && nodo->der == NULL) {
			abb->raiz = NULL;
		}
		// Caso 2: La raíz tiene un hijo
		else if (nodo->izq == NULL) {
			abb->raiz = nodo->der;
		} else if (nodo->der == NULL) {
			abb->raiz = nodo->izq;
		}
		// Caso 3: La raíz tiene dos hijos
		else {
			nodo_t *reemplazo = nodo->izq;
			nodo_t *padre_reemplazo = nodo;

			// Encuentra el mayor en el subárbol izquierdo
			while (reemplazo->der != NULL) {
				padre_reemplazo = reemplazo;
				reemplazo = reemplazo->der;
			}

			// Sustituye el valor del nodo a eliminar con el valor del reemplazo
			nodo->elemento = reemplazo->elemento;

			// Ajusta el puntero del padre del reemplazo
			if (padre_reemplazo == nodo) {
				nodo->izq =
					reemplazo->izq; // Si el reemplazo es el hijo izquierdo
			} else {
				padre_reemplazo->der =
					reemplazo->izq; // Si no, lo eliminamos
			}
		}
	} else {
		// Caso 4: El nodo a eliminar no es la raíz
		if (nodo->izq == NULL && nodo->der == NULL) {
			// Si no tiene hijos, simplemente lo eliminamos
			if (padre->izq == nodo) {
				padre->izq = NULL;
			} else {
				padre->der = NULL;
			}
		} else if (nodo->izq == NULL) {
			// Si tiene un hijo derecho
			if (padre->izq == nodo) {
				padre->izq = nodo->der;
			} else {
				padre->der = nodo->der;
			}
		} else if (nodo->der == NULL) {
			// Si tiene un hijo izquierdo
			if (padre->izq == nodo) {
				padre->izq = nodo->izq;
			} else {
				padre->der = nodo->izq;
			}
		} else {
			// Caso 3: El nodo tiene dos hijos
			nodo_t *reemplazo = nodo->izq;
			nodo_t *padre_reemplazo = nodo;

			// Encuentra el mayor en el subárbol izquierdo
			while (reemplazo->der != NULL) {
				padre_reemplazo = reemplazo;
				reemplazo = reemplazo->der;
			}

			// Sustituye el valor del nodo a eliminar con el valor del reemplazo
			nodo->elemento = reemplazo->elemento;

			// Ajusta el puntero del padre del reemplazo
			if (padre_reemplazo == nodo) {
				nodo->izq =
					reemplazo->izq; // Si el reemplazo es el hijo izquierdo
			} else {
				padre_reemplazo->der =
					reemplazo->izq; // Si no, lo eliminamos
			}
		}
	}

	// Libera el nodo
	free(nodo);
	nodo = NULL;
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

size_t abb_iterar_inorden_r(nodo_t *nodo, bool (*f)(void *, void *), void *ctx,
			    size_t *contador)
{
	if (nodo == NULL)
		return 0;

	abb_iterar_inorden_r(nodo->izq, f, ctx, contador);

	if (f(nodo->elemento, ctx) == false)
		return *contador;

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
