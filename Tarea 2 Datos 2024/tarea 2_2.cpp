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
    Director(const char* nombre) {
        nombre_director = nombre;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    /*~Director(){
        lNodo* curr = head;
        while (curr != nullptr) {
            lNodo* temp = curr;
            curr = curr->sig;
            delete temp;
        }
    }*/

    void agregar_pelicula ( Pelicula* pelicula ){
        lNodo* nuevoNodo = new lNodo;
        nuevoNodo->val = pelicula;
        nuevoNodo->sig = head; // insertamos al principio
        head = nuevoNodo;
        size++;
        cout << "Se ha agregado " << nuevoNodo->val->nombre << " de " << nuevoNodo->val->director << endl;
    } //añadir el tail con un if para la 1° iteración

    void ordenar () ; // ordena la lista
    void calcular_rating_promedio () ;

    void mostrar_peliculas(){
        lNodo* curr = head;
        while (curr != nullptr) {
            cout << curr->val->nombre << " / " << curr->val->rating << endl;
            curr = curr->sig;
        }
    }

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

    Arboles():root_1(nullptr), root_2(nullptr), size_1(0), size_2(0){}; // constructor

    ~Arboles() {
        eliminar_arbol(root_1);
        eliminar_arbol(root_2);
    } // destructor

    void eliminar_arbol(aNodo* nodo) {
        if (nodo != nullptr) {
            eliminar_arbol(nodo->izq);
            eliminar_arbol(nodo->der);
            //delete nodo->val; // libera Director
            delete nodo; // libera nodo
        }
    }

    void insertar_pelicula (Pelicula* pelicula ){
        /*puede que haya un error al llamar a un director que ya haya salido ingresado en el arbol*/
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
            while(flag){
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
            }
        }   
        cout << "Insertada película: " << pelicula->nombre << " de " << pelicula->director << endl;
    };
    void copiar_arbol (); // hace copia de arbol 1 en arbol 2 ordenado respecto de rating
    Director* buscar_director ( string director ) ; // retorna arreglo de peliculas
    Pelicula* buscar_pelicula ( string pelicula ) ; // retorna peliculas 3
    void mejores_directores ( int n ) ; // Muestra por pantalla los mejores n directores .Enumerando de 1 a n .
    void peores_directores ( int n ) ; // Muestra por pantalla los peores n directores .Enumerando desde m ( cantidad de directores ) hasta m - n .
};

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

    cout<<t_p<<endl;

    l_p = new string[t_p];
    pel = new string[t_p];
    dir = new string[t_p];
    rat = new float[t_p];

    for(int z= 0; z<(t_p);z++){
        getline(file, ph);
        l_p[z] = ph;
        l_p[z] += ' ';
    }

    /*cout<<l_p[0]<<endl;
    cout<<l_p[1]<<endl;
    cout<<l_p[2]<<endl;*/

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

    /*cout<<pel[0]<<endl;
    cout<<pel[1]<<endl;
    cout<<pel[2]<<endl;
    cout<<dir[0]<<endl;
    cout<<dir[1]<<endl;
    cout<<dir[2]<<endl;
    cout<<rat[0]<<endl;
    cout<<rat[1]<<endl;
    cout<<rat[2]<<endl;*/

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



    delete[] l_p;
    delete[] pel;
    delete[] dir;
    delete[] rat;
    return 0;
};