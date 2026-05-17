#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "ConexionBD.h"
using namespace std;
class Proveedores
{
private:
	int id_proveedor = 0;
	string proveedor, nit, direccion, telefono;

	//constructor
public:
	Proveedores();
	Proveedores(int idprov, string prov, string n, string dir, string tel) {
		id_proveedor = idprov;
		proveedor = prov;
		nit = n;
		direccion = dir;
		telefono = tel;


	}
	//metodos get y set
	void setId_proveedor(int idprov) { id_proveedor = idprov; }
	void setProveedor(string prov) { proveedor = prov; }
	void setNit(string n) { nit = n; }
	void setDireccion(string dir) { direccion = dir; }
	void setTelefono(string tel) { telefono = tel; }

	//get
	int getId_proveedor() { return id_proveedor; }
	string getProveedor() { return proveedor; }
	string getNit() { return nit; }
	string getDireccion() { return direccion; }
	string getTelefono() { return telefono; }

	//CRUD
	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {

			string consulta = "INSERT INTO proveedores(proveedor,nit,direccion,telefono) VALUES ('" + proveedor + "','" + nit + "','" + direccion + "','" + telefono + "') ";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				cout << "Ingreso de datos exitoso (ID generado automaticamente)..." << endl;
			}
			else {
				cout << "Error en la consulta SQL: " << mysql_error(cn.getConector()) << endl;
			}
		}
		else {
			cout << "Conexion Fallida" << endl;
		}
		cn.cerrar_conexion();
	};
	void leer() {

		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();

		if (cn.getConector()) {

			string consulta = "SELECT id_proveedor, proveedor, nit, direccion, telefono FROM proveedores;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());

				
				cout << "\n================================================ PROVEEDORES REGISTRADOS ================================================\n";
				cout << left << setw(6) << "ID"
					<< setw(25) << "Proveedor"
					<< setw(12) << "NIT"
					<< setw(35) << "Direccion"
					<< setw(12) << "Telefono" << "\n";
				cout << "-------------------------------------------------------------------------------------------------------------------------\n";

				
				while (fila = mysql_fetch_row(resultado)) {
					
					cout << left << setw(6) << (fila[0] ? fila[0] : "N/A")
						<< setw(25) << (fila[1] ? fila[1] : "N/A")
						<< setw(12) << (fila[2] ? fila[2] : "N/A")
						<< setw(35) << (fila[3] ? fila[3] : "N/A")
						<< setw(12) << (fila[4] ? fila[4] : "N/A") << "\n";
				}
				cout << "=========================================================================================================================\n";

				mysql_free_result(resultado); 
			}
			else {
				cout << "Error al consultar los datos: " << mysql_error(cn.getConector()) << endl;
			}
		}
		else {
			cout << "Fallo la conexion con la base de datos." << endl;
		}
		cn.cerrar_conexion();
	};

	void actualizar() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string id_pv = to_string(id_proveedor);
			string consulta = "update proveedores set proveedor, nit, direccion, telefono = '" + proveedor + "','" + nit + "','" + direccion + "', '" + telefono + "'  where id_proveedor = " + id_pv + " ";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				cout << "Modificacion de datos exitoso..." << endl;
			}
			else {
				cout << "Error en la consulta SQL: " << mysql_error(cn.getConector()) << endl;
			}
		}
		else {
			cout << "Conexion Fallida" << endl;
		}
		cn.cerrar_conexion();
	};
	void borrar() {


		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string id_pv = to_string(id_proveedor);
			string consulta = "delete from proveedores where id_proveedor = " + id_pv + " ";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				cout << "Eliminacion de datos exitoso..." << endl;
			}
			else {
				cout << "Error en la consulta SQL: " << mysql_error(cn.getConector()) << endl;
			}
		}
		else {
			cout << "Conexion Fallida" << endl;
		}
		cn.cerrar_conexion();

	};
};

