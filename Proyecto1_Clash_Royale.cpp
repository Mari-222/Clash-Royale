#include <iostream>
#include <limits>   //para dar limites de numeros y opciones donde solo se permiten numeros


using namespace std;

/*Documentación Interna:

Fecha de inicio: 24 de abril
Última modificación: 8 de mayo
Nombre de los integrantes del grupo de trabajo:
Mariana González Céspedes
Fabricio Alejandro Castro Muñoz 
Josué David González Alvarado

*/


// Lista simple con inserción al inicio, almacena todas las cartas disponibles del juego
// con sus atributos de rareza, tipo, costo de elixir, daño base y vida base. 
struct Cartas{
    int IDCarta;
    string Nombre;
    string Rareza;
    string Tipo;
    int costoElixir;
    double danioBase;
    int vidaBase;
    int vecesUsada;//lo adicional para ver las cant de cartas mas usadas

    Cartas *sig;

    Cartas(int IDC, string n, string r, string t, int ce, double db, int vb){
        IDCarta = IDC;
        Nombre = n;
        Rareza = r;
        Tipo = t;
        costoElixir = ce;
        danioBase = db; 
        vidaBase = vb;
        vecesUsada = 0;
        
        sig = NULL;
    }
}*primerCarta;


// Lista doble ordenada alfabéticamente por nombreUsuario, almacena los jugadores del sistema
// con sus trofeos, nivel de rey, arena y clan asignados.
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


// Nodo de la sublista de cartas dentro de un mazo, guarda únicamente el ID de la carta
// para referenciarla sin duplicar su información.
struct NodoCartaMazo {
    int IDCarta;
    NodoCartaMazo *sig;

    NodoCartaMazo(int id) {
        IDCarta = id;
        sig = NULL;
    }
};


// Lista simple con inserción al final, almacena los mazos de los jugadores.
// Cada mazo contiene una sublista de exactamente 8 cartas referenciadas por ID.
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


// Nodo de la sublista de jugadores dentro de un clan, guarda únicamente el ID del jugador
// para referenciarlo sin duplicar su información.
struct NodoJugadorClan {
    int IDJugador;
    NodoJugadorClan *sig;

    NodoJugadorClan(int id) {
        IDJugador = id;
        sig = NULL;
    }
};


// Lista circular con inserción al final, almacena los clanes del sistema.
// Cada clan contiene una sublista de sus jugadores miembros referenciados por ID.
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


// Lista simple con inserción al inicio, almacena las arenas del juego.
// Cada arena define un rango de trofeos que clasifica a los jugadores y escenarios de batalla.
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


// Lista doble circular con inserción al final, almacena el historial de batallas del sistema.
// Registra los jugadores, mazos, arena, coronas, ganador, duración y estadísticas opcionales.
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
    string fecha; 
    


    // ===== ESTADISTICAS DEL MAZO =====
    double promedioElixirJ1, promedioElixirJ2;
    string tipoMazoJ1, tipoMazoJ2;
    double consumoElixirJ1, consumoElixirJ2;

    Batallas *sig, *ant;

    Batallas(int IDB, int IDJ1, int IDJ2, int IDM1, int IDM2, string g, int cJ1, int cJ2, float d, int IDA, string f,double pe1, double pe2, string t1, string t2,
         double ce1, double ce2){//se agregan las funciones de estadisticas del mazo
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

// Recorre la lista de cartas y retorna el puntero al nodo con el ID indicado, o NULL si no existe.
Cartas *buscarCarta(int IDCarta){
    Cartas *temp = primerCarta;

    while(temp != NULL){
        if(temp -> IDCarta == IDCarta)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

// Recorre la lista de jugadores y retorna el puntero al nodo con el ID indicado, o NULL si no existe.
Jugadores *buscarJugador(int IDJugador){
    Jugadores *temp = primerJugador;

    while(temp != NULL){
        if(temp -> IDJugador == IDJugador)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

// Recorre la lista de mazos y retorna el puntero al nodo con el ID indicado, o NULL si no existe.
Mazos *buscarMazo(int IDMazo){
    Mazos *temp = primerMazo;

    while(temp != NULL){
        if(temp -> IDMazo == IDMazo)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

// Recorre la lista circular de clanes y retorna el puntero al nodo con el ID indicado, o NULL si no existe.
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

// Recorre la lista de arenas y retorna el puntero al nodo con el ID indicado, o NULL si no existe.
Arenas *buscarArena(int IDArena){
    Arenas *temp = primerArena;

    while(temp != NULL){
        if(temp -> IDArena == IDArena)
            return temp;
        temp = temp -> sig;
    }
    return NULL;
}

// Recorre la lista doble circular de batallas y retorna el puntero al nodo con el ID indicado, o NULL si no existe.
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

// Convierte todos los caracteres mayúsculas de un string a minúsculas
// para permitir comparaciones sin distinción de mayúsculas y minúsculas.
string toLower(string s) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 32;
    }
    return s;
}


//Funciones de leerEntero y de leerBooleano para evitar bucles y solo permitir el ingreso de numeros

// Lee un entero dentro de un rango [min, max] (inclusive)
int leerEntero(string mensaje, int min, int max) {
    int valor;
    bool ok;
    do {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Error: debe ingresar un numero entero. Intente de nuevo.\n";
            ok = false;
        } else if (valor < min || valor > max) {
            cout << "  Error: el valor debe estar entre " << min << " y " << max << ". Intente de nuevo.\n";
            ok = false;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            ok = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!ok);
    return valor;
}

// Lee un double dentro de un rango [min, max]
double leerDouble(string mensaje, double min, double max) {
    double valor;
    bool ok;
    do {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Error: debe ingresar un numero. Intente de nuevo.\n";
            ok = false;
        } else if (valor < min || valor > max) {
            cout << "  Error: el valor debe estar entre " << min << " y " << max << ". Intente de nuevo.\n";
            ok = false;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            ok = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!ok);
    return valor;
}


//Funcion por si se ingresan eapacs o caracteres vacios o distintos en opciones como nombres del menu
string leerString(string mensaje, bool permitirVacio = false) {
    string valor;
    do {
        cout << mensaje;
        getline(cin, valor);
        if (!permitirVacio && valor.empty()) {
            cout << "  Error: no puede estar vacio. Intente de nuevo.\n";
        } else {
            break;
        }
    } while (true);
    return valor;
}























//INSERCIONES

// Inserta una nueva carta al inicio de la lista simple. Valida ID único, rareza válida,
// tipo válido, costo de elixir entre 1 y 9, y valores no negativos para daño y vida. 
void insertarCartas(int IDCarta, string nombre, string rareza, string tipo, int costoElixir, double danioBase, int vidaBase){
    // Validar que los datos de la carta sean válidos.
    if (IDCarta < 0 || nombre.empty() || rareza.empty() || tipo.empty() || costoElixir < 1 || costoElixir > 9 || danioBase < 0 || vidaBase < 0) {
        cout << "Error: Datos de la carta no válidos. Por favor, intente de nuevo." << endl;
        return;
    }

    // Convertir a minúsculas para comparar
    string rarezaLower = toLower(rareza);
    string tipoLower = toLower(tipo);
   

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

    Cartas *nuevaCarta = new Cartas(IDCarta, nombre, rareza, tipo, costoElixir, danioBase, vidaBase);

    nuevaCarta -> sig = primerCarta;
    primerCarta = nuevaCarta;
}

// Inserta un nuevo jugador manteniendo el orden alfabético en la lista doble.
// Valida ID único, existencia de arena y clan, y compatibilidad de trofeos con el rango de la arena.
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
    if(IDC != 0 && buscarClan(IDC) == NULL){
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

    if(IDC != 0){ // Si el jugador tiene clan asignado, agregarlo a la lista de miembros del clan
        Clanes *clan = buscarClan(IDC);
        NodoJugadorClan *nuevoMiembro = new NodoJugadorClan(IDJ);
        if(clan->listaJugadores == NULL){
            clan->listaJugadores = nuevoMiembro;
        } else {
            NodoJugadorClan *temp = clan->listaJugadores;
            while(temp->sig != NULL){
                temp = temp->sig;
            }
            temp->sig = nuevoMiembro;
        }
        clan->cantidadMiembros++;
    }
}

// Inserta un nuevo mazo al final de la lista simple.
// Valida ID único y que el jugador propietario exista en el sistema.
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

// Inserta un nuevo clan al final de la lista circular.
// Valida ID único y que los datos no sean negativos ni vacíos.
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

// Inserta una nueva arena al inicio de la lista simple.
// Valida ID único, que trofeosMin no sea mayor que trofeosMax,
// y que el rango no se solape con ninguna arena existente.
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

    //Validar que dos arenas no tengas los mismos rangos de trofeos
    Arenas *temp = primerArena;
    while(temp != NULL){
        if((tmin >= temp->trofeosMin && tmin <= temp->trofeosMax) || 
        (tmax >= temp->trofeosMin && tmax <= temp->trofeosMax) ||
        (tmin <= temp->trofeosMin && tmax >= temp->trofeosMax)){
            cout << "Error: El rango de trofeos se solapa con otra arena." << endl;
            return;
        }
        temp = temp->sig;
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

// Inserta una nueva batalla al final de la lista doble circular.
// Valida ID único, existencia de jugadores, arena y mazos, que los mazos pertenezcan
// a los jugadores correctos, que tengan 8 cartas, que el ganador sea uno de los dos jugadores
// y que las coronas estén en rango válido.
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

// Agrega una carta a la sublista de un mazo. Valida que el mazo exista, que la carta exista
// en el sistema, que el mazo no tenga ya 8 cartas y que la carta no esté repetida en el mazo.
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

// Agrega un jugador a la sublista de un clan. Valida que el clan y el jugador existan,
// que el jugador no pertenezca ya a otro clan y que no esté duplicado en la sublista.
// Actualiza el IDClan del jugador y el contador de miembros del clan.
void insertarJugadorEnClan(int IDClan, int IDJugador){
    // Verificar que el clan existe
    Clanes *clan = buscarClan(IDClan);
    if(clan == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    // Verificar que el jugador existe
    Jugadores *jugador = buscarJugador(IDJugador);
    if(jugador == NULL){
        cout << "Error: No existe un jugador con ese ID." << endl;
        return;
    }

    // Verificar que el jugador no esté en OTRO clan
    if(jugador->IDClan != 0){
        cout << "Error: El jugador ya pertenece a otro clan." << endl;
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

    // actualizar relación en el jugador
    jugador->IDClan = IDClan;

    clan->cantidadMiembros++;

    cout << "Jugador agregado al clan correctamente." << endl;
}


//MODIFICACIONES

// Solicita nuevos valores para todos los atributos de una carta existente.
// Valida rareza, tipo y que el costo de elixir no sea negativo.
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
    double nuevoDanio;

    cout << "Nuevo nombre: ";
    cin.ignore();
    getline(cin, nuevoNombre);
    cout << "Nueva rareza: ";
    getline(cin, nuevaRareza);
    cout << "Nuevo tipo: ";
    getline(cin, nuevoTipo);
    nuevoCosto = leerEntero("Nuevo costo de elixir: ", 1, 9);
    nuevoDanio = leerDouble("Nuevo dano base: ", 0, 99999);
    nuevaVida = leerEntero("Nueva vida base: ", 0, 99999);

    // Validar
    if(nuevoCosto < 0 || nuevoDanio < 0 || nuevaVida < 0){
        cout << "Error: No se permiten valores negativos." << endl;
        return;
    }

    // Convertir a minúsculas para comparar
    string rarezaLower = toLower(nuevaRareza);
    string tipoLower = toLower(nuevoTipo);


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
    temp->danioBase = nuevoDanio;
    temp->vidaBase = nuevaVida;

    cout << "Carta actualizada correctamente." << endl;
}

// Solicita nuevos valores para un jugador. Maneja el cambio de clan actualizando las sublistas
// correspondientes. Elimina y reinserta el nodo para mantener el orden alfabético de la lista.
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
    cin.ignore();
    getline(cin, nuevoNombre);

    nuevoNivelRey= leerEntero("Nuevo nivel del rey: ",1,90);//90 nivel max del rey
    nuevosTrofeos=leerEntero("Nuevos trofeos: ",1,14000);//nivel max de trofeos que se pueda tener
    nuevoIDArena=leerEntero("Nuevo ID de Arena: ",1,9999);
    nuevoIDClan=leerEntero("Nuevo ID del Clan (0=sin Clan alguno): ",0,9999);//desde 0 


    // Validar valores negativos
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

    // Validar que el clan exista (0 = sin clan, se permite)
    if(nuevoIDClan != 0 && buscarClan(nuevoIDClan) == NULL){
        cout << "Error: No existe un clan con ese ID." << endl;
        return;
    }

    // Validar trofeos con el rango de la arena
    if(nuevosTrofeos < arena->trofeosMin || nuevosTrofeos > arena->trofeosMax){
        cout << "Error: El número de trofeos no es compatible con la nueva arena." << endl;
        return;
    }

    // Manejo de cambio de clan: actualizar sublistas
    if(temp->IDClan != nuevoIDClan){
        // Quitar del clan anterior si tenía
        if(temp->IDClan != 0){
            Clanes *clanViejo = buscarClan(temp->IDClan);
            if(clanViejo != NULL){
                NodoJugadorClan *nj = clanViejo->listaJugadores;
                NodoJugadorClan *njAnt = NULL;
                while(nj != NULL){
                    if(nj->IDJugador == IDJ){
                        if(njAnt == NULL) clanViejo->listaJugadores = nj->sig;
                        else              njAnt->sig = nj->sig;
                        delete nj;
                        clanViejo->cantidadMiembros--;
                        break;
                    }
                    njAnt = nj;
                    nj = nj->sig;
                }
            }
        }
        // Agregar al nuevo clan si no es 0
        if(nuevoIDClan != 0){
            Clanes *clanNuevo = buscarClan(nuevoIDClan);
            if(clanNuevo != NULL){
                NodoJugadorClan *nuevoNodo = new NodoJugadorClan(IDJ);
                if(clanNuevo->listaJugadores == NULL){
                    clanNuevo->listaJugadores = nuevoNodo;
                } else {
                    NodoJugadorClan *ultimo = clanNuevo->listaJugadores;
                    while(ultimo->sig != NULL) ultimo = ultimo->sig;
                    ultimo->sig = nuevoNodo;
                }
                clanNuevo->cantidadMiembros++;
            }
        }
    }

    // Guardar el ID antes de eliminar el nodo
    int id = temp->IDJugador;

    // Eliminar de la lista para no romper el orden alfabético
    if(temp->ant != NULL) temp->ant->sig = temp->sig;
    else                  primerJugador = temp->sig;
    if(temp->sig != NULL) temp->sig->ant = temp->ant;
    delete temp;

    // Reinsertar con los nuevos datos en la posición correcta
    insertarJugador(id, nuevoNombre, nuevoNivelRey, nuevosTrofeos, nuevoIDArena, nuevoIDClan);

    cout << "Jugador actualizado correctamente." << endl;
}

// Solicita nuevo nombre y tipo para un mazo. Opcionalmente permite reemplazar una carta
// de la sublista, validando que la carta nueva exista y no esté ya en el mazo.
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

// Solicita nuevo nombre, región y puntaje para un clan. Opcionalmente permite reemplazar
// un jugador de la sublista, validando que el nuevo jugador no pertenezca ya a otro clan.
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

    nuevoNombreClan = leerString("Nuevo nombre del clan: ");
    nuevaRegion = leerString("Nueva region: ");
    nuevoPuntaje = leerDouble("Nuevo puntaje del clan: ", 0, 99999);

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

            Jugadores *nuevo = buscarJugador(IDJugadorNuevo);
            if(nuevo == NULL){
                cout << "Error: No existe ese jugador en el sistema." << endl;
            } else if(nuevo->IDClan != 0){
                // validar que no esté en otro clan
                cout << "Error: El jugador ya pertenece a otro clan." << endl;
            } else {
                // actualizar jugador viejo
                Jugadores *viejo = buscarJugador(IDJugadorViejo);
                if(viejo != NULL){
                    viejo->IDClan = 0;
                }

                //  asignar nuevo jugador
                tempJugador->IDJugador = IDJugadorNuevo;
                nuevo->IDClan = IDClan;

                cout << "Jugador reemplazado correctamente." << endl;
            }
        }
    }

    cout << "Clan actualizado correctamente." << endl;
}

// Solicita nuevo nombre y rangos de trofeos para una arena.
// Valida que el nuevo rango no se solape con ninguna otra arena existente.
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

    nuevoNombreArena = leerString("Nuevo nombre de la arena: ");
    nuevoTrofeosMin = leerEntero("Nuevo rango minimo de trofeos: ", 0, 15000);
    nuevoTrofeosMax = leerEntero("Nuevo rango maximo de trofeos: ", 0, 15000);

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

    //Validar que dos arenas no tengas los mismos rangos de trofeos
    Arenas *tempVal = primerArena;
    while(tempVal != NULL){
        if(tempVal->IDArena != IDA){ // saltar la arena actual
            if((nuevoTrofeosMin >= tempVal->trofeosMin && nuevoTrofeosMin <= tempVal->trofeosMax) || 
            (nuevoTrofeosMax >= tempVal->trofeosMin && nuevoTrofeosMax <= tempVal->trofeosMax) ||
            (nuevoTrofeosMin <= tempVal->trofeosMin && nuevoTrofeosMax >= tempVal->trofeosMax)){
                cout << "Error: El rango de trofeos se solapa con otra arena." << endl;
                return;
            }
        }
        tempVal = tempVal->sig;
    }

    // Asignar todo de una vez
    temp->nombreArena = nuevoNombreArena;
    temp->trofeosMin = nuevoTrofeosMin;
    temp->trofeosMax = nuevoTrofeosMax;

    cout << "Arena actualizada correctamente." << endl;
}

// Elimina una carta de la lista principal. 
void eliminarCarta(int IDCarta){
    Cartas *temp = primerCarta;
    Cartas *ant = NULL;

    // validar si la carta está en algún mazo
    Mazos *mazo = primerMazo;
    while(mazo != NULL){
        NodoCartaMazo *c = mazo->listaCartas;
        while(c != NULL){
            if(c->IDCarta == IDCarta){
                cout << "Error: No se puede eliminar la carta porque esta en uso en un mazo." << endl;
                return;
            }
            c = c->sig;
        }
        mazo = mazo->sig;
    }

    // Buscar la carta
    while(temp != NULL){
        if(temp->IDCarta == IDCarta){
            if(ant == NULL){
                primerCarta = temp->sig;
            } else {
                ant->sig = temp->sig;
            }
            delete temp;
            cout << "Carta eliminada correctamente." << endl;
            return;
        }
        ant = temp;
        temp = temp->sig;
    }

    cout << "Error: No se encontró una carta con ese ID." << endl;
}

// Elimina un mazo de la lista y libera la memoria de su sublista de cartas.
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

// Elimina un jugador de la lista doble. Primero lo remueve de su clan si pertenece a uno,
// luego elimina todos sus mazos en cascada, y finalmente ajusta los enlaces de la lista doble.
void eliminarJugador(int IDJ){
    Jugadores *temp = buscarJugador(IDJ);
    // Si no se encuentra el jugador
    if(temp == NULL){
        cout << "Error: No se encontró un jugador con ese ID." << endl;
        return;
    }

    // eliminarlo del clan si pertenece a uno
    if(temp->IDClan != 0){
        Clanes *clan = buscarClan(temp->IDClan);
        if(clan != NULL){
            NodoJugadorClan *act = clan->listaJugadores;
            NodoJugadorClan *ant = NULL;

            while(act != NULL){
                if(act->IDJugador == IDJ){
                    if(ant == NULL){
                        clan->listaJugadores = act->sig;
                    } else {
                        ant->sig = act->sig;
                    }
                    delete act;
                    clan->cantidadMiembros--;
                    break;
                }
                ant = act;
                act = act->sig;
            }
        }
    }

    // eliminar sus mazos
    Mazos *mazo = primerMazo;
    while(mazo != NULL){
        Mazos *sig = mazo->sig;
        if(mazo->IDJugador == IDJ){
            eliminarMazo(mazo->IDMazo);
        }
        mazo = sig;
    }

    // Ajustar los enlaces de la lista doblemente enlazada
    if(temp->ant != NULL) temp->ant->sig = temp->sig;
    else                  primerJugador = temp->sig;

    if(temp->sig != NULL) temp->sig->ant = temp->ant;

    delete temp;
    cout << "Jugador eliminado correctamente." << endl;
}

// Elimina un clan de la lista circular. Ajusta el enlace del nodo anterior para mantener
// la circularidad y libera la memoria de su sublista de jugadores.
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

// Elimina una arena de la lista simple reconectando los nodos vecinos.
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

// Elimina una batalla de la lista doble circular. Si es el único nodo deja la lista vacía,
// de lo contrario reconecta los enlaces sig y ant de los nodos vecinos.
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

// Elimina una carta específica de la sublista de un mazo y decrementa el contador de cartas.
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

// Elimina un jugador específico de la sublista de un clan y decrementa el contador de miembros.
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

// Carga automáticamente al inicio del programa al menos 10 registros por cada entidad principal
// mediante datos definidos directamente en código, sin lectura de archivos externos.
// El orden de carga es: arenas → cartas → clanes → jugadores → asignación a clanes → mazos → batallas.
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
    insertarArena(10, "Liga de Oro", 3000, 10000);

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
    insertarJugador(1, "Alejandro", 10, 2400, 8, 0);
    insertarJugador(2, "Beatriz", 8, 1700, 6, 0);
    insertarJugador(3, "Carlos", 12, 3100, 10, 0);
    insertarJugador(4, "Diana", 9, 2100, 7, 0);
    insertarJugador(5, "Eduardo", 11, 2800, 9, 0);
    insertarJugador(6, "Fernanda", 7, 1400, 5, 0);
    insertarJugador(7, "Gabriel", 13, 3500, 10, 0);
    insertarJugador(8, "Helena", 6, 900, 3, 0);
    insertarJugador(9, "Ivan", 10, 2300, 8, 0);
    insertarJugador(10, "Julia", 8, 1600, 6, 00);

    // ===== ASIGNAR JUGADORES A CLANES =====
    insertarJugadorEnClan(3, 1);  // Alejandro -> Legion Dorada
    insertarJugadorEnClan(2, 2);  // Beatriz -> Guerreros del Sur
    insertarJugadorEnClan(1, 3);  // Carlos -> Dragones del Norte
    insertarJugadorEnClan(4, 4);  // Diana -> Furia Barbara
    insertarJugadorEnClan(7, 5);  // Eduardo -> Caballeros Reales
    insertarJugadorEnClan(6, 6);  // Fernanda -> Guardianes del Hielo
    insertarJugadorEnClan(5, 7);  // Gabriel -> Sombras Eternas
    insertarJugadorEnClan(9, 8);  // Helena -> Guardianes del Hielo
    insertarJugadorEnClan(10, 9); // Ivan -> Alianza Suprema
    insertarJugadorEnClan(8, 10);  // Julia -> Tormenta Arcana

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
    // Las batallas precargadas usan 0 en estadísticas porque son datos históricos.
    // Las batallas nuevas se registran con estadísticas reales desde simularBatalla().
    insertarBatalla(1, 1, 2, 1, 2, "Alejandro", 3, 1, 2.5f, 8, "2026-04-01", 0,0,"","",0,0);
    insertarBatalla(2, 3, 4, 3, 4, "Carlos", 2, 0, 3.1f, 9, "2026-04-02", 0,0,"","",0,0);
    insertarBatalla(3, 5, 6, 5, 6, "Eduardo", 3, 2, 2.8f, 8, "2026-04-03", 0,0,"","",0,0);
    insertarBatalla(4, 7, 8, 7, 8, "Gabriel", 3, 0, 1.9f, 10, "2026-04-04", 0,0,"","",0,0);
    insertarBatalla(5, 9, 10, 9, 10, "Ivan", 2, 1, 2.3f, 7, "2026-04-05", 0,0,"","",0,0);
    insertarBatalla(6, 2, 3, 2, 3, "Carlos", 1, 3, 3.5f, 9, "2026-04-06", 0,0,"","",0,0);
    insertarBatalla(7, 4, 5, 4, 5, "Eduardo", 0, 3, 2.7f, 8, "2026-04-07", 0,0,"","",0,0);
    insertarBatalla(8, 6, 7, 6, 7, "Gabriel", 1, 3, 2.1f, 10, "2026-04-08", 0,0,"","",0,0);
    insertarBatalla(9, 8, 9, 8, 9, "Ivan", 2, 3, 3.0f, 7, "2026-04-09", 0,0,"","",0,0);
    insertarBatalla(10, 1, 10, 1, 10, "Alejandro", 3, 2, 2.6f, 8, "2026-04-10", 0,0,"","",0,0);
    
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
double calcularDanioTotal(Mazos* mazo) {
    double total = 0;
    NodoCartaMazo* temp = mazo->listaCartas;
    while (temp != NULL) {
        Cartas* carta = buscarCarta(temp->IDCarta);
        if (carta != NULL) {
            total += carta->danioBase;
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
    double danioJ1=calcularDanioTotal(m1);
    double danioJ2=calcularDanioTotal(m2);

    // Poder defensivo: suma de vida de las 8 cartas
    int vidaJ1=calcularVidaTotal(m1);
    int vidaJ2=calcularVidaTotal(m2);

    // Costo promedio de elixir
    double elixirJ1=calcularPromedioElixir(m1);
    double elixirJ2=calcularPromedioElixir(m2);

    // Tipo predominante del mazo
    string tipoJ1 = calcularTipoPredominante(m1);
    string tipoJ2 = calcularTipoPredominante(m2);

    // Ciclos de elixir estimados
    double ciclosJ1= calcularConsumoDElixir(m1);
    double ciclosJ2= calcularConsumoDElixir(m2);

    /* ================================================================
    // ENCOnTRAR GANADOR
    // poderJ=dañoPropio-(vidaRival * 0.3) tiene qye haber un 30% de daño hacaia el otro 
    el.3 sería la defensa que lo afecta del otro jugador */
    double poderJ1=danioJ1-(vidaJ2 * 0.3);
    double poderJ2=danioJ2-(vidaJ1 * 0.3);

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
    cout << "  Danio total del mazo   : " << danioJ1 << endl;//uso de Danio en vez de daño por impresion en terminal
    cout << "  Vida total del mazo   : " << vidaJ1 << endl;
    cout << "  Promedio de elixir    : " << elixirJ1 << endl;
    cout << "  Tipo predominante     : " << tipoJ1 << endl;
    cout << "  Ciclos de elixir est. : " << ciclosJ1 << endl;
    cout << "  Poder calculado       : " << poderJ1 << endl;

    cout << "\n[JUGADOR 2] " << j2->nombreUsuario << " - Mazo: " << m2->nombreMazo << endl;
    cout << "  Danio total del mazo   : " << danioJ2 << endl;
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
        opcion = leerEntero("Seleccione una opcion: ",1,3);


        switch (opcion) {
            case 1: {
                cout << "\n--- Simular Batalla ---" << endl;
                int idJ1, idJ2, idM1, idM2, idArena;
                string fecha;

                idJ1=leerEntero("ID del jugador 1: ", 1, 99999);
                idJ2=leerEntero("ID del jugador 2: ", 1,99999);
                idM1=leerEntero("ID del mazo del jugador 1: ", 1,99999);
                idM2=leerEntero("ID del mazo del jugador 2: ", 1,99999);
                idArena=leerEntero("ID de la arena: ", 1,99999);
                fecha=leerString("Fecha (AAAA-MM-DD): ");
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


// CONSULTAS


// Recorre todas las cartas y cuenta en cuántos mazos aparece cada una,
// retornando el nombre de la carta con mayor cantidad de apariciones.
void consultaCartaMasUsada() {
    cout << "\n=== Carta mas utilizada en mazos ===" << endl;

    if (!primerCarta) {
        cout << "  No hay cartas registradas." << endl;
        return;
    }

    int mejorID = -1, mejorCont = 0;
    Cartas *c = primerCarta;

    // recorrer todas las cartas
    while (c) {
        int cont = 0;
        Mazos *m = primerMazo;

        // contar en cuantos mazos aparece
        while (m) {
            NodoCartaMazo *nc = m->listaCartas;
            while (nc) {
                if (nc->IDCarta == c->IDCarta) cont++;
                nc = nc->sig;
            }
            m = m->sig;
        }

        // actualizar mejor
        if (cont > mejorCont) {
            mejorCont = cont;
            mejorID = c->IDCarta;
        }

        c = c->sig;
    }

    if (mejorID == -1 || mejorCont == 0) {
        cout << "  Ninguna carta esta en algun mazo." << endl;
        return;
    }

    Cartas *res = buscarCarta(mejorID);
    if (res) {
        cout << "  Carta: " << res->Nombre << " (ID: " << res->IDCarta << ")" << endl;
        cout << "  Aparece en " << mejorCont << " mazo(s)." << endl;
    }
}


// Recorre la lista de jugadores y retorna el que tenga el mayor valor de trofeos.

void consultaJugadorMasTrofeos() {
    cout << "\n=== Jugador con mas trofeos ===" << endl;

    if (!primerJugador) {
        cout << "  No hay jugadores registrados." << endl;
        return;
    }

    Jugadores *mejor = primerJugador;
    Jugadores *t = primerJugador->sig;

    while (t) {
        if (t->trofeos > mejor->trofeos)
            mejor = t;
        t = t->sig;
    }

    cout << "  Jugador : " << mejor->nombreUsuario << endl;
    cout << "  Trofeos : " << mejor->trofeos << endl;
}


// Recorre la lista circular de clanes y retorna el que tenga mayor cantidadMiembros.
void consultaClanMasMiembros() {
    cout << "\n=== Clan con mas miembros ===" << endl;

    if (!primerClan) {
        cout << "  No hay clanes registrados." << endl;
        return;
    }

    // caso: un solo nodo
    if (primerClan->sig == primerClan) {
        cout << "  Clan     : " << primerClan->nombreClan << endl;
        cout << "  Miembros : " << primerClan->cantidadMiembros << endl;
        return;
    }

    Clanes *mejor = primerClan;
    Clanes *t = primerClan->sig;

    while (t != primerClan) {
        if (t->cantidadMiembros > mejor->cantidadMiembros)
            mejor = t;
        t = t->sig;
    }

    cout << "  Clan     : " << mejor->nombreClan << endl;
    cout << "  Miembros : " << mejor->cantidadMiembros << endl;
}


// Recorre todos los mazos, calcula el promedio de elixir de cada uno sumando
// el costoElixir de sus cartas y retorna el mazo con el promedio más bajo.
void consultaMazoCostoMenor() {
    cout << "\n=== Mazo con menor costo promedio de elixir ===" << endl;

    if (!primerMazo) {
        cout << "  No hay mazos registrados." << endl;
        return;
    }

    Mazos *mejor = NULL;
    double menorProm = 999999;
    Mazos *m = primerMazo;

    while (m) {
        if (m->cantidadCartas > 0) {
            double suma = 0;
            NodoCartaMazo *nc = m->listaCartas;

            while (nc) {
                Cartas *c = buscarCarta(nc->IDCarta);
                if (c) suma += c->costoElixir;
                nc = nc->sig;
            }

            double prom = suma / m->cantidadCartas;
            if (prom < menorProm) {
                menorProm = prom;
                mejor = m;
            }
        }
        m = m->sig;
    }

    if (!mejor) {
        cout << "  Ningun mazo tiene cartas." << endl;
        return;
    }

    cout << "  Mazo   : " << mejor->nombreMazo << " (ID: " << mejor->IDMazo << ")" << endl;
    cout << "  Prom.  : " << menorProm << " de elixir" << endl;
}


// Recorre todas las arenas y para cada una cuenta cuántos jugadores tienen ese IDArena,
// retornando la arena con mayor cantidad de jugadores asociados.
void consultaArenaMasJugadores() {
    cout << "\n=== Arena con mas jugadores ===" << endl;

    if (!primerArena) {
        cout << "  No hay arenas registradas." << endl;
        return;
    }

    Arenas *mejor = NULL;
    int maxJ = -1;
    Arenas *a = primerArena;

    while (a) {
        int cnt = 0;
        Jugadores *j = primerJugador;

        while (j) {
            if (j->IDArena == a->IDArena) cnt++;
            j = j->sig;
        }

        if (cnt > maxJ) {
            maxJ = cnt;
            mejor = a;
        }

        a = a->sig;
    }

    if (!mejor) {
        cout << "  No se encontro arena." << endl;
        return;
    }

    cout << "  Arena    : " << mejor->nombreArena << " (ID: " << mejor->IDArena << ")" << endl;
    cout << "  Jugadores: " << maxJ << endl;
}


// Recorre todos los jugadores y para cada uno cuenta cuántas batallas tienen su nombre
// en el campo ganador, retornando el jugador con más victorias.
void consultaJugadorMasVictorias() {
    cout << "\n=== Jugador con mas victorias en batallas ===" << endl;

    if (!primerBatalla || !primerJugador) {
        cout << "  No hay suficientes datos." << endl;
        return;
    }

    Jugadores *mejor = NULL;
    int maxV = 0;
    Jugadores *j = primerJugador;

    while (j) {
        int wins = 0;
        Batallas *b = primerBatalla;

        do {
            if (b->ganador == j->nombreUsuario)
                wins++;
            b = b->sig;
        } while (b != primerBatalla);

        if (wins > maxV) {
            maxV = wins;
            mejor = j;
        }

        j = j->sig;
    }

    if (!mejor || maxV == 0) {
        cout << "  Ningun jugador tiene victorias registradas." << endl;
        return;
    }

    cout << "  Jugador  : " << mejor->nombreUsuario << endl;
    cout << "  Victorias: " << maxV << endl;
}


// Solicita un ID de arena y muestra todas las batallas cuyo IDArena coincida,
// mostrando jugadores, ganador y fecha de cada una.
void consultaBatallasPorArena() {
    cout << "\n=== Batallas por arena ===" << endl;

    int IDA;
    IDA = leerEntero("Ingrese el ID de la Arena: ", 1,99999);


    Arenas *a = buscarArena(IDA);
    if (!a) {
        cout << "  Error: No existe esa arena." << endl;
        return;
    }

    cout << "\n  Arena: " << a->nombreArena << endl;

    if (!primerBatalla) {
        cout << "  No hay batallas registradas." << endl;
        return;
    }

    bool encontrado = false;
    Batallas *b = primerBatalla;

    do {
        if (b->IDArena == IDA) {
            Jugadores *j1 = buscarJugador(b->IDJugador1);
            Jugadores *j2 = buscarJugador(b->IDJugador2);

            cout << "  Batalla #" << b->IDBatalla << " | "
                 << (j1 ? j1->nombreUsuario : "?") << " vs "
                 << (j2 ? j2->nombreUsuario : "?")
                 << " | Ganador: " << b->ganador
                 << " | Fecha: " << b->fecha << endl;

            encontrado = true;
        }
        b = b->sig;
    } while (b != primerBatalla);

    if (!encontrado)
        cout << "  No se encontraron batallas en esa arena." << endl;
}


// Solicita un ID de clan y recorre su sublista de jugadores mostrando
// el nombre y trofeos de cada miembro.
void consultaJugadoresDeClan() {
    cout << "\n=== Jugadores de un clan ===" << endl;

    int IDC;
    IDC = leerEntero("Ingrese el ID del Clan: ", 1,99999);

    Clanes *clan = buscarClan(IDC);
    if (!clan) {
        cout << "  Error: No existe ese clan." << endl;
        return;
    }

    cout << "\n  Clan: " << clan->nombreClan << endl;

    NodoJugadorClan *nj = clan->listaJugadores;
    if (!nj) {
        cout << "  Sin miembros registrados." << endl;
        return;
    }

    while (nj) {
        Jugadores *j = buscarJugador(nj->IDJugador);
        if (j) {
            cout << "  - " << j->nombreUsuario
                 << " (ID: " << j->IDJugador
                 << ", Trofeos: " << j->trofeos << ")" << endl;
        }
        nj = nj->sig;
    }
}



// Recorre la lista de cartas y muestra las que tienen rareza "legendaria",
// usando toLower para comparar sin distinción de mayúsculas.
void consultaCartasLegendarias() {
    cout << "\n=== Cartas de rareza Legendaria ===" << endl;

    bool encontrado = false;
    Cartas *c = primerCarta;

    while (c) {
        if (toLower(c->Rareza) == "legendaria") {
            cout << "  - " << c->Nombre
                 << " (ID: " << c->IDCarta
                 << ", Elixir: " << c->costoElixir << ")" << endl;
            encontrado = true;
        }
        c = c->sig;
    }

    if (!encontrado)
        cout << "  No hay cartas legendarias registradas." << endl;
}


// Solicita un ID de jugador y muestra todos los mazos cuyo IDJugador coincida,
// mostrando nombre, tipo y cantidad de cartas de cada mazo.
void consultaMazosDeJugador() {
    cout << "\n=== Mazos de un jugador ===" << endl;

    int IDJ;
    IDJ = leerEntero("Ingrese el ID deL mazo: ", 1,99999);

    Jugadores *j = buscarJugador(IDJ);
    if (!j) {
        cout << "  Error: No existe ese jugador." << endl;
        return;
    }

    cout << "\n  Jugador: " << j->nombreUsuario << endl;

    bool encontrado = false;
    Mazos *m = primerMazo;

    while (m) {
        if (m->IDJugador == IDJ) {
            cout << "  - " << m->nombreMazo
                 << " (ID: " << m->IDMazo
                 << ", Tipo: " << m->tipoMazo
                 << ", Cartas: " << m->cantidadCartas << "/8)" << endl;
            encontrado = true;
        }
        m = m->sig;
    }

    if (!encontrado)
        cout << "  Este jugador no tiene mazos registrados." << endl;
}

//REPORTES
// Muestra un listado resumido de todas las listas principales del sistema:
// cartas, jugadores, mazos, clanes, arenas y batallas.

void reporteTodasListas() {
    cout << "\n=== REPORTE: Todas las listas ===" << endl;

    // CARTAS
    cout << "\n CARTAS\n";
    Cartas *c = primerCarta;
    while (c) {
        cout << c->Nombre << " | Elixir: " << c->costoElixir << "\n";
        c = c->sig;
    }

    // JUGADORES
    cout << "\n JUGADORES\n";
    Jugadores *j = primerJugador;
    while (j) {
        cout << j->nombreUsuario << " | Trofeos: " << j->trofeos << "\n";
        j = j->sig;
    }

    // MAZOS
    cout << "\n MAZOS\n";
    Mazos *m = primerMazo;
    while (m) {
        cout << m->nombreMazo << " | Cartas: " << m->cantidadCartas << "\n";
        m = m->sig;
    }

    // CLANES (lista circular)
    cout << "\n CLANES\n";
    if (primerClan) {
        Clanes *cl = primerClan;
        do {
            cout << cl->nombreClan << " | Miembros: " << cl->cantidadMiembros << "\n";
            cl = cl->sig;
        } while (cl != primerClan);
    }

    // ARENAS
    cout << "\n ARENAS\n";
    Arenas *a = primerArena;
    while (a) {
        cout << a->nombreArena << "\n";
        a = a->sig;
    }

    // BATALLAS (lista doble circular)
    cout << "\n BATALLAS\n";
    if (primerBatalla) {
        Batallas *b = primerBatalla;
        do {
            cout << "Batalla " << b->IDBatalla << " | Ganador: " << b->ganador << "\n";
            b = b->sig;
        } while (b != primerBatalla);
    }
}


// Muestra cada jugador con su arena, clan y lista de mazos asociados,
// buscando las relaciones por ID en sus respectivas listas.
void reporteDetalleJugadores() {
    cout << "\n=== REPORTE: Detalle jugadores ===" << endl;

    Jugadores *j = primerJugador;

    while (j) {
        // Buscar relaciones
        Arenas *a = buscarArena(j->IDArena);
        Clanes *cl = buscarClan(j->IDClan);

        cout << "\nJugador: " << j->nombreUsuario << "\n";
        cout << "Arena: " << (a ? a->nombreArena : "No") << "\n";
        cout << "Clan: " << (cl ? cl->nombreClan : "No") << "\n";

        // MAZOS DEL JUGADOR
        cout << "// MAZOS\n";
        Mazos *m = primerMazo;
        while (m) {
            if (m->IDJugador == j->IDJugador) {
                cout << "- " << m->nombreMazo << "\n";
            }
            m = m->sig;
        }

        j = j->sig;
    }
}


// Muestra cada mazo con el nombre de las cartas que contiene,
// recorriendo la sublista de cada mazo y buscando cada carta por ID.
void reporteMazosConCartas() {
    cout << "\n=== REPORTE: Mazos con cartas ===" << endl;

    Mazos *m = primerMazo;

    while (m) {
        cout << "\nMazo: " << m->nombreMazo << "\n";

        NodoCartaMazo *nc = m->listaCartas;

        // CARTAS DEL MAZO
        while (nc) {
            Cartas *c = buscarCarta(nc->IDCarta);
            if (c) cout << "- " << c->Nombre << "\n";
            nc = nc->sig;
        }

        m = m->sig;
    }
}


// Recorre la lista circular de clanes y para cada uno muestra sus miembros
// buscando cada jugador por ID en la sublista correspondiente.
void reporteClanesMiembros() {
    cout << "\n=== REPORTE: Clanes ===" << endl;

    if (!primerClan) return;

    Clanes *cl = primerClan;

    do {
        cout << "\nClan: " << cl->nombreClan << "\n";

        NodoJugadorClan *nj = cl->listaJugadores;

        // MIEMBROS
        while (nj) {
            Jugadores *j = buscarJugador(nj->IDJugador);
            if (j) cout << "- " << j->nombreUsuario << "\n";
            nj = nj->sig;
        }

        cl = cl->sig;
    } while (cl != primerClan);
}


// Recorre todas las arenas y para cada una muestra los jugadores
// cuyo IDArena coincide con el de la arena actual.
void reporteArenaJugadores() {
    cout << "\n=== REPORTE: Arenas ===" << endl;

    Arenas *a = primerArena;

    while (a) {
        cout << "\nArena: " << a->nombreArena << "\n";

        Jugadores *j = primerJugador;

        // JUGADORES EN ESA ARENA
        while (j) {
            if (j->IDArena == a->IDArena) {
                cout << "- " << j->nombreUsuario << "\n";
            }
            j = j->sig;
        }

        a = a->sig;
    }
}


// Recorre la lista doble circular de batallas y muestra el ID y ganador de cada una.
void reporteBatallas() {
    cout << "\n=== REPORTE: Batallas ===" << endl;

    if (!primerBatalla) return;

    Batallas *b = primerBatalla;

    do {
        cout << "\nBatalla: " << b->IDBatalla << "\n";
        cout << "Ganador: " << b->ganador << "\n";
        b = b->sig;
    } while (b != primerBatalla);
}


// Ordena las cartas de menor a mayor costo de elixir intercambiando datos entre nodos
// mediante el algoritmo de burbuja aplicado sobre la lista enlazada, luego las muestra.
void reporteCartasPorElixir() {
    cout << "\n=== REPORTE: Cartas ordenadas por elixir ===" << endl;

    Cartas *i = primerCarta;

    while (i) {
        Cartas *j = i->sig;

        while (j) {
            if (i->costoElixir > j->costoElixir) {
                // intercambio
                swap(i->IDCarta, j->IDCarta);
                swap(i->Nombre, j->Nombre);
                swap(i->Rareza, j->Rareza);
                swap(i->Tipo, j->Tipo);
                swap(i->costoElixir, j->costoElixir);
                swap(i->danioBase, j->danioBase);
                swap(i->vidaBase, j->vidaBase);
            }
            j = j->sig;
        }
        i = i->sig;
    }

    // MOSTRAR
    Cartas *c = primerCarta;
    while (c) {
        cout << c->Nombre << " | Elixir: " << c->costoElixir 
             << " | Daño: " << c->danioBase << " | Vida: " << c->vidaBase << "\n";
        c = c->sig;
    }
}
// Muestra los jugadores en orden alfabético. Como la lista se mantiene ordenada
// en tiempo de inserción, simplemente recorre y muestra sin necesidad de reordenar.
void reporteJugadoresAlfabetico() {
    cout << "\n=== REPORTE: Jugadores alfabetico ===" << endl;

    Jugadores *aux = primerJugador;

    if (aux == NULL) {
        cout << "No hay jugadores registrados." << endl;
        return;
    }

    // Como la inserción ya garantiza el orden, solo imprime
    while (aux != NULL) {
        cout << "Usuario: " << aux->nombreUsuario << " | Trofeos: " << aux->trofeos << endl;
        aux = aux->sig; 
    }
}


// Recorre la lista de jugadores y para cada uno cuenta cuántas batallas registradas
// tienen su nombre en el campo ganador, mostrando el conteo total de victorias.
void reporteBatallasPorJugador() {
    cout << "\n=== REPORTE: Victorias por jugador ===" << endl;

    Jugadores *j = primerJugador;

    while (j) {
        int wins = 0;

        if (primerBatalla) {
            Batallas *b = primerBatalla;
            do {
                if (b->ganador == j->nombreUsuario) wins++;
                b = b->sig;
            } while (b != primerBatalla);
        }

        cout << j->nombreUsuario << " -> " << wins << "\n";

        j = j->sig;
    }
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
        opcion = leerEntero("Seleccione una opcion: ", 1, 4);


        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Carta ---" << endl;
                int id, costo, vida;
                double danio;
                string nombre, rareza, tipo;

                id = leerEntero("ID de la carta: ", 0, 9999);//ponemoslimites hatsa 9999 para que no existan errores con letras o floats
                nombre = leerString("Nombre: ");
                rareza = leerString("Rareza (Comun/Rara/Epica/Legendaria): ");
                tipo = leerString("Tipo (Tropa/Hechizo/Edificio): ");
                costo = leerEntero("Costo de elixir: ", 1, 9);
                danio = leerDouble("Daño base: ", 0, 99999);//cambiamos daño por danio para mejor visualizacion en la terminal 
                vida = leerEntero("Vida base: ", 0, 99999);

                insertarCartas(id, nombre, rareza, tipo, costo, danio, vida);
                break;
            }
            case 2: {
                cout << "\n--- Modificar Carta ---" << endl;
                int id;
                id=leerEntero("ID de la carta a modificar: ", 0, 9999);
                modificarCarta(id);
                break;
            }
            case 3: {
                cout << "\n--- Eliminar Carta ---" << endl;
                int id;
                id=leerEntero("ID de la carta a eliminar: ", 0, 9999);
                eliminarCarta(id);
                break;
            }
            case 4:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion!=4);
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
        opcion = leerEntero("Seleccione una opcion: ", 1, 4);


        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Jugador ---" << endl;
                int id, nivel, trofeos, idArena, idClan;
                string nombre;

                id = leerEntero("ID del jugador: ", 0, 9999);
                nombre = leerString("Nombre de usuario: ");
                nivel = leerEntero("Nivel del rey (1-15): ", 1, 15);
                trofeos = leerEntero("Trofeos: ", 0, 10000);
                idArena = leerEntero("ID de arena: ", 1, 10); //segun la arena
                idClan = leerEntero("ID de clan (0 = sin clan): ", 0, 10);

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
        opcion = leerEntero("Seleccione una opcion: ",1,6);


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
        opcion = leerEntero("Seleccione una opcion: ",1,6);


        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Clan ---" << endl;
                int id, miembros;
                double puntaje;
                string nombre, region;


                id = leerEntero("ID del clan:  ", 0, 9999);
                nombre = leerString("Nombre del clan: ");
                region = leerString("Region: ");
                miembros = leerEntero("Cantidad de miembros: ", 0, 9999);
                puntaje = leerDouble("Puntaje del clan: ",1,99999);   

                insertarClan(id, nombre, region, miembros,puntaje);
                break;
            }
            case 2: {
                cout << "\n--- Agregar Jugador a Clan ---" << endl;
                int idClan, idJugador;
                idClan = leerEntero("ID del clan:  ", 0, 9999);
                idJugador = leerEntero("ID del Jugador:  ", 0, 9999);
                insertarJugadorEnClan(idClan, idJugador);
                break;
            }
            case 3: {
                cout << "\n--- Modificar Clan ---" << endl;
                int id;
                id = leerEntero("ID del clan a modificar:  ", 0, 9999);
                modificarClan(id);
                break;
            }
            case 4: {
                cout << "\n--- Eliminar Clan ---" << endl;
                int id;
                id = leerEntero("ID del clan a eliminar:  ", 0, 9999);
                eliminarClan(id);
                break;
            }
            case 5: {
                cout << "\n--- Eliminar Jugador de Clan ---" << endl;
                int idClan, idJugador;
                idClan = leerEntero("ID del clan del jugador:  ", 0, 9999);
                idJugador = leerEntero("ID del Jugador a eliminar:  ", 0, 9999);
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
        opcion = leerEntero("Seleccione una opcion: ",1,6);


        switch (opcion) {
            case 1: {
                cout << "\n--- Insertar Arena ---" << endl;
                int id, tmin, tmax;
                string nombre;
                id = leerEntero("ID de la Arena:  ", 0, 99999);
                nombre = leerString("Nombre de la Arena: ");
                tmin = leerEntero("Trofeos minimos:  ", 0, 15000);
                tmax = leerEntero("Trofeos maximos  ", 0, 15000);
                insertarArena(id, nombre, tmin, tmax);
                break;
            }
            case 2: {
                cout << "\n--- Modificar Arena ---" << endl;
                int id;
                id = leerEntero("ID de la Arena a modificar:  ", 0, 99999);
                modificarArena(id);
                break;
            }
            case 3: {
                cout << "\n--- Eliminar Arena ---" << endl;
                int id;
                id = leerEntero("ID de la Arena a eliminar:  ", 0, 99999);
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
        opcion =leerEntero("Seleccione una opcion: ",1,3);


        switch (opcion) {
            case 1: {
                cout << "\n--- Registrar Batalla ---" << endl;
                int id, idJ1, idJ2, idM1, idM2, cJ1, cJ2, idArena;
                float duracion;
                string ganador, fecha;

                id = leerEntero("ID de la batalla: ", 0, 9999);
                idJ1 = leerEntero("ID jugador 1: ", 0, 9999);
                idJ2 = leerEntero("ID jugador 2: ", 0, 9999);
                idM1 = leerEntero("ID mazo jugador 1: ", 0, 9999);
                idM2 = leerEntero("ID mazo jugador 2: ", 0, 9999);
                ganador = leerString("Nombre del ganador: ");
                cJ1 = leerEntero("Coronas jugador 1 (0-3): ", 0, 3);
                cJ2 = leerEntero("Coronas jugador 2 (0-3): ", 0, 3);
                duracion = (float)leerDouble("Duracion (minutos): ", 0, 10.0);
                idArena = leerEntero("ID de arena: ", 0, 9999);
                fecha = leerString("Fecha (AAAA-MM-DD): ");

                insertarBatalla(id, idJ1, idJ2, idM1, idM2, ganador, cJ1, cJ2, duracion, idArena, fecha, 0,0,"","",0,0);
                break;

                
            }
            case 2: {
                cout << "\n--- Eliminar Batalla ---" << endl;
                int id;
                id = leerEntero("ID de la batalla a eliminar: ", 0, 9999);
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

// Menú de reportes. Permite al usuario seleccionar entre los 9 reportes disponibles
// del sistema y navegar de regreso al menú principal.
void menuReportes() {
    int op;
    do {
        cout << "\n     REPORTES\n";
        cout << "1. Todas las listas\n";
        cout << "2. Detalle jugadores\n";
        cout << "3. Mazos con cartas\n";
        cout << "4. Clanes con miembros\n";
        cout << "5. Arenas con jugadores\n";
        cout << "6. Batallas\n";
        cout << "7. Cartas por elixir\n";
        cout << "8. Jugadores alfabetico\n";
        cout << "9. Victorias por jugador\n";
        cout << "10. Volver\n";
        op= leerEntero("Seleccione una opcion: ",1,10);

        

        switch(op) {
            case 1: reporteTodasListas(); break;
            case 2: reporteDetalleJugadores(); break;
            case 3: reporteMazosConCartas(); break;
            case 4: reporteClanesMiembros(); break;
            case 5: reporteArenaJugadores(); break;
            case 6: reporteBatallas(); break;
            case 7: reporteCartasPorElixir(); break;
            case 8: reporteJugadoresAlfabetico(); break;
            case 9: reporteBatallasPorJugador(); break;
            case 10: break;
            default: cout << "Opcion invalida\n"; break;
        }

    } while(op != 10);
}


// Menú de consultas. Permite al usuario seleccionar entre las 10 consultas disponibles
// del sistema y navegar de regreso al menú principal.
void menuConsultas() {
    int op;
    do {
        cout << "\n       CONSULTAS\n";
        cout << "1.  Carta mas usada en mazos\n";
        cout << "2.  Jugador con mas trofeos\n";
        cout << "3.  Clan con mas miembros\n";
        cout << "4.  Mazo con menor costo de elixir\n";
        cout << "5.  Arena con mas jugadores\n";
        cout << "6.  Jugador con mas victorias\n";
        cout << "7.  Batallas por arena\n";
        cout << "8.  Jugadores de un clan\n";
        cout << "9.  Cartas legendarias\n";
        cout << "10. Mazos de un jugador\n";
        cout << "11. Volver\n";
        op=leerEntero("Seleccione una opcion: ",1,11);


        switch(op) {
            case 1:  consultaCartaMasUsada();       break;
            case 2:  consultaJugadorMasTrofeos();   break;
            case 3:  consultaClanMasMiembros();     break;
            case 4:  consultaMazoCostoMenor();      break;
            case 5:  consultaArenaMasJugadores();   break;
            case 6:  consultaJugadorMasVictorias(); break;
            case 7:  consultaBatallasPorArena();    break;
            case 8:  consultaJugadoresDeClan();     break;
            case 9:  consultaCartasLegendarias();   break;
            case 10: consultaMazosDeJugador();      break;
            case 11: break;
            default: cout << "Opcion invalida\n";  break;
        }

    } while(op != 11);
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
        opcion=leerEntero("Seleccione una opcion: ",1,7);


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
        opcion = leerEntero("Seleccione una opcion: ", 1, 5);


        switch (opcion) {
            case 1: menuMantenimiento(); break;
            case 2: menuConsultas(); break;     
            case 3: menuReportes(); break;
            case 4: menuSimulacion(); break;
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
