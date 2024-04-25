#include <iostream>
#include <cstdlib>
using namespace std;

#define T 2 //constante que define el valor de T en 3
//#define T 1 //Ã¡rbol binario 
//añadido
//Modificacion adicional

struct BTreeNode{
    int keys[2*T-1]; //arreglo para almacenar hasta 2*T-1 claves en cada nodo
    BTreeNode* C[2*T]; //Arreglo de punteros hacia los hijos del nodo 
    int n; //Número actual de claves
    bool hoja; //indica si el nodo actual es o no una hoja
};

BTreeNode* initNode(bool hoja); //Inicializa un nuevo nodo del Ã¡rbol
void insertNotFull(BTreeNode* x, int k); //inserta una clave en un nodo no lleno
void splitChild(BTreeNode* x, int i, BTreeNode *y); //divide el nodo hijo cuando el nodo estÃ¡ lleno
void insert(BTreeNode*& root, int k); //Insertar una calve en el Ã¡rbol
void print(BTreeNode* root, int space=0);

int main()
{
    /*BTreeNode prueba;
    cout<<"Claves: "<<sizeof(prueba.keys)/sizeof(prueba.keys[0])<<endl;
    cout<<"Hijos: "<<sizeof(prueba.C)/sizeof(prueba.C[0]);*/
    BTreeNode* root = nullptr;
    insert(root,10);
    insert(root,13);
    insert(root,5);
    insert(root,8);
    insert(root,11);
    insert(root,19);
    insert(root,-1);
    insert(root,34);
    insert(root,14);
    insert(root,100);
    insert(root,15);
    
    print(root);
}

BTreeNode* initNode(bool hoja){
    //Inicializa un nuevo nodo del Árbol
    BTreeNode* node = new BTreeNode; //crea un nuevo nodo
    node->hoja = hoja; //establece si el nuevo nodo es una hoja o no
    node->n=0;//cantidad inicial de claves del nodo (valores llenos)
    
    //Inicializamos todos los hijos del nodo en null
    for(int i=0; i<2*T; i++){
    	node->C[i]=nullptr;
	}
	return node; //Devuelve el nuevo nodo inicializado
} 
void insertNotFull(BTreeNode* x, int k){
    //inserta una clave en un nodo no lleno
    
    int i = x->n-1; //i contiene el índice del último elemento del nodo
    
    //Si el nodo en el que estamos es una hoja
    if(x->hoja){
    	//Mueve todas las claves mayores que el valor k una posición hacia adelante
    	//para crear un espacio para la nueva clave k
    	while(i>=0 && x->keys[i]>k){
    		x->keys[i+1] =  x->keys[i];
    		i--;
		}
		//Insertamos la nueva clave k en la posición correcta que encontramos
		x->keys[i+1] = k;
		//Incrementamos el contador de claves del nodo
		x->n++; //x->n = x->n+1;
	}else{ //si el nodo no es una hoja, encuentra el 
			//hijo que debe contener la clave
		while(i>=0 && x->keys[i]>k){
			i--; //retrocedemos hasta encontrar el índice correcto
		}
		//i+1 es el índice del hijo que podrá contener a la nueva clave k
		//comprobamos si este hijo está lleno
		if(x->C[i+1]->n==2*T-1){
			//si el hijo está lleno, debemos dividirlo
			splitChild(x,i+1,x->C[i+1]);
			//Después de dividir, el valor medio se sube 
			//y actualizamos el índice de inserción:
			if(k>x->keys[i+1]){
				i++;
			}
		}
		//Realiza la inserción recursiva
		insertNotFull(x->C[i+1],k);
	}
	
    
} 
void splitChild(BTreeNode* x, int i, BTreeNode *y){
    //divide el hijo lleno (y) de un nodo (x)
    //Creamos un nuevo nodo que estará a la derecha del nodo (y)
    BTreeNode* z = initNode(y->hoja);
    z->n = T-1;
    
    //Copia las últimas T-1 claves desde (y) hacia (z)
    for(int j=0; j<T-1; j++){
    	z->keys[j] = y->keys[j+T];
	}
	
	//Si (y) no es una hoja, copia también los ùltimos T hijos de (y) a (z)
	if(!y->hoja){
		for(int j=0; j<T; j++){
			z->C[j] = y->C[j+T];
		}
	}
	//Reduce el número de claves de (y)
	y->n = T-1;
	
	//Mueve los hijos de x para hacer espacio para el nuevo hijo (z)
	for(int j = x->n; j>= i+1; j--){
		x->C[j+1] = x->C[j];
	}
	//Enlaza el nuevo nodo (z) como hijo de (x)
	x->C[i+1] = z;
	
	//Mueve los valores(claves) de (x) para hacer espacio para la clave media 
	//de y
	
	for(int j = x->n-1; j>=i; j--){
		x->keys[j+1] = y->keys[j];
	}
	
	//subimos la clave media de (y) a su padre (x)
	x->keys[i] = y->keys[T-1];
	
	//Incrementamos el número de claves en c
	x->n++;
	//x->n = x-> n + 1;
	
} 
void insert(BTreeNode*& root, int k){
  //Insertar una clave k en el árrbol  
  //si el árbol está vaí, crea un nuevo nodo raíz
  if(root==nullptr){
      root = initNode(true); //Creamos un nuevo nodo que es hoja
      root->keys[0] = k; //insertamos la clave en la primera componente(llave)
      					//del nodo
      root-> n = 1; //Establece el número de claves del nodo en 1
  }else{//el árbol ya existe
      //si la raíz está llena, creamos un nuevo nodo, pero la altura del Ã¡rbol crece
      if(root-> n ==2*T-1){
          BTreeNode* s = initNode(false); //creamos un nuevo nodo que no es hoja
          s->C[0] = root; //Hace que el nodo actual sea el hijo de este nuevo nodo
          splitChild(s,0,root); //Divide la raÃ­z la anterior, que ahora serÃ¡ el hijo del nuevo nodo
      
      	   //Determinar en cuÃ¡l de los nuevos hijos se insertarÃ¡ la nueva clave
      	  int i = 0;
	      if(s->keys[0]<k){
	          i++;
	      }
	      insertNotFull(s->C[i],k);
	      root = s;
      }else{//si el nodo no está lleno
          insertNotFull(root,k); //inserta la clave en el mismo nodo cuando NO estÃ¡ lleno
    }
  }
}

void print(BTreeNode* root, int space){
    //Imprime el contenido de un árbol
    if(root!=nullptr){
    	//Incrementamos el contador de espacios para diferenciar los niveles
    	int count = space + 5;
    	//Llamamos recursivamente para imprimir el subárbol derecho
    	print(root->C[root->n],count);
    	
    	for(int i=root->n-1;i>=0; i--){
    		//Imprime espacios para diferenciar los niveles:
    		cout<<endl;
    		for(int j=0; j<space; j++){ //marcamos espacios para separar los valores
    			cout<<' ';
			}
			//Imprimimos cada clave:
			cout<<root->keys[i]<<endl;
			
			//Llamamos recursivamente para imprimir el subárbol izquierdo
			print(root->C[i],count);
		}
    	
	}
    
} 
