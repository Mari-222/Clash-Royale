#include <iostream>

using namespace std;

//lista simple 
struct Cartas{
    int IDCarta;
    string Nombre;
    string Rareza;
    string Tipo;
    int costoElixir;
    double dañoBase;
    int vidaBase;

    Cartas *sig;

    Cartas(int IDC, string n, string r, string t, int ce, double db, int vb){
        IDCarta = IDC;
        Nombre = n;
        Rareza = r;
        Tipo = t;
        costoElixir = ce;
        dañoBase = db; 
        vidaBase = vb;
        sig = NULL;
    }
}*primerCarta;


//lista doble
struct Jugadores{
    int IDJugador;
    string nombreUsuario;
    int nivelRey;
    int trofeos;
    int IDArena;
    int IDClan;

    Jugadores *sig, *ant;

    Jugadores(int IDJ, string n, int nr, int t, int IDA, int IDC){
        IDJugador = IDJ;
        nombreUsuario = n;
        nivelRey = nr;
        trofeos = t;
        IDArena = IDA;
        IDClan = IDC;
        sig = NULL;
        ant = NULL;
    }
}*primerJugador;


// Nodo de la sublista (guarda el ID de la carta)
struct NodoCartaMazo {
    int IDCarta;
    NodoCartaMazo *sig;

    NodoCartaMazo(int id) {
        IDCarta = id;
        sig = NULL;
    }
};


//lista simple
struct Mazos{
    int IDMazo;
    string nombreMazo;
    string tipoMazo;
    int IDJugador; 
    NodoCartaMazo *listaCartas;
    int cantidadCartas;

    Mazos *sig;

    Mazos(int IDM, string nm, string tm, int IDJ){
        IDMazo = IDM;
        nombreMazo = nm;
        tipoMazo = tm;
        IDJugador = IDJ;
        listaCartas = NULL;
        cantidadCartas = 0;
        sig = NULL;
    }
}*primerMazo;


// Nodo de la sublista
struct NodoJugadorClan {
    int IDJugador;
    NodoJugadorClan *sig;

    NodoJugadorClan(int id) {
        IDJugador = id;
        sig = NULL;
    }
};


//lista circular de clanes 
struct Clanes{
    int IDClan;
    string nombreClan;
    string region;
    int cantidadMiembros;
    double puntajeClan;
    NodoJugadorClan *listaJugadores;

    Clanes *sig;

    Clanes(int idclan, string nclan, string reg, int cantmienbros, double puntaje){
        IDClan = idclan;
        nombreClan = nclan;
        region = reg;
        cantidadMiembros = cantmienbros;
        puntajeClan = puntaje;
        listaJugadores = NULL;
        sig = NULL;
    }
}*primerClan;


//lista simple de arenas
struct Arenas{
    int IDArena;
    string nombreArena;
    int trofeosMin;
    int trofeosMax;

    Arenas *sig;

    Arenas(int IDA, string nA, int tmin, int tmax){
        IDArena = IDA;
        nombreArena = nA;
        trofeosMin = tmin;
        trofeosMax = tmax;
        sig = NULL;
    }
}*primerArena;


//lista circular doble de batallas
struct Batallas{
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
    string fecha; //investigar como almacenar la fecha de manera eficiente

    Batallas *sig, *ant;

    Batallas(int IDB, int IDJ1, int IDJ2, int IDM1, int IDM2, string g, int cJ1, int cJ2, float d, int IDA, string f){
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
}*primerBatalla;
