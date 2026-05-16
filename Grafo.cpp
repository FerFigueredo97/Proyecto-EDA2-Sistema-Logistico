#include "Grafo.h"
#include <iomanip>
#include <algorithm>
#include <cctype>

int verificarNombreCiudad(std::string, Ciudad*[], int);

Grafo::Grafo() {
    cantidadNodos = 0;
    //Inicializamos la matriz vacia
    for (int i = 0; i < MAX_NODOS; i++) {
        ciudades[i] = nullptr;
        for (int j = 0; j < MAX_NODOS; j++) {
            if (i == j) {
                matriz[i][j] = 0; // Distancia a sí mismo es 0
            }
            else {
                matriz[i][j] = INFINITO; // El resto arranca sin conexión
            }
        }
    }
}

void Grafo::agregarCiudad(Ciudad* nuevaCiudad) {
    if (cantidadNodos < MAX_NODOS) { 
		if (verificarNombreCiudad(nuevaCiudad->getNombre(), ciudades, cantidadNodos) != -1) {
			std::cout << "Error: El nombre de la ciudad '" << nuevaCiudad->getNombre() << "' ya existe en el grafo. No se puede agregar.\n";
			return;
		}
        ciudades[nuevaCiudad->getId()] = nuevaCiudad;
        cantidadNodos++;
    }
}

void Grafo::conectarRuta(int idOrigen, int idDestino, int distancia) {
    matriz[idOrigen][idDestino] = distancia;
    matriz[idDestino][idOrigen] = distancia;
}

void Grafo::cortarRuta(int idOrigen, int idDestino) {
    matriz[idOrigen][idDestino] = INFINITO;
    matriz[idDestino][idOrigen] = INFINITO;
}

void Grafo::imprimirMatriz() {
    std::cout << "\nMatriz de Adyacencia Logistica:\n";

    // 1. Imprimir los nombres de las ciudades arriba (Cabecera de columnas)
    std::cout << std::setw(20) << " ";
    for (int i = 0; i < cantidadNodos; i++) {
        // Imprimimos el nombre de la ciudad con un ancho fijo para que quede alineado
        std::cout << std::setw(18) << ciudades[i]->getNombre();
    }
    std::cout << "\n";

    // 2. Imprimir las filas con sus nombres y datos
    for (int i = 0; i < cantidadNodos; i++) {
        // Imprimir el nombre de la ciudad a la izquierda (Cabecera de fila)
        std::cout << std::setw(20) << ciudades[i]->getNombre();

        // Imprimir las distancias o el estado de la ruta
        for (int j = 0; j < cantidadNodos; j++) {
            if (matriz[i][j] == INFINITO) {
                std::cout << std::setw(18) << "INF";
            }
            else {
                std::cout << std::setw(18) << matriz[i][j];
            }
        }
        std::cout << "\n";
    }
}

//Función para verificar si el nombre de la ciudad ya existe en el grafo, evita clones de ciudades con el mismo nombre (aunque con diferente ID).
int verificarNombreCiudad(std::string nuevaCiudadNombre, Ciudad* ciudades[], int cantidadNodos) {

    std::transform(nuevaCiudadNombre.begin(), nuevaCiudadNombre.end(), nuevaCiudadNombre.begin(),
        [](unsigned char c) { return std::tolower(c); });
    
    for (int i = 0; i < cantidadNodos; i++) {
        std::string nombreExistente = ciudades[i]->getNombre();    
        std::transform(nombreExistente.begin(), nombreExistente.end(), nombreExistente.begin(),
            [](unsigned char c) { return std::tolower(c); });

		if (nuevaCiudadNombre == nombreExistente) {
            return i;
		}
	}
    return -1; 
}