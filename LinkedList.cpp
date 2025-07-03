// LinkedList
// Angel Bello
// Fecha: Friday, 2025-06-06

#include <iostream>

using namespace std;

// Clase Nodo 
template <typename T>
class Node {
    public:
        T data;
        Node<T>* next;

        // Constructor
        Node(T value) : data(value), next(nullptr) {}
};

// Clase LinkedList
template <typename T>
class LinkedList {
    private:
        Node<T> *head, *tail;
        int size;
    
    public:

        //Tamano de la lista
        int Size() {
            return size;
        }

        // Constructor
        LinkedList() : head(nullptr), tail(nullptr), size(0) {}

        //Constructor de copia
        LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
            Node<T>* current = other.head;
            while(current != nullptr) {
                add(current->data);
                current = current->next;
            }
        }

        //operador de asignacion
        LinkedList<T>& operator=(const LinkedList<T>& other) {
            if(this != &other) {
                clear(); // Limpiar la lista actual
                Node<T>* current = other.head;
                while(current != nullptr) {
                    add(current->data);
                    current = current->next;
                }
            }
            return *this;
        }

        //Agregar elemento al final de la lista
        void add(T value) {
            if(isEmpty()){
                head = new Node<T>(value);
                tail = head;
            } else {
                tail->next = new Node<T>(value);
                tail = tail->next;
            }
            size++;
        }

        //Agregar en una posicion especifica (por defecto al inicio)
        void insert(T value, int position=0) {
            if(position < 0 || position > size) {
                cout << "Posicion fuera de rango." << endl;
                return;
            }
            Node<T>* newNode = new Node<T>(value);
            if(position == 0) {
                newNode->next = head;
                head = newNode;
            } else {
                Node<T>* current = head;
                for(int i = 0; i < position - 1; i++) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
            if(position == size) tail = newNode;
            size++;
        }


        //Eliminar por indice
        void pop(int index){
            if(index <0) index = size + index; // Soporte para indices negativos
            if(index >= size) {
                cout << "indice fuera de rango." << endl;
                return;
            }
            if(index == 0) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                if(size == 1) tail = head;
            } else {
                Node<T>* current = head;
                for(int i = 0; i < index - 1; i++) {
                    current = current->next;
                }
                Node<T>* temp = current->next;
                current->next = temp->next;
                delete temp;
                if(current->next == nullptr) tail = current;
            }
            size--; 
        }

        //Eliminar por valor (primera coincidencia)
        void remove(T value, bool allOccurrences = false) {
            if(isEmpty()) {
                cout << "La lista esta vacia." << endl;
                return;
            }
            Node<T>* current = head;
            Node<T>* previous = nullptr;

            while(current != nullptr) {
                if(current->data == value) {
                    if(previous == nullptr) { // Eliminar el primer nodo
                        head = current->next;
                        if(head == nullptr) tail = nullptr; // Lista quedo vacia
                    } else {
                        previous->next = current->next;
                        if(current->next == nullptr) tail = previous; // Actualizar tail si es necesario
                    }
                    delete current;
                    size--;
                    if(!allOccurrences) {
                        return; // Si no se quieren eliminar todas las ocurrencias, salir
                    }
                }
                previous = current;
                current = current->next;
            }
            if(allOccurrences && previous != nullptr) {
                tail = previous; // Actualizar tail si se eliminaron todos los nodos
            }
        }

        //Obtener valor por indice de la forma 'list[index]'
        T operator[](int index){
            if(index < 0) index = size + index; // Soporte para indices negativos
            if(index >= size) {
                cout << "indice fuera de rango." << endl;
                return -1; // O un valor que indique error
            }
            Node<T>* current = head;
            for(int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

        //Obtener valor por indice de la forma list.get(index)
        T get(int index){
            if(index < 0) index = size + index; // Soporte para indices negativos
            if(index >= size) {
                cout << "indice fuera de rango." << endl;
                return -1; // O un valor que indique error
            }
            Node<T>* current = head;
            for(int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

        //obtener cuantos elementos tiene el valor 'value'
        int count(T value) {
            int count = 0;
            Node<T>* current = head;
            while(current != nullptr) {
                if(current->data == value) {
                    count++;
                }
                current = current->next;
            }
            return count;
        }

        //acotar la lista a un rango
        void slice(int start, int end){
            if(start < 0 || end >= size || start > end) {
                cout << "Rango invalido." << endl;
                return;
            }
            Node<T>* current = head;
            Node<T>* newHead = nullptr;
            Node<T>* newTail = nullptr;
            int index = 0;
            while(current != nullptr) {
                if(index >= start && index <= end) {
                    Node<T>* newNode = new Node<T>(current->data);
                    if(newHead == nullptr) {
                        newHead = newNode;
                        newTail = newNode;
                    } else {
                        newTail->next = newNode;
                        newTail = newTail->next;
                    }
                }
                current = current->next;
                index++;
            }
            head = newHead;
            tail = newTail;
            size = end - start + 1;
            if(newTail != nullptr) {
                newTail->next = nullptr;
            }
        }

        //Voltear elementos
        void reverse() {
            Node<T>* prev = nullptr;
            Node<T>* current = head;
            Node<T>* next = nullptr;
            tail = head; // Actualizar tail al inicio antes de invertir
            while(current != nullptr) {
                next = current->next; // Guardar el siguiente nodo
                current->next = prev; // Invertir el enlace
                prev = current; // Mover prev hacia adelante
                current = next; // Mover current hacia adelante
                }
            head = prev; // Actualizar head al nuevo inicio
        }

        //vaciar lista
        void clear() {
            while(!isEmpty()) {
                pop(-1); // Eliminar el ultimo elemento
            }
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        //indice de un valor
        int indexOf(T value) {
            Node<T>* current = head;
            int index = 0;
            while(current != nullptr) {
                if(current->data == value) {
                    return index; // Retorna el primer indice encontrado
                }
                current = current->next;
                index++;
            }
            return -1; // Retorna -1 si el valor no se encuentra
        }

        //Verificar si la lista esta vacia
        bool isEmpty() {
            return size == 0;
        }

        //Imprimir la lista separando los elementos por 'sep'
        void print(string sep = " ") {
            if(isEmpty()) {
                return;
            }
            Node<T>* current = head;
            while(current != nullptr) {
                current->data.print();
                if(current->next != nullptr) {
                    cout << sep;
                }
                current = current->next;
            }
            cout << endl;
        }

        //Ordenar elementos de mayor a menor
        void sort() {
            if (isEmpty()) {
                return;
            }
            Node<T>* current = head;
            bool swapped;
            do {
                swapped = false;
                current = head;
                while (current->next != nullptr) {
                    if (current->data < current->next->data) {
                        // Intercambiar los datos
                        int temp = current->data;
                        current->data = current->next->data;
                        current->next->data = temp;
                        swapped = true;
                    }
                    current = current->next;
                }
            } while (swapped);
        }

        Node<T> *getHead(){
            return head;
        }

        void setHead(Node<T>* newHead){
            head = newHead;
        }

        Node<T> *getTail(){
            return tail;
        }

        void setTail(Node<T>* newTail){
            tail = newTail;
        }

        //Destructor
        ~LinkedList() {
            clear();
            head = nullptr;
            tail = nullptr;
        }
};
