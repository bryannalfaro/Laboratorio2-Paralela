#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//comparar
int compare (const int * a, const int * b) //what is it returning?
{
   return ( *(int*)a - *(int*)b ); //What is a and b?
}

void par_qsort(int *data, int lo, int hi) //}, int (*compare)(const int *, const int*))
{
  if(lo > hi) return;
  int l = lo;
  int h = hi;
  int p = data[(hi + lo)/2];

  while(l <= h){
    while((data[l] - p) < 0) l++;
    while((data[h] - p) > 0) h--;
    if(l<=h){
      //swap
      int tmp = data[l];
      data[l] = data[h];
      data[h] = tmp;
      l++; h--;
    }
  }
  //recursive call
  par_qsort(data, lo, h);
  par_qsort(data, l, hi);
}

int main(int argc, char * argv[]) {

    int n = 10;
    int Array[n];
    int j;

    printf("Generando lista random con %d elementos\n", n);

    for (j=0; j<n; j++)
        Array[j] = rand()%10;

    FILE *fp;
    fp = fopen("aleatorios.csv", "w");
    //Print array
    for (j=0; j<n-1; j++){
        //Write to file in csv separated by comma
        fprintf(fp, "%d,", Array[j]);
    }
    fprintf(fp, "%d", Array[n-1]);
    fclose(fp);

    //Read file
    FILE *fp2;
    fp2 = fopen("aleatorios.csv", "r");
    int i = 0;
    char ch;
    //Read with fscanf
    while (fscanf(fp2, "%d,", &Array[i]) != EOF){
        i++;
    }
    //Print array
    for (j=0; j<n; j++){
        printf("%d ", Array[j]);
    }

    fclose(fp2);

    //Sort array
    par_qsort(Array, 0, n-1);
    printf("\n");
    //Print array
    for (j=0; j<n; j++){
        printf("%d ", Array[j]);
    }

    //Write into another file
    FILE *fp3;
    fp3 = fopen("ordenados.csv", "w");

    for (j=0; j<n-1; j++){
        //Write to file in csv separated by comma
        fprintf(fp3, "%d,", Array[j]);
    }
    fprintf(fp3, "%d", Array[n-1]);
    fclose(fp3);




    /*----------
     *Constructor del manejador de archivos
     *
     *  in/out - fstream <identificador>("<archivo>",modo)
     *  out only - ofstream <identificador>("<archivo>",modo)
     *  in only - ifstream <identificador>("<archivo>")
     *
     *  modos:
     *      ios::app - append to file
     *      ios::out - new/overwrite file
     *      ios::binary - nontext input & output
     *      ios::in - read from file
     */
    /*ofstream escribirNumeros(INFILE,ios::out);
    if( escribirNumeros.bad() ) {
        cerr<<"Falló la creación del archivo "<<INFILE<<endl;
        exit(EXIT_FAILURE);
    }

    //Llenamos el archivo INFILE con números
    for(int i=0; i<limit;i++){
        escribirNumeros<<i<<",";
    }
    escribirNumeros<<limit<<endl;
    escribirNumeros.close();    //Cerramos el archivo si no lo vamos a usar nuevamente

    //Constructores para lectura de archivo y escritura de resultados
    //Esta es otra forma de realizar el manejo de arhivos
    ifstream leerNumeros;
    leerNumeros.open(INFILE);
    if( leerNumeros.bad() ) {
        cerr<<"No se pudo leer el archivo "<<INFILE<<endl;
        exit(EXIT_FAILURE);
    }

    ofstream escribirPrimos;
    escribirPrimos.open(OUTFILE);
    if( escribirPrimos.bad() ) {
        cerr<<"No se pudo crear el archivo "<<OUTFILE<<endl;
        exit(EXIT_FAILURE);
    }

    //Probamos que un número sea primo y lo escribimos al archivo OUTFILE
    string ch;
    while(getline(leerNumeros,ch,',')) {

        int numero = stoi(ch);  //Debemos convertir el string a int

        if(isPrime(numero)) {
            cout<<ch<<" ";
            escribirPrimos<<ch<<" ";
        }
    }
    cout<<endl;*/



    return 0;
}