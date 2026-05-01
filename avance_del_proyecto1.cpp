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
    int vecesUsada;//lo adicional para ver las cant de cartas mas usadas

    Cartas *sig;

    Cartas(int IDC, string n, string r, string t, int ce, double db, int vb){
        IDCarta = IDC;
        Nombre = n;
        Rareza = r;
        Tipo = t;
        costoElixir = ce;
        dañoBase = db; 
        vidaBase = vb;
        vecesUsada = 0;
        
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
    string fecha; //hay qu elamacenar la fecha todavia
    


    // ===== ESTADISTICAS DEL MAZO (OPCIONAL DEL DOC) =====
    double promedioElixirJ1, promedioElixirJ2;
    string tipoMazoJ1, tipoMazoJ2;
    double consumoElixirJ1, consumoElixirJ2;







    Batallas *sig, *ant;

    Batallas(int IDB, int IDJ1, int IDJ2, int IDM1, int IDM2, string g, int cJ1, int cJ2, float d, int IDA, string f,double pe1, double pe2, string t1, string t2,
         double ce1, double ce2){//se agregan las funciones de estadisticas del mazo(la opcional)
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

        promedioElixirJ1 = pe1;//funciones de estadisticas 
        promedioElixirJ2 = pe2;
        tipoMazoJ1 = t1;
        tipoMazoJ2 = t2;
        consumoElixirJ1 = ce1;
        consumoElixirJ2 = ce2;



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
void insertarBatalla(int IDB, int IDJ1, int IDJ2, int IDM1, int IDM2, string g, int cJ1, int cJ2, float d, int IDA, string f, double pe1, 
double pe2, string t1, string t2,double ce1, double ce2){

//Ver que los datos de batalla si existan o sean validos
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

    Batallas *nuevaBatalla = new Batallas(IDB, IDJ1, IDJ2, IDM1, IDM2, g, cJ1, cJ2, d, IDA, f,pe1, pe2, t1, t2, ce1, ce2);
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
    cin.ignore(); // limpiar buffer antes de getline
    getline(cin, nuevoNombre);

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

    // Validar que la arena exista
    Arenas *arena = buscarArena(nuevoIDArena);
    if(arena == NULL){
        cout << "Error: No existe una arena con ese ID." << endl;
        return;
    }

    // Validar que el clan exista (permitiendo 0 = sin clan)
    if(nuevoIDClan != 0 && buscarClan(nuevoIDClan) == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    // validar los trofeos del jugador con el rango de la arena
    if(nuevosTrofeos < arena->trofeosMin || nuevosTrofeos > arena->trofeosMax){
        cout << "Error: El número de trofeos no es compatible con la nueva arena." << endl;
        return;
    }

    // 🔴 MANEJO DE CAMBIO DE CLAN
    if(temp->IDClan != nuevoIDClan){
        // quitar del clan anterior si tenía
        if(temp->IDClan != 0){
            eliminarJugadorDeClan(temp->IDClan, IDJ);
        }

        // agregar al nuevo clan si no es 0
        if(nuevoIDClan != 0){
            insertarJugadorEnClan(nuevoIDClan, IDJ);
        }
    }

    // guardar datos antes de reordenar (por el nombre)
    int id = temp->IDJugador;

    // Eliminar de la lista(para no romper el orden)
    Jugadores* actual = primerJugador;
    Jugadores* ant = NULL;

    while(actual != NULL && actual != temp){
        ant = actual;
        actual = actual->sig;
    }

    if(ant == NULL){
        primerJugador = temp->sig;
    } else {
        ant->sig = temp->sig;
    }

    delete temp;

    // reinsertar nuevos datos ordenados
    insertarJugador(id, nuevoNombre, nuevoNivelRey, nuevosTrofeos, nuevoIDArena, nuevoIDClan);

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







/*-----------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------

------------------------------------------SIMULACION DE PARTIDAS -----------------------------------------

----------------------------------------------------------------------------------------------------*/


// ============================================================
// SIMULACIÓN DE BATALLAS
// Lógica inspirada en Clash Royale:
// - Poder de ataque = suma de dañoBase de las 8 cartas del mazo
// - Poder de defensa = suma de vidaBase de las 8 cartas del mazo
// - Costo promedio = suma de costoElixir / 8
// - Tipo predominante = tipo que más aparece entre las 8 cartas
// - Ganador: se calcula con poderJ = dañoTotal - (vidaRival * 0.3)
//   simulando que el daño del mazo debe "atravesar" la vida del rival
// - Coronas:
//   > 40% de diferencia de poder= 3 coronas (arrasó)
//   > 20% de diferencia de poder= 2 coronas (victoria clara)
//   <= 20% de diferencia de poder= 1 corona (batalla ajustada)
// - Duración simulada según resultado:
//   3 coronas = 1.5 a 2.5 min (victoria rápida)
//   2 coronas = 2.5 a 3.5 min (victoria normal)
//   1 corona  = 3.5 a 4.0 min (prórroga, batalla muy pareja)
// ============================================================



// ------------------------------------------------------------
//DañoTotal que representa el poder ofensivo del mazo
// ------------------------------------------------------------
double calcularDañoTotal(Mazos* mazo) {
    double total = 0;
    NodoCartaMazo* temp = mazo->listaCartas;
    while (temp != NULL) {
        Cartas* carta = buscarCarta(temp->IDCarta);
        if (carta != NULL) {
            total += carta->dañoBase;
        }
        temp = temp->sig;
    }
    return total;
}

// ------------------------------------------------------------
// Calcula la vida total sumando vidaBase de las 8 cartas
// del mazo. Representa el poder defensivo del mazo.
// ------------------------------------------------------------
int calcularVidaTotal(Mazos* mazo) {
    int total = 0;
    NodoCartaMazo* temp=mazo->listaCartas;
    while (temp!=NULL) {
        Cartas*carta=buscarCarta(temp->IDCarta);
        if (carta!=NULL) {
            total+=carta->vidaBase;
        }
        temp=temp->sig;
    }
    return total;
}

// ------------------------------------------------------------
// Promedio de elixir
// ------------------------------------------------------------
double calcularPromedioElixir(Mazos* mazo) {
    int totalElixir = 0;
    int cantidad = 0;
    NodoCartaMazo* temp = mazo->listaCartas;
    while (temp != NULL) {
        Cartas* carta = buscarCarta(temp->IDCarta);
        if (carta != NULL) {
            totalElixir += carta->costoElixir;
            cantidad++;
        }
        temp = temp->sig;
    }
    if (cantidad == 0) return 0;
    return (double)totalElixir / cantidad;
}

/* ------------------------------------------------------------
 Tipo Predominante según sean las cartas Tropa, Hechizo o Edificio
 el que mas aparece define el estilo del mazo
 ------------------------------------------------------------*/
string calcularTipoPredominante(Mazos* mazo) {
    int tropas = 0, hechizos = 0, edificios = 0;
    NodoCartaMazo* temp = mazo->listaCartas;

    while (temp != NULL) {
        Cartas* carta = buscarCarta(temp->IDCarta);
        if (carta != NULL) {
            string tipo = carta->Tipo;
            if (tipo=="Tropa" ||tipo=="tropa")tropas++;//por si la escriben en minuscula o mayuscula
            if (tipo=="Hechizo"||tipo=="hechizo")hechizos++;
            if (tipo=="Edificio"||tipo=="edificio")edificios++;
        }
        temp=temp->sig;
    }

    if (tropas >= hechizos && tropas >= edificios)    return "Tropa";
    if (hechizos >= tropas && hechizos >= edificios)  return "Hechizo";
    return "Edificio";//como en intro
}

// ------------------------------------------------------------
// total de elixir, aprox 24 por minuto 

// ------------------------------------------------------------
double calcularConsumoDElixir(Mazos* mazo) {//usamos double porque es un promedio 
    double promedio = calcularPromedioElixir(mazo);
    if (promedio == 0) return 0;
    double elixirTotal=72;//elixir promedio en clash cada 3 min
    double ciclos=elixirTotal/(promedio*8);//ciclo completo
    return ciclos;
}

// ------------------------------------------------------------
//funcion principal con ID, mazos y arena
// Calcula el resultado y registra la batalla automáticamente
// ------------------------------------------------------------
void simularBatalla(int IDJ1, int IDJ2, int IDM1, int IDM2, int IDArena, string fecha) {
    Jugadores* j1 = buscarJugador(IDJ1);//para validar que existen los juigadores 
    Jugadores* j2 = buscarJugador(IDJ2);
    if (j1 == NULL) {
        cout << "Error: No existe el jugador 1 con ID " << IDJ1 << "." << endl;
        return;
    }
    if (j2 == NULL) {
        cout << "Error: No existe el jugador 2 con ID " << IDJ2 << "." << endl;
        return;
    }
    if (IDJ1 == IDJ2) {
        cout << "Error: Un jugador no puede batallar contra sí mismo." << endl;
        return;
    }

    Mazos* m1 = buscarMazo(IDM1);//qu esi existan los mazos y sean de esos mismos jugadores 
    Mazos* m2 = buscarMazo(IDM2);
    if (m1 == NULL) {
        cout << "Error: No existe el mazo 1 con ID " << IDM1 << "." << endl;
        return;
    }
    if (m2 == NULL) {
        cout << "Error: No existe el mazo 2 con ID " << IDM2 << "." << endl;
        return;
    }
    if (m1->IDJugador != IDJ1) {
        cout << "Error: El mazo " << IDM1 << " no pertenece al jugador " << IDJ1 << "." << endl;
        return;
    }
    if (m2->IDJugador != IDJ2) {
        cout << "Error: El mazo " << IDM2 << " no pertenece al jugador " << IDJ2 << "." << endl;
        return;
    }
    if (m1->cantidadCartas != 8 || m2->cantidadCartas != 8) {
        cout << "Error: Ambos mazos deben tener exactamente 8 cartas." << endl;
        return;
    }

    Arenas* arena = buscarArena(IDArena);//que si exsta la arena 
    if (arena == NULL) {
        cout << "Error: No existe una arena con ID " << IDArena << "." << endl;
        return;
    }

    // ================================================================
    // CÁLCULO DE ESTADÍSTICAS DE CADA MAZO
    // ================================================================

    // Poder ofensivo: suma de daño de las 8 cartas
    double dañoJ1 = calcularDañoTotal(m1);
    double dañoJ2 = calcularDañoTotal(m2);

    // Poder defensivo: suma de vida de las 8 cartas
    int vidaJ1 = calcularVidaTotal(m1);
    int vidaJ2 = calcularVidaTotal(m2);

    // Costo promedio de elixir
    double elixirJ1 = calcularPromedioElixir(m1);
    double elixirJ2 = calcularPromedioElixir(m2);

    // Tipo predominante del mazo
    string tipoJ1 = calcularTipoPredominante(m1);
    string tipoJ2 = calcularTipoPredominante(m2);

    // Ciclos de elixir estimados
    double ciclosJ1 = calcularConsumoDElixir(m1);
    double ciclosJ2 = calcularConsumoDElixir(m2);

    /* ================================================================
    // ENCOnTRAR GANADOR
    // poderJ=dañoPropio-(vidaRival * 0.3) tiene qye haber un 30% de daño hacaia el otro 
    el.3 sería la defensa que lo afecta del otro jugador */
    double poderJ1=dañoJ1-(vidaJ2 *0.3);
    double poderJ2=dañoJ2-(vidaJ1*0.3);

    // ================================================================
    // CÁLCULO DE CORONAS
    // Diferencia > 40%: 3 coronas (arrasó al rival)
    // Diferencia > 20%: 2 coronas (victoria clara)
    // <= 20%: 1 corona  (batalla muy ajustada / prórroga)
    // Si los poderes son iguales o muy cercanos → empate (0 coronas c/u)
    // ================================================================
    int coronasJ1 = 0, coronasJ2 = 0;
    string ganador;
    float duracion;

    double maxPoder=(poderJ1 > poderJ2) ? poderJ1 : poderJ2;// un trie que clacula dofenrecia con el mayor poder 
    double diferencia=0;
    if (maxPoder>0) {
        diferencia=((poderJ1 > poderJ2)? (poderJ1 - poderJ2): (poderJ2 - poderJ1)) / maxPoder * 100.0;// trie
    }

    if (poderJ1 > poderJ2) {
        // J1 gana
        ganador = j1->nombreUsuario;
        if (diferencia > 40) {
            coronasJ1 = 3; coronasJ2 = 0;
            duracion = 1.5 + ((float)(IDJ1 % 10) / 10.0); // entre 1.5 y 2.5
        } else if (diferencia > 20) {
            coronasJ1 = 2; coronasJ2 = 1;
            duracion = 2.5 + ((float)(IDJ1 % 10) / 10.0); // entre 2.5 y 3.5
        } else {
            coronasJ1 = 2; coronasJ2 = 1;
            duracion = 3.5 + ((float)(IDJ1 % 5) / 10.0);  // entre 3.5 y 4.0
        }
    } else if (poderJ2 > poderJ1) {
        // J2 gana
        ganador = j2->nombreUsuario;
        if (diferencia > 40) {
            coronasJ2 = 3; coronasJ1 = 0;
            duracion = 1.5 + ((float)(IDJ2 % 10) / 10.0);
        } else if (diferencia > 20) {
            coronasJ2 = 2; coronasJ1 = 1;
            duracion = 2.5 + ((float)(IDJ2 % 10) / 10.0);
        } else {
            coronasJ2 = 2; coronasJ1 = 1;
            duracion = 3.5 + ((float)(IDJ2 % 5) / 10.0);
        }
    } else {
        //Si es que empatan con mismos puntos en todo
        ganador = "Empate";
        coronasJ1 = 1; coronasJ2 = 1;
        duracion = 4.0;
    }








    // CONTAR USO DE CARTAS
    NodoCartaMazo* tempC = m1->listaCartas;
    while (tempC != NULL) {
        Cartas* c = buscarCarta(tempC->IDCarta);
        if (c != NULL) c->vecesUsada++;
        tempC = tempC->sig;
    }

    tempC = m2->listaCartas;
    while (tempC != NULL) {
        Cartas* c = buscarCarta(tempC->IDCarta);
        if (c != NULL) c->vecesUsada++;
        tempC = tempC->sig;
    }



    //RESUMEN DE BATTALLA siempre antes de registrarla-----------------------------------------------------------------------------
    cout << "\n========================================" << endl;
    cout << "       RESULTADO DE LA SIMULACION       " << endl;
    cout << "========================================" << endl;
    cout << "Arena: " << arena->nombreArena << endl;
    cout << "Fecha: " << fecha << endl;
    cout << "----------------------------------------" << endl;

    cout << "\n[JUGADOR 1] " << j1->nombreUsuario << " - Mazo: " << m1->nombreMazo << endl;
    cout << "  Daño total del mazo   : " << dañoJ1 << endl;
    cout << "  Vida total del mazo   : " << vidaJ1 << endl;
    cout << "  Promedio de elixir    : " << elixirJ1 << endl;
    cout << "  Tipo predominante     : " << tipoJ1 << endl;
    cout << "  Ciclos de elixir est. : " << ciclosJ1 << endl;
    cout << "  Poder calculado       : " << poderJ1 << endl;

    cout << "\n[JUGADOR 2] " << j2->nombreUsuario << " - Mazo: " << m2->nombreMazo << endl;
    cout << "  Daño total del mazo   : " << dañoJ2 << endl;
    cout << "  Vida total del mazo   : " << vidaJ2 << endl;
    cout << "  Promedio de elixir    : " << elixirJ2 << endl;
    cout << "  Tipo predominante     : " << tipoJ2 << endl;
    cout << "  Ciclos de elixir est. : " << ciclosJ2 << endl;
    cout << "  Poder calculado       : " << poderJ2 << endl;

    cout << "\n----------------------------------------" << endl;
    cout << "  Diferencia de poder   : " << diferencia << "%" << endl;
    cout << "  Ganador               : " << ganador << endl;
    cout << "  Coronas " << j1->nombreUsuario << " : " << coronasJ1 << endl;
    cout << "  Coronas " << j2->nombreUsuario << " : " << coronasJ2 << endl;
    cout << "  Duracion simulada     : " << duracion << " min" << endl;
    cout << "========================================" << endl;


// REGISTRAR LA BATALLA EN LA LISTA
// Se genera un ID automático buscando el mayor ID existente+1

    int nuevoID = 1;
    if (primerBatalla != NULL) {
        Batallas* temp = primerBatalla;
        do {
            if (temp->IDBatalla >= nuevoID) {
                nuevoID = temp->IDBatalla + 1;
            }
            temp = temp->sig;
        } while (temp != primerBatalla);
    }

    insertarBatalla(nuevoID, IDJ1, IDJ2, IDM1, IDM2, ganador,coronasJ1, coronasJ2, duracion, IDArena, fecha,elixirJ1, elixirJ2, tipoJ1, tipoJ2,
ciclosJ1, ciclosJ2);

    cout << "Batalla registrada con ID: " << nuevoID << endl;
}



void mostrarCartasMasUsadas() {//cartas mas usadas (extra)
    if (primerCarta == NULL) {
        cout << "No hay cartas registradas." << endl;
        return;
    }
    int maxUso = 0;
    Cartas* temp = primerCarta;

    // Encontrar el máximo uso
    while (temp != NULL) {
        if (temp->vecesUsada > maxUso)
            maxUso = temp->vecesUsada;
        temp = temp->sig;
    }
    if (maxUso==0) {
        cout << "Aun no se han usado cartas en batallas." << endl;
        return;
    }
    cout << "\n=== CARTAS MAS USADAS ===" << endl;
    temp = primerCarta;
    while (temp!=NULL) {
        if (temp->vecesUsada == maxUso) {
            cout << "Carta: " << temp->Nombre
                 << " | Usos: " << temp->vecesUsada << endl;
        }
        temp = temp->sig;
    }
}






// ============================================================
// MENÚ DE SIMULACIÓN
// ============================================================
void menuSimulacion() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "        SIMULACION DE BATALLAS          " << endl;
        cout << "========================================" << endl;
        cout << " 1. Simular nueva batalla" << endl;
        cout << " 2. Ver cartas mas usadas" << endl;        
        cout << " 3. Volver al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- Simular Batalla ---" << endl;
                int idJ1, idJ2, idM1, idM2, idArena;
                string fecha;

                cout << "ID del jugador 1: ";
                cin >> idJ1;
                cout << "ID del jugador 2: ";
                cin >> idJ2;
                cout << "ID del mazo del jugador 1: ";
                cin >> idM1;
                cout << "ID del mazo del jugador 2: ";
                cin >> idM2;
                cout << "ID de la arena: ";
                cin >> idArena;
                cin.ignore();
                cout << "Fecha (AAAA-MM-DD): ";
                getline(cin, fecha);

                simularBatalla(idJ1, idJ2, idM1, idM2, idArena, fecha);
                break;
            }
            case 2:
                mostrarCartasMasUsadas();
                break;

            case 3:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 3);
}


























/*-----------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------

---------------------------------------------MENUS-----------------------------------------



----------------------------------------------------------------------------------------------------


*/
// ============================================================
// MENÚ CARTAS
// ============================================================
void menuCartas() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "         MANTENIMIENTO - CARTAS         " << endl;
        cout << "========================================" << endl;
        cout << " 1. Insertar carta" << endl;
        cout << " 2. Modificar carta" << endl;
        cout << " 3. Eliminar carta" << endl;
        cout << " 4. Volver al menu anterior" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Carta ---" << endl;
                int id, costo, vida;
                double daño;
                string nombre, rareza, tipo;

                cout << "ID de la carta: ";
                cin >> id;
                cin.ignore();
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Rareza (Comun/Rara/Epica/Legendaria): ";
                getline(cin, rareza);
                cout << "Tipo (Tropa/Hechizo/Edificio): ";
                getline(cin, tipo);
                cout << "Costo de elixir: ";
                cin >> costo;
                cout << "Daño base: ";
                cin >> daño;
                cout << "Vida base: ";
                cin >> vida;

                insertarCartas(id, nombre, rareza, tipo, costo, daño, vida);
                break;
            }
            case 2: {
                cout << "\n--- Modificar Carta ---" << endl;
                int id;
                cout << "ID de la carta a modificar: ";
                cin >> id;
                modificarCarta(id);
                break;
            }
            case 3: {
                cout << "\n--- Eliminar Carta ---" << endl;
                int id;
                cout << "ID de la carta a eliminar: ";
                cin >> id;
                eliminarCarta(id);
                break;
            }
            case 4:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 4);
}


// ============================================================
// MENÚ JUGADORES
// ============================================================
void menuJugadores() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "       MANTENIMIENTO - JUGADORES        " << endl;
        cout << "========================================" << endl;
        cout << " 1. Insertar jugador" << endl;
        cout << " 2. Modificar jugador" << endl;
        cout << " 3. Eliminar jugador" << endl;
        cout << " 4. Volver al menu anterior" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Jugador ---" << endl;
                int id, nivel, trofeos, idArena, idClan;
                string nombre;

                cout << "ID del jugador: ";
                cin >> id;
                cin.ignore();
                cout << "Nombre de usuario: ";
                getline(cin, nombre);
                cout << "Nivel del rey (1-15): ";
                cin >> nivel;
                cout << "Trofeos: ";
                cin >> trofeos;
                cout << "ID de arena: ";
                cin >> idArena;
                cout << "ID de clan (0 si no pertenece a ninguno): ";
                cin >> idClan;

                insertarJugador(id, nombre, nivel, trofeos, idArena, idClan);
                break;
            }
            case 2: {
                cout << "\n--- Modificar Jugador ---" << endl;
                int id;
                cout << "ID del jugador a modificar: ";
                cin >> id;
                modificarJugador(id);
                break;
            }
            case 3: {
                cout << "\n--- Eliminar Jugador ---" << endl;
                int id;
                cout << "ID del jugador a eliminar: ";
                cin >> id;
                eliminarJugador(id);
                break;
            }
            case 4:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 4);
}


// ============================================================
// MENÚ MAZOS
// ============================================================
void menuMazos() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "         MANTENIMIENTO - MAZOS          " << endl;
        cout << "========================================" << endl;
        cout << " 1. Insertar mazo" << endl;
        cout << " 2. Agregar carta a mazo" << endl;
        cout << " 3. Modificar mazo" << endl;
        cout << " 4. Eliminar mazo" << endl;
        cout << " 5. Eliminar carta de mazo" << endl;
        cout << " 6. Volver al menu anterior" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Mazo ---" << endl;
                int id, idJugador;
                string nombre, tipo;

                cout << "ID del mazo: ";
                cin >> id;
                cin.ignore();
                cout << "Nombre del mazo: ";
                getline(cin, nombre);
                cout << "Tipo del mazo: ";
                getline(cin, tipo);
                cout << "ID del jugador dueño: ";
                cin >> idJugador;

                insertarMazo(id, nombre, tipo, idJugador);
                break;
            }
            case 2: {
                cout << "\n--- Agregar Carta a Mazo ---" << endl;
                int idMazo, idCarta;
                cout << "ID del mazo: ";
                cin >> idMazo;
                cout << "ID de la carta a agregar: ";
                cin >> idCarta;
                insertarCartaEnMazo(idMazo, idCarta);
                break;
            }
            case 3: {
                cout << "\n--- Modificar Mazo ---" << endl;
                int id;
                cout << "ID del mazo a modificar: ";
                cin >> id;
                modificarMazo(id);
                break;
            }
            case 4: {
                cout << "\n--- Eliminar Mazo ---" << endl;
                int id;
                cout << "ID del mazo a eliminar: ";
                cin >> id;
                eliminarMazo(id);
                break;
            }
            case 5: {
                cout << "\n--- Eliminar Carta de Mazo ---" << endl;
                int idMazo, idCarta;
                cout << "ID del mazo: ";
                cin >> idMazo;
                cout << "ID de la carta a eliminar: ";
                cin >> idCarta;
                eliminarCartaDeMazo(idMazo, idCarta);
                break;
            }
            case 6:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 6);
}


// ============================================================
// MENU CLANES
// ============================================================
void menuClanes() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "         MANTENIMIENTO - CLANES         " << endl;
        cout << "========================================" << endl;
        cout << " 1. Insertar clan" << endl;
        cout << " 2. Agregar jugador a clan" << endl;
        cout << " 3. Modificar clan" << endl;
        cout << " 4. Eliminar clan" << endl;
        cout << " 5. Eliminar jugador de clan" << endl;
        cout << " 6. Volver al menu anterior" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Clan ---" << endl;
                int id, miembros;
                double puntaje;
                string nombre, region;

                cout << "ID del clan: ";
                cin >> id;
                cin.ignore();
                cout << "Nombre del clan: ";
                getline(cin, nombre);
                cout << "Region: ";
                getline(cin, region);
                cout << "Cantidad de miembros: ";
                cin >> miembros;
                cout << "Puntaje del clan: ";
                cin >> puntaje;

                insertarClan(id, nombre, region, miembros, puntaje);
                break;
            }
            case 2: {
                cout << "\n--- Agregar Jugador a Clan ---" << endl;
                int idClan, idJugador;
                cout << "ID del clan: ";
                cin >> idClan;
                cout << "ID del jugador: ";
                cin >> idJugador;
                insertarJugadorEnClan(idClan, idJugador);
                break;
            }
            case 3: {
                cout << "\n--- Modificar Clan ---" << endl;
                int id;
                cout << "ID del clan a modificar: ";
                cin >> id;
                modificarClan(id);
                break;
            }
            case 4: {
                cout << "\n--- Eliminar Clan ---" << endl;
                int id;
                cout << "ID del clan a eliminar: ";
                cin >> id;
                eliminarClan(id);
                break;
            }
            case 5: {
                cout << "\n--- Eliminar Jugador de Clan ---" << endl;
                int idClan, idJugador;
                cout << "ID del clan: ";
                cin >> idClan;
                cout << "ID del jugador a eliminar: ";
                cin >> idJugador;
                eliminarJugadorDeClan(idClan, idJugador);
                break;
            }
            case 6:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 6);
}


// ============================================================
// MENU ARENAS
// ============================================================
void menuArenas() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "         MANTENIMIENTO - ARENAS         " << endl;
        cout << "========================================" << endl;
        cout << " 1. Insertar arena" << endl;
        cout << " 2. Modificar arena" << endl;
        cout << " 3. Eliminar arena" << endl;
        cout << " 4. Volver al menu anterior" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Arena ---" << endl;
                int id, tmin, tmax;
                string nombre;

                cout << "ID de la arena: ";
                cin >> id;
                cin.ignore();
                cout << "Nombre de la arena: ";
                getline(cin, nombre);
                cout << "Trofeos minimos: ";
                cin >> tmin;
                cout << "Trofeos maximos: ";
                cin >> tmax;

                insertarArena(id, nombre, tmin, tmax);
                break;
            }
            case 2: {
                cout << "\n--- Modificar Arena ---" << endl;
                int id;
                cout << "ID de la arena a modificar: ";
                cin >> id;
                modificarArena(id);
                break;
            }
            case 3: {
                cout << "\n--- Eliminar Arena ---" << endl;
                int id;
                cout << "ID de la arena a eliminar: ";
                cin >> id;
                eliminarArena(id);
                break;
            }
            case 4:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 4);
}


// ============================================================
// MENU BATALLAS
// ============================================================
void menuBatallas() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "        MANTENIMIENTO - BATALLAS        " << endl;
        cout << "========================================" << endl;
        cout << " 1. Registrar batalla" << endl;
        cout << " 2. Eliminar batalla" << endl;
        cout << " 3. Volver al menu anterior" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                cout << "\n--- Registrar Batalla ---" << endl;
                int id, idJ1, idJ2, idM1, idM2, cJ1, cJ2, idArena;
                float duracion;
                string ganador, fecha;

                cout << "ID de la batalla: ";
                cin >> id;
                cout << "ID jugador 1: ";
                cin >> idJ1;
                cout << "ID jugador 2: ";
                cin >> idJ2;
                cout << "ID mazo jugador 1: ";
                cin >> idM1;
                cout << "ID mazo jugador 2: ";
                cin >> idM2;
                cin.ignore();
                cout << "Nombre del ganador: ";
                getline(cin, ganador);
                cout << "Coronas jugador 1 (0-3): ";
                cin >> cJ1;
                cout << "Coronas jugador 2 (0-3): ";
                cin >> cJ2;
                cout << "Duracion (minutos): ";
                cin >> duracion;
                cout << "ID de arena: ";
                cin >> idArena;
                cin.ignore();
                cout << "Fecha (AAAA-MM-DD): ";
                getline(cin, fecha);

                insertarBatalla(id, idJ1, idJ2, idM1, idM2, ganador,cJ1, cJ2, duracion, idArena, fecha);
                break;
            }
            case 2: {
                cout << "\n--- Eliminar Batalla ---" << endl;
                int id;
                cout << "ID de la batalla a eliminar: ";
                cin >> id;
                eliminarBatalla(id);
                break;
            }
            case 3:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 3);
}


// ============================================================
// MENU MANTENIMIENTO
// ============================================================
void menuMantenimiento() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "           MENU MANTENIMIENTO           " << endl;
        cout << "========================================" << endl;
        cout << " 1. Cartas" << endl;
        cout << " 2. Jugadores" << endl;
        cout << " 3. Mazos" << endl;
        cout << " 4. Clanes" << endl;
        cout << " 5. Arenas" << endl;
        cout << " 6. Batallas" << endl;
        cout << " 7. Volver al menu principal" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: menuCartas();      break;
            case 2: menuJugadores();   break;
            case 3: menuMazos();       break;
            case 4: menuClanes();      break;
            case 5: menuArenas();      break;
            case 6: menuBatallas();    break;
            case 7:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 7);
}





// ============================================================
// MENÚ PRINCIPAL
// ============================================================
void menuPrincipal() {
    int opcion;
    do {
        cout << "\n========================================" << endl;
        cout << "    SISTEMA CLASH ROYALE - TEC 2026     " << endl;
        cout << "========================================" << endl;
        cout << " 1. Mantenimiento" << endl;
        cout << " 2. Consultas" << endl;
        cout << " 3. Reportes" << endl;
        cout << " 4. Simulacion de batallas" << endl;
        cout << " 5. Salir" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: menuMantenimiento(); break;
            case 2: cout << "(Consultas - por implementar)" << endl; break;
            case 3: cout << "(Reportes - por implementar)"  << endl; break;
            case 4: cout << "(Simulacion - por implementar)" << endl; break;
            case 5: cout << "\nHasta luego!" << endl; break;
            default: cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 5);
}


// ============================================================
// MAIN
// ============================================================
int main() {
    cargarDatos();
    menuPrincipal();
    return 0;
}
