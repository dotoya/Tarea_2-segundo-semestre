#include <iostream>
#include <fstream>
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
        Director * val ;
        aNodo *izq ;
        aNodo *der ;
    };

    aNodo* root_1 ; // raiz arbol ordenado por directores
    aNodo* curr_1 ;
    size_t size_1 ;
    aNodo* root_2 ; // raiz arbol ordenado por rating
    aNodo* curr_2 ;
    size_t size_2 ;
public :

    Arboles () ; // constructor
    ~ Arboles () ; // destructor
    void insertar_pelicula (Pelicula* pelicula ){
        
    } ;
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
    exit(1);}
    int t_p=0;
    float *rat;
    string *l_p, *pel, *dir;
    string ph, pa; 

    for(int i=0;i<1;i++){
        getline(file, ph);
        t_p= stoi(ph);
    };
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
    con= new Pelicula[t_p];
    for(int u= 0; u<(t_p);u++){
        con[u].nombre= pel[u];
        con[u].director= dir[u];
        con[u].rating= rat[u];
    }
};