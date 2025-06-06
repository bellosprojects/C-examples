// LinkedList
// Angel Bello
// Fecha: Friday, 2025-06-06

#include <iostream>

using namespace std;

// Clase Nodo
class Node {
    public:
        int data;
        Node* next;

        // Constructor
        Node(int value) : data(value), next(nullptr) {}
};

// Clase LinkedList
class LinkedList {
    private:
        Node *head, *tail;
        
    public:
        //Tamano de la lista
        int size;

        // Constructor
        LinkedList() : head(nullptr), tail(nullptr), size(0) {}

        //Agregar elemento al final de la lista
        void add(int value) {
            if(isEmpty()){
                head = new Node(value);
                tail = head;
            } else {
                tail->next = new Node(value);
                tail = tail->next;
            }
            size++;
        }

        //Agregar en una posicion especifica (por defecto al inicio)
        void insert(int value, int position=0) {
            if(position < 0 || position > size) {
                cout << "Posicion fuera de rango." << endl;
                return;
            }
            Node* newNode = new Node(value);
            if(position == 0) {
                newNode->next = head;
                head = newNode;
            } else {
                Node* current = head;
                for(int i = 0; i < position - 1; i++) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
            if(position == size) tail = newNode;
            size++;
        }

        //Eliminar el ultimo elemento
        void removeLast() {
            if(isEmpty()) {
                cout << "La lista esta vacia." << endl;
                return;
            }
            if(size == 1) {
                delete head;
                head = tail = nullptr;
            } else {
                Node* current = head;
                while(current->next != tail) {
                    current = current->next;
                }
                delete tail;
                tail = current;
                tail->next = nullptr;
            }
            size--;
        }

        //Eliminar por indice
        void pop(int index){
            if(index < 0 || index >= size) {
                cout << "indice fuera de rango." << endl;
                return;
            }
            if(index == 0) {
                Node* temp = head;
                head = head->next;
                delete temp;
                if(size == 1) tail = head;
            } else {
                Node* current = head;
                for(int i = 0; i < index - 1; i++) {
                    current = current->next;
                }
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                if(current->next == nullptr) tail = current;
            }
            size--; 
        }

        //Eliminar por valor (primera coincidencia)
        void remove(int value) {
            if(isEmpty()) {
                cout << "La lista esta vacia." << endl;
                return;
            }
            Node* current = head;
            Node* previous = nullptr;

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
                    return; // Salir despues de eliminar el primer valor encontrado
                }
                previous = current;
                current = current->next;
            }
            cout << "Valor no encontrado en la lista." << endl;
        }

        //Obtener valor por indice de la forma 'list[index]'
        int operator[](int index){
            if(index < 0 || index >= size) {
                cout << "indice fuera de rango." << endl;
                return -1; // O un valor que indique error
            }
            Node* current = head;
            for(int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

        //Obtener valor por indice de la forma list.get(index)
        int get(int index){
            if(index < 0 || index >= size) {
                cout << "indice fuera de rango." << endl;
                return -1; // O un valor que indique error
            }
            Node* current = head;
            for(int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

        //obtener cuantos elementos tiene el valor 'value'
        int count(int value) {
            int count = 0;
            Node* current = head;
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
            Node* current = head;
            Node* newHead = nullptr;
            Node* newTail = nullptr;
            int index = 0;
            while(current != nullptr) {
                if(index >= start && index <= end) {
                    Node* newNode = new Node(current->data);
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
            Node* prev = nullptr;
            Node* current = head;
            Node* next = nullptr;
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
                removeLast();
            }
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        //indice de un valor
        int indexOf(int value) {
            Node* current = head;
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
            Node* current = head;
            while(current != nullptr) {
                cout << current->data;
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
            Node* current = head;
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

        //Destructor
        ~LinkedList() {
            clear();
            head = nullptr;
            tail = nullptr;
        }
};

int main() {
    
    //Muestra de uso
    LinkedList list; // Crear una lista enlazada

    // Agregar elementos
    list.add(5);
    list.add(67);
    list.add(2);
    list.add(7);
    list.add(23);
    list.add(8);
    list.add(1);
    list.add(8);
    list.add(9);

    // Imprimir la lista
    cout << "Lista original: ";
    list.print();

    // Insertar en una posicion especifica
    list.insert(3, 2);
    cout << "Lista despues de insertar 3 en la posicion 2: ";
    list.print();

    //Agregar al inicio
    list.insert(0);

    cout << "Lista despues de insertar 0 al inicio: ";
    list.print();

    // Eliminar el ultimo elemento
    list.removeLast();
    cout << "Lista despues de eliminar el ultimo elemento: ";
    list.print();

    // Eliminar por indice
    list.pop(2);
    cout << "Lista despues de eliminar el elemento en el indice 2: ";
    list.print();

    // Eliminar por valor
    list.remove(5);
    cout << "Lista despues de eliminar el valor 5: ";
    list.print();

    // Obtener valor por indice
    cout << "Valor en el indice 1: " << list[1] << endl;

    // Obtener valor por metodo get
    cout << "Valor en el indice 1 usando get: " << list.get(1) << endl;

    // Contar ocurrencias de un valor
    cout << "Numero de ocurrencias del valor 8: " << list.count(8) << endl;

    // Acotar la lista a un rango
    list.slice(1, 4);
    cout << "Lista despues de acotar a los indices 1 a 4: ";
    list.print();

    // Voltear la lista
    list.reverse();
    cout << "Lista despues de voltear: ";
    list.print();

    // Verificar si la lista esta vacia
    cout << "La lista esta vacia? " << (list.isEmpty() ? "Si" : "No") << endl;

    // Obtener el indice de un valor
    cout << "indice del valor 7: " << list.indexOf(7) << endl;

    // Ordenar la lista de mayor a menor
    list.sort();
    cout << "Lista despues de ordenar de mayor a menor: ";
    list.print();

    // Vaciar la lista
    list.clear();

    // Tamano de la lista
    cout << "Tamano de la lista despues de vaciar: " << list.size << endl; //0 por estar vacia

    // Imprimir la lista vacia
    cout << "Lista vacia: ";
    list.print(); // No deberia imprimir nada

    // Verificar si la lista esta vacia
    cout << "La lista esta vacia? " << (list.isEmpty() ? "Si" : "No") << endl;

    return 0;
}