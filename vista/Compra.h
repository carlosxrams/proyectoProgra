#pragma once
#include <iostream>
#include <iomanip>
#include "ConexionBD.h"
#include "Productos.h"
#include "Proveedores.h"

using namespace std;
class Compra{
private : 
	int id_proveedor = 0;
	string no_orden_compra, fecha_orden, fecha_ingreso;

//constructor
public : 
	Compra() {};
	Compra(int idprov, string nocomp, string fechord, string feching) {
		id_proveedor = idprov;
		no_orden_compra = nocomp;
		fecha_orden = fechord;
		fecha_ingreso = feching;
	}

//metodo set
	void setId_proveedor(int idprov) { id_proveedor = idprov; }
	void setNo_orden_compra(string nocomp) { no_orden_compra = nocomp; }
	void setFecha_orden(string fechord) { fecha_orden = fechord; }
	void setFecha_ingreso(string feching) { fecha_ingreso = feching; }

//get




};

