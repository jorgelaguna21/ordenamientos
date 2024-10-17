#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solicitud {
public:
    string nombreAlumno;
    string nombreCarrera;
    string nombrePreparatoria;
    float promedio;

    Solicitud(string nombre, string carrera, string preparatoria, float prom)
        : nombreAlumno(nombre), nombreCarrera(carrera), nombrePreparatoria(preparatoria), promedio(prom) {}
};

class Lista {
private:
    vector<Solicitud> solicitudes;

public:
    void darDeAlta(const Solicitud& solicitud) {
        solicitudes.push_back(solicitud);
        ordenarPorPromedio(); // Ordenar después de cada alta
    }

    void insertarAdjunto(const Solicitud& solicitud, int posicion) {
        if (posicion < 0 || posicion > solicitudes.size()) {
            cout << "Posición inválida. Debe estar entre 0 y " << solicitudes.size() << ".\n";
            return;
        }
        solicitudes.insert(solicitudes.begin() + posicion, solicitud);
        ordenarPorPromedio(); // Ordenar después de la inserción
    }

    void ordenarPorPromedio() {
        // Implementación de la inserción
        for (int i = 1; i < solicitudes.size(); i++) {
            Solicitud aux = solicitudes[i];
            int j = i - 1;
            while (j >= 0 && aux.promedio > solicitudes[j].promedio) {
                solicitudes[j + 1] = solicitudes[j];
                j--;
            }
            solicitudes[j + 1] = aux;
        }
    }

    int buscarSolicitud(const string& nombre) {
        int i = 0, j = solicitudes.size() - 1;
        while (i <= j) {
            int medio = (i + j) / 2;
            if (solicitudes[medio].nombreAlumno == nombre) {
                return medio; // Se encontró el elemento
            } else if (solicitudes[medio].nombreAlumno < nombre) {
                i = medio + 1; // Buscar en la mitad derecha
            } else {
                j = medio - 1; // Buscar en la mitad izquierda
            }
        }
        return -1; // No encontrado
    }

    void mostrarSolicitudes() {
        cout << "\n--- Lista de Solicitudes ---\n";
        for (size_t i = 0; i < solicitudes.size(); i++) {
            cout << "Solicitud " << i + 1 << ": "
                 << "Nombre: " << solicitudes[i].nombreAlumno
                 << ", Carrera: " << solicitudes[i].nombreCarrera
                 << ", Preparatoria: " << solicitudes[i].nombrePreparatoria
                 << ", Promedio: " << solicitudes[i].promedio << endl;
        }
        cout << "-----------------------------\n";
    }

    const Solicitud& getSolicitud(int index) const {
        return solicitudes[index];
    }
};

int main() {
    Lista listaSolicitudes;
    int opcion;

    do {
        cout << "\n--- ++ MENU UNIVERSITARIO ++ ---\n";
        cout << "-----------------------------\n\n";
        cout << "1. Dar de alta la solicitud\n\n";
        cout << "2. Buscar una solicitud\n\n";
        cout << "3. Mostrar solicitudes\n\n";
        cout << "4. Salir\n\n";
        cout << "Seleccione una opcion: \n";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1: {
                string nombre, carrera, preparatoria;
                float promedio;
                cout << "Ingrese nombre del alumno: ";
                getline(cin, nombre);
                cout << "Ingrese nombre de la carrera: ";
                getline(cin, carrera);
                cout << "Ingrese nombre de la preparatoria: ";
                getline(cin, preparatoria);
                cout << "Ingrese promedio: ";
                cin >> promedio;

                Solicitud nuevaSolicitud(nombre, carrera, preparatoria, promedio);
                listaSolicitudes.darDeAlta(nuevaSolicitud);
                cout << "Solicitud dada de alta exitosamente.\n";
                break;
            }
            case 2: {
                string nombre;
                cout << "Ingrese nombre del alumno a buscar: ";
                getline(cin, nombre);

                int posicion = listaSolicitudes.buscarSolicitud(nombre);
                if (posicion != -1) {
                    const Solicitud& solicitud = listaSolicitudes.getSolicitud(posicion);
                    cout << "\n --- Solicitud Encontrada ---\n";
                    cout << "Nombre: " << solicitud.nombreAlumno << "\n";
                    cout << "Carrera: " << solicitud.nombreCarrera << "\n";
                    cout << "Preparatoria: " << solicitud.nombrePreparatoria << "\n";
                    cout << "Promedio: " << solicitud.promedio << "\n";
                    cout << "Posicion en la lista: " << posicion + 1 << "\n";
                    cout << "-----------------------------\n";
                } else {
                    cout << "Solicitud no encontrada. Debe dar de alta una solicitud.\n";
                }
                break;
            }
            case 3:
                listaSolicitudes.mostrarSolicitudes();
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 4);

    return 0;
}
