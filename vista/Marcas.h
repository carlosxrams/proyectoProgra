#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "ConexionBD.h"
using namespace std;

class Marcas
{
private:
	int id_marca = 0;
	string marca;

	//constructor
public:
	Marcas();
	Marcas(int idmar, string mar) {
		id_marca = idmar;
		marca = mar;

	}
	//metodos get y set
	void setId_marca(int idmar) { id_marca = idmar; }
	void setMarca(string mar) { marca = mar; }

	//get
	int getId_marca() { return id_marca; }
	string getMarca() { return marca; }

	//CRUD
	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {

			string consulta = "INSERT INTO marcas(marca) VALUES ('" + marca + "') ";
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

			string consulta = "SELECT id_marca, marca FROM marcas;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());

				cout << "\n=================================== MARCAS REGISTRADAS ===================================\n";
				cout << left << setw(8) << "ID"
					<< setw(25) << "Marca" << "\n";
				cout << "------------------------------------------------------------------------------------------\n";

				while (fila = mysql_fetch_row(resultado)) {
					
					cout << left << setw(8) << (fila[0] ? fila[0] : "N/A")
						<< setw(25) << (fila[1] ? fila[1] : "N/A") << "\n";
				}
				cout << "==========================================================================================\n";

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
			string id_m = to_string(id_marca);
			string consulta = "update marcas set marca = '" + marca + "'  where id_marca = " + id_m + " ";
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
			string id_m = to_string(id_marca);
			string consulta = "delete from marcas where id_marca = " + id_m + " ";
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

