#include <iostream>
#include "ConexionBD.h"
#include "Puestos.h"
#include "Marcas.h"
#include "Proveedores.h"
#include "Clientes.h"
using namespace std;

void menuPuestos();
void menuMarcas();
void menuProveedores();
void menuClientes();

int main()
{
    int opcion;

    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "   SISTEMA DE INVENTARIO - SUPERMERCADO" << endl;
        cout << "========================================" << endl;
        cout << "1. Mantenimiento de puestos" << endl;
        cout << "2. Mantenimiento de marcas" << endl;
        cout << "3. Mantenimiento de proveedores" << endl;
        cout << "4. Mantenimiento de clientes" << endl;
        cout << "0. Salir del programa" << endl;
        cout << "========================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuPuestos();
            break;
        case 2:
            menuMarcas();
            break;
        case 3:
            menuProveedores();
            break;
        case 4:
            menuClientes();
            break;
        case 0:
            cout << "\nSaliendo del sistema..." << endl;
            break;
        default:
            cout << "\nOpcion no valida, intente de nuevo" << endl;
            system("pause");
            break;
        }
    } while (opcion != 0);
}


void menuPuestos() {
    int opcion_p, id_puesto;
    string puesto;
    
    Puestos p = Puestos(0, puesto);

    do {
        system("cls");
        cout << ">>> MENU: MANTENIMIENTO PUESTOS <<<" << endl;
        cout << "1. Listar puestos" << endl;
        cout << "2. Crear nuevo puesto" << endl;
        cout << "3. Actualizar puesto" << endl;
        cout << "4. Eliminar puesto" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione: ";
        cin >> opcion_p;
        cin.ignore(256, '\n');
   
    switch (opcion_p) {
    case 1:
        p.leer();
        break;

    case 2:
        //crear y leer
        cout << "Ingrese el nombre del puesto (ej. Gerente): ";
        getline(cin, puesto);

        p.setPuesto(puesto);

        p.crear();
        p.leer();

        puesto = "";

        cout << "------------------------------------" << endl;
        break;


    case 3:
        //actualizar
        cout << "Ingrese el ID a modificar: ";
        cin >> id_puesto;
        cin.ignore(256, '\n');
        cout << "Ingrese el puesto: ";
        getline(cin, puesto);

        p.setId_puesto(id_puesto);
        p.setPuesto(puesto);

        p.actualizar();
        p.leer();

        puesto = "";
        break;


    case 4:
        //eliminar
        cout << "Ingrese el ID a eliminar: ";
        cin >> id_puesto;
        p.setId_puesto(id_puesto);
        p.borrar();
        p.leer();
        break;
    }
    if (opcion_p != 0) system("pause");
  } while (opcion_p != 0); 
}

void menuMarcas() {
    int opcion_m, id_marca;
    string marca;

    Marcas m = Marcas(0, marca);

    do {
        system("cls");
        cout << ">>> MENU: MANTENIMIENTO MARCAS <<<" << endl;
        cout << "1. Listar marcas" << endl;
        cout << "2. Crear nueva marca" << endl;
        cout << "3. Actualizar marca" << endl;
        cout << "4. Eliminar marca" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione: ";
        cin >> opcion_m;
        cin.ignore(256, '\n');

        switch (opcion_m) {
        case 1:
            m.leer();
            break;

        case 2:
            //crear y leer
            cout << "Ingrese el nombre de la marca (ej. Nike): ";
            getline(cin, marca);

            m.setMarca(marca);

            m.crear();
            m.leer();

            marca = "";

            cout << "------------------------------------" << endl;
            break;


        case 3:
            //actualizar
            cout << "Ingrese el ID a modificar: ";
            cin >> id_marca;
            cin.ignore(256, '\n');
            cout << "Ingrese la marca: ";
            getline(cin, marca);

            m.setId_marca(id_marca);
            m.setMarca(marca);

            m.actualizar();
            m.leer();

            marca = "";
            break;


        case 4:
            //eliminar
            cout << "Ingrese el ID a eliminar: ";
            cin >> id_marca;
            m.setId_marca(id_marca);
            m.borrar();
            m.leer();
            break;
        }
        if (opcion_m != 0) system("pause");
    } while (opcion_m != 0);
}

void menuProveedores() {
    int opcion_pv, id_proveedor;
    string proveedor, nit, direccion, telefono;

    Proveedores pr = Proveedores(0, proveedor, nit, direccion, telefono);

    do {
        system("cls");
        cout << ">>> MENU: MANTENIMIENTO PROVEEDORES <<<" << endl;
        cout << "1. Listar proveedor" << endl;
        cout << "2. Crear nuevo proveedor" << endl;
        cout << "3. Actualizar proveedor" << endl;
        cout << "4. Eliminar proveedor" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione: ";
        cin >> opcion_pv;
        cin.ignore(256, '\n');

        switch (opcion_pv) {
        case 1:
            pr.leer();
            break;

        case 2:
            //crear y leer
            cout << "Ingrese el nombre del proveedor (ej. Pepsi): ";
            getline(cin, proveedor);
            cout << "Ingrese el NIT del proveedor : ";
            getline(cin, nit);
            cout << "Ingrese la direccion del proveedor : ";
            getline(cin, direccion);
            cout << "Ingrese el telefono del proveedor : ";
            getline(cin, telefono);

            pr.setProveedor(proveedor);
            pr.setNit(nit);
            pr.setDireccion(direccion);
            pr.setTelefono(telefono);

            pr.crear();
            pr.leer();

            proveedor = ""; nit = ""; direccion = ""; telefono = "";

            cout << "------------------------------------" << endl;
            break;


        case 3:
            //actualizar
            cout << "Ingrese el ID a modificar: ";
            cin >> id_proveedor;
            cin.ignore(256, '\n');
            cout << "Ingrese el nuevo nombre del proveedor: ";
            getline(cin, proveedor);
            cout << "Ingrese el nuevo NIT del proveedor: ";
            getline(cin, nit);
            cout << "Ingrese la nueva direccion del proveedor: ";
            getline(cin, direccion);
            cout << "Ingrese el nuevo numero de telefono del proveedor: ";
            getline(cin, telefono);

            pr.setId_proveedor(id_proveedor);
            pr.setProveedor(proveedor);
            pr.setNit(nit);
            pr.setDireccion(direccion);
            pr.setTelefono(telefono);

            pr.actualizar();
            pr.leer();

            proveedor = ""; nit = ""; direccion = ""; telefono = "";
            break;


        case 4:
            //eliminar
            cout << "Ingrese el ID a eliminar: ";
            cin >> id_proveedor;
            pr.setId_proveedor(id_proveedor);
            pr.borrar();
            pr.leer();
            break;
        }
        if (opcion_pv != 0) system("pause");
    } while (opcion_pv != 0);

}

void menuClientes() {

    int opcion_c, id_cliente, genero = 0;
    string nombres,apellidos, nit, telefono, correo_electronico, fecha_ingreso;

    Clientes c = Clientes(0, nombres,apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso);

    do {
        system("cls");
        cout << ">>> MENU: MANTENIMIENTO CLIENTES <<<" << endl;
        cout << "1. Listar clientes" << endl;
        cout << "2. Crear nuevo cliente" << endl;
        cout << "3. Actualizar cliente" << endl;
        cout << "4. Eliminar cliente" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Seleccione: ";
        cin >> opcion_c;
        cin.ignore(256, '\n');

        switch (opcion_c) {
        case 1:
            c.leer();
            break;

        case 2:
            //crear y leer
            cout << "Ingrese el nombre del cliente : ";
            getline(cin, nombres);
            cout << "Ingrese el apellido del cliente: ";
            getline(cin, apellidos);
            cout << "Ingrese el NIT del cliente (o enter para CF): ";
            getline(cin, nit);
            if (nit.empty() or nit == "cf" or nit == "CF") {
                nit = "C/F";
            }
            cout << "Ingrese el genero del cliente(0: Masculino / 1: Femenino): ";
            cin >> genero;
            cin.ignore(256, '\n');
            cout << "Ingrese el numero de telefono del cliente: ";
            getline(cin, telefono);
            cout << "Ingrese el correo electronico del cliente: ";
            getline(cin, correo_electronico);


            c.setNombres(nombres);
            c.setApellidos(apellidos);
            c.setNit(nit);
            c.setGenero(genero);
            c.setTelefono(telefono);
            c.setCorreo_electronico(correo_electronico);

            c.crear();
            c.leer();

            nombres = ""; apellidos = ""; nit = ""; telefono = ""; correo_electronico = "";
            break;

            cout << "------------------------------------" << endl;
            break;


        case 3:
            //actualizar
            cout << "Ingrese el ID del cliente que desea modificar: ";
            cin >> id_cliente;
            cin.ignore(256, '\n'); //
            cout << "Ingrese el nombre del cliente : ";
            getline(cin, nombres);
            cout << "Ingrese el apellido del cliente: ";
            getline(cin, apellidos);
            cout << "Ingrese el nuevo NIT: ";
            getline(cin, nit);
            cout << "Ingrese el genero del cliente(0: Masculino / 1: Femenino): ";
            cin >> genero;
            cin.ignore(256, '\n');
            cout << "Ingrese el numero de telefono del cliente: ";
            getline(cin, telefono);
            cout << "Ingrese el correo electronico del cliente: ";
            getline(cin, correo_electronico);

            c.setId_cliente(id_cliente);
            c.setNombres(nombres);
            c.setApellidos(apellidos);
            c.setNit(nit);
            c.setGenero(genero);
            c.setTelefono(telefono);
            c.setCorreo_electronico(correo_electronico);

            c.actualizar();
            c.leer();

            nombres = ""; apellidos = ""; nit = ""; telefono = ""; correo_electronico = "";
            break;


        case 4:
            //eliminar
            cout << "Ingrese el ID a eliminar: ";
            cin >> id_cliente;
            c.setId_cliente(id_cliente);
            c.borrar();
            c.leer();
            break;
        }
        if (opcion_c != 0) system("pause");
    } while (opcion_c != 0);
}


    
   



