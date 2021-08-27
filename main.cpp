#include <iostream>
#include <codeco.h>

//"../lab info II/2.0_Practica_3/BD/entrada.txt"
//"../2.0 Practica 3/BD/salida.txt

using namespace std;

/*El siguiente programa permite codificar y decodificar mediante dos metodos ,archivos de texto
  El programa emplea las funciones de la librería codeco.h
  Existen dos metodos para decodificar, su funcionalidad se encuentra en la libreria codeco.h
  El programa escribe en un archivo de texto la cadena decodificada o codificada
  --------------------------------------------------------------------------------------------
  Restricciones del programa: El programa fallará en caso de ingresar una semilla mayor al
  tamaño de la cadena a codificar o decodificar.
 */


int main()
{   string txtin="../2.0_Practica_3/BD/entrada.txt";
    string txtout="../2.0_Practica_3/BD/salida.txt";

    int decision=opcion();

    if(decision==1){

        //string txtin=txt1();
        //string txtout=txt2();
        int met =metodo();
        int n= semilla();

        codificar(n,met,txtin,txtout);

    }

    else{

        //string txtin=txt1();
        //string txtout=txt2();
        int met =metodo();
        int n= semilla();

        decodificar(n,met,txtin,txtout);


    }

   return 0;

}
