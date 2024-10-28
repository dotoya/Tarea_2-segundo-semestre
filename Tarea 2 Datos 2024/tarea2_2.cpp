#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Pelicula {
    string nombre ;
    string director ;
    float rating ;
};

class Director{
private :
    struct lNodo {
        Pelicula * val ;
        lNodo * sig ;
    };

    Director () ; // constructor
    ~ Director () ; // destructor
    lNodo * head ;
    lNodo * curr ;
    lNodo * tail ;
    size_t size ; // longitud lista
    string nombre_director ;

public:

/*****
* Director::Director(const char* nombre)
******
* Resumen Función
* Constructor de la clase Director que inicializa el nombre del director y establece la lista de películas como vacía.
******
* Input :
* const char* nombre : Nombre del director.
******
* Returns :
* void, No retorna valor.
**** */
    Director(const char* nombre) {
        nombre_director = nombre;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

/*****
* void Director::agregar_pelicula(Pelicula* pelicula)
******
* Resumen Función
* Agrega una película a la lista del director.
******
* Input :
* Pelicula* pelicula : Puntero a la estructura de la película a agregar.
******
* Returns :
* void, No retorna valor.
**** */
    void agregar_pelicula ( Pelicula* pelicula ){
        lNodo* nuevoNodo = new lNodo;
        nuevoNodo->val = pelicula;
        nuevoNodo->sig = head; // insertamos al principio
        head = nuevoNodo;
        size++;
    }

/*****
* void Director::ordenar()
******
* Resumen Función
* Ordena las películas de la lista del director según su rating.
******
* Input :
* No tiene.
******
* Returns :
* void, No retorna valor.
**** */
    void ordenar (){
        lNodo* curr = head;
        while(curr != nullptr){
            lNodo* temp = curr;
            curr = curr->sig;
            if(temp->val->rating < curr->val->rating){
                temp->sig = curr->sig;
                curr->sig = temp;
            }
        }
    } // ordena la lista

/*****
* float Director::devolver_rating()
******
* Resumen Función
* Calcula y devuelve el rating promedio de las películas del director.
******
* Input :
* No tiene.
******
* Returns :
* float, Rating promedio de las películas.
**** */
    float devolver_rating (){
        float sum = 0;
        int can_rat = 0;
        lNodo* curr = head;
        while(curr != nullptr){
            sum += curr->val->rating;
            can_rat++;
            curr = curr->sig;
        }

        float rat_prom = (sum/can_rat);
        return rat_prom; 
    }

/*****
* void Director::encontrar_pelicula(string peli)
******
* Resumen Función
* Busca una película en la lista del director y la muestra por pantalla.
******
* Input :
* string peli : Nombre de la película a buscar.
******
* Returns :
* void, No retorna valor.
**** */
    void encontrar_pelicula(string peli){
        lNodo* curr = head;
        while (curr != nullptr) {
            if(curr->val->nombre==peli){
                cout << curr->val->nombre << " / " << curr->val->director << " / "<< curr->val->rating << endl;
                return;
            }
            curr = curr->sig;
        }
    }

/*****
* void Director::mostrar_peliculas()
******
* Resumen Función
* Muestra todas las películas del director por pantalla.
******
* Input :
* No tiene.
******
* Returns :
* void, No retorna valor.
**** */
    void mostrar_peliculas(){
        lNodo* curr = head;
        while (curr != nullptr) {
            cout << curr->val->nombre << " / " << curr->val->rating << endl;
            curr = curr->sig;
        }
    }

/*****
* string Director::get_nombre()
******
* Resumen Función
* Devuelve el nombre del director.
******
* Input :
* No tiene.
******
* Returns :
* string, Nombre del director.
**** */
    string get_nombre(){
        return nombre_director;
    }
};

class Arboles {
private :
    struct aNodo {
        Director *val ;
        aNodo *izq ;
        aNodo *der ;
    };

    aNodo* root_1 ; // raiz arbol ordenado por directores
    aNodo* curr_1 ;
    size_t size_1 ; // el tammaño de un arbol es por la cantidad de niveles?
    aNodo* root_2 ; // raiz arbol ordenado por rating
    aNodo* curr_2 ;
    size_t size_2 ;
    
public :

/*****
* Arboles::Arboles()
******
* Resumen Función
* Constructor de la clase Arboles que inicializa el árbol de directores y el árbol de ratings.
******
* Input :
* No tiene.
******
* Returns :
* No retorna valor.
**** */
    Arboles(): root_1(nullptr), curr_1(nullptr), size_1(0), root_2(nullptr), curr_2(nullptr), size_2(0) {} // constructor

/*****
* Arboles::~Arboles()
******
* Resumen Función
* Destructor de la clase Arboles que libera la memoria de los árboles.
******
* Input :
* No tiene.
******
* Returns :
* No retorna valor.
**** */
    ~Arboles() {
        eliminar_arbol(root_1);
        eliminar_arbol(root_2);
    } // destructor

    
/*****
* void Arboles::eliminar_arbol(aNodo* nodo)
******
* Resumen Función
* Elimina un árbol de nodos comenzando desde el nodo dado.
******
* Input :
* aNodo* nodo : Puntero al nodo raíz del árbol a eliminar.
******
* Returns :
* void, No retorna valor.
**** */
    void eliminar_arbol(aNodo* nodo) {
        if (nodo != nullptr) {
            eliminar_arbol(nodo->izq);
            eliminar_arbol(nodo->der);
            delete nodo; // libera nodo
        }
    }

/*****
* void Arboles::insertar_pelicula(Pelicula* pelicula)
******
* Resumen Función
* Inserta una película en el árbol de directores.
******
* Input :
* Pelicula* pelicula : Puntero a la película a insertar.
******
* Returns :
* void, No retorna valor.
**** */
    void insertar_pelicula (Pelicula* pelicula ){
        aNodo* nuevoNodo = new aNodo;
        nuevoNodo->val = new Director(pelicula->director.c_str()); // Convertir a const char*
        nuevoNodo->val->agregar_pelicula(pelicula);
        nuevoNodo->izq = nuevoNodo->der = nullptr;

        if(root_1 == nullptr){
            root_1 = nuevoNodo;
        }
        else{
            aNodo* curr = root_1;
            aNodo* parent = nullptr;
            bool flag = true;
            while(flag && pelicula->director != curr->val->get_nombre()){
                parent = curr;
                string v_1_c = pelicula->director;
                string v_2_c = curr->val->get_nombre();

                if (v_1_c < v_2_c) {
                    curr = curr->izq;
                    if (curr == nullptr) {
                        parent->izq = nuevoNodo;
                        flag = false;

                    }
                } else {
                    curr = curr->der;
                    if (curr == nullptr) {
                        parent->der = nuevoNodo;
                        flag = false;
                    }
                }
                size_1++;
            }

            if(curr != nullptr){
                curr->val->agregar_pelicula(pelicula);
            }
        }
    };

/*****
* void Arboles::copiar_arbol()
******
* Resumen Función
* Realiza una copia del árbol de directores en otro árbol ordenado por rating.
******
* Input :
* No tiene.
******
* Returns :
* void, No retorna valor.
**** */
    void copiar_arbol (){
        FC(root_1);

    }; // hace copia de arbol 1 en arbol 2 ordenado respecto de rating

/*****
* void Arboles::FD(aNodo *Nodo, string dir)
******
* Resumen Función
* Busca y muestra las películas de un director específico en el árbol.
******
* Input :
* aNodo *Nodo : Nodo actual del árbol.
* string dir : Nombre del director a buscar.
******
* Returns :
* void, No retorna valor.
**** */
    void FD(aNodo *Nodo, string dir){
        if(Nodo==nullptr)return;
        string a= Nodo->val->get_nombre();
        FD(Nodo->izq, dir);
        if(a==dir){
            Nodo->val->mostrar_peliculas();
        }
        FD(Nodo->der, dir);
    }

/*****
* void Arboles::FP(aNodo *Nodo, string peli)
******
* Resumen Función
* Busca una película en el árbol y la muestra si se encuentra.
******
* Input :
* aNodo *Nodo : Nodo actual del árbol.
* string peli : Nombre de la película a buscar.
******
* Returns :
* void, No retorna valor.
**** */
    void FP(aNodo *Nodo, string peli){
        if(Nodo==nullptr)return;
        FP(Nodo->izq, peli);
        Nodo->val->encontrar_pelicula(peli);
        FP(Nodo->der, peli);
    }

/*****
* void Arboles::FC(aNodo *Nodo)
******
* Resumen Función
* Copia el árbol de directores en un segundo árbol ordenado por rating.
******
* Input :
* aNodo *Nodo : Nodo actual del árbol a copiar.
******
* Returns :
* void, No retorna valor.
**** */
    void FC(aNodo *Nodo){
        if(Nodo==nullptr)return;
        copiar_a2(Nodo);
        FC(Nodo->izq);
        FC(Nodo->der);
    }

/*****
* void Arboles::pre(aNodo *Nodo)
******
* Resumen Función
* Realiza un recorrido preorden del árbol y muestra los nombres de los directores.
******
* Input :
* aNodo *Nodo : Nodo actual del árbol.
******
* Returns :
* void, No retorna valor.
**** */
    void pre(aNodo *Nodo){
        if(Nodo==nullptr)return;
        cout<<Nodo->val->get_nombre()<<endl;
        pre(Nodo->izq);
        pre(Nodo->der);
    }

/*****
* void Arboles::contar_total(aNodo *Nodo, int *valor)
******
* Resumen Función
* Cuenta el total de nodos en el árbol.
******
* Input :
* aNodo *Nodo : Nodo actual del árbol.
* int *valor : Puntero a variable para acumular el conteo.
******
* Returns :
* void, No retorna valor.
**** */
    void contar_total(aNodo *Nodo, int *valor){
        if(Nodo==nullptr)return;
        *valor+=1;
        contar_total(Nodo->izq, valor);
        contar_total(Nodo->der, valor);
    }

/*****
* void Arboles::ayuda_p(aNodo *Nodo, int n, int &actual, int total)
******
* Resumen Función
* Ayuda en la enumeración de los peores n directores.
******
* Input :
* aNodo *Nodo : Nodo actual del árbol.
* int n : Número de directores a mostrar.
* int &actual : Contador actual.
* int total : Total de directores.
******
* Returns :
* void, No retorna valor.
**** */
    void ayuda_p(aNodo *Nodo, int n, int &actual, int total){
        if(Nodo==nullptr)return;
        ayuda_p(Nodo->izq, n, actual, total);
        if (actual<n){
            cout<<"("<< total-actual <<")"<<Nodo->val->get_nombre()<<endl;
            actual+=1;
        }
        ayuda_p(Nodo->der, n, actual, total);
    }

/*****
* void Arboles::ayuda_m(aNodo *Nodo, int n, int &actual)
******
* Resumen Función
* Ayuda en la enumeración de los mejores n directores.
******
* Input :
* aNodo *Nodo : Nodo actual del árbol.
* int n : Número de directores a mostrar.
* int &actual : Contador actual.
******
* Returns :
* void, No retorna valor.
**** */
    void ayuda_m(aNodo *Nodo, int n, int &actual){
        if(Nodo==nullptr){
            return;
        }

        ayuda_m(Nodo->der, n, actual);
        if (actual<n){
            cout<<"("<< actual+1 <<")"<<Nodo->val->get_nombre()<<endl;
            actual+=1;
        }
        ayuda_m(Nodo->izq, n, actual);
    }

/*****
* void Arboles::copiar_a2(aNodo* aprev)
******
* Resumen Función
* Copia un nodo del árbol anterior al nuevo árbol, ordenado por rating.
******
* Input :
* aNodo* aprev : Nodo a copiar del árbol original.
******
* Returns :
* void, No retorna valor.
**** */
    void copiar_a2 (aNodo* aprev ){
        aNodo* nuevoNodo = new aNodo;
        nuevoNodo->val = aprev->val; 
        nuevoNodo->izq = nuevoNodo->der = nullptr;

        if(root_2 == nullptr){
            root_2 = nuevoNodo;
        }
        else{
            aNodo* curr = root_2;
            aNodo* parent = nullptr;
            bool flag = true;
            while(flag && nuevoNodo->val->get_nombre() != curr->val->get_nombre()){
                parent = curr;
                string v_1_c = nuevoNodo->val->get_nombre();
                string v_2_c = curr->val->get_nombre();
                float r_1= nuevoNodo->val->devolver_rating();
                float r_2= curr->val->devolver_rating();

                if (r_1 < r_2) {
                    curr = curr->izq;
                    if (curr == nullptr) {
                        parent->izq = nuevoNodo;
                        flag = false;
                    }
                } else {
                    curr = curr->der;
                    if (curr == nullptr) {
                        parent->der = nuevoNodo;
                        flag = false;
                    }
                }
            }
        }
    };

/*****
* Director* Arboles::buscar_director(string director)
******
* Resumen Función
* Busca y devuelve las películas de un director específico.
******
* Input :
* string director : Nombre del director a buscar.
******
* Returns :
* Director*, Puntero a la estructura de director.
**** */
    Director* buscar_director ( string director ){
        string dir= director;
        FD(root_1, dir);
        return nullptr;
    } ; // retorna arreglo de peliculas

/*****
* Pelicula* Arboles::buscar_pelicula(string pelicula)
******
* Resumen Función
* Busca y devuelve la película específica en el árbol.
******
* Input :
* string pelicula : Nombre de la película a buscar.
******
* Returns :
* Pelicula*, Puntero a la estructura de película.
**** */
    Pelicula* buscar_pelicula ( string pelicula ){
        FP(root_1, pelicula);
        return nullptr;
    } ; // retorna peliculas 3

/*****
* void Arboles::mejores_directores(int n)
******
* Resumen Función
* Muestra los mejores n directores.
******
* Input :
* int n : Número de mejores directores a mostrar.
******
* Returns :
* void, No retorna valor.
**** */
    void mejores_directores ( int n ){
        int *b;
        b= new int(0);
        ayuda_m(root_2,n,*b);

    } ; // Muestra por pantalla los mejores n directores .Enumerando de 1 a n .

/*****
* void Arboles::peores_directores(int n)
******
* Resumen Función
* Muestra los peores n directores.
******
* Input :
* int n : Número de peores directores a mostrar.
******
* Returns :
* void, No retorna valor.
**** */
    void peores_directores ( int n ){
        int *valor;
        valor= new int(0);
        contar_total(root_2, valor);
        int lol= *valor;
        delete [] valor;
        int *a;
        a= new int(0);
        ayuda_p(root_2, n, *a, lol);
    } ; // Muestra por pantalla los peores n directores .Enumerando desde m ( cantidad de directores ) hasta m - n .

/*****
* void Arboles::testing()
******
* Resumen Función
* Función de prueba que muestra los nombres de los directores en preorden.
******
* Input :
* No tiene.
******
* Returns :
* void, No retorna valor.
**** */
    void testing (){
        pre(root_2);
    }
};

/*****
* int main()
******
* Resumen Función
* Función principal que carga películas desde un archivo, construye un árbol de directores, 
* y permite la interacción del usuario para buscar directores y películas.
******
* Input :
* No tiene.
******
* Returns :
* Código de salida del programa (0 si se ejecuta correctamente).
**** */
int main(){
    ifstream file;

    file.open("Peliculas.txt");

    if (!file.is_open()){
        cout<<"error al abrir el archivo"<<endl;
        exit(1);
    }

    int t_p;
    float *rat;
    string *l_p, *pel, *dir;
    string ph, pa;
    getline(file, ph);
    t_p = stoi(ph);

    l_p = new string[t_p];
    pel = new string[t_p];
    dir = new string[t_p];
    rat = new float[t_p];

    for(int z= 0; z<(t_p);z++){
        getline(file, ph);
        l_p[z] = ph;
        l_p[z] += ' ';
    }

    for(int c= 0; c<(t_p);c++){
        int posac= 0;
        pa= "";
        for(l_p[c][posac]; l_p[c][posac] != ';'; posac++){
            pel[c]+= l_p[c][posac];
        }
        posac+=1;
        for(l_p[c][posac]; l_p[c][posac] != ';'; posac++){
            dir[c]+= l_p[c][posac];
        }
        posac+=1;
        for(l_p[c][posac]; l_p[c][posac] != ' '; posac++){
            pa+= l_p[c][posac];
        }
        rat[c]= stof(pa);
    }

    Pelicula *con;
    con = new Pelicula[t_p];
    for(int u = 0; u<(t_p);u++){
        con[u].nombre= pel[u];
        con[u].director= dir[u];
        con[u].rating= rat[u];
    }

    Arboles arbol;
    for(int i = 0; i< t_p; i++){
        arbol.insertar_pelicula(&con[i]);
    }
    arbol.copiar_arbol();

    bool flag = true;
    while(flag){
        string input , acción , exacta;
        getline(cin,input);

        if(input == "e"){
            break;
        }

        size_t espacio_pos = input.find(' ');
        acción = input.substr(0,espacio_pos);
        exacta = input.substr(espacio_pos + 1);

        if(acción == "sd"){
            arbol.buscar_director(exacta);
        }

        if(acción == "sm"){
            arbol.buscar_pelicula(exacta);
        }

        if(acción == "br"){
            int n = stoi(exacta);
            arbol.mejores_directores(n);
        }

        if(acción == "wr"){
            int n = stoi(exacta);
            arbol.peores_directores(n);
        }
    }




    delete[] l_p;
    delete[] pel;
    delete[] dir;
    delete[] rat;
    return 0;
};