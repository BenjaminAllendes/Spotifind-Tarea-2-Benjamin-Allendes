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
  char tempo[100];
  char track_genre[1000] ;
} Song;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("              Spotifind                 ");
  puts("========================================");

  puts("1) Cargar canciones");
  puts("2) Buscar por genero");
  puts("3) Buscar por artista") ;
  puts("4) Buscar por tempo") ;
  puts("5) Salir");
}

/**
  Compara dos claves de tipo string para determinar si son iguales.
  Esta función se utiliza para inicializar mapas con claves de tipo string.
 */
int is_equal_str(void *key1, void *key2) {
  return strcmp((char *)key1, (char *)key2) == 0;
}

/*
   Compara dos claves de tipo entero para determinar si son iguales.
   Esta función se utiliza para inicializar mapas con claves de tipo entero.
 */
int is_equal_int(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2; // Compara valores enteros directamente
}

/**
 * Carga películas desde un archivo CSV y las almacena en distintos mapas, los cuales 
 * son los criterios de busqueda
 */
void cargar_peliculas(Map *songs_bygenres, Map *songs_byartist, Map *songs_bytempo) {
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
    // Crea una nueva estructura Song y almacena los datos de cada cancion
    Song *cancion = (Song *)malloc(sizeof(Song));
    strcpy(cancion->id, campos[0]);  ;// Asigna ID
    strcpy(cancion->artists, campos[2]);     // Asigna titulo
    strcpy(cancion->album_name, campos[3]); // Asigna nombre del album
    strcpy(cancion->track_name, campos[4]); // Asigna nombre de la cancion
    strcpy(cancion->tempo, campos[18]); // Asigna BPM 
    strcpy(cancion->track_genre, campos[20]); // Asigna genero 
    
    /* Para los mapas de genero y artista primero se pregunta si la llave no se encuentra. Si esto se cumple
    se agrega el nuevo par al mapa con el genero y el valor como una lista nueva que almacenara canciones. En cambio 
    si la llave esta entonces se agrega la cancion a la lista correspondiente.
    */
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
    if (atof(cancion->tempo) < 80){
      MapPair *par = map_search(songs_bytempo, "lentas") ;
      list_pushBack(par->value, cancion) ;
    }
    else if (atof(cancion->tempo) >= 80 && atof(cancion->tempo) <= 120) {
      MapPair *par = map_search(songs_bytempo, "moderadas") ;
      list_pushBack(par->value, cancion) ;
    }
    else {
      MapPair *par = map_search(songs_bytempo, "rapidas") ;
      list_pushBack(par->value, cancion) ;
    }
    printf("ID: %s, Titulo: %s, Artista: %s, Album: %s, Genero: %s Tempo: %s\n", cancion->id, cancion->track_name, cancion->artists, 
      cancion->album_name, cancion->track_genre, cancion->tempo) ; // Muestra cada cancion cargada

    


  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas


}

// Funcion para ingresar un genero y buscar el mapa que tenga la llave ingresada.
// Luego se muestra la lista de canciones.
void buscar_por_genero(Map *songs_bygenre) {
  char genero[100];

  // Se solicita el genero de la cancion para buscar el mapa
  printf("Ingrese el genero de la cancion: ");
  scanf(" %[^\n]s", genero); // Lee el genero del teclado

  MapPair *pair = map_search(songs_bygenre, genero);
  
  if (pair != NULL) {
      List* songs = pair->value;
      Song *canc = list_first(songs);
      // Se recorre la lista y se muestran la informacion de cada cancion
      while (canc != NULL) {
        printf("ID: %s, Titulo: %s, Artista: %s, Album: %s, Tempo: %s\n", canc->id, canc->track_name, canc->artists, canc->album_name,
           canc->tempo);
        canc = list_next(songs);
      }
  }
}
// Funcion para ingresar un artista y buscar el mapa que tenga la llave ingresada.
// Luego se muestra la lista de canciones.
void buscar_por_artista(Map *songs_byartist){
  char artista[100];
  printf("Ingrese el artista de la cancion: ");
  scanf(" %[^\n]s", artista); // Lee el artista del teclado

  MapPair *pair = map_search(songs_byartist, artista);
  
  if (pair != NULL) {
      List *songs = pair->value;
      Song *canc = list_first(songs);
      
      while (canc != NULL) {
        printf("ID : %s, Titulo: %s, Album: %s, Genero: %s, Tempo: %s \n", canc->id, canc->track_name, canc->album_name, canc->track_genre, 
          canc->tempo);
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
        printf("ID: %s,Titulo: %s, Artista: %s, Album: %s, Genero: %s Tempo: %s \n", canc->id, canc->track_name, canc->artists, canc->album_name, 
          canc->track_genre, canc->tempo);
        canc = list_next(songs);
      }
  }
}

// Funcion para ingresar una  y buscar el mapa que tenga la llave ingresada.
// Luego se muestra la lista de canciones.
void buscar_por_tempo(Map *songs_bytempo){
  
  puts("1) Lentas <80 BPM") ;
  puts("2) Moderadas 80-120 BPM") ;
  puts("3) Rapidas 120< BPM") ;
  printf("Ingrese su opcion: ") ;
  
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

// Al inicializar el mapa tempo se agregan los pares de datos ya que solo se necesitan tres tipos de llaves fijas
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

  // Se crea un mapa para cada tipo de busqueda
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
      cargar_peliculas(songs_bygenres, songs_byartist, songs_bytempo);
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
      printf("Cerrando Spotifind...\n") ;
      break;
    }
    presioneTeclaParaContinuar();

  } while (opcion != '5');

  return 0;
}
