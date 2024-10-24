/*#include <iostream>
#include <fstream>
#include<stdalign.h>
using namespace std;*/

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

    ~Director(){
        lNodo* aux;
        while (head) {
            aux = head;
            head = head->sig;
            delete aux->val; // libera la Pelicula
            delete aux; // libera el nodo
        }
    }

    void agregar_pelicula ( Pelicula* pelicula ){
        lNodo* nuevoNodo = new lNodo;
        nuevoNodo->val = new Pelicula;
        nuevoNodo->val->nombre = pelicula->nombre;
        nuevoNodo->val->director = pelicula->director;
        nuevoNodo->val->rating = pelicula->rating;
        nuevoNodo->sig = nullptr;

        if (head == nullptr){
            head = nuevoNodo;
            tail = nuevoNodo;
        } 
        else{
            tail->sig = nuevoNodo;
            tail = nuevoNodo;
        }

        size++;
        cout << "Se a agregado " << nuevoNodo->val->nombre << " de " << nuevoNodo->val->director << endl; //eliminar despés

    } ; // agrega pelicula al final de la lista enlazada
    void ordenar () ; // ordena la lista
    void calcular_rating_promedio () ;
    void mostrar_peliculas();

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

    void eliminar_arbol(aNodo* nodo);

    void insertar_pelicula (Pelicula* pelicula ){
        /*puede que haya un error al llamar a un director que ya haya salido ingresado en el arbol*/
        aNodo* nuevoNodo = new aNodo;
        nuevoNodo->val = new Director(pelicula->director.c_str()); // Convertir a const char*
        //nuevoNodo->val = new Director(pelicula->director);
        nuevoNodo->val->agregar_pelicula(pelicula);
        nuevoNodo->izq = nuevoNodo->der = nullptr;
        aNodo* aux = nullptr;

        if(root_1 == nullptr){
            root_1 = nuevoNodo;
        }
        else{
            curr_1 = root_1;
            bool flag = true;
            while(flag){
                aux = curr_1;
                string v_1_c = pelicula->director;
                string v_2_c = curr_1->val->get_nombre();
                int largo_aux;
                int largo_v1 = v_1_c.length();
                int largo_v2 = v_2_c.length();

                if(largo_v1>largo_v2){
                    largo_aux = largo_v1;
                }
                else{
                    largo_aux = largo_v2;
                }

                for (int i = 0; i < largo_aux; i++){
                    char x = v_1_c[i];
                    char y = v_2_c[i];
                    const char* punteroConst_1 = &x;
                    const char* punteroConst_2 = &y;

                    if(strcmp(punteroConst_1,punteroConst_2) != 0){
                        if(strcmp(punteroConst_1,punteroConst_2) < 0){
                            curr_1 = curr_1->izq;
                            if(curr_1 == nullptr){
                                aux->izq = nuevoNodo;
                                flag = false; /*rompe el while, dado que ya se inserto el nuevo dato*/
                            }
                        }
                        else{
                            curr_1 = curr_1->der;
                            if(curr_1 == nullptr){
                                aux->der = nuevoNodo;
                                flag = false; /*rompe el while, dado que ya se inserto el nuevo dato*/
                            }
                        }
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
    con = new Pelicula[t_p];
    for(int u = 0; u<(t_p);u++){
        con[u].nombre= pel[u];
        con[u].director= dir[u];
        con[u].rating= rat[u];
    }

    /*Arboles arbol;
    for(int i = 0; i< t_p; i++){
        arbol.insertar_pelicula(&con[i]);
    }*/


    /*insertar_pelicula (Pelicula* pelicula )*/


    delete[] l_p;
    delete[] pel;
    delete[] dir;
    delete[] rat;
    return 0;
};