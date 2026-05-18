#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Estudiante {

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;
};

struct Nodo {

    Estudiante estudiante;
    Nodo* siguiente;
};

class HashTable {

private:

    static const int SIZE = 20;

    Nodo* tabla[SIZE];

    int totalElementos;
    int totalColisiones;

    int funcionHash(int id) {

        return id % SIZE;
    }

public:

    HashTable() {

        for (int i = 0; i < SIZE; i++) {

            tabla[i] = nullptr;
        }

        totalElementos = 0;
        totalColisiones = 0;
    }

    Estudiante* buscar(int id) {

        int indice = funcionHash(id);

        Nodo* actual = tabla[indice];

        while (actual != nullptr) {

            if (actual->estudiante.student_id == id) {

                return &actual->estudiante;
            }

            actual = actual->siguiente;
        }

        return nullptr;
    }

    bool insertar(Estudiante estudiante) {

        int indice = funcionHash(estudiante.student_id);

        if (buscar(estudiante.student_id) != nullptr) {

            cout << "Error: estudiante duplicado.\n";

            return false;
        }

        Nodo* nuevo = new Nodo;

        nuevo->estudiante = estudiante;

        nuevo->siguiente = tabla[indice];

        if (tabla[indice] != nullptr) {

            totalColisiones++;
        }

        tabla[indice] = nuevo;

        totalElementos++;

        return true;
    }

    bool eliminar(int id) {

        int indice = funcionHash(id);

        Nodo* actual = tabla[indice];

        Nodo* anterior = nullptr;

        while (actual != nullptr) {

            if (actual->estudiante.student_id == id) {

                if (anterior == nullptr) {

                    tabla[indice] = actual->siguiente;

                } else {

                    anterior->siguiente = actual->siguiente;
                }

                delete actual;

                totalElementos--;

                cout << "Estudiante eliminado.\n";

                return true;
            }

            anterior = actual;

            actual = actual->siguiente;
        }

        cout << "No encontrado.\n";

        return false;
    }

    void cargarCSV(string nombreArchivo) {

        ifstream archivo(nombreArchivo);

        cout << "\nIntentando abrir: "
             << nombreArchivo
             << endl;

        if (!archivo.is_open()) {

            cout << "ERROR: no se pudo abrir estudiantes.csv\n";

            return;
        }

        string linea;

        getline(archivo, linea);

        while (getline(archivo, linea)) {

            stringstream ss(linea);

            string dato;

            Estudiante e;

            getline(ss, dato, ',');
            e.student_id = stoi(dato);

            getline(ss, e.full_name, ',');

            getline(ss, e.career, ',');

            getline(ss, dato, ',');
            e.semester = stoi(dato);

            getline(ss, dato, ',');
            e.gpa = stof(dato);

            getline(ss, dato, ',');
            e.skill_score = stoi(dato);

            insertar(e);

            cout << "Cargando estudiante: "
                 << e.student_id
                 << " - "
                 << e.full_name
                 << endl;
        }

        archivo.close();

        cout << "\nCarga masiva completada.\n";
    }

    void mostrarTabla() {

    cout << "\n===== TABLA HASH =====\n";

    for (int i = 0; i < SIZE; i++) {

        cout << "Bucket [" << i << "] -> ";

        Nodo* actual = tabla[i];

        if (actual == nullptr) {

            cout << "vacio -> NULL";
        }

        while (actual != nullptr) {

            cout << "("
                 << actual->estudiante.student_id
                 << ", "
                 << actual->estudiante.full_name
                 << ") -> ";

            actual = actual->siguiente;
        }

        if (tabla[i] != nullptr) {

            cout << "NULL";
        }

        cout << endl;
    }
}

    void mostrarEstadisticas() {

        cout << "\n===== ESTADISTICAS =====\n";

        cout << "Total estudiantes: "
             << totalElementos
             << endl;

        cout << "Total colisiones: "
             << totalColisiones
             << endl;

        cout << "Factor de carga: "
             << (float) totalElementos / SIZE
             << endl;
    }

    ~HashTable() {

        for (int i = 0; i < SIZE; i++) {

            Nodo* actual = tabla[i];

            while (actual != nullptr) {

                Nodo* temp = actual;

                actual = actual->siguiente;

                delete temp;
            }
        }
    }
};

void mostrarMenu() {

    cout << "\n===== MENU =====\n";

    cout << "1. Cargar CSV\n";
    cout << "2. Buscar estudiante\n";
    cout << "3. Eliminar estudiante\n";
    cout << "4. Mostrar tabla hash\n";
    cout << "5. Mostrar estadisticas\n";
    cout << "6. Salir\n";

    cout << "Opcion: ";
}

void buscarEstudiante(HashTable& hash) {

    int id;

    cout << "Ingrese ID: ";

    cin >> id;

    Estudiante* e = hash.buscar(id);

    if (e != nullptr) {

        cout << "\n===== ESTUDIANTE ENCONTRADO =====\n";

        cout << "ID: "
             << e->student_id
             << endl;

        cout << "Nombre: "
             << e->full_name
             << endl;

        cout << "Carrera: "
             << e->career
             << endl;

        cout << "Semestre: "
             << e->semester
             << endl;

        cout << "GPA: "
             << e->gpa
             << endl;

        cout << "Skill Score: "
             << e->skill_score
             << endl;

    } else {

        cout << "Estudiante no encontrado.\n";
    }
}

void eliminarEstudiante(HashTable& hash) {

    int id;

    cout << "Ingrese ID: ";

    cin >> id;

    hash.eliminar(id);
}

int main() {

    cout << "Julio Cesar Xam Chivalan\n";
    cout << "Carnet: 9941-24-8897\n";

    HashTable hash;

    int opcion;

    do {

        mostrarMenu();

        cin >> opcion;

        switch (opcion) {

            case 1:

                hash.cargarCSV("estudiantes.csv");

                break;

            case 2:

                buscarEstudiante(hash);

                break;

            case 3:

                eliminarEstudiante(hash);

                break;

            case 4:

                hash.mostrarTabla();

                break;

            case 5:

                hash.mostrarEstadisticas();

                break;

            case 6:

                cout << "Saliendo del programa...\n";

                break;

            default:

                cout << "Opcion invalida.\n";
        }

    } while (opcion != 6);

    return 0;
}