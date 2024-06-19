///Ejercicio:
///Autor:DEK
///Fecha:
///Comentario:

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Fecha{
private:
	int dia, mes, anio;
public:
	int getDia(){return dia;}
	int getMes(){return mes;}
	int getAnio(){return anio;}
};

class Vendedor{
	private:
		char codigoVendedor[5];
		char nombre[30];
		int provincia,calificacion;
		bool estado;
	public:
		const char *getCodigoVendedor(){return codigoVendedor;}
		const char *getNombreVendedor(){return nombre;}

		int getCalificacion(){return calificacion;};
		int getProvincia(){return provincia;}

		void setEstado(bool e){estado=e;}
};



class ArchivoVendedores{
private:
	char nombre[30];
public:
	ArchivoVendedores(const char *n="vendedores.dat"){
		strcpy(nombre, n);
	}
	Vendedor leerRegistro(int pos){
		Vendedor reg;
		reg.setEstado(false);
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
        return tam/sizeof(Vendedor);
    }
    bool grabarRegistro(Vendedor reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};



class Usuario{
private:
	char codigoUsuario[5];
	char nombre[30];
	int DNI;
	Fecha registro;
	bool estado;
public:
	void setEstado(bool e){estado=e;}
	Fecha getFechaRegistro(){return registro;}
};

class ArchivoUsuarios{
private:
	char nombre[30];
public:
	ArchivoUsuarios(const char *n="usuarios.dat"){
		strcpy(nombre, n);
	}
	Usuario leerRegistro(int pos){
		Usuario reg;
		reg.setEstado(false);
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
        return tam/sizeof(Usuario);
    }
    bool grabarRegistro(Usuario reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

class Venta{
private:
	int numeroCompra;
	char codigoVendedor[5];
	char codigoUsuario[5];
	float importe;
	Fecha fechaVenta;
	int tipoPago;
	bool estado;
public:
	const char *getCodigoVendedor(){return codigoVendedor;}
	Fecha getFechaVenta(){return fechaVenta;}
	void setEstado(bool e){estado=e;}

};

class ArchivoVentas{
private:
	char nombre[30];
public:
	ArchivoVentas(const char *n="ventas.dat"){
		strcpy(nombre, n);
	}
	Venta leerRegistro(int pos){
		Venta reg;
		reg.setEstado(false);
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
        return tam/sizeof(Venta);
    }
    bool grabarRegistro(Venta reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
        }
};

class Inactivo{
private:
	char codigoVendedor[5];
	char nombre[30];
	bool estado;
public:
	void setCodigoVendedor(const char *cv){strcpy(codigoVendedor,cv);}
	void setNombreVendedor(const char *n){strcpy(nombre,n);}
	void setEstado(bool e){estado=e;};
};

class ArchivoInactivos{
private:
	char nombre[30];
public:
	ArchivoInactivos(const char *n="inactivos.dat"){
		strcpy(nombre, n);
	}
	Inactivo leerRegistro(int pos){
		Inactivo reg;
		reg.setEstado(false);
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
        return tam/sizeof(Inactivo);
    }
    bool grabarRegistro(Inactivo reg){
        FILE *p;
        p=fopen(nombre, "ab");
        if(p==NULL) return false;
        bool escribio=fwrite(&reg, sizeof reg,1, p);
        fclose(p);
        return escribio;
    }
};

void puntoA();
void puntoB();
void puntoC();

int main() {
	puntoA();
	puntoB();
	puntoC();
	return 0;
}

bool buscarVentas(const char *cv, int anio){
	Venta reg;
	ArchivoVentas archiVe;
	int cantreg=archiVe.contarRegistros();
	for(int i=0;i<cantreg;i++){
        reg=archiVe.leerRegistro(i);

		if(reg.getFechaVenta().getAnio()==anio)
			if(strcmp(reg.getCodigoVendedor(),cv)==0)
				return true;
 	}
	return false;
}

void puntoA(){
	Inactivo aux;
	Vendedor reg;
	ArchivoInactivos archiI;
	ArchivoVendedores archiVe;
	int cantreg=archiVe.contarRegistros();
	for(int i=0;i<cantreg;i++){
        reg=archiVe.leerRegistro(i);
     	if(buscarVentas(reg.getCodigoVendedor(),2024)==false){
			aux.setCodigoVendedor(reg.getCodigoVendedor());
			aux.setNombreVendedor(reg.getNombreVendedor());
			aux.setEstado(true);
			archiI.grabarRegistro(aux);
        }
    }
}

void mostrarVector(int *v, int tam){

}

void puntoB(){
	Usuario reg;
	int v2023[12]={0};
	ArchivoUsuarios archiU;
	int cantreg=archiU.contarRegistros();
	for(int i=0;i<cantreg;i++){
        reg=archiU.leerRegistro(i);
		if(reg.getFechaRegistro().getAnio()==2023)
			v2023[reg.getFechaRegistro().getMes()-1]++;
        }
	mostrarVector(v2023, 12);
}

int buscarProvincia(const char *cv){
    ///hacer
    return 1;
}

///La cantidad de ventas realizadas por los vendedores de las provincias del Litoral
/// (números de provincia 8, 9, y 10), el primer semestre de este año.
void puntoC(){
	Venta reg;
	int cant=0, prov;
    ArchivoVentas archiVe;
	int cantreg=archiVe.contarRegistros();
	for(int i=0;i<cantreg;i++){
        reg=archiVe.leerRegistro(i);
		if(reg.getFechaVenta().getAnio()==2024 &&
           reg.getFechaVenta().getMes()<7 ){
                prov=buscarProvincia(reg.getCodigoVendedor());
                if(prov>=7 &&prov<=9)
                    cant++;
           }
	}
	cout<<"LA CANTIDAD DE VENTAS DE LOS VENDEDORES DE LITORAL FUE: "<<cant<<endl;
}
