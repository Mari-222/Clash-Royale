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
