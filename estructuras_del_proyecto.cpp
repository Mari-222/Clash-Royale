#include <iostream>
using namespace std;



// Lista simple - inserción al inicio
struct Cartas {
    int IDCarta;
    string Nombre;
    string Rareza;
    string Tipo;
    int costoElixir;
    double dañoBase;
    int vidaBase;
    Cartas* sig;

    Cartas(int IDC, string n, string r, string t, int ce, double db, int vb) {
        IDCarta = IDC;
        Nombre = n;
        Rareza = r;
        Tipo = t;
        costoElixir = ce;
        dañoBase = db;
        vidaBase = vb;
        sig = NULL;
    }
} *primerCarta = NULL;


// Lista doble ordenada por nombre
struct Jugadores {
    int IDJugador;
    string nombreUsuario;
    int nivelRey;
    int trofeos;
    int IDArena;
    int IDClan;
    Jugadores* sig;
    Jugadores* ant;

    Jugadores(int IDJ, string n, int nr, int t, int IDA, int IDC) {
        IDJugador = IDJ;
        nombreUsuario = n;
        nivelRey = nr;
        trofeos = t;
        IDArena = IDA;
        IDClan = IDC;
        sig = NULL;
        ant = NULL;
    }
} *primerJugador = NULL;

// Nodo sublista de cartas dentro de un mazo
struct NodoCartaMazo {
    int IDCarta;
    NodoCartaMazo* sig;

    NodoCartaMazo(int id) {
        IDCarta = id;
        sig = NULL;
    }
};

// Lista simple - inserción al final
struct Mazos {
    int IDMazo;
    string nombreMazo;
    string tipoMazo;
    int IDJugador;
    NodoCartaMazo* listaCartas;
    int cantidadCartas;
    Mazos* sig;

    Mazos(int IDM, string nm, string tm, int IDJ) {
        IDMazo = IDM;
        nombreMazo = nm;
        tipoMazo = tm;
        IDJugador = IDJ;
        listaCartas = NULL;
        cantidadCartas = 0;
        sig = NULL;
    }
} *primerMazo = NULL;

// Nodo sublista de jugadores dentro de un clan
struct NodoJugadorClan {
    int IDJugador;
    NodoJugadorClan* sig;

    NodoJugadorClan(int id) {
        IDJugador = id;
        sig = NULL;
    }
};

// Lista circular - inserción al final
struct Clanes {
    int IDClan;
    string nombreClan;
    string region;
    int cantidadMiembros;
    double puntajeClan;
    NodoJugadorClan* listaJugadores;
    Clanes* sig;

    Clanes(int idclan, string nclan, string reg, int cantmiembros, double puntaje) {
        IDClan = idclan;
        nombreClan = nclan;
        region = reg;
        cantidadMiembros = cantmiembros;
        puntajeClan = puntaje;
        listaJugadores = NULL;
        sig = NULL;
    }
} *primerClan = NULL;

// Lista simple - inserción al inicio
struct Arenas {
    int IDArena;
    string nombreArena;
    int trofeosMin;
    int trofeosMax;
    Arenas* sig;

    Arenas(int IDA, string nA, int tmin, int tmax) {
        IDArena = IDA;
        nombreArena = nA;
        trofeosMin = tmin;
        trofeosMax = tmax;
        sig = NULL;
    }
} *primerArena = NULL;

// Lista doble circular - inserción al final
struct Batallas {
    int IDBatalla;
    int IDJugador1;
    int IDJugador2;
    int IDMazo1;
    int IDMazo2;
    string ganador;
    int coronasJ1;
    int coronasJ2;
    float duracion;
    int IDArena;
    string fecha;
    Batallas* sig;
    Batallas* ant;

    Batallas(int IDB, int IDJ1, int IDJ2, int IDM1, int IDM2, string g,
             int cJ1, int cJ2, float d, int IDA, string f) {
        IDBatalla = IDB;
        IDJugador1 = IDJ1;
        IDJugador2 = IDJ2;
        IDMazo1 = IDM1;
        IDMazo2 = IDM2;
        ganador = g;
        coronasJ1 = cJ1;
        coronasJ2 = cJ2;
        duracion = d;
        IDArena = IDA;
        fecha = f;
        sig = NULL;
        ant = NULL;
    }
} *primerBatalla = NULL;











// FUNCIONES DE CARTAS (Lista simple - inserción al inicio)


// Ver si existe carta con ese ID
bool existeCarta(int id) {
    Cartas* temp = primerCarta;
    while (temp != NULL) {
        if (temp->IDCarta == id) {
            return true;
        }
        temp = temp->sig;
    }
    return false;
}

void insertarCarta(int id, string nombre, string rareza, string tipo,
                   int costoElixir, double dañoBase, int vidaBase) {

    if (existeCarta(id)) {
        cout << "Error: Ya existe una carta con el ID " << id << endl;

    } else if (costoElixir <= 0) {
        cout << "Error: El costo de elixir debe ser mayor a 0" << endl;

    } else if (dañoBase < 0) {
        cout << "Error: El daño base no puede ser negativo" << endl;

    } else if (vidaBase <= 0) {
        cout << "Error: La vida base debe ser mayor a 0" << endl;

    } else {
        Cartas* nueva = new Cartas(id, nombre, rareza, tipo, costoElixir, dañoBase, vidaBase);

// Inserción al inicio
        nueva->sig = primerCarta;
        primerCarta = nueva;

        cout << "Carta '" << nombre << "' insertada correctamente." << endl;
    }
}


// FUNCIONES DE ARENAS (Lista simple - inserción al inicio)


// Verifica si ya existe una arena con ese ID
bool existeArena(int id) {
    Arenas* temp = primerArena;
    while (temp != NULL) {
        if (temp->IDArena == id) {
            return true;
        }
        temp = temp->sig;
    }
    return false;
}

void insertarArena(int id, string nombre, int trofeosMin, int trofeosMax) {

    if (existeArena(id)) {
        cout << "Error: Ya existe una arena con el ID " << id << "." << endl;

    } else if (trofeosMin < 0) {
        cout << "Error: El mínimo de trofeos no puede ser negativo." << endl;

    } else if (trofeosMax <= trofeosMin) {
        cout << "Error: El máximo de trofeos debe ser mayor al mínimo." << endl;

    } else {
        Arenas* nueva = new Arenas(id, nombre, trofeosMin, trofeosMax);

        // Inserción al inicio
        nueva->sig = primerArena;
        primerArena = nueva;

        cout << "Arena '" << nombre << "' insertada correctamente." << endl;
    }
}


// FUNCIONES DE JUGADORES (Lista doble - ordenada por nombre)

// Ver si existe un jugador con ese ID
bool existeJugador(int id) {
    Jugadores* temp = primerJugador;
    while (temp != NULL) {
        if (temp->IDJugador == id) {
            return true;
        }
        temp = temp->sig;
    }
    return false;
}

// Busca una arena por ID y devuelve su puntero (para validar trofeos)
Arenas* buscarArena(int id) {
    Arenas* temp = primerArena;
    while (temp != NULL) {
        if (temp->IDArena == id) {
            return temp;
        }
        temp = temp->sig;
    }
    return NULL;
}

// Ver si existe un clan con ese ID
bool existeClan(int id) {
    if (primerClan == NULL) return false;
    Clanes* temp = primerClan;
    do {
        if (temp->IDClan == id) return true;
        temp = temp->sig;
    } while (temp != primerClan);
    return false;
}

void insertarJugador(int id, string nombre, int nivelRey, int trofeos, int IDArena, int IDClan) {

    if (existeJugador(id)) {
        cout << "Error: Ya existe un jugador con el ID " << id << "." << endl;

    } else if (nivelRey <= 0 || nivelRey > 15) {
        cout << "Error: El nivel del rey debe estar entre 1 y 15." << endl;

    } else if (trofeos < 0) {
        cout << "Error: Los trofeos no pueden ser negativos." << endl;

    } else if (!existeArena(IDArena)) {
        cout << "Error: No existe una arena con el ID " << IDArena << "." << endl;

    } else if (IDClan != 0 && !existeClan(IDClan)) {
// IDClan = 0 significa que el jugador no pertenece a ningún clan
        cout << "Error: No existe un clan con el ID " << IDClan << "." << endl;

    } else {
//ver que lso trofeos si sean del rango de esa arena
        Arenas* arena = buscarArena(IDArena);
        if (trofeos < arena->trofeosMin || trofeos > arena->trofeosMax) {
            cout << "Error: Los trofeos (" << trofeos << ") no corresponden al rango de la arena '"
                 << arena->nombreArena << "' (" << arena->trofeosMin << " - " << arena->trofeosMax << ")." << endl;

        } else {
            Jugadores* nuevo = new Jugadores(id, nombre, nivelRey, trofeos, IDArena, IDClan);

            if (primerJugador == NULL) {
                primerJugador = nuevo;

// Insertar al inicio (nombre menor al primero)
            } else if (nombre < primerJugador->nombreUsuario) {
                nuevo->sig = primerJugador;
                primerJugador->ant = nuevo;
                primerJugador = nuevo;

            // Buscar posición ordenada por nombre
            } else {
                Jugadores* temp = primerJugador;
                while (temp->sig != NULL && temp->sig->nombreUsuario < nombre) {
                    temp = temp->sig;
                }
                nuevo->sig = temp->sig;
                nuevo->ant = temp;
                if (temp->sig != NULL) {
                    temp->sig->ant = nuevo;
                }
                temp->sig = nuevo;
            }

            cout << "Jugador '" << nombre << "' insertado correctamente." << endl;
        }
    }
}


// FUNCIONES DE CLANES (Lista circular - inserción al final)

void insertarClan(int id, string nombre, string region, int cantMiembros, double puntaje) {

    if (existeClan(id)) {
        cout << "Error: Ya existe un clan con el ID " << id << "." << endl;

    } else if (cantMiembros < 0) {
        cout << "Error: La cantidad de miembros no puede ser negativa." << endl;

    } else if (puntaje < 0) {
        cout << "Error: El puntaje del clan no puede ser negativo." << endl;

    } else {
        Clanes* nuevo = new Clanes(id, nombre, region, cantMiembros, puntaje);

        if (primerClan==NULL) {
            nuevo->sig=nuevo;
            primerClan=nuevo;

// Inserción al final: recorrer hasta el último y enlazar   /ver si es circular en el docu
        } else {
            Clanes* temp = primerClan;
            while (temp->sig != primerClan) {
                temp = temp->sig;
            }
            temp->sig = nuevo;     
            nuevo->sig = primerClan; 
        }

        cout << "Clan '" << nombre << "' insertado correctamente." << endl;
    }
}





// FUNCIONES DE MAZOS (Lista simple - inserción al final)

// Ver si y ahay mazo con ese ID
bool existeMazo(int id) {
    Mazos* temp = primerMazo;
    while (temp != NULL) {
        if (temp->IDMazo == id) return true;
        temp = temp->sig;
    }
    return false;
}

void insertarMazo(int id, string nombre, string tipo, int IDJugador) {

    if (existeMazo(id)) {
        cout << "Error: Ya existe un mazo con el ID " << id << "." << endl;

    } else if (!existeJugador(IDJugador)) {
        cout << "Error: No existe un jugador con el ID " << IDJugador << "." << endl;

    } else {
        Mazos* nuevo = new Mazos(id, nombre, tipo, IDJugador);

        if (primerMazo == NULL) {
            primerMazo = nuevo;

// Inserción al final
        } else {
            Mazos* temp = primerMazo;
            while (temp->sig != NULL) {
                temp = temp->sig;
            }
            temp->sig = nuevo;
        }

        cout << "Mazo '" << nombre << "' insertado correctamente." << endl;
        cout << "Recuerde agregar exactamente 8 cartas al mazo." << endl;
    }
}

// Agrega una carta a la sublista de un mazo (debe tener exactamente 8 al confirmar)
void agregarCartaAMazo(int IDMazo, int IDCarta) {
    Mazos* mazo = primerMazo;
    while (mazo != NULL && mazo->IDMazo != IDMazo) {
        mazo = mazo->sig;
    }

    if (mazo == NULL) {
        cout << "Error: No existe un mazo con el ID " << IDMazo << "." << endl;

    } else if (!existeCarta(IDCarta)) {
        cout << "Error: No existe una carta con el ID " << IDCarta << "." << endl;

    } else if (mazo->cantidadCartas >= 8) {
        cout << "Error: El mazo ya tiene 8 cartas." << endl;

    } else {
//ver que carta no se repita en el mazo
        NodoCartaMazo* temp = mazo->listaCartas;
        bool repetida = false;
        while (temp != NULL) {
            if (temp->IDCarta == IDCarta) {
                repetida = true;
                break;
            }
            temp = temp->sig;
        }

        if (repetida) {
            cout << "Error: La carta " << IDCarta << " ya está en este mazo." << endl;

        } else {
            NodoCartaMazo* nuevaCarta = new NodoCartaMazo(IDCarta);
            nuevaCarta->sig = mazo->listaCartas;
            mazo->listaCartas = nuevaCarta;
            mazo->cantidadCartas++;
            cout << "Carta agregada al mazo. Total: " << mazo->cantidadCartas << "/8" << endl;
        }
    }
}


// FUNCIONES DE BATALLAS (Lista doble circular - inserción al final)


// Verr si t
bool existeBatalla(int id) {
    if (primerBatalla == NULL) return false;
    Batallas* temp = primerBatalla;
    do {
        if (temp->IDBatalla == id) return true;
        temp = temp->sig;
    } while (temp != primerBatalla);
    return false;
}

// Busca un mazo por ID y devuelve su puntero
Mazos* buscarMazo(int id) {
    Mazos* temp = primerMazo;
    while (temp != NULL) {
        if (temp->IDMazo == id) return temp;
        temp = temp->sig;
    }
    return NULL;
}

void insertarBatalla(int id, int IDJ1, int IDJ2, int IDM1, int IDM2,
                     string ganador, int coronasJ1, int coronasJ2,
                     float duracion, int IDArena, string fecha) {

    if (existeBatalla(id)) {
        cout << "Error: Ya existe una batalla con el ID " << id << "." << endl;

    } else if (!existeJugador(IDJ1)) {
        cout << "Error: No existe el jugador 1 con ID " << IDJ1 << "." << endl;

    } else if (!existeJugador(IDJ2)) {
        cout << "Error: No existe el jugador 2 con ID " << IDJ2 << "." << endl;

    } else if (IDJ1 == IDJ2) {
        cout << "Error: Los dos jugadores no pueden ser el mismo." << endl;

    } else if (!existeArena(IDArena)) {
        cout << "Error: No existe una arena con el ID " << IDArena << "." << endl;

    } else if (coronasJ1 < 0 || coronasJ1 > 3) {
        cout << "Error: Las coronas del jugador 1 deben estar entre 0 y 3." << endl;

    } else if (coronasJ2 < 0 || coronasJ2 > 3) {
        cout << "Error: Las coronas del jugador 2 deben estar entre 0 y 3." << endl;

    } else if (duracion <= 0) {
        cout << "Error: La duración de la batalla debe ser mayor a 0." << endl;

    } else {
//ver que mazo sea de jugador correcto
        Mazos* mazo1 = buscarMazo(IDM1);
        Mazos* mazo2 = buscarMazo(IDM2);

        if (mazo1 == NULL) {
            cout << "Error: No existe el mazo 1 con ID " << IDM1 << "." << endl;

        } else if (mazo2 == NULL) {
            cout << "Error: No existe el mazo 2 con ID " << IDM2 << "." << endl;

        } else if (mazo1->IDJugador != IDJ1) {
            cout << "Error: El mazo " << IDM1 << " no pertenece al jugador " << IDJ1 << "." << endl;

        } else if (mazo2->IDJugador != IDJ2) {
            cout << "Error: El mazo " << IDM2 << " no pertenece al jugador " << IDJ2 << "." << endl;

        } else {
            Batallas* nueva = new Batallas(id, IDJ1, IDJ2, IDM1, IDM2, ganador,
                                           coronasJ1, coronasJ2, duracion, IDArena, fecha);

// Lista vacía: apuntarse a sí mismo (circular doble)
            if (primerBatalla == NULL) {
                nueva->sig = nueva;
                nueva->ant = nueva;
                primerBatalla = nueva;

// Inserción al final
            } else {
                Batallas* ultimo = primerBatalla->ant; // en circular doble, ant del primero=ultimo
                ultimo->sig = nueva;
                nueva->ant = ultimo;
                nueva->sig = primerBatalla;
                primerBatalla->ant = nueva;
            }

            cout << "Batalla " << id << " registrada correctamente." << endl;
        }
    }
}


//main para probar
int main() {
    cout << "Sistema Clash Royale iniciado." << endl;
    return 0;
}