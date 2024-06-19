#pragma once
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

void cargarCadena(char *pal, int tam){
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++) {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

class Fecha {
private:
    int dia, mes, anio;
public:
    void Cargar(){
        cin >> dia >> mes >> anio;
    }
    void Mostrar(){
        cout << dia << "/" << mes << "/" << anio << endl;
    }
    int getDia(){ return dia; }
    int getMes(){ return mes; }
    int getAnio(){ return anio; }
    void setDia(int d){ dia = d; }
    void setMes(int m){ mes = m; }
    void setAnio(int a){ anio = a; }
};

class Proveedor {
private:
    int numeroProveedor;
    char nombre[30];
    char provincia[30];
    bool estado;
public:
    void Cargar(){
        cout << "Numero de Proveedor: ";
        cin >> numeroProveedor;
        cout << "Nombre: ";
        cargarCadena(nombre, 29);
        cout << "Provincia: ";
        cargarCadena(provincia, 29);
        estado = true;
    }
    void Mostrar(){
        cout << "Numero de Proveedor: " << numeroProveedor << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Provincia: " << provincia << endl;
        if (!estado) cout << "ESTA INACTIVO" << endl;
    }
    void setNumeroProveedor(int num){ numeroProveedor = num; }
    void setNombre(const char* nom){ strcpy(nombre, nom); }
    void setProvincia(const char* prov){ strcpy(provincia, prov); }
    void setEstado(bool est){ estado = est; }
    int getNumeroProveedor(){ return numeroProveedor; }
    const char* getNombre(){ return nombre; }
    const char* getProvincia(){ return provincia; }
    bool getEstado(){ return estado; }
};

class ArchivoProveedores {
private:
    char nombre[30];
public:
    ArchivoProveedores(const char* n){
        strcpy(nombre, n);
    }
    Proveedor leerRegistro(int pos){
        Proveedor reg;
        reg.setEstado(false);
        FILE* p = fopen(nombre, "rb");
        if (p == NULL) return reg;
        fseek(p, sizeof reg * pos, 0);
        fread(&reg, sizeof reg, 1, p);
        fclose(p);
        return reg;
    }
    int contarRegistros(){
        FILE* p = fopen(nombre, "rb");
        if (p == NULL) return -1;
        fseek(p, 0, 2);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Proveedor);
    }
    bool grabarRegistro(Proveedor reg){
        FILE* p = fopen(nombre, "ab");
        if (p == NULL) return false;
        bool escribio = fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        return escribio;
    }
    void listarProveedoresSinCompras(const char* archivoCompras, const char* archivoSalida, int anioActual);
};

struct Compra {
    int numeroProveedor;
    Fecha fechaCompra;
    // Otros campos que puedan ser necesarios
};

void ArchivoProveedores::listarProveedoresSinCompras(const char* archivoCompras, const char* archivoSalida, int anioActual) {
    FILE* pCompras = fopen(archivoCompras, "rb");
    if (pCompras == NULL) {
        cout << "No se pudo abrir el archivo de compras." << endl;
        return;
    }

    int cantidadProveedores = contarRegistros();
    bool* proveedoresConCompras = new bool[cantidadProveedores];
    for (int i = 0; i < cantidadProveedores; i++) {
        proveedoresConCompras[i] = false;
    }

    Compra compra;
    while (fread(&compra, sizeof(Compra), 1, pCompras)) {
        if (compra.fechaCompra.getAnio() == anioActual) {
            int numeroProveedor = compra.numeroProveedor;
            for (int i = 0; i < cantidadProveedores; i++) {
                Proveedor proveedor = leerRegistro(i);
                if (proveedor.getNumeroProveedor() == numeroProveedor) {
                    proveedoresConCompras[i] = true;
                    break;
                }
            }
        }
    }
    fclose(pCompras);

    FILE* pSalida = fopen(archivoSalida, "wb");
    if (pSalida == NULL) {
        cout << "No se pudo abrir el archivo de salida." << endl;
        delete[] proveedoresConCompras;
        return;
    }

    for (int i = 0; i < cantidadProveedores; i++) {
        if (!proveedoresConCompras[i]) {
            Proveedor proveedor = leerRegistro(i);
            fwrite(&proveedor, sizeof(Proveedor), 1, pSalida);
        }
    }
    fclose(pSalida);
    delete[] proveedoresConCompras;
}

int main() {
    ArchivoProveedores archivoProveedores("proveedores.dat");

    int opcion;
    int anioActual = 2024; // Puedes actualizar esto según el año actual

    do {
        cout << "---- MENU ----" << endl;
        cout << "1 - Agregar Proveedor" << endl;
        cout << "2 - Listar Proveedores" << endl;
        cout << "3 - Listar Proveedores sin Compras" << endl;
        cout << "0 - Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            Proveedor proveedor;
            proveedor.Cargar();
            if (archivoProveedores.grabarRegistro(proveedor)) {
                cout << "Proveedor agregado correctamente" << endl;
            } else {
                cout << "Error al agregar proveedor" << endl;
            }
            break;
        }
        case 2: {
            int cantidad = archivoProveedores.contarRegistros();
            for (int i = 0; i < cantidad; i++) {
                Proveedor proveedor = archivoProveedores.leerRegistro(i);
                proveedor.Mostrar();
            }
            break;
        }
        case 3: {
            archivoProveedores.listarProveedoresSinCompras("compras.dat", "proveedores_sin_compras.dat", anioActual);
            cout << "Listado de proveedores sin compras generado en 'proveedores_sin_compras.dat'" << endl;
            break;
        }
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 0);

    return 0;
}
