#include <iostream>
#include <fstream>
#include<stdalign.h>
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

    void agregar_pelicula ( Pelicula* pelicula ){

    } ; // agrega pelicula al final de la lista enlazada
    void ordenar () ; // ordena la lista
    void calcular_rating_promedio () ;
    void mostrar_peliculas () ;
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

    Arboles () ; // constructor
    ~ Arboles () ; // destructor
    void insertar_pelicula (Pelicula* pelicula ){
        aNodo *nuevoNodo = new aNodo;
        nuevoNodo->val = new Director(pelicula.director);          //new Director(pelicula.director); new Director(pelicula[0].director);
        nuevoNodo->izq = nuevoNodo->der = nullptr;

        // Insertar la película en el director correspondiente
        if (root_1 == nullptr){
            root_1 = nuevoNodo;
        }
        else{
            aNodo *curr_1 = root_1;
            aNodo *parent = nullptr;

            while (curr_1 != nullptr){
                parent = curr_1;
                if (strcmp(curr_1->val->get_nombre(), pelicula[0].director) < 0){
                    curr_1 = curr_1->der;
                }
                else{
                    curr_1 = curr_1->izq;
                }
            }

            // Insertar el nuevo nodo
            if (strcmp(parent->val->get_nombre(), pelicula[0].director) < 0){
                parent->der = nuevoNodo;
            }
            else{
                parent->izq = nuevoNodo;
            }
        }

        // Agregar la película al director
        buscar_director(pelicula[0].director)->agregar_pelicula(pelicula);
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
    t_p= stoi(ph);

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

    cout<<l_p[0]<<endl;
    cout<<l_p[1]<<endl;
    cout<<l_p[2]<<endl;

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
    cout<<pel[0]<<endl;
    cout<<pel[1]<<endl;
    cout<<pel[2]<<endl;
    cout<<dir[0]<<endl;
    cout<<dir[1]<<endl;
    cout<<dir[2]<<endl;
    cout<<rat[0]<<endl;
    cout<<rat[1]<<endl;
    cout<<rat[2]<<endl;

    Pelicula *con;
    Arboles arbol;
    con= new Pelicula[t_p];
    for(int u= 0; u<(t_p);u++){
        con[u].nombre= pel[u];
        con[u].director= dir[u];
        con[u].rating= rat[u];
    }
    arbol.insertar_pelicula(con);


    /*insertar_pelicula (Pelicula* pelicula )*/


    delete[] l_p;
    delete[] pel;
    delete[] dir;
    delete[] rat;
    return 0;
};