#include <iostream>
#include <cstdlib>
using namespace std;

#define T 2 //constante que define el valor de T en 3
//#define T 1 //árbol binario



struct BTreeNode{
    int keys[2*T-1]; //arreglo para almacenar hasta 2*T-1 claves en cada nodo
    BTreeNode* C[2*T]; //Arreglo de punteros hacia los hijos del nodo 
    int n; //Número actual de claves
    bool hoja; //indica si el nodo actual es o no una hoja
};

BTreeNode* initNode(bool hoja); //Inicializa un nuevo nodo del árbol
void insertNotFull(BTreeNode* x, int k); //inserta una clave en un nodo no lleno
void splitChild(BTreeNode* x, int i, BTreeNode *y); //divide el nodo hijo cuando el nodo está lleno
void insert(BTreeNode*& root, int k); //Insertar una calve en el árbol
void print(BTreeNode* root); //Imprime el contenido de un árbol

int main()
{
    /*BTreeNode prueba;
    cout<<"Claves: "<<sizeof(prueba.keys)/sizeof(prueba.keys[0])<<endl;
    cout<<"Hijos: "<<sizeof(prueba.C)/sizeof(prueba.C[0]);*/
    BTreeNode* root = nullptr;
    insert(root,10);
    insert(root,13);
    insert(root,5);
    
    print(root);
}

BTreeNode* initNode(bool hoja){
    //Inicializa un nuevo nodo del árbol
    return nullptr;
} 
void insertNotFull(BTreeNode* x, int k){
    //inserta una clave en un nodo no lleno
    
    
} 
void splitChild(BTreeNode* x, int i, BTreeNode *y){
    //divide el nodo hijo cuando el nodo está lleno | divide el hijo lleno (y) de un nodo (x)
    //Creamos un nuevo nodo que estara a la derecha del nodo (y)
    BTreeNode* z = initNode(y->hoja);
    z->n = T-1;
    // Copia las ultimas T-1 claves desde (y) hasta (z)
    for(int j=0; j<T-1; j++){
    	z->keys[j] = y->keys[j+t];	
	}
	//Si (y) no es una hoja, copia tambien en los ultimos T hijos de (y) a (z)
	
	if(!y->hoja){
		for(int j=0; j<T; j++){
			z->C[j]=y->C[j+T];
		}
	}
	//Reduce el numero de claves
} 
void insert(BTreeNode*& root, int k){ // K => es el valor del dato a ingresar
  //Insertar una clave k en el árbol  
  //si el árbol está vacío, crea un nuevo nodo raíz
  if(root=nullptr){
      root = initNode(true); // Se crea un nuevo nodo que es hoja
      root->keys[0] = k;//insertamos la clave en la primera componente (llave) del nodo
      root-> n = 1; // Establece el numero de claves del nodo 1
  }else{ // el arbol ya existe
      //si la raíz está llena, creamos un nuevo nodo, pero la altura del árbol crece
      if(root-> n ==2*T-1){
          BTreeNode* s = initNode(false); //creamos un nuevo nodo que no es hoja
          s->C[0] = root; //Hace que el nodo actual sea el hijo de este nuevo nodo
          splitChild(s,0,root); //Divide la raíz la anterior, que ahora será el hijo del nuevo nodo
      
      //Determinar en cuál de los nuevos hijos se insertará la nueva clave
      int i = 0;
      if(s->keys[0]<k){
          i++;
      }
      insertNotFull(s->C[i],k);
      root = s;
      }else{//si el nodo no está lleno
          insertNotFull(root,k); //inserta la clave en el mismo nodo cuando NO está lleno
      }
  }
} 
void print(BTreeNode* root){
    //Imprime el contenido de un árbol
} 
