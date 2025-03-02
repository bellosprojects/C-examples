//Codigos basicos de Cpp para manipulacion de strings

//Basico
#include <iostream>
using namespace std;

//Size del string
int lenght(string s){
    for(int i=0; ; i++){
        if(s[i]=='\0'){
            return i;
        }
    }
}

//String a entero
int str_to_int(string s){
    int n = 0;
    for(int i=0; i<lenght(s); i++){
        n = n*10 + (s[i]-'0');
    }
    return n;
}

//Entero a String
string int_to_str(int n){
    string str = "";
    if(n==0){
        return "0";
    }
    while(n>0){
        str = char(n%10+'0') + str;
        n/=10;
    }
    return str;
}

//Saber si a esta dentro de b
bool str_in_str(string a, string b){
    for(int i=0; i<=lenght(b)-lenght(a); i++){
        bool enc=true;
        for(int j=0; j<lenght(a); j++){
            if(b[i+j]!=a[j]){
                enc=false;
                break;
            }
        }
        if(enc){
            return true;
        }
    }
    return false;
}

//Saber si a comienza con b,  Ejemplo si Hola comienza con Ho
bool str_start_str(string a, string b){
    for (int i = 0; i < lenght(b); i++)
    {
        if(a[i]!=b[i]){
            return false;
        }
    }
    return true;
}

//Eliminar el ultimo caracter de una cadena
void pop_last(string &a){
    for(int i=0; true; i++){
        if(a[i]=='\0'){
            a[i-1] = '\0';
            break;
        }
    }
}

//Eliminar primer caracter
void pop_one(string &a){
    for(int i=0; i<lenght(a); i++){
        a[i]=a[i+1];
    }
    pop_last(a);
}

//Convertir string en cadena de chars (c_str())
char *str_to_char(string a){
    char *aux=new char[lenght(a)+1];
    for(int i=0; i<lenght(a); i++){
        aux[i]=a[i];
    }
    aux[lenght(a)]='\0';
    return aux;
}

int main(){

    return 0;
}
