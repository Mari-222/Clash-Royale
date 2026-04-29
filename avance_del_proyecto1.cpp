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
    // Validar que los datos de la carta sean válidos.
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

    // Validar que no exista una carta con el mismo ID
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
    // Validar que los datos del jugador sean válidos
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

    //si la lita está vacia 
    if(primerJugador == NULL){
        primerJugador = nuevoJugador;
        return;
    }

    //si va antes del primero de la lista
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
    // Validar que los datos del mazo sean válidos
    if (IDM < 0 || nm.empty() || tm.empty() || IDJ < 0) {
        cout << "Error: Datos del mazo no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    // Validar si el ID del mazo ya existe
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

    //si la lista está vacia
    if(primerMazo == NULL){
        primerMazo = nuevoMazo;
        return;
    }

    Mazos *temp = primerMazo;

    //recorre hasta el final de la lista
    while(temp -> sig != NULL){
        temp = temp -> sig;
    }
    temp -> sig = nuevoMazo;
}

//Insertar al final
void insertarClan(int idclan, string nclan, string reg, int cantmiembros, double puntaje){
    // Validar que los datos del clan sean válidos
    if (idclan < 0 || nclan.empty() || reg.empty() || cantmiembros < 0 || puntaje < 0) {
        cout << "Error: Datos del clan no válidos. Por favor, intente de nuevo." << endl;
        return;
    }
    
    //validar que le ID del clan no exista 
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
    //Validar que los datos insertados sena validos 
    if (IDA < 0 || nA.empty() || tmin < 0 || tmax < 0) {
        cout << "Error: Datos de la arena no válidos. Por favor, intente de nuevo." << endl;
        return;
    }
    // Validar que no exista una arena con el mismo ID
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
    // Validar que los datos de la batalla sean válidos
    if (IDB < 0 || IDJ1 < 0 || IDJ2 < 0 || IDM1 < 0 || IDM2 < 0 || g.empty() || cJ1 < 0 || cJ2 < 0 || d < 0 || IDA < 0 || f.empty()) {
        cout << "Error: Datos de la batalla no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    //validar que no exista una batalla con el mismo ID
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
    //Validar que los mazos tengan exactamente 8 cartas
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
        nuevaBatalla->sig = primerBatalla; // lo cambié porque en listas circulares el primer nodo debe apuntar a sí mismo
        nuevaBatalla->ant = primerBatalla; 
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

    // Validar
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
    cin .ignore(); 
    cout << "Nuevo nivel del rey: ";
    cin >> nuevoNivelRey;
    cout << "Nuevos trofeos: ";
    cin >> nuevosTrofeos;
    cout << "Nuevo ID de arena: ";
    cin >> nuevoIDArena;
    cout << "Nuevo ID de clan: ";
    cin >> nuevoIDClan;

    // Validar
    if(nuevoNivelRey < 0 || nuevosTrofeos < 0 || nuevoIDArena < 0 || nuevoIDClan < 0){
        cout << "Error: No se permiten valores negativos." << endl;
        return;
    }

    // Validar que la arena el clan existan
    if(buscarArena(nuevoIDArena) == NULL){
        cout << "Error: No existe una arena con ese ID." << endl;
        return;
    }
    // Validar que la arena el clan existan
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

void modificarMazo(int IDM){
    // Buscar el mazo
    Mazos *temp = buscarMazo(IDM);

    // Si no existe
    if(temp == NULL){
        cout << "Error: No existe un mazo con ese ID." << endl;
        return;
    }

    // Pedir todos los nuevos valores
    string nuevoNombreMazo, nuevoTipoMazo;

    cout << "Nuevo nombre del mazo: ";
    cin >> nuevoNombreMazo;
    cin .ignore(); 
    cout << "Nuevo tipo de mazo: ";
    cin >> nuevoTipoMazo;
    cin .ignore(); 

    // Asignar todo de una vez
    temp->nombreMazo = nuevoNombreMazo;
    temp->tipoMazo = nuevoTipoMazo;

    // Preguntar si también quiere modificar una carta
    char respuesta;
    cout << "¿Desea reemplazar alguna carta del mazo? (s/n): ";
    cin >> respuesta;

    if(respuesta == 's' || respuesta == 'S'){
        int IDCartaVieja, IDCartaNueva;

        cout << "ID de la carta a reemplazar: ";
        cin >> IDCartaVieja;

        // Buscar la carta en la sublista
        NodoCartaMazo *tempCarta = temp->listaCartas;
        while(tempCarta != NULL){
            if(tempCarta->IDCarta == IDCartaVieja) break;
            tempCarta = tempCarta->sig;
        }

        // Si no se encuentra la carta a reemplazar
        if(tempCarta == NULL){
            cout << "Error: Esa carta no está en el mazo." << endl;
        } else {
            cout << "ID de la nueva carta: ";
            cin >> IDCartaNueva;

            // Validar que exista en el sistema
            Cartas *cartaGlobal = primerCarta;
            while(cartaGlobal != NULL){
                if(cartaGlobal->IDCarta == IDCartaNueva) break;
                cartaGlobal = cartaGlobal->sig;
            }

            if(cartaGlobal == NULL){
                cout << "Error: No existe esa carta en el sistema." << endl;
            } else {
                // Validar que no esté ya en el mazo
                NodoCartaMazo *verificar = temp->listaCartas;
                bool repetida = false;
                while(verificar != NULL){
                    if(verificar->IDCarta == IDCartaNueva){
                        repetida = true;
                        break;
                    }
                    verificar = verificar->sig;
                }

                if(repetida){
                    cout << "Error: Esa carta ya está en el mazo." << endl;
                } else {
                    tempCarta->IDCarta = IDCartaNueva;
                    cout << "Carta reemplazada correctamente." << endl;
                    }
                }
            }
        }
    cout << "Mazo actualizado correctamente." << endl;
}

void modificarClan(int IDClan){
    // Buscar el clan
    Clanes *temp = buscarClan(IDClan);

    // Si no existe
    if(temp == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    // Pedir todos los nuevos valores
    string nuevoNombreClan, nuevaRegion;
    double nuevoPuntaje;

    cout << "Nuevo nombre del clan: ";
    cin >> nuevoNombreClan;
    cin.ignore();
    cout << "Nueva región: ";
    cin >> nuevaRegion;
    cin.ignore();
    cout << "Nuevo puntaje del clan: ";
    cin >> nuevoPuntaje;

    // Validación básica
    if(nuevoPuntaje < 0){
        cout << "Error: No se permiten valores negativos." << endl;
        return;
    }

    // Asignar
    temp->nombreClan = nuevoNombreClan;
    temp->region = nuevaRegion;
    temp->puntajeClan = nuevoPuntaje;

    // Preguntar si también quiere modificar un jugador del clan
    char respuesta;
    cout << "¿Desea reemplazar algún jugador del clan? (s/n): ";
    cin >> respuesta;

    if(respuesta == 's' || respuesta == 'S'){
        int IDJugadorViejo, IDJugadorNuevo;

        cout << "ID del jugador a reemplazar: ";
        cin >> IDJugadorViejo;

        // Buscar el jugador en la sublista
        NodoJugadorClan *tempJugador = temp->listaJugadores;
        while(tempJugador != NULL){
            if(tempJugador->IDJugador == IDJugadorViejo) break;
            tempJugador = tempJugador->sig;
        }

        if(tempJugador == NULL){
            cout << "Error: Ese jugador no está en el clan." << endl;
        } else {
            cout << "ID del nuevo jugador: ";
            cin >> IDJugadorNuevo;

            // Validar que exista en el sistema
            if(buscarJugador(IDJugadorNuevo) == NULL){
                cout << "Error: No existe ese jugador en el sistema." << endl;
            } else {
                // Validar que no esté ya en el clan
                NodoJugadorClan *verificar = temp->listaJugadores;
                bool repetido = false;
                while(verificar != NULL){
                    if(verificar->IDJugador == IDJugadorNuevo){
                        repetido = true;
                        break;
                    }
                    verificar = verificar->sig;
                }

                if(repetido){
                    cout << "Error: Ese jugador ya está en el clan." << endl;
                } else {
                    tempJugador->IDJugador = IDJugadorNuevo;
                    cout << "Jugador reemplazado correctamente." << endl;
                }
            }
        }
    }
    cout << "Clan actualizado correctamente." << endl;
}


void modificarArena(int IDA){
    // Buscar la arena
    Arenas *temp = buscarArena(IDA);

    // Si no existe
    if(temp == NULL){
        cout << "Error: No existe una arena con ese ID." << endl;
        return;
    }

    // Pedir todos los nuevos valores
    string nuevoNombreArena;
    int nuevoTrofeosMin, nuevoTrofeosMax;

    cout << "Nuevo nombre de la arena: ";
    cin >> nuevoNombreArena;
    cin.ignore();
    cout << "Nuevo rango mínimo de trofeos: ";
    cin >> nuevoTrofeosMin;
    cout << "Nuevo rango máximo de trofeos: ";
    cin >> nuevoTrofeosMax;

    // Validacioenes básicas
    if(nuevoTrofeosMin < 0 || nuevoTrofeosMax < 0){
        cout << "Error: No se permiten valores negativos." << endl;
        return;
    }
    // Validar que el número mínimo de trofeos no sea mayor que el máximo
    if(nuevoTrofeosMin > nuevoTrofeosMax){
        cout << "Error: El número mínimo de trofeos no puede ser mayor que el máximo." << endl;
        return;
    }

    // Asignar todo de una vez
    temp->nombreArena = nuevoNombreArena;
    temp->trofeosMin = nuevoTrofeosMin;
    temp->trofeosMax = nuevoTrofeosMax;

    cout << "Arena actualizada correctamente." << endl;
}

void eliminarCarta(int IDCarta){
    // Buscar la carta
    Cartas *temp = primerCarta;
    Cartas *tempAnt = NULL;

    while(temp != NULL){
        if(temp -> IDCarta == IDCarta){
            // Si es el primero de la lista
            if(tempAnt == NULL){
                primerCarta = temp -> sig;
            } else {
                tempAnt -> sig = temp -> sig;
            }
            delete temp;
            cout << "Carta eliminada correctamente." << endl;
            return;
        }
        tempAnt = temp;
        temp = temp -> sig;
    }
    cout << "Error: No se encontró una carta con ese ID." << endl;
}

void eliminarJugador(int IDJ){
    Jugadores *temp = buscarJugador(IDJ);
    // Si no se encuentra el jugador
    if(temp == NULL){
        cout << "Error: No se encontró un jugador con ese ID." << endl;
        return;
    }
    // Ajustar los enlaces de la lista doblemente enlazada
    if(temp->ant != NULL) temp->ant->sig = temp->sig;
    else                  primerJugador = temp->sig;

    if(temp->sig != NULL) temp->sig->ant = temp->ant;

    delete temp;
    cout << "Jugador eliminado correctamente." << endl;
}


void eliminarMazo(int IDM){
    Mazos *temp = primerMazo;
    Mazos *tempAnt = NULL;
    // Buscar el mazo 
    while(temp != NULL){
        if(temp->IDMazo == IDM){
            if(tempAnt == NULL){
                primerMazo = temp->sig;
            } else {
                tempAnt->sig = temp->sig;
            }

            // Liberar sublista de cartas antes de eliminar el mazo
            NodoCartaMazo *carta = temp->listaCartas;
            while(carta != NULL){
                NodoCartaMazo *cartaTemp = carta;
                carta = carta->sig;
                delete cartaTemp;
            }

            delete temp;
            cout << "Mazo eliminado correctamente." << endl;
            return;
        }
        tempAnt = temp;
        temp = temp->sig;
    }
    cout << "Error: No se encontró un mazo con ese ID." << endl;
}

void eliminarClan(int IDClan){
    Clanes *temp = buscarClan(IDClan);

    if(temp == NULL){
        cout << "Error: No se encontró un clan con ese ID." << endl;
        return;
    }

    // Si es el único nodo en la lista
    if(temp->sig == temp){
        primerClan = NULL;
    } 
    
    else {
        // Buscar el nodo anterior para ajustar el enlace circular
        Clanes *tempAnt = temp;
        while(tempAnt->sig != temp){
            tempAnt = tempAnt->sig;
        }
        tempAnt->sig = temp->sig;

        // Si el nodo a eliminar es el primer nodo, actualizar el puntero
        if(temp == primerClan){
            primerClan = temp->sig;
        }
    }

    // Liberar sublista de jugadores antes de eliminar el clan
    NodoJugadorClan *jugador = temp->listaJugadores;
    while(jugador != NULL){
        NodoJugadorClan *jugadorTemp = jugador;
        jugador = jugador->sig;
        delete jugadorTemp;
    }

    delete temp;
    cout << "Clan eliminado correctamente." << endl;
}

void eliminarArena(int IDA){
    Arenas *temp = primerArena;
    Arenas *tempAnt = NULL;
    // Buscar la arena
    while(temp != NULL){
        // Si se encuentra la arena a eliminar
        if(temp->IDArena == IDA){
            if(tempAnt == NULL){
                primerArena = temp->sig;
            } else {
                tempAnt->sig = temp->sig;
            }
            delete temp;
            cout << "Arena eliminada correctamente." << endl;
            return;
        }
        tempAnt = temp;
        temp = temp->sig;
    }
    cout << "Error: No se encontró una arena con ese ID." << endl;
}

void eliminarBatalla(int IDB){
    Batallas *temp = buscarBatalla(IDB);

    if(temp == NULL){
        cout << "Error: No se encontró una batalla con ese ID." << endl;
        return;
    }

    // Si es el único nodo
    if(temp->sig == temp){
        primerBatalla = NULL;
    } else {
        temp->ant->sig = temp->sig;
        temp->sig->ant = temp->ant;

        // Si era el primero, actualizar primerBatalla
        if(temp == primerBatalla){
            primerBatalla = temp->sig;
        }
    }

    delete temp;
    cout << "Batalla eliminada correctamente." << endl;
}

//ELIMINACIÓN DE SUBLISTAS
void eliminarCartaDeMazo(int IDMazo, int IDCarta){
    Mazos *mazo = buscarMazo(IDMazo);
    if(mazo == NULL){
        cout << "Error: No existe un mazo con ese ID." << endl;
        return;
    }

    NodoCartaMazo *temp = mazo->listaCartas;
    NodoCartaMazo *tempAnt = NULL;

    // Buscar la carta en la sublista
    while(temp != NULL){
        if(temp->IDCarta == IDCarta){
            if(tempAnt == NULL){
                mazo->listaCartas = temp->sig;
            } else {
                tempAnt->sig = temp->sig;
            }
            delete temp;
            mazo->cantidadCartas--; // Disminuir el contador de cartas en el mazo
            cout << "Carta eliminada del mazo correctamente." << endl;
            return;
        }
        tempAnt = temp;
        temp = temp->sig;
    }
    cout << "Error: No se encontró una carta con ese ID en el mazo." << endl;
}

void eliminarJugadorDeClan(int IDClan, int IDJugador){
    Clanes *clan = buscarClan(IDClan);
    if(clan == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    NodoJugadorClan *temp = clan->listaJugadores;
    NodoJugadorClan *tempAnt = NULL;

    // Buscar el jugador en la sublista
    while(temp != NULL){
        if(temp->IDJugador == IDJugador){
            if(tempAnt == NULL){
                clan->listaJugadores = temp->sig;
            } else {
                tempAnt->sig = temp->sig;
            }
            delete temp;
            clan->cantidadMiembros--; // Disminuir el contador de miembros en el clan
            cout << "Jugador eliminado del clan correctamente." << endl;
            return;
        }
        tempAnt = temp;
        temp = temp->sig;
    }
    cout << "Error: No se encontró un jugador con ese ID en el clan." << endl;
}

//CARGAR DATOS
void cargarDatos(){
    // ===== ARENAS (primero porque jugadores dependen de ellas) =====
    insertarArena(1, "Terreno de Entrenamiento", 0, 299);
    insertarArena(2, "Estadio de Duendes", 300, 599);
    insertarArena(3, "Aldea Barbara", 600, 999);
    insertarArena(4, "Cueva de Hielo", 1000, 1299);
    insertarArena(5, "Torre de Hechizos", 1300, 1599);
    insertarArena(6, "Guarida del Cerdo", 1600, 1999);
    insertarArena(7, "Constructor Real", 2000, 2299);
    insertarArena(8, "Arena Legendaria", 2300, 2599);
    insertarArena(9, "Liga de Plata", 2600, 2999);
    insertarArena(10, "Liga de Oro", 3000, 9999);

    // ===== CARTAS (segundo porque mazos dependen de ellas) =====
    insertarCartas(1, "Caballero", "Comun", "Tropa", 3, 75.0, 1400);
    insertarCartas(2, "Bola de Fuego", "Rara", "Hechizo", 4, 330.0, 0);
    insertarCartas(3, "Arqueras", "Comun", "Tropa", 3, 60.0, 500);
    insertarCartas(4, "Gigante", "Rara", "Tropa", 5, 95.0, 3000);
    insertarCartas(5, "Principe", "Epica", "Tropa", 5, 320.0, 1920);
    insertarCartas(6, "Bruja", "Epica", "Tropa", 5, 100.0, 1000);
    insertarCartas(7, "Esqueletos", "Comun", "Tropa", 1, 45.0, 150);
    insertarCartas(8, "Rayo", "Rara", "Hechizo", 6, 880.0, 0);
    insertarCartas(9, "Pekka", "Epica", "Tropa", 7, 450.0, 3300);
    insertarCartas(10, "Dragon Infernal", "Legendaria", "Tropa", 4, 160.0, 1600);
    insertarCartas(11, "Mosquetero", "Rara", "Tropa", 4, 120.0, 1100);
    insertarCartas(12, "Minipekka", "Rara", "Tropa", 4, 325.0, 1000);
    insertarCartas(13, "Globo", "Epica", "Tropa", 5, 250.0, 1400);
    insertarCartas(14, "Tornado", "Epica", "Hechizo", 3, 0.0, 0);
    insertarCartas(15, "Golem", "Legendaria", "Tropa", 8, 180.0, 4200);
    insertarCartas(16, "Leñador", "Legendaria", "Tropa", 4, 190.0, 1300);

    // ===== CLANES (tercero porque jugadores dependen de ellos) =====
    insertarClan(1, "Dragones del Norte", "America", 0, 5000.0);
    insertarClan(2, "Guerreros del Sur", "America", 0, 4500.0);
    insertarClan(3, "Legion Dorada", "Europa", 0, 6000.0);
    insertarClan(4, "Furia Barbara", "Europa", 0, 3800.0);
    insertarClan(5, "Sombras Eternas", "Asia", 0, 7000.0);
    insertarClan(6, "Reyes del Caos", "Asia", 0, 5500.0);
    insertarClan(7, "Caballeros Reales", "America", 0, 4200.0);
    insertarClan(8, "Tormenta Arcana", "Europa", 0, 6500.0);
    insertarClan(9, "Guardianes del Hielo", "Asia", 0, 3500.0);
    insertarClan(10, "Alianza Suprema", "America", 0, 8000.0);

    // ===== JUGADORES (cuarto porque mazos dependen de ellos) =====
    // Trofeos deben corresponder al rango de la arena asignada
    insertarJugador(1, "Alejandro", 10, 2400, 8, 3);  // Arena 8: 2300-2599
    insertarJugador(2, "Beatriz", 8, 1700, 6, 1);     // Arena 6: 1600-1999
    insertarJugador(3, "Carlos", 12, 3100, 10, 5);    // Arena 10: 3000-9999
    insertarJugador(4, "Diana", 9, 2100, 7, 2);       // Arena 7: 2000-2299
    insertarJugador(5, "Eduardo", 11, 2800, 9, 4);    // Arena 9: 2600-2999
    insertarJugador(6, "Fernanda", 7, 1400, 5, 6);    // Arena 5: 1300-1599
    insertarJugador(7, "Gabriel", 13, 3500, 10, 5);   // Arena 10: 3000-9999
    insertarJugador(8, "Helena", 6, 900, 3, 7);       // Arena 3: 600-999
    insertarJugador(9, "Ivan", 10, 2300, 8, 8);       // Arena 8: 2300-2599
    insertarJugador(10, "Julia", 8, 1600, 6, 9);      // Arena 6: 1600-1999

    // ===== ASIGNAR JUGADORES A CLANES =====
    insertarJugadorEnClan(3, 1);  // Alejandro -> Legion Dorada
    insertarJugadorEnClan(1, 2);  // Beatriz -> Dragones del Norte
    insertarJugadorEnClan(5, 3);  // Carlos -> Sombras Eternas
    insertarJugadorEnClan(2, 4);  // Diana -> Guerreros del Sur
    insertarJugadorEnClan(4, 5);  // Eduardo -> Furia Barbara
    insertarJugadorEnClan(6, 6);  // Fernanda -> Reyes del Caos
    insertarJugadorEnClan(5, 7);  // Gabriel -> Sombras Eternas
    insertarJugadorEnClan(7, 8);  // Helena -> Caballeros Reales
    insertarJugadorEnClan(8, 9);  // Ivan -> Tormenta Arcana
    insertarJugadorEnClan(9, 10); // Julia -> Guardianes del Hielo

    // ===== MAZOS (quinto porque batallas dependen de ellos) =====
    insertarMazo(1, "Mazo Gigante", "Asalto", 1);
    insertarCartaEnMazo(1, 4);
    insertarCartaEnMazo(1, 1);
    insertarCartaEnMazo(1, 3);
    insertarCartaEnMazo(1, 2);
    insertarCartaEnMazo(1, 7);
    insertarCartaEnMazo(1, 11);
    insertarCartaEnMazo(1, 8);
    insertarCartaEnMazo(1, 14);

    insertarMazo(2, "Mazo Pekka", "Control", 2);
    insertarCartaEnMazo(2, 9);
    insertarCartaEnMazo(2, 12);
    insertarCartaEnMazo(2, 2);
    insertarCartaEnMazo(2, 3);
    insertarCartaEnMazo(2, 7);
    insertarCartaEnMazo(2, 1);
    insertarCartaEnMazo(2, 8);
    insertarCartaEnMazo(2, 14);

    insertarMazo(3, "Mazo Golem", "Ataque", 3);
    insertarCartaEnMazo(3, 15);
    insertarCartaEnMazo(3, 10);
    insertarCartaEnMazo(3, 6);
    insertarCartaEnMazo(3, 2);
    insertarCartaEnMazo(3, 3);
    insertarCartaEnMazo(3, 7);
    insertarCartaEnMazo(3, 14);
    insertarCartaEnMazo(3, 16);

    insertarMazo(4, "Mazo Principe", "Agresivo", 4);
    insertarCartaEnMazo(4, 5);
    insertarCartaEnMazo(4, 1);
    insertarCartaEnMazo(4, 3);
    insertarCartaEnMazo(4, 2);
    insertarCartaEnMazo(4, 7);
    insertarCartaEnMazo(4, 11);
    insertarCartaEnMazo(4, 8);
    insertarCartaEnMazo(4, 14);

    insertarMazo(5, "Mazo Globo", "Ciclo", 5);
    insertarCartaEnMazo(5, 13);
    insertarCartaEnMazo(5, 1);
    insertarCartaEnMazo(5, 7);
    insertarCartaEnMazo(5, 2);
    insertarCartaEnMazo(5, 3);
    insertarCartaEnMazo(5, 11);
    insertarCartaEnMazo(5, 8);
    insertarCartaEnMazo(5, 14);

    insertarMazo(6, "Mazo Bruja", "Defensa", 6);
    insertarCartaEnMazo(6, 6);
    insertarCartaEnMazo(6, 1);
    insertarCartaEnMazo(6, 3);
    insertarCartaEnMazo(6, 2);
    insertarCartaEnMazo(6, 7);
    insertarCartaEnMazo(6, 11);
    insertarCartaEnMazo(6, 8);
    insertarCartaEnMazo(6, 14);

    insertarMazo(7, "Mazo Dragon", "Mixto", 7);
    insertarCartaEnMazo(7, 10);
    insertarCartaEnMazo(7, 1);
    insertarCartaEnMazo(7, 3);
    insertarCartaEnMazo(7, 2);
    insertarCartaEnMazo(7, 7);
    insertarCartaEnMazo(7, 11);
    insertarCartaEnMazo(7, 8);
    insertarCartaEnMazo(7, 14);

    insertarMazo(8, "Mazo Rayo", "Control", 8);
    insertarCartaEnMazo(8, 8);
    insertarCartaEnMazo(8, 1);
    insertarCartaEnMazo(8, 3);
    insertarCartaEnMazo(8, 2);
    insertarCartaEnMazo(8, 7);
    insertarCartaEnMazo(8, 11);
    insertarCartaEnMazo(8, 4);
    insertarCartaEnMazo(8, 14);

    insertarMazo(9, "Mazo Leñador", "Agresivo", 9);
    insertarCartaEnMazo(9, 16);
    insertarCartaEnMazo(9, 1);
    insertarCartaEnMazo(9, 3);
    insertarCartaEnMazo(9, 2);
    insertarCartaEnMazo(9, 7);
    insertarCartaEnMazo(9, 11);
    insertarCartaEnMazo(9, 8);
    insertarCartaEnMazo(9, 14);

    insertarMazo(10, "Mazo Esqueletos", "Ciclo", 10);
    insertarCartaEnMazo(10, 7);
    insertarCartaEnMazo(10, 1);
    insertarCartaEnMazo(10, 3);
    insertarCartaEnMazo(10, 2);
    insertarCartaEnMazo(10, 5);
    insertarCartaEnMazo(10, 11);
    insertarCartaEnMazo(10, 8);
    insertarCartaEnMazo(10, 14);

    // ===== BATALLAS =====
    //ESTA PARTE NO SE SI ESTARÁ BIEN, YA QUE FALTA LO DE SIMULAR BATLLAS ENTONCES NO SE
    //QUEDA PROVICIONALMENTE
    insertarBatalla(1, 1, 2, 1, 2, "Alejandro", 3, 1, 2.5, 8, "2026-04-01");
    insertarBatalla(2, 3, 4, 3, 4, "Carlos", 2, 0, 3.1, 9, "2026-04-02");
    insertarBatalla(3, 5, 6, 5, 6, "Eduardo", 3, 2, 2.8, 8, "2026-04-03");
    insertarBatalla(4, 7, 8, 7, 8, "Gabriel", 3, 0, 1.9, 10, "2026-04-04");
    insertarBatalla(5, 9, 10, 9, 10, "Ivan", 2, 1, 2.3, 7, "2026-04-05");
    insertarBatalla(6, 2, 3, 2, 3, "Carlos", 1, 3, 3.5, 9, "2026-04-06");
    insertarBatalla(7, 4, 5, 4, 5, "Eduardo", 0, 3, 2.7, 8, "2026-04-07");
    insertarBatalla(8, 6, 7, 6, 7, "Gabriel", 1, 3, 2.1, 10, "2026-04-08");
    insertarBatalla(9, 8, 9, 8, 9, "Ivan", 2, 3, 3.0, 7, "2026-04-09");
    insertarBatalla(10, 1, 10, 1, 10, "Alejandro", 3, 2, 2.6, 8, "2026-04-10");
}
