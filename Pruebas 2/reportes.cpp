///Ejercicio:
///Autor:DEK
///Fecha:
///Comentario:

# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace std;

# include "parcial2.h"


class ProveedorSinCompras{
    private:
        int numeroProveedor,provincia;
        char nombre[30];
        bool estado;
    public:
        void setNumero(int n){numeroProveedor=n;}
        void setProvincia(int p){provincia=p;}
        void setNombre(const char *n){strcpy(nombre,n);}
};

class ArchivoProveedoresSin{
    private:
        char nombre[30];
    public:
        ArchivoProveedoresSin(const char *n="nuevo.dat"){
            strcpy(nombre, n);
        }
        bool Resetear(){
            FILE *p;
            p=fopen(nombre, "wb");
            if(p==NULL) return false;
            fclose(p);
            return true;
        }

        ProveedorSinCompras leerRegistro(int pos){
            ProveedorSinCompras reg;
            reg.setNumero(-1);
            FILE *p;
            p=fopen(nombre, "rb");
            if(p==NULL) return reg;
            fseek(p, sizeof reg*pos,0);
            fread(&reg, sizeof reg,1, p);
            fclose(p);
            return reg;
        }
        int contarRegistros(){
            FILE *p;
            p=fopen(nombre, "rb");
            if(p==NULL) return -1;
            fseek(p, 0,2);
            int tam=ftell(p);
            fclose(p);
            return tam/sizeof(ProveedorSinCompras);
        }
        bool grabarRegistro(ProveedorSinCompras reg){
            FILE *p;
            p=fopen(nombre, "ab");
            if(p==NULL) return false;
            bool escribio=fwrite(&reg, sizeof reg,1, p);
            fclose(p);
            return escribio;
        }

};

void punto1();
    bool contarComprasProveedor(int np, int anio);

void punto2();
    int minimoVector(int *vTipos, int tam);

bool punto3();

int main(){
    punto1();
    punto2();
    punto3();
	cout<<endl;
	system("pause");
	return 0;
}


void punto1(){
    Proveedor reg;
    ArchivoProveedores archiP("proveedores.dat");
    ProveedorSinCompras aux;
    ArchivoProveedoresSin archiNuevo;
    archiNuevo.Resetear();

    int cantReg=archiP.contarRegistros();
    bool tuvoCompras;
    for(int i=0;i<cantReg;i++){
        reg=archiP.leerRegistro(i);
        tuvoCompras=contarComprasProveedor(reg.getNumeroProveedor(), 2024);
        if(tuvoCompras==false){
            ///setear el registro del archivo nuevo
            aux.setNumero(reg.getNumeroProveedor());
            aux.setProvincia(reg.getProvincia());
            aux.setNombre(reg.getNombre());
            ///grabar el registro en el archivo
            archiNuevo.grabarRegistro(aux);
        }
    }
}

bool contarComprasProveedor(int np, int anio){
    Compra reg;
    ArchivoCompras archiC("compras.dat");

    int cantReg=archiC.contarRegistros();
    for(int i=0;i<cantReg;i++){
        reg=archiC.leerRegistro(i);
        if(reg.getNumeroproveedor()==np && reg.getFechaCompra().getAnio()==anio)
            return true;
    }
    return false;

}

void punto2(){
    Material reg;
    ArchivoMateriales archiM("materiales.dat");
    int vTipos[6]={0};

    int cantReg=archiM.contarRegistros();
    for(int i=0;i<cantReg;i++){
        reg=archiM.leerRegistro(i);
        vTipos[reg.getTipo()-1]++;

    }
    cout<<"EL TIPO CON MENOS MATERIALES ES "<<minimoVector(vTipos, 6)+1<<endl;
}

int minimoVector(int *vTipos, int tam){

    return 1;
}


bool punto3(){
    Material *pMat, reg;
    ArchivoMateriales archiM("materiales.dat");
    int cantReg=archiM.contarRegistros();
    pMat=new Material[cantReg];
    if(pMat==NULL) return false;

    for(int i=0;i<cantReg;i++){
        reg=archiM.leerRegistro(i);
        pMat[i]=reg;
    }
    int tipo;
    cout<<"INGRESE EL TIPO PARA LISTAR ";
    cin>>tipo;
    for(int i=0;i<cantReg;i++){
            if(pMat[i].getTipo()==tipo){
                pMat[i].Mostrar();
            }
        }
    delete pMat;
    return true;
}

///Otro enunciado distinto
///Copiar en un vector dinámico los materiales pertenecientes a un tipo de material
///que se ingresa por teclado.
///Listar el vector

bool otropunto3(){
    Material *pMat, reg;
    ArchivoMateriales archiM("materiales.dat");
    int cantReg=archiM.contarRegistros();

    int cant, tipo, pos=0;

    cout<<"INGRESE EL TIPO PARA LISTAR ";
    cin>>tipo;
    for(int i=0;i<cantReg;i++){
        reg=archiM.leerRegistro(i);
        if(reg.getTipo()==tipo) cant++;
    }
    if(cant>0){
        pMat=new Material[cant];
        if(pMat==NULL) return false;
        for(int i=0;i<cantReg;i++){
            reg=archiM.leerRegistro(i);
            if(reg.getTipo()==tipo){
            pMat[pos]=reg;
            pos++;
            }
        }

    for(int i=0;i<pos;i++){
        pMat[i].Mostrar();
        }
    }

    delete pMat;
    return true;
}
