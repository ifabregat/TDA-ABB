#include "src/split.h"
#include "src/csv.h"
#include "src/abb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
} Pokemon;

bool parsear_entero(const char *campo, void *ctx)
{
	int *numero = ctx;

	if (campo == NULL || numero == NULL) {
		return false;
	}

	return sscanf(campo, "%d", numero) == 1;
}

bool parsear_nombre(const char *campo, void *ctx)
{
	if (campo == NULL || ctx == NULL) {
		return false;
	}

	char **nombre = (char **)ctx;

	if (*nombre != NULL) {
		free(*nombre);
		*nombre = NULL;
	}

	size_t longitud = strlen(campo);

	if (longitud == 0) {
		return false;
	}

	*nombre = malloc(longitud + 1);

	if (*nombre == NULL) {
		return false;
	}

	strcpy(*nombre, campo);

	return true;
}

bool parsear_tipo(const char *campo, void *ctx)
{
	char *tipo = ctx;

	if (campo == NULL || strlen(campo) != 1) {
		return false;
	}

	*tipo = campo[0];

	return true;
}

struct archivo_csv *abrir_archivo(const char *ruta)
{
	struct archivo_csv *archivo = abrir_archivo_csv(ruta, ';');

	if (archivo == NULL) {
		printf("No se pudo abrir el archivo %s\n", ruta);
		return NULL;
	}

	return archivo;
}

abb_t *inicializar_abb(int (*comparador)(void *, void *))
{
	return abb_crear(comparador);
}

Pokemon *crear_pokemon(char *nombre, char tipo, int fuerza, int destreza,
		       int resistencia)
{
	Pokemon *pokemon = malloc(sizeof(Pokemon));

	if (pokemon == NULL) {
		return NULL;
	}

	pokemon->nombre = malloc(strlen(nombre) + 1);

	if (pokemon->nombre == NULL) {
		free(pokemon);
		return NULL;
	}

	strcpy(pokemon->nombre, nombre);
	pokemon->tipo = tipo;
	pokemon->fuerza = fuerza;
	pokemon->destreza = destreza;
	pokemon->resistencia = resistencia;

	return pokemon;
}

void agregar_pokemon(struct archivo_csv *archivo, abb_t *abb)
{
	bool (*parseadores[5])(const char *,
			       void *) = { parsear_nombre, parsear_tipo,
					   parsear_entero, parsear_entero,
					   parsear_entero };

	char *nombre = malloc(100);

	if (nombre == NULL) {
		cerrar_archivo_csv(archivo);
		abb_destruir(abb);
		return;
	}

	char tipo;
	int fuerza, destreza, resistencia;

	void *ctx[5] = { &nombre, &tipo, &fuerza, &destreza, &resistencia };

	while (leer_linea_csv(archivo, 5, parseadores, ctx) == 5) {
		Pokemon *pokemon = crear_pokemon(nombre, tipo, fuerza, destreza,
						 resistencia);

		if (pokemon == NULL) {
			free(nombre);
			cerrar_archivo_csv(archivo);
			abb_destruir(abb);
			return;
		}

		if (!abb_insertar(abb, pokemon)) {
			free(pokemon->nombre);
			free(pokemon);
		}
	}

	free(nombre);

	return;
}

int comparar_pokemones(void *elemento1, void *elemento2)
{
	Pokemon *pokemon1 = elemento1;
	Pokemon *pokemon2 = elemento2;

	if (pokemon1 == NULL || pokemon2 == NULL) {
		return 0;
	}

	return strcmp(pokemon1->nombre, pokemon2->nombre);
}

bool imprimir_elemento(void *elemento, void *ctx)
{
	Pokemon *pokemon = elemento;

	if (pokemon == NULL) {
		return false;
	}

	printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
	       pokemon->nombre, pokemon->tipo, pokemon->fuerza,
	       pokemon->destreza, pokemon->resistencia);

	return true;
}

void destructor_pokemon(void *elemento)
{
	Pokemon *pokemon = elemento;

	if (pokemon == NULL) {
		return;
	}

	free(pokemon->nombre);
	free(pokemon);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Uso: %s <archivo>\n", argv[0]);
		return 1;
	}

	struct archivo_csv *archivo = abrir_archivo(argv[1]);

	if (archivo == NULL) {
		return 2;
	}

	abb_t *abb = inicializar_abb(comparar_pokemones);

	if (abb == NULL) {
		cerrar_archivo_csv(archivo);
		return 3;
	}

	agregar_pokemon(archivo, abb);

	char opcion = 0;

	printf("Ingrese una opción: ");
	printf("M (Para mostrar todos los pokemones) o B (Para buscar un pokemon): ");

	if (scanf(" %c", &opcion) != 1) {
		cerrar_archivo_csv(archivo);
		abb_destruir(abb);
		return 4;
	}
	
	if (opcion == 'M' || opcion == 'm') {
		char orden = 0;

		printf("Ingrese el orden de impresión: I (Inorden), P (Preorden) o O (Postorden): ");

		scanf(" %c", &orden);

		printf("\n");

		switch (orden) {
		case 'I':
			abb_iterar_inorden(abb, imprimir_elemento, NULL);
			printf("\n");
			break;

		case 'i':
			abb_iterar_inorden(abb, imprimir_elemento, NULL);
			printf("\n");
			break;

		case 'P':
			abb_iterar_preorden(abb, imprimir_elemento, NULL);
			printf("\n");
			break;

		case 'p':
			abb_iterar_preorden(abb, imprimir_elemento, NULL);
			printf("\n");
			break;

		case 'O':
			abb_iterar_postorden(abb, imprimir_elemento, NULL);
			printf("\n");
			break;

		case 'o':
			abb_iterar_postorden(abb, imprimir_elemento, NULL);
			printf("\n");
			break;

		default:
			printf("Opción inválida\n");
			printf("\n");
			break;
		}
	} else if (opcion == 'B' || opcion == 'b') {
		Pokemon pokemon_buscar = { 0 };

		pokemon_buscar.nombre = malloc(100);

		printf("Ingrese el nombre del pokemon a buscar: ");

		if (scanf(" %99[^\n]", pokemon_buscar.nombre) != 1) {
			free(pokemon_buscar.nombre);
			cerrar_archivo_csv(archivo);
			abb_destruir(abb);
			return 5;
		}

		void *resultado = abb_obtener(abb, &pokemon_buscar);

		printf("\n");

		if (resultado != NULL) {
			printf("Pokemon encontrado!\n");
			imprimir_elemento(resultado, NULL);
			printf("\n");
		} else {
			printf("No se encontró el pokemon\n");
		}
		free(pokemon_buscar.nombre);
	} else {
		printf("Opción inválida\n");
	}

	abb_destruir_todo(abb, destructor_pokemon);
	cerrar_archivo_csv(archivo);

	return 0;
}
