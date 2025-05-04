#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char id[100];
  char artists[100];
  char album_name[100];
  char track_name[100];
  float tempo;
  char track_genre[1000] ;
} Song;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Base de Datos de canciones");
  puts("========================================");

  puts("1) Cargar canciones");
  puts("2) Buscar por genero");
  puts("3) Buscar por artista") ;
  puts("4) Buscar por tempo") ;
  puts("5) Salir");
}

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/**
 * Compara dos claves de tipo entero para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo entero.
 *
 * @param key1 Primer puntero a la clave entera.
 * @param key2 Segundo puntero a la clave entera.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

/**
 * Carga películas desde un archivo CSV y las almacena en un mapa por ID.
 */
void cargar_peliculas(List *list_canciones, Map *songs_bygenres, Map *songs_byartist, Map *songs_bytempo) {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/song_dataset_.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV
  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    // Crea una nueva estructura Film y almacena los datos de cada película
    Song *cancion = (Song *)malloc(sizeof(Song));
    strcpy(cancion->id, campos[0]); ;// Asigna ID
    strcpy(cancion->artists, campos[2]);     // Asigna título
    strcpy(cancion->album_name, campos[3]); // Asigna director
    strcpy(cancion->track_name, campos[4]);
    cancion->tempo = atof(campos[18]) ;
    strcpy(cancion->track_genre, campos[20]);
    
    list_pushBack(list_canciones, cancion);

    if (map_search(songs_bygenres, cancion->track_genre) == NULL){
      List *list_genre = list_create() ;
      list_pushFront(list_genre, cancion) ;
      map_insert(songs_bygenres, cancion->track_genre, list_genre) ;
    }
    else {
      MapPair *par = map_search(songs_bygenres, cancion->track_genre) ;
      list_pushBack(par->value, cancion) ;
    }
    if (map_search(songs_byartist, cancion->artists) == NULL){
      List *list_artist = list_create() ;
      list_pushFront(list_artist, cancion) ;
      map_insert(songs_byartist, cancion->artists, list_artist) ;
    }
    else {
      MapPair *par = map_search(songs_byartist, cancion->artists) ;
      list_pushBack(par->value, cancion) ;
    }
    if (cancion->tempo < 80){
      MapPair *par = map_search(songs_bytempo, "lentas") ;
      list_pushBack(par->value, cancion) ;
    }
    else if (cancion->tempo >= 80 && cancion->tempo <= 120) {
      MapPair *par = map_search(songs_bytempo, "moderadas") ;
      list_pushBack(par->value, cancion) ;
    }
    else {
      MapPair *par = map_search(songs_bytempo, "rapidas") ;
      list_pushBack(par->value, cancion) ;
    }

    


  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas


}

void buscar_por_genero(Map *songs_bygenre) {
  char genero[100];

  // Solicita al usuario el ID de la película
  printf("Ingrese el género de la cancion: ");
  scanf(" %[^\n]s", genero); // Lee el genero del teclado

  MapPair *pair = map_search(songs_bygenre, genero);
  
  if (pair != NULL) {
      List* songs = pair->value;
      Song *canc = list_first(songs);
      
      while (canc != NULL) {
        printf("titulo: %s, artista: %s, nombre del album: %s, id: %s \n", canc->track_name, canc->artists, canc->album_name, canc->id);
        canc = list_next(songs);
      }
  }
}

void buscar_por_artista(Map *songs_byartist){
  char artista[100];
  printf("Ingrese el artista de la cancion: ");
  scanf(" %[^\n]s", artista); // Lee el artista del teclado

  MapPair *pair = map_search(songs_byartist, artista);
  
  if (pair != NULL) {
      List *songs = pair->value;
      Song *canc = list_first(songs);
      
      while (canc != NULL) {
        printf("id: %d, titulo: %s, nombre del album: %s \n", canc->id,  canc->track_name, canc->artists, canc->album_name);
        canc = list_next(songs);
      }
  }
}
void mostrar_tempo(Map* songs_bytempo,char temp[10]){ 
  MapPair *pair = map_search(songs_bytempo, temp);
      
  if (pair != NULL) {
      List* songs = pair->value;
      Song *canc = list_first(songs);
      
      while (canc != NULL) {
        printf("Titulo: %s, artista: %s, album: %s, tempo: %f \n", canc->track_name, canc->artists, canc->album_name, canc->tempo);
        canc = list_next(songs);
      }
  }
}


void buscar_por_tempo(Map *songs_bytempo){
  printf("Ingrese la opcion:\n") ;
  puts("1) Lentas <80 BPM") ;
  puts("2) Moderadas 80-120 BPM") ;
  puts("3) Rapidas 120< BPM") ;
  
  char opcion ;
  scanf(" %c", &opcion) ;
  MapPair *pair ;
  switch (opcion)
  {
    case '1':
      mostrar_tempo(songs_bytempo, "lentas") ;
      break;
    case '2':  
      mostrar_tempo(songs_bytempo, "moderadas") ;
      break;

    case '3':
      mostrar_tempo(songs_bytempo, "rapidas") ;
      break;
  }
}

void asignar_claves_tempo(Map *tempo){
  List *lentas = list_create() ;
  List *moderadas = list_create() ;
  List *rapidas = list_create() ;
  
  map_insert(tempo, "lentas", lentas) ;
  map_insert(tempo, "moderadas", moderadas) ;
  map_insert(tempo, "rapidas", rapidas) ;

}


int main() {
  char opcion; // Variable para almacenar una opción ingresada por el usuario
               // (sin uso en este fragmento)

  // Crea un mapa para almacenar películas, utilizando una función de
  // comparación que trabaja con claves de tipo string.
  List *list_canciones = list_create() ;
  Map *songs_bygenres = map_create(is_equal_str);
  Map *songs_byartist = map_create(is_equal_str) ;
  Map *songs_bytempo = map_create(is_equal_str) ;
  asignar_claves_tempo(songs_bytempo) ;

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opcion: ");
    scanf(" %c", &opcion);

    switch (opcion) {
    case '1':
      cargar_peliculas(list_canciones, songs_bygenres, songs_byartist, songs_bytempo);
      break;
    case '2':
      buscar_por_genero(songs_bygenres);
      break;
    case '3':
      buscar_por_artista(songs_byartist) ;
      break;
    case '4':
      buscar_por_tempo(songs_bytempo) ;
      break;
    case '5':
      printf("saliendo...\n") ;
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '5');

  return 0;
}
