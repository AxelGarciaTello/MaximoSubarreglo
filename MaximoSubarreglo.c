#include <stdio.h>
#include <stdlib.h>

#define INFINITONEG -1000000

void MaxCrossingSubArray(int A[], int bajo, int mitad, int alto,
  int *max_izq, int *max_der, int *sumaTotal){
  int sumaIzq=INFINITONEG,
      suma=0,
      i=0,
      maxIzq=0,
      sumaDer=INFINITONEG,
      j=0,
      maxDer;
  for(i=mitad; i>=bajo; i--){
    suma+=A[i];
    if(suma>sumaIzq){
      sumaIzq=suma;
      maxIzq=i;
    }
  }
  suma=0;
  for(j=mitad+1; j<=alto; j++){
    suma+=A[j];
    if(suma>sumaDer){
      sumaDer=suma;
      maxDer=j;
    }
  }
  *max_izq=maxIzq;
  *max_der=maxDer;
  *sumaTotal=sumaIzq+sumaDer;
}

void MaxSubArrayDC(int A[], int bajo, int alto, int *izq, int *der,
  int *suma){
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
  if(alto==bajo){
    *izq=bajo;
    *der=alto;
    *suma=A[bajo];
  }
  else{
    mitad=(bajo+alto)/2;
    MaxSubArrayDC(A, bajo, mitad, &bajo_izq, &alto_izq, &suma_izq);
    MaxSubArrayDC(A, mitad+1, alto, &bajo_der, &alto_der, &suma_der);
    MaxCrossingSubArray(A, bajo, mitad, alto, &cruz_izq, &cruz_der,
      &suma_cruz);
    if(suma_izq>suma_der && suma_izq>suma_cruz){
      *izq=bajo_izq;
      *der=alto_izq;
      *suma=suma_izq;
    }
    else if(suma_der>suma_izq && suma_der>suma_cruz){
      *izq=bajo_der;
      *der=alto_der;
      *suma=suma_der;
    }
    else{
      *izq=cruz_izq;
      *der=cruz_der;
      *suma=suma_cruz;
    }
  }
}

int main(void){
  int A[]={13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15,
    -4, 7};
  int izq=0,
      der=0,
      suma=0;
  MaxSubArrayDC(A, 0, 15, &izq, &der, &suma);
  printf("Izquierda: %d\tDerecha:%d\tSuma=%d\n", izq, der, suma);
}
