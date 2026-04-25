#include <iostream>
#include <algorithm>

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

    Clanes(int idclan, string nclan, string reg, int cantmiembros, double puntaje){
        IDClan = idclan;
        nombreClan = nclan;
        region = reg;
        cantidadMiembros = cantmiembros;
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

//CODIGO AUXILIAR PARA BUSQUEDAS, Y ASI NO TENER QUE ESTAR VALIDANDO EN CADA INSERCION SI EXISTE O NO EL ID
Cartas *buscarCarta(int IDCarta){
    Cartas *temp = primerCarta;

    while(temp != NULL){
        if(temp -> IDCarta == IDCarta)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

Jugadores *buscarJugador(int IDJugador){
    Jugadores *temp = primerJugador;

    while(temp != NULL){
        if(temp -> IDJugador == IDJugador)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

Mazos *buscarMazo(int IDMazo){
    Mazos *temp = primerMazo;

    while(temp != NULL){
        if(temp -> IDMazo == IDMazo)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

Clanes *buscarClan(int IDClan){
    Clanes *temp = primerClan;

    if(temp != NULL){
        do {
            if(temp -> IDClan == IDClan)
                return temp;
            temp = temp -> sig;
        } while(temp != primerClan);
    }
    return NULL;
}

Arenas *buscarArena(int IDArena){
    Arenas *temp = primerArena;

    while(temp != NULL){
        if(temp -> IDArena == IDArena)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

Batallas *buscarBatalla(int IDBatalla){
    Batallas *temp = primerBatalla;

    if(temp != NULL){
        do {
            if(temp->IDBatalla == IDBatalla)
                return temp;
            temp = temp->sig;
        } while(temp != primerBatalla);
    }
    return NULL;
}


//INSERCIONES

//Insertar al inicio 
void insertarCartas(int IDCarta, string nombre, string rareza, string tipo, int costoElixir, double dañoBase, int vidaBase){
    if (IDCarta < 0 || nombre.empty() || rareza.empty() || tipo.empty() || costoElixir < 0 || dañoBase < 0 || vidaBase < 0) {
        cout << "Error: Datos de la carta no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    // Convertir a minúsculas para comparar
    string rarezaLower = rareza;
    string tipoLower = tipo;
    transform(rarezaLower.begin(), rarezaLower.end(), rarezaLower.begin(), ::tolower);
    transform(tipoLower.begin(), tipoLower.end(), tipoLower.begin(), ::tolower);

    // Validar rareza
    if(rarezaLower != "comun" && rarezaLower != "rara" && rarezaLower != "epica" && rarezaLower != "legendaria"){
        cout << "Error: Rareza no válida. Debe ser Comun, Rara, Epica o Legendaria." << endl;
        return;
    }

    // Validar tipo
    if(tipoLower != "tropa" && tipoLower != "hechizo" && tipoLower != "edificio"){
        cout << "Error: Tipo no válido. Debe ser Tropa, Hechizo o Edificio." << endl;
        return;
    }

    if(buscarCarta(IDCarta) != NULL){
        cout << "Error: Ya existe una carta con ese ID." << endl;
        return;
    }

    Cartas *nuevaCarta = new Cartas(IDCarta, nombre, rareza, tipo, costoElixir, dañoBase, vidaBase);

    nuevaCarta -> sig = primerCarta;
    primerCarta = nuevaCarta;
}

//Insertar por orden alfabetico
//no sabía que condicón poner porque en el documento solo dice por nombre, no dice si al principio o al final 
void insertarJugador(int IDJ, string n, int nr, int t, int IDA, int IDC){
   if (IDJ < 0 || n.empty() || nr < 0 || t < 0 || IDA < 0 || IDC < 0) {
        cout << "Error: Datos del jugador no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    // Validar si el ID del jugador ya existe
    if(buscarJugador(IDJ) != NULL){
        cout << "Error: Ya existe un jugador con el mismo ID. Por favor, intente de nuevo." << endl;
        return;
    }

    //Validar si existe la arena
    if(buscarArena(IDA) == NULL){
        cout << "Error: No existe una arena con ese ID." << endl;
        return;
    }

    //Validar si existe el clan
    if(buscarClan(IDC) == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    //validar los trofeos del jugador con el rango de la arena
    Arenas *arena = buscarArena(IDA);
    if(t < arena->trofeosMin || t > arena->trofeosMax){
        cout << "Error: El número de trofeos no es compatible con la arena seleccionada." << endl;
        return;
    }

    Jugadores *nuevoJugador = new Jugadores(IDJ, n, nr, t, IDA, IDC);

    //si la lista está vacia 
    if(primerJugador == NULL){
        primerJugador = nuevoJugador;
        return;
    }

    //si va antes del primero de la lista
    //según lo que busqué, en C++ se puede comparar strings directamente con los operadores de comparación.
    if(nuevoJugador->nombreUsuario < primerJugador->nombreUsuario){
        nuevoJugador->sig = primerJugador;
        primerJugador->ant = nuevoJugador;
        primerJugador = nuevoJugador;
        return;
    }

    // Buscar la posición correcta
    Jugadores *actual = primerJugador;
    while(actual->sig != NULL && actual->sig->nombreUsuario < nuevoJugador->nombreUsuario){
        actual = actual->sig;
    }

    //inserta en el medio o al final
    nuevoJugador->sig = actual->sig;
    nuevoJugador->ant = actual;
    if(actual->sig != NULL){
        actual->sig->ant = nuevoJugador;
    }
    actual->sig = nuevoJugador;
}

//Insertar al final
void insertarMazo(int IDM, string nm, string tm, int IDJ){
    if (IDM < 0 || nm.empty() || tm.empty() || IDJ < 0) {
        cout << "Error: Datos del mazo no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    if(buscarMazo(IDM) != NULL){
        cout << "Error: Ya existe un mazo con el mismo ID. Por favor, intente de nuevo." << endl;
        return;
    }

    //Validar si el jugador existe
    if(buscarJugador(IDJ) == NULL){
        cout << "Error: No existe un jugador con ese ID." << endl;
        return;
    }

    Mazos *nuevoMazo = new Mazos(IDM, nm, tm, IDJ);

    if(primerMazo == NULL){
        primerMazo = nuevoMazo;
        return;
    }

    Mazos *temp = primerMazo;

    while(temp -> sig != NULL){
        temp = temp -> sig;
    }
    temp -> sig = nuevoMazo;
}

//Insertar al final
void insertarClan(int idclan, string nclan, string reg, int cantmiembros, double puntaje){
    //valida los datos de entrada
    if (idclan < 0 || nclan.empty() || reg.empty() || cantmiembros < 0 || puntaje < 0) {
        cout << "Error: Datos del clan no válidos. Por favor, intente de nuevo." << endl;
        return;
    }
    // Validar si el ID del clan ya existe
    if (buscarClan(idclan) != NULL) {
        cout << "Error: Ya existe un clan con el mismo ID. Por favor, intente de nuevo." << endl;
        return;
    }

    Clanes *nuevoClan = new Clanes(idclan, nclan, reg, cantmiembros, puntaje);

    //si la lista está vacia
    if(primerClan == NULL){
        primerClan = nuevoClan;
        nuevoClan->sig = primerClan; // Apunta a sí mismo para formar la lista circular
        return;
    }

    Clanes *temp = primerClan;
    while(temp->sig != primerClan){
        temp = temp->sig;
    }
    temp->sig = nuevoClan;
    nuevoClan->sig = primerClan; // Cierra el ciclo
}

//Insertar al inicio
void insertarArena(int IDA, string nA, int tmin, int tmax){
    //valida los datos de entrada
    if (IDA < 0 || nA.empty() || tmin < 0 || tmax < 0) {
        cout << "Error: Datos de la arena no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    // Validar si el ID de la arena ya existe
    if (buscarArena(IDA) != NULL) {
        cout << "Error: Ya existe una arena con el mismo ID. Por favor, intente de nuevo." << endl;
        return;
    }

    // Validar que el número mínimo de trofeos no sea mayor que el máximo
    if (tmin > tmax) {
        cout << "Error: El número mínimo de trofeos no puede ser mayor que el máximo." << endl;
        return;
    }

    Arenas *nuevaArena = new Arenas(IDA, nA, tmin, tmax);
    //si la lista está vacia
    if(primerArena == NULL){
        primerArena = nuevaArena;
        return;
    }

    nuevaArena -> sig = primerArena;
    primerArena = nuevaArena;
}

//Insertar al final
void insertarBatalla(int IDB, int IDJ1, int IDJ2, int IDM1, int IDM2, string g, int cJ1, int cJ2, float d, int IDA, string f){
    //valida los datos de entrada
    if (IDB < 0 || IDJ1 < 0 || IDJ2 < 0 || IDM1 < 0 || IDM2 < 0 || g.empty() || cJ1 < 0 || cJ2 < 0 || d < 0 || IDA < 0 || f.empty()) {
        cout << "Error: Datos de la batalla no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    // Validar si el ID de la batalla ya existe
    if (buscarBatalla(IDB) != NULL) {
        cout << "Error: Ya existe una batalla con el mismo ID. Por favor, intente de nuevo." << endl;
        return;
    }
    
    //Validar si los jugadores existen
    if(buscarJugador(IDJ1) == NULL || buscarJugador(IDJ2) == NULL){
        cout << "Error: Uno o ambos jugadores no existen." << endl;
        return;
    }

    //Validar si la arena existe
    if(buscarArena(IDA) == NULL){
        cout << "Error: No existe una arena con ese ID." << endl;
        return;
    }

    //Validar que los mazos existan y que corresponadn a los jugadores
    Mazos *mazo1 = buscarMazo(IDM1);
    Mazos *mazo2 = buscarMazo(IDM2);
    if(mazo1 == NULL || mazo2 == NULL){
        cout << "Error: Uno o ambos mazos no existen." << endl;
        return;
    }

    //Validar que los mazos correspondan a los jugadores
    if(mazo1->IDJugador != IDJ1 || mazo2->IDJugador != IDJ2){
        cout << "Error: Uno o ambos mazos no pertenecen a los jugadores indicados." << endl;
        return;
    }

    //Validar que los mazos tengan 8 cartas
    if(mazo1->cantidadCartas != 8 || mazo2->cantidadCartas != 8){
        cout << "Error: Ambos mazos deben tener exactamente 8 cartas." << endl;
        return;
    }

    //Validar que el ganador sea uno de los jugadores
    Jugadores *j1 = buscarJugador(IDJ1);
    Jugadores *j2 = buscarJugador(IDJ2);
    if(g != j1->nombreUsuario && g != j2->nombreUsuario){
        cout << "Error: El ganador debe ser uno de los jugadores indicados." << endl;
        return;
    }

    //Validar que el número de coronas sea entre 0 y 3, y que no puedan ser ambos 0
    if(cJ1 < 0 || cJ2 < 0 || cJ1 > 3 || cJ2 > 3 || (cJ1 == 0 && cJ2 == 0)){
        cout << "Error: El número de coronas debe ser entre 0 y 3, y no pueden ser ambos 0." << endl;
        return;
    }

    Batallas *nuevaBatalla = new Batallas(IDB, IDJ1, IDJ2, IDM1, IDM2, g, cJ1, cJ2, d, IDA, f);

    //si la lista está vacia
    if(primerBatalla == NULL){
        primerBatalla = nuevaBatalla;
        return;
    }

    Batallas *temp = primerBatalla;
    while(temp -> sig != primerBatalla){
        temp = temp -> sig;
    }
    temp -> sig = nuevaBatalla;
    nuevaBatalla -> ant = temp; // Establece el enlace hacia atrás
    nuevaBatalla->sig = primerBatalla;
    primerBatalla->ant = nuevaBatalla; // Cierra el ciclo
}


//INSERCIONES EN SUBLISTAS
void insertarCartaEnMazo(int IDMazo, int IDCarta){
    // Verificar que el mazo existe
    Mazos *mazo = buscarMazo(IDMazo);
    if(mazo == NULL){
        cout << "Error: No existe un mazo con ese ID." << endl;
        return;
    }

    // Verificar que la carta existe en el sistema
    if(buscarCarta(IDCarta) == NULL){
        cout << "Error: No existe una carta con ese ID." << endl;
        return;
    }

    // Verificar que el mazo no tenga ya 8 cartas
    if(mazo->cantidadCartas >= 8){
        cout << "Error: El mazo ya tiene 8 cartas." << endl;
        return;
    }

    // Verificar que la carta no esté ya en el mazo
    NodoCartaMazo *temp = mazo->listaCartas;
    while(temp != NULL){
        if(temp->IDCarta == IDCarta){
            cout << "Error: Esa carta ya está en el mazo." << endl;
            return;
        }
        temp = temp->sig;
    }

    // Insertar la carta al final de la sublista
    NodoCartaMazo *nuevaCarta = new NodoCartaMazo(IDCarta);
    if(mazo->listaCartas == NULL){
        mazo->listaCartas = nuevaCarta;
    } else {
        NodoCartaMazo *ultimo = mazo->listaCartas;
        while(ultimo->sig != NULL){
            ultimo = ultimo->sig;
        }
        ultimo->sig = nuevaCarta;
    }
    mazo->cantidadCartas++;
}


void insertarJugadorEnClan(int IDClan, int IDJugador){
    // Verificar que el clan existe
    Clanes *clan = buscarClan(IDClan);
    if(clan == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    // Verificar que el jugador existe
    if(buscarJugador(IDJugador) == NULL){
        cout << "Error: No existe un jugador con ese ID." << endl;
        return;
    }

    // Verificar que el jugador no esté ya en el clan
    NodoJugadorClan *temp = clan->listaJugadores;
    while(temp != NULL){
        if(temp->IDJugador == IDJugador){
            cout << "Error: Ese jugador ya está en el clan." << endl;
            return;
        }
        temp = temp->sig;
    }

    // Insertar el jugador al final de la sublista
    NodoJugadorClan *nuevoJugador = new NodoJugadorClan(IDJugador);
    if(clan->listaJugadores == NULL){
        clan->listaJugadores = nuevoJugador;
    } else {
        NodoJugadorClan *ultimo = clan->listaJugadores;
        while(ultimo->sig != NULL){
            ultimo = ultimo->sig;
        }
        ultimo->sig = nuevoJugador;
    }
    clan->cantidadMiembros++;
}


//MODIFICACIONES
void modificarCarta(int IDCarta){
    // Buscar la carta
    Cartas *temp = buscarCarta(IDCarta);

    // Si no existe
    if(temp == NULL){
        cout << "Error: No existe una carta con ese ID." << endl;
        return;
    }

    // Pedir todos los nuevos valores
    string nuevoNombre, nuevaRareza, nuevoTipo;
    int nuevoCosto, nuevaVida;
    double nuevoDaño;

    cout << "Nuevo nombre: ";
    cin >> nuevoNombre;
    cin .ignore();
    cout << "Nueva rareza: ";
    cin >> nuevaRareza;
    cin .ignore();
    cout << "Nuevo tipo: ";
    cin >> nuevoTipo;
    cin .ignore(); 
    cout << "Nuevo costo de elixir: ";
    cin >> nuevoCosto;
    cout << "Nuevo daño base: ";
    cin >> nuevoDaño;
    cout << "Nueva vida base: ";
    cin >> nuevaVida;

    // Validar que no haya valores negativos
    if(nuevoCosto < 0 || nuevoDaño < 0 || nuevaVida < 0){
        cout << "Error: No se permiten valores negativos." << endl;
        return;
    }

    // Convertir a minúsculas para comparar
    string rarezaLower = nuevaRareza;
    string tipoLower = nuevoTipo;
    transform(rarezaLower.begin(), rarezaLower.end(), rarezaLower.begin(), ::tolower);
    transform(tipoLower.begin(), tipoLower.end(), tipoLower.begin(), ::tolower);

    // Validar rareza
    if(rarezaLower != "comun" && rarezaLower != "rara" && rarezaLower != "epica" && rarezaLower != "legendaria"){
        cout << "Error: Rareza no válida. Debe ser Comun, Rara, Epica o Legendaria." << endl;
        return;
    }

    // Validar tipo
    if(tipoLower != "tropa" && tipoLower != "hechizo" && tipoLower != "edificio"){
        cout << "Error: Tipo no válido. Debe ser Tropa, Hechizo o Edificio." << endl;
        return;
    }

    // Asignar todo de una vez
    temp->Nombre = nuevoNombre;
    temp->Rareza = nuevaRareza;
    temp->Tipo = nuevoTipo;
    temp->costoElixir = nuevoCosto;
    temp->dañoBase = nuevoDaño;
    temp->vidaBase = nuevaVida;

    cout << "Carta actualizada correctamente." << endl;
}

void modificarJugador(int IDJ){
    // Buscar el jugador
    Jugadores *temp = buscarJugador(IDJ);

    // Si no existe
    if(temp == NULL){
        cout << "Error: No existe un jugador con ese ID." << endl;
        return;
    }

    // Pedir todos los nuevos valores
    string nuevoNombre;
    int nuevoNivelRey, nuevosTrofeos, nuevoIDArena, nuevoIDClan;

    cout << "Nuevo nombre de usuario: ";
    cin >> nuevoNombre;
    cin .ignore(); // Limpiar el buffer para permitir espacios en el nombre de usuario
    cout << "Nuevo nivel del rey: ";
    cin >> nuevoNivelRey;
    cout << "Nuevos trofeos: ";
    cin >> nuevosTrofeos;
    cout << "Nuevo ID de arena: ";
    cin >> nuevoIDArena;
    cout << "Nuevo ID de clan: ";
    cin >> nuevoIDClan;

    // Validar que no haya valores negativos
    if(nuevoNivelRey < 0 || nuevosTrofeos < 0 || nuevoIDArena < 0 || nuevoIDClan < 0){
        cout << "Error: No se permiten valores negativos." << endl;
        return;
    }

    // Validar que la arena exista
    if(buscarArena(nuevoIDArena) == NULL){
        cout << "Error: No existe una arena con ese ID." << endl;
        return;
    }

    // Validar que el clan exista
    if(buscarClan(nuevoIDClan) == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    //validar los trofeos del jugador con el rango de la arena
    Arenas *arena = buscarArena(nuevoIDArena);
    if(nuevosTrofeos < arena->trofeosMin || nuevosTrofeos > arena->trofeosMax){
        cout << "Error: El número de trofeos no es compatible con la nueva arena." << endl;
        return;
    }

    // Asignar todo de una vez
    temp->nombreUsuario = nuevoNombre;
    temp->nivelRey = nuevoNivelRey;
    temp->trofeos = nuevosTrofeos;
    temp->IDArena = nuevoIDArena;
    temp->IDClan = nuevoIDClan;

    cout << "Jugador actualizado correctamente." << endl;
}