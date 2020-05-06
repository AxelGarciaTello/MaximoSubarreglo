/*
Instituto Politecnico Nacional
Escuela Superior de Cómputo
Analisis de algoritmos
Grupo: 3CV2
Alumnos: Garcia Tello Axel
		 Rodríguez Acosta Alan
Profesor: Benjamin Luna Benoso
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Máximo subarreglo

Fecha: 29 de abril de 2020
*/
#include <stdio.h>
#include <stdlib.h>

#define INFINITONEG -1000000

//Función para encontrar el máximo subarreglo cruzado
void MaxCrossingSubArray(int A[], int bajo, int mitad, int alto,
  int *max_izq, int *max_der, int *sumaTotal, int *contador){
  int sumaIzq=INFINITONEG,
      suma=0,
      i=0,
      maxIzq=0,
      sumaDer=INFINITONEG,
      j=0,
      maxDer;
  *contador+=7;
  for(i=mitad; i>=bajo; i--){
    *contador+=1;
    suma+=A[i]; *contador+=1;
    if(suma>sumaIzq){
      sumaIzq=suma;
      maxIzq=i;
      *contador+=2;
    }
    *contador+=1;
  }
  *contador+=1;
  suma=0; *contador+=1;
  for(j=mitad+1; j<=alto; j++){
    *contador+=1;
    suma+=A[j]; *contador+=1;
    if(suma>sumaDer){
      sumaDer=suma;
      maxDer=j;
      *contador+=2;
    }
    *contador+=1;
  }
  *contador+=1;
  *max_izq=maxIzq;
  *max_der=maxDer;
  *sumaTotal=sumaIzq+sumaDer;
  *contador+=3;
}

//Función recursiva para encontrar el máximo subarreglo
void MaxSubArrayDC(int A[], int bajo, int alto, int *izq, int *der,
  int *suma, int *contador){
  int mitad=0,
      bajo_izq=0,
      alto_izq=0,
      suma_izq=0,
      bajo_der=0,
      alto_der=0,
      suma_der=0,
      cruz_izq=0,
      cruz_der=0,
      suma_cruz=0;
  *contador+=10;
  if(alto==bajo){ //Caso limite
    *izq=bajo;
    *der=alto;
    *suma=A[bajo];
    *contador+=3;
  }
  else{
    mitad=(bajo+alto)/2; *contador+=1;
    MaxSubArrayDC(A, bajo, mitad, &bajo_izq, &alto_izq, &suma_izq, contador);
    MaxSubArrayDC(A, mitad+1, alto, &bajo_der, &alto_der, &suma_der, contador);
    MaxCrossingSubArray(A, bajo, mitad, alto, &cruz_izq, &cruz_der,
      &suma_cruz, contador);
    //Devolvemos el mayor de los valores
    if(suma_izq>suma_der && suma_izq>suma_cruz){
      *izq=bajo_izq;
      *der=alto_izq;
      *suma=suma_izq;
      *contador+=3;
    }
    else if(suma_der>suma_izq && suma_der>suma_cruz){
      *izq=bajo_der;
      *der=alto_der;
      *suma=suma_der;
      *contador+=3;
    }
    else{
      *izq=cruz_izq;
      *der=cruz_der;
      *suma=suma_cruz;
      *contador+=3;
    }
  }
}

//Función de inicio para la función de máximo subarreglo
int main(void){
  int A[]={13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
  int izq=0,
      der=0,
      suma=0,
      contador=0,
      tamanio=0,
      x=0;
  for(tamanio=3; tamanio<16; tamanio++){
    MaxSubArrayDC(A, 0, tamanio, &izq, &der, &suma, &contador);
    printf("Tamaño del arreglo: %d\t Lineas ejecutadas: %d\n", tamanio+1,
    contador);
    for(x=0; x<=tamanio; x++){
      printf("%d,", A[x]);
    }
    printf("\nMaximo Izquierda: %d\tMaximo Derecha: %d\t", izq, der);
    printf("Suma total %d\n\n\n", suma);
    contador=0;
  }
}

//Función de inicio para la función de máximo subarreglo cruzado
/*int main(void){
  int A[]={13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7,
    8, 0};
  int contador=0,
      bajo=0,
      mitad=0,
      alto=0,
      maxIzq=0,
      maxDer=0,
      sumaTotal=0,
      x=0;
  for(alto=3; alto<18; alto++){
    mitad=(alto-1)/2;
    MaxCrossingSubArray(A, bajo, mitad, alto, &maxIzq, &maxDer, &sumaTotal,
      &contador);
    printf("Tamaño del arreglo: %d\t Lineas ejecutadas: %d\n", alto+1,
      contador);
    for(x=0; x<=alto; x++){
      printf("%d,",A[x]);
    }
    printf("\nMaximo Izquierda: %d\tMaximo Derecha: %d\t", maxIzq, maxDer);
    printf("Suma Total: %d\n\n\n", sumaTotal);
    contador=0;
  }
}*/
