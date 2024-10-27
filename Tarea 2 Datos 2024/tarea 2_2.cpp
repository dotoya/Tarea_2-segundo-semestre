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

    void ordenar (){
        lNodo* curr = head;
        while(curr != nullptr){
            lNodo* temp = curr;
            curr = curr->sig;

            cout<<"antes "<< temp->val->nombre << " / " << temp->val->rating << " el siguiente nodo es " << curr->val->nombre << " / " << curr->val->rating<<endl;

            if(temp->val->rating < curr->val->rating){
                temp->sig = curr->sig;
                curr->sig = temp;
            
                cout<<"después "<< curr->val->nombre << " / "<< curr->val->rating << " el siguiente nodo es " << temp->val->nombre << " / "<< temp->val->rating<<endl;
            }
        }
    } // ordena la lista

    void calcular_rating_promedio(){
        float sum = 0;
        int can_rat = 0;
        lNodo* curr = head;
        while(curr != nullptr){
            sum += curr->val->rating;
            can_rat++;
            curr = curr->sig;
        }

        float rat_prom = (sum/can_rat);

        cout<<"el rating promedio del director "<< head->val->director << " es de "<<rat_prom<<endl; 
    }

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

    void encontrar_pelicula(string peli){
        lNodo* curr = head;
        while (curr != nullptr) {
            if(curr->val->nombre==peli){
                cout << curr->val->nombre << "/" << curr->val->director << "/ "<< curr->val->rating << endl;
                return;
            }
            curr = curr->sig;
        }
    }

    void mostrar_peliculas(){
        lNodo* curr = head;
        while (curr != nullptr) {
            cout << curr->val->nombre << "/ " << curr->val->rating << endl;
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
            }

            if(curr != nullptr){
                curr->val->agregar_pelicula(pelicula);
            }
        } 
        cout << "Insertada película: " << pelicula->nombre << " de " << pelicula->director << endl;
    };
    void copiar_arbol (){
        FC(root_1);
    }; // hace copia de arbol 1 en arbol 2 ordenado respecto de rating
    void FD(aNodo *Nodo, string dir){
        if(Nodo==nullptr)return;
        string a= Nodo->val->get_nombre();
        FD(Nodo->izq, dir);
        if(a==dir){
            Nodo->val->mostrar_peliculas();
        }
        FD(Nodo->der, dir);
    }

    void FP(aNodo *Nodo, string peli){
        if(Nodo==nullptr)return;
        FP(Nodo->izq, peli);
        Nodo->val->encontrar_pelicula(peli);
        FP(Nodo->der, peli);
    }

    void FC(aNodo *Nodo){
        if(Nodo==nullptr)return;
        copiar_a2(Nodo);
        FC(Nodo->izq);
        FC(Nodo->der);
    }

    void pre(aNodo *Nodo){
        if(Nodo==nullptr)return;
        cout<<Nodo->val->get_nombre()<<endl;
        pre(Nodo->izq);
        pre(Nodo->der);
    }

    void contar_total(aNodo *Nodo, int *valor){
        if(Nodo==nullptr)return;
        *valor+=1;
        contar_total(Nodo->izq, valor);
        contar_total(Nodo->der, valor);
    }

    void ayuda_p(aNodo *Nodo, int n, int &actual, int total){
        if(Nodo==nullptr)return;
        ayuda_p(Nodo->izq, n, actual, total);
        if (actual<n){
            cout<<"("<< total-actual <<")"<<Nodo->val->get_nombre()<<endl;
            actual+=1;
        }
        ayuda_p(Nodo->der, n, actual, total);
    }

    void ayuda_m(aNodo *Nodo, int n, int &actual){
        if(Nodo==nullptr)return;
        ayuda_m(Nodo->der, n, actual);
        if (actual<n){
            cout<<"("<< actual+1 <<")"<<Nodo->val->get_nombre()<<endl;
            actual+=1;
        }
        ayuda_m(Nodo->izq, n, actual);
    }

    void copiar_a2 (aNodo* aprev ){
        /*puede que haya un error al llamar a un director que ya haya salido ingresado en el arbol*/
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
        nuevoNodo->val->calcular_rating_promedio();
    };

    Director* buscar_director ( string director ){
        string dir= " "+director+" ";
        FD(root_1, dir);
    } ; // retorna arreglo de peliculas
    Pelicula* buscar_pelicula ( string pelicula ){
        int actual= 0;
        pelicula+= " ";
        FP(root_1, pelicula);
    } ; // retorna peliculas 3
    void mejores_directores ( int n ){
        int *b;
        b= new int(0);
        ayuda_m(root_2,n,*b);

    } ; // Muestra por pantalla los mejores n directores .Enumerando de 1 a n .
    void peores_directores ( int n ){
        int *valor;
        valor= new int(0);
        contar_total(root_2, valor);
        cout<<*valor<<endl;
        int lol= *valor;
        delete [] valor;
        cout<<n<<endl;
        int *a;
        a= new int(0);
        ayuda_p(root_2, n, *a, lol);
        delete[] a;

    } ; // Muestra por pantalla los peores n directores .Enumerando desde m ( cantidad de directores ) hasta m - n .
    void testing (){
        pre(root_2);
    }
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

    arbol.buscar_director("Martin Scorsese");
    arbol.buscar_pelicula("Arrival");
    arbol.copiar_arbol();
    arbol.testing();
    arbol.peores_directores(3);
    arbol.mejores_directores(3);




    delete[] l_p;
    delete[] pel;
    delete[] dir;
    delete[] rat;
    return 0;
};