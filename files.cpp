//Ficheros

#include <iostream>
#include <fstream>

using namespace std;

void write(string ruta, string texto){
    ofstream fichero(ruta);
    fichero << texto;
    fichero.close();
}

string getInfo(string ruta){
    string salida="";
    string pal;
    ifstream fichero(ruta);
    while(fichero >> pal){
        salida+=pal;
    }
    return salida;
}

void cargarCarpeta(string rutaCarpeta){

    string comando = "dir /b \""+rutaCarpeta+"\"";
    FILE *fichero = popen(comando.c_str(), "r");
    if(!fichero){
        return;
    }
    char buffer[1000];
    while(true){
        if(fgets(buffer, 1000, fichero)==NULL){
            break;
        }
        cout <<  (rutaCarpeta + "/" + buffer);
    }
}

int main(){

    return 0;
}
