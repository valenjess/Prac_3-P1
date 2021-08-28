#ifndef CODECO_H
#define CODECO_H

//Librerias necesarias para el desarrollo de las funciones de la libreria "codeco.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

                         ///PROTOTIPOS DE LAS FUNCIONES EMPLEADAS///

int opcion();   //Funcion tipo int, sin parametros
                //pide al usuario ingresar 1, si desea codificar o 0 si desea decodificar
                //retorna el entero seleccionado

int semilla();  //Esta funcion de tipo entero int pide al usuario un numero entero que será la semilla,
                //y lo retorna (n)


int metodo(); //Esta funcion de tipo entero pide al usuario un numero entero 1 o 2, el cual representa el
                          //metodo de codificacion


string codone(string oracion_Binaria,int n);
                // Función tipo string, tiene como parámetros un string (código en binario del ASCII),
                // y un entero n (semilla), es decir, el string se separa en bloques de n bits.
                // Lo que hace esta función es codificar el string siguiendo las condiciones :
                // En el primer bloque se cambian todos los 1 por 0 y viceversa.
                // Para los grupos siguientes se debe contar el número de 1s y 0s en el grupo anterior
                // y hacer cambios según la siguiente regla:
                //   °Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
                //   °Si hay mayor cantidad de 0s se invierte cada 2 bits.
                //   °Si hay mayor cantidad de 1s se invierte cada 3 bits.


string codtwo(string cadena_Binaria, int n);
                // Función tipo string, tiene como parámetros un string (código en binario del ASCII),
                // y un entero n (semilla), es decir, el string se separa en bloques de n bits.
                // Y desplaza cada elemento del bloque un bit hacia la derecha
                // Ejemplo:
                // cadena binaria = 01011000       n=3
                // Se divide en bloques de 3 bits    -->  010  110  01
                // Se desplaza cada bit una posición -->  001  011  10  CADENA CODIFICADA
                // En cuanto a los indices de las cadenas:
                // cadena_Binaria   = [0][1][2]  [3][4][5]  [6][7]
                // cadena_codificada= [2][0][1]  [5][3][4]  [7][6]
                //la función retorna un string que corresponde a la cadena codificada "00101110"


string binario(string palabra);//funcion tipo string
                               //Parametros: string que representa la cadena en ASCII
                               //convierte el ASCII en binario gracias al corrimiento de bits
                               //y retorna ese string convertido

string decone(string cadena_codificada,int n);//Funcion tipo string
                                     //Parametros: string(cadena codificada) y un entero n (semilla)
                                     //Esta funcion tiene en cuenta las mismas reglas de
                                     //codificacion del metodo 1, pero en este caso se cuentan
                                     //los unos y ceros del grupo anterior de LA CADENA DECODIFICADA

string decotwo(string cadena_codificada, int n);//Funcion tipo string
                           //Parametros: string (cadena codificada), entero n (semilla)
                           //Esta funcion decodifica la cadena_codificada
                           //Ejemplo:
                           // Si n = 4 y la cadena es: "0010100000110001"
                           //CADENA CODIFICADA:
                           //[0][1][2][3]  [4][5][6][7]  [8][9][10][11]  [12][13][14][15]
                           // 0  0  1  0    1  0  0  0    0  0  1   1      0   0   0  1

                           //CADENA DECODIFICADA:(indices de los elementos de cadena codificada)
                           // [3][0][1][2]  [5][6][7][4]  [9][10][11][8]  [13][14][15][12]
                           // 0  0  0  1    0  0  0  1    0   1   1  0     0   0   1   0

void escritura(string archivo,string texto); //funcion sin retorno que recibe el nombre del txt en
                                             //el que se va a escribir la cadena codificada, y ademas
                                             //recibe la cadena codificada que posteriormente sera
                                             //escrita en este txt


///////////////////////          CUERPO  DE LAS FUNCIONES    //////////////////////////////////////

int opcion(){

    int eleccion=0;

    cout<<"            --<<   QUE DESEA HACER  >>--       "<<endl;
    cout<<"Presione 0 para Decodificar o 1 para codificar ";cin>>eleccion;
    cout<<endl;

    while(eleccion!=1 && eleccion!=0){                                  //MANEJO DE EXCEPCIONES

        cout<<" - - - - - - - - - - - - - - - - - - - - - - "<<endl;
        cout<<"SOLO PUEDE ELEGIR ENTRE 1 O 2 "<<endl;                   //Solo discrimina entre numeros
        cout<<" Ingrese de nuevo el numero de eleccion  --> ";
        cin>>eleccion;
    }
    return eleccion;

}

int semilla(){
    int n=0;

    cout<<"Ingrese la semilla << n >> :  "<<endl;cin>>n;
        if(n==false){
            cout<<"Debe ingresar un numero ";
        }
        else{
            cout<<"  Dato correcto ";
        }
        return n;


}


int metodo(){

    int metodo=0;

    cout<<" --  ELIGA EL METODO DE CODIFICACION O DECODIFICACION  --"<<endl;
    cout<<"     Presione 1 o 2   : ";cin>>metodo;

    while(metodo!=1 && metodo!=2){                                  //MANEJO DE EXCEPCIONES
        cout<<"SOLO PUEDE ELEGIR ENTRE 1 O 2 "<<endl;
        cout<<" Ingrese de nuevo el numero del metodo --> "<<endl;
        cin>>metodo;
    }
    return metodo;

}

string binario(string palabra){  //Funcion tipo string que retorna un string
    int c;                             //convierte una cadena de caracteres en
    string palbin;                       //numeros binarios, por medio del corrimiento
                                            //de bits
    for (int i=0;palabra[i]!='\0';i++){
        c=palabra[i];
        for(int j=7;j+1>0;j--){
            if(c>=(1<<j)){
                c=c-(1<<j);
                palbin+="1";

            }
            else{
               palbin+="0";
            }
        }
    } return palbin;
}




string codone(string oracion_Binaria,int n){


    string cadena_Codificada=""; //variable tipo string que almacena la cadena resultante de aplicar
                                 //las condiciones de codificacion a oracion_Binaria(cadena en ASCII)

    //inicializacion de variables tipo int

    int ceros=0,unos=0;               //Registra la cantidad de unos y ceros de el bloque anterior
    int tamano=oracion_Binaria.length(); //largo de la cadena ASCII
    int lim=(tamano)/n;               //representa la cantidad de bloques de n bits
    int lim_2=(tamano%n);             //representa los bits sobrantes en cado de no poder partirse
                                      //la cadena ASCII en n bits exactamente
    int seguir=0;                     //contador que registra la cantidad de bloques codificados




if((tamano%n)==0){           //CONDICIONAL EN CASO DE QUE LA CADENA SE PUEDA PARTIR
                             //EN n BITS EXACTAMENTE
    while(seguir<lim){

        if(seguir==0){                        //Reglas para codificar:
            for(int i=0;i<n;i++){
                if(oracion_Binaria[i]=='0'){
                    cadena_Codificada+='1';      // 1.Primer bloque:
                    ceros+=1;                    // los unos cambian por ceros
                }                                // y viceversa
                else{
                    cadena_Codificada+='0';
                    unos+=1;
                     }
                    }
             seguir+=1;

                }

        else if(ceros==unos){                           // 2.cantidad de ceros = cantidad
            ceros=0,unos=0;                             // de unos:
            for(int i=0;i<n;i++){
                if(oracion_Binaria[(seguir*n)+i]=='0'){   //se invierten bit a bit(1->0),(0->1)
                    cadena_Codificada+='1';
                    ceros+=1;
                }
                else{
                    cadena_Codificada+='0';
                    unos+=1;
                     }
                    }
             seguir+=1;
            }

        else if(ceros>unos){                                // 3.Cantidad de ceros mayor a
            ceros=0,unos=0;                                 //cantidad de unos :
            for(int k=0;k<n;k++){                           //Se invierte cada 2 bits
                if(k%2!=0){                                 //Ejemplo:
                    if(oracion_Binaria[(seguir*n)+k]=='0'){ //se tiene un bloque (n=4)
                                                            //[0][1][2][3]
                        cadena_Codificada+='1';             //cada dos bits es cuando
                        ceros+=1;                           //el indice no es divisor
                    }                                       //de 2 --> (indice%2)!=0

                    else{
                        cadena_Codificada+='0';
                        unos+=1;
                    }}

                 else{
                    if(oracion_Binaria[(seguir*n)+k]=='0'){
                            cadena_Codificada+='0';
                            ceros+=1;
                        }

                    else{
                            cadena_Codificada+='1';
                            unos+=1;
                        }
                    }}
               seguir+=1;
                }

        else{                                      //4.Cantidad de unos mayor a
            ceros=0;unos=0;                        //cantidad de ceros:
            for(int j=1;j<=n;j++){                 //Se invierte cada 3 bits
               if(j%3==0){                         //j es la posicion, en este caso,
                                                   //indice+1,por lo cual cuando j%3=0
                                                                //esta ubicandose cada 3 bits
                    if(oracion_Binaria[(seguir*n)+(j-1)]=='0'){ //Ejemplo:
                        cadena_Codificada+='1';                 //[0][1][2][3][4][5]->indices
                                                             //j = 1, 2, 3, 4, 5, 6
                        ceros+=1;                               //los bits que deben cambiarse
                     }                                          //respresentan los divisores
                                                                //j de 3,es decir,
                    else{                                       //los elementos con indices
                        cadena_Codificada+='0';                 //2 y 5
                        unos+=1;
                     }

                  }

                else{
                   if(oracion_Binaria[(seguir*n)+(j-1)]=='0'){
                       cadena_Codificada+='0';
                       ceros+=1;
                   }

                   else{
                       cadena_Codificada+='1';
                       unos+=1;
                   }


                }


            }

          seguir+=1;
        }


            }

}


else{                       //CONDICIONAL EN CASO DE QUE LA CADENA NO SE PUEDA
                            //PARTIR EN n BITS EXACTAMENTE
    while(seguir < lim){
        if(seguir==0){
            for(int i=0;i<n;i++){
                if(oracion_Binaria[i]=='0'){
                    cadena_Codificada+='1';
                    ceros+=1;
                }
                else{
                    cadena_Codificada+='0';
                    unos+=1;
                     }
                    }
             seguir+=1;

                }

        else if(ceros==unos){
            ceros=0,unos=0;
            for(int i=0;i<n;i++){
                if(oracion_Binaria[(seguir*n)+i]=='0'){
                    cadena_Codificada+='1';
                    ceros+=1;
                }
                else{
                    cadena_Codificada+='0';
                    unos+=1;
                     }
                    }
             seguir+=1;
            }

        else if(ceros>unos){
            ceros=0,unos=0;
            for(int k=0;k<n;k++){
                if(k%2!=0){
                    if(oracion_Binaria[(seguir*n)+k]=='0'){
                        cadena_Codificada+='1';
                        ceros+=1;
                    }

                    else{
                        cadena_Codificada+='0';
                        unos+=1;
                    }}

                 else{
                    if(oracion_Binaria[(seguir*n)+k]=='0'){
                            cadena_Codificada+='0';
                            ceros+=1;
                        }

                    else{
                            cadena_Codificada+='1';
                            unos+=1;
                        }
                    }}
               seguir+=1;
                }

        else{                                      //4.Cantidad de unos mayor a
            ceros=0;unos=0;                        //cantidad de ceros:
            for(int j=1;j<=n;j++){                 //Se invierte cada 3 bits
               if(j%3==0){                         //j es la posicion, en este caso,
                                                   //indice+1,por lo cual cuando j%3=0
                                                                //esta ubicandose cada 3 bits
                    if(oracion_Binaria[(seguir*n)+(j-1)]=='0'){ //Ejemplo:
                        cadena_Codificada+='1';                 //[0][1][2][3][4][5]->indices
                                                             //j = 1, 2, 3, 4, 5, 6
                        ceros+=1;                               //los bits que deben cambiarse
                     }                                          //respresentan los divisores
                                                                //j de 3,es decir,
                    else{                                       //los elementos con indices
                        cadena_Codificada+='0';                 //2 y 5
                        unos+=1;
                     }

                  }

                else{
                   if(oracion_Binaria[(seguir*n)+(j-1)]=='0'){
                       cadena_Codificada+='0';
                       ceros+=1;
                   }

                   else{
                       cadena_Codificada+='1';
                       unos+=1;
                   }


                }


            }

          seguir+=1;
        }




            }

    //En caso de que la cadena no pueda formar grupos de exactamente n bits,
    //el grupo que sobra se procesa en esta parte, aplicando las mismas condiciones
    //de codificación
    //  lim_2 --> representa la cantidad de bits sobrantes
    if(ceros==unos){
        for(int i=0;i<lim_2;i++){
           if(oracion_Binaria[(seguir*n)+i]=='0'){
                    cadena_Codificada+='1';
                }
            else{
                    cadena_Codificada+='0';
                     }
                    }
        }


     else if(ceros>unos){
          for(int k=0;k<(lim_2);k++){
             if(k%2!=0){
                   if(oracion_Binaria[(seguir*n)+k]=='0'){
                        cadena_Codificada+='1';
                    }

                    else{
                        cadena_Codificada+='0';
                                }
                     }
                   }
           }

     else{

          for(int j=1;j<=(lim_2);j++){
                 if(j%3==0){

                        if(oracion_Binaria[(seguir*n)+(j-1)]=='0'){
                            cadena_Codificada+='1';
                            }

                         else{
                            cadena_Codificada+='0';

                            }

                    }

                  else{
                        if(oracion_Binaria[(seguir*n)+(j-1)]=='0'){
                            cadena_Codificada+='0';

                         }

                        else{
                            cadena_Codificada+='1';

                            }

                        }


        }


    }

}
return cadena_Codificada;

}


string codtwo(string cadena_Binaria,int n){

    string cadena_codificada="";
    int j=(n-1);
    int tamano=cadena_Binaria.length();
    int lon=(tamano)/n;  //cantidad de bloques de n bits
    int modulo=(tamano)%n; //variable que indica la cantidad de elementos sobrantes en caso de que la
                           //la cadena_Binaria(string del ASCC), no se pueda dividir exactamente en bloques
                           //de n bits
    int falta=modulo-1, seguir=0;


    //Si el string en binario se puede dividir exactamente en grupos de n bits:
    if (modulo==0){

         while(seguir<lon){
             //Ejemplo: 0 1 0 1 (primer bloque sin codificar), seguir=0 , n=4 ,indice=3, j=3
             cadena_codificada+=cadena_Binaria[(seguir*n)+j]; //Paso en el que el ultimo elemento de
                                                              //cada grupo se convierte en el primero,
                                                              //al desplazarse un bit
                                                              // en el caso del ejemplo : "1"
             for(int indice=j;indice>0;indice--){
             cadena_codificada+=cadena_Binaria[((seguir*n)+j)-indice];
                                        // "1"+elemento en la posición[((0*4)+3)-3]
                                        //"1"+elemento en la posicion 0
                                        //"1"+"0", y así sucesivamente hasta mover los 3 elementos restantes del grupo de 4 bits

             }

             seguir++;//contador que indica la cantidad de bloques procesados

              }


         }


    //Si el string en binario se puede dividir exactamente en grupos de n bits:
    else{

        while(seguir<lon){ //en este ciclo se procesan los grupos de exactamente n bits
                          //de igual forma que se hace cuando se pueden dividir exactamente en n bits

            cadena_codificada+=cadena_Binaria[(seguir*n)+j];

            for(int indice=j;indice>0;indice--){
            cadena_codificada+=cadena_Binaria[((seguir*n)+j)-indice];
            }

            seguir++;

             }
        cadena_codificada+=cadena_Binaria[tamano-1];//el ultimo delemento de la cadena sin codificar
                                                    //se convierte en el priemr elemento del ultimo
                                                    //grupo de los bits sobrantes

        for(int i=falta;i>0;i--){               //Se desplazan los bits del grupo sobrante
            cadena_codificada+=cadena_Binaria[(tamano-1)-i];

        }

        //Ejemplo:
        // cadena_Binaria="01000001011000100100001101100100", n=7, falta=(32%7)-1=3
        // En este caso hay 4 grupos de 7 bits, sobra un grupo de 4 bits
        // 0100000  1011000  1001000  0110110   0100
        // 0010000  0101100  0100100  0011011   0010 --> se ubica el bit de la posicion [31] de primero
                                                      //en el grupo y se desplazan los 3 bits restantes
                                                      //[28] [29] [30] [31]
                                                      //[31] [28] [29] [30]
    }
    return cadena_codificada;

}


string decone(string cadena_codificada,int n){

    string cadena_Decod="";
    int lon= cadena_codificada.length();
    int grupos=lon/n, sobrante=lon%n; //grupos -->cantidad de grupos de exactamente n bits
    int seguir=0,unos=0,ceros=0;      //sobrante->En caso de no poderse dividir la cadena
                                      //en grupos de exactamente n bits, sobrante es la cantidad
                                      //de elementos del grupo que falta por codificar

//En caso de que la cadena_codificada se pueda dividir en grupos de exactamente n bits
if(lon%n==0){

        while(seguir<grupos){

            if(seguir==0){                        //Reglas para codificar:
                for(int i=0;i<n;i++){
                    if(cadena_codificada[i]=='0'){
                        cadena_Decod+='1';      // 1.Primer bloque:
                        unos+=1;                    // los unos cambian por ceros
                    }                                // y viceversa
                    else{
                        cadena_Decod+='0';
                        ceros+=1;
                         }
                        }
                 seguir+=1;

                    }

            else if(ceros==unos){                           // 2.cantidad de ceros = cantidad
                ceros=0,unos=0;                             // de unos:
                for(int i=0;i<n;i++){
                    if(cadena_codificada[(seguir*n)+i]=='0'){   //se invierten bit a bit(1->0),(0->1)
                        cadena_Decod+='1';
                        unos+=1;
                    }
                    else{
                        cadena_Decod+='0';
                        ceros+=1;
                         }
                        }
                 seguir+=1;
                }

            else if(ceros>unos){                                // 3.Cantidad de ceros mayor a
                ceros=0,unos=0;                                 //cantidad de unos :
                for(int k=0;k<n;k++){                           //Se invierte cada 2 bits
                    if(k%2!=0){                                 //Ejemplo:
                        if(cadena_codificada[(seguir*n)+k]=='0'){ //se tiene un bloque (n=4)
                                                                //[0][1][2][3]
                            cadena_Decod+='1';             //cada dos bits es cuando
                            unos+=1;                           //el indice no es divisor
                        }                                       //de 2 --> (indice%2)!=0

                        else{
                            cadena_Decod+='0';
                            ceros+=1;
                        }}

                     else{
                        if(cadena_codificada[(seguir*n)+k]=='0'){
                                cadena_Decod+='0';
                                ceros+=1;
                            }

                        else{
                                cadena_Decod+='1';
                                unos+=1;
                            }
                        }}
                   seguir+=1;
                    }

            else{                                      //4.Cantidad de unos mayor a
                ceros=0;unos=0;                        //cantidad de ceros:
                for(int j=1;j<=n;j++){                 //Se invierte cada 3 bits
                   if(j%3==0){                         //j es la posicion, en este caso,
                                                       //indice+1,por lo cual cuando j%3=0
                                                                    //esta ubicandose cada 3 bits
                        if(cadena_codificada[(seguir*n)+(j-1)]=='0'){ //Ejemplo:
                            cadena_Decod+='1';                 //[0][1][2][3][4][5]->indices
                                                                 //j = 1, 2, 3, 4, 5, 6
                            unos+=1;                               //los bits que deben cambiarse
                         }                                          //respresentan los divisores
                                                                    //j de 3,es decir,
                        else{                                       //los elementos con indices
                            cadena_Decod+='0';                 //2 y 5
                            ceros+=1;
                         }

                      }

                    else{
                       if(cadena_codificada[(seguir*n)+(j-1)]=='0'){
                           cadena_Decod+='0';
                           ceros+=1;
                       }

                       else{
                           cadena_Decod+='1';
                           unos+=1;
                       }


                     }


                }
                seguir+=1;

            }


        }
  }



else{                       //CONDICIONAL EN CASO DE QUE LA CADENA NO SE PUEDA
                                //PARTIR EN n BITS EXACTAMENTE
        while(seguir < grupos){

            if(seguir==0){
                for(int i=0;i<n;i++){
                    if(cadena_codificada[i]=='0'){
                        cadena_Decod+='1';
                        unos+=1;
                    }
                    else{
                        cadena_Decod+='0';
                        ceros+=1;
                         }
                        }
                 seguir+=1;

                    }

            else if(ceros==unos){
                ceros=0,unos=0;
                for(int i=0;i<n;i++){
                    if(cadena_codificada[(seguir*n)+i]=='0'){
                        cadena_Decod+='1';
                        unos+=1;
                    }
                    else{
                        cadena_Decod+='0';
                        ceros+=1;
                         }
                        }
                 seguir+=1;
                }

            else if(ceros>unos){
                ceros=0,unos=0;
                for(int k=0;k<n;k++){
                    if(k%2!=0){
                        if(cadena_codificada[(seguir*n)+k]=='0'){
                            cadena_Decod+='1';
                            unos+=1;
                        }

                        else{
                            cadena_Decod+='0';
                            ceros+=1;
                        }}

                     else{
                        if(cadena_codificada[(seguir*n)+k]=='0'){
                                cadena_Decod+='0';
                                ceros+=1;
                            }

                        else{
                                cadena_Decod+='1';
                                unos+=1;
                            }
                        }}
                   seguir+=1;
                    }

            else{                                      //4.Cantidad de unos mayor a
                ceros=0;unos=0;                        //cantidad de ceros:
                for(int j=1;j<=n;j++){                 //Se invierte cada 3 bits
                   if(j%3==0){                         //j es la posicion, en este caso,
                                                       //indice+1,por lo cual cuando j%3=0
                                                                    //esta ubicandose cada 3 bits
                        if(cadena_codificada[(seguir*n)+(j-1)]=='0'){ //Ejemplo:
                            cadena_Decod+='1';                 //[0][1][2][3][4][5]->indices
                                                                 //j = 1, 2, 3, 4, 5, 6
                            unos+=1;                               //los bits que deben cambiarse
                         }                                          //respresentan los divisores
                                                                    //j de 3,es decir,
                        else{                                       //los elementos con indices
                            cadena_Decod+='0';                 //2 y 5
                            ceros+=1;
                         }

                      }

                    else{
                       if(cadena_codificada[(seguir*n)+(j-1)]=='0'){
                           cadena_Decod+='0';
                           ceros+=1;
                       }

                       else{
                           cadena_Decod+='1';
                           unos+=1;
                       }


                     }


                }
                seguir+=1;

            }


                }


        if(ceros==unos){
            for(int i=0;i<sobrante;i++){
               if(cadena_codificada[(seguir*n)+i]=='0'){
                        cadena_Decod+='1';
                    }
                else{
                        cadena_Decod+='0';
                         }
                        }
            }


         else if(ceros>unos){
              for(int k=0;k<(sobrante);k++){
                 if(k%2!=0){
                       if(cadena_codificada[(seguir*n)+k]=='0'){
                            cadena_Decod+='1';
                        }

                        else{
                            cadena_Decod+='0';
                                    }
                         }
                       }
               }

         else{

              for(int j=1;j<=(sobrante);j++){
                     if(j%3==0){

                            if(cadena_codificada[(seguir*n)+(j-1)]=='0'){
                                cadena_Decod+='1';
                                }

                             else{
                                cadena_Decod+='0';

                                }

                        }

                      else{
                            if(cadena_codificada[(seguir*n)+(j-1)]=='0'){
                                cadena_Decod+='0';

                             }

                            else{
                                cadena_Decod+='1';

                                }

                      }


                }


        }
}

return cadena_Decod;


}


string decotwo(string cadena_codificada, int n){

    string cadena_Decod="";
    int j=(n-1);
    int tamano=cadena_codificada.length();
    int lon=(tamano)/n;  //cantidad de bloques de n bits
    int modulo=(tamano)%n; //variable que indica la cantidad de elementos sobrantes en caso de que la
                           //la cadena_Binaria(string del ASCC), no se pueda dividir exactamente en bloques
                           //de n bits
    int falta=modulo-1, seguir=0;


    //Si el string en binario se puede dividir exactamente en grupos de n bits:
    if (modulo==0){

         while(seguir<lon){

             for(int indice=(j-1);indice>=0;indice--){
             cadena_Decod+=cadena_codificada[((seguir*n)+j)-indice];

             }
             cadena_Decod+=cadena_codificada[(seguir*n)];

             seguir++;//contador que indica la cantidad de bloques procesados

              }


          }


    //Si el string en binario se puede dividir exactamente en grupos de n bits:
    else{

        while(seguir<lon){

            for(int indice=(j-1);indice>=0;indice--){
            cadena_Decod+=cadena_codificada[((seguir*n)+j)-indice];
            }
            cadena_Decod+=cadena_codificada[(seguir*n)];

            seguir++;

             }


        for(int i=(falta-1);i>=0;i--){
            cadena_Decod+=cadena_codificada[(tamano-1)-i];

        }

         cadena_Decod+=cadena_codificada[tamano-modulo];

    return cadena_Decod;

    }
}



void escritura(string archivo,string texto){

    ofstream outfile;

    outfile.open(archivo);

    if (!outfile.is_open()){
        cout<<"Error abriendo el archivo de escritura"<<endl;
        exit(1);
    }

    outfile<<texto;

    outfile.close();

}


string lectura(string archivotxt){

    string data,texto;     //variable que almacena el texto
    ifstream infile;       //data-->almacena palabra a palabra del txt
                           //texto-->recolecta una a una las palabra (data) del txt

     // PARA LEER EN TXT

     // cout<<"Ingrese el archivo para leer ";cin>>lect;
     infile.open(archivotxt);

     if (!infile.is_open())
          {
            cout << "Error abriendo el archivo" << endl;
            exit(1);
          }


          cout << "!Apertura de arcchivo EXITOSA¡" << endl;

          int cont = 0;
          while(!infile.eof()){
                cont++;
                if (cont > 1){
                    data+= '\n';
                }
                getline(infile,texto);
                data+=texto;


          }

          infile.close();

          return data;

}

string txt1(){
      string txtentrada="";
      cout<<"Ingrese el nombre del archivo de entrada "<<endl;
      cin>>txtentrada;

      return txtentrada;
}


string txt2(){
      string txtsalida="";
      cout<<"Ingrese el nombre del archivo de salida "<<endl;
      cin>>txtsalida;

      return txtsalida;
}


void codificar(int n,int met, string txtin , string txtout ){

        string texto=lectura(txtin);
        if (met==1){
            string cadenabinaria=binario(texto);
            string final=codone(cadenabinaria,n);
            escritura(txtout,final);
        }

         else{
            string cadenabinaria=binario(texto);
            string final=codtwo(cadenabinaria,n);
            escritura(txtout,final);
         }

}


void decodificar(int n,int met, string txtin , string txtout ){

        string texto=lectura(txtin);
        if (met==1){
            string final=decone(texto,n);
            escritura(txtout,final);
        }

         else{
            string final=decotwo(texto,n);
            escritura(txtout,final);
         }

}


#endif // CODECO_H
