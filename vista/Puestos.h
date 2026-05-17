#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "ConexionBD.h"
using namespace std;

class Puestos
{
private : 
	int id_puesto = 0;
	string puesto;
		
	//constructor
public : 
	Puestos();
	Puestos(int idpue, string pue) {
		id_puesto = idpue;
		puesto = pue;
	
	}
	//metodos get y set
	void setId_puesto(int idpue) { id_puesto = idpue; }
	void setPuesto(string pue) { puesto = pue; }

	//get
	int getId_puesto() {return id_puesto;}
	string getPuesto() {return puesto;	}

	//CRUD
	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			
			string consulta = "INSERT INTO puestos(puesto) VALUES ('" + puesto + "') ";
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

			string consulta = "SELECT id_puesto, puesto FROM puestos;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());

				
				cout << "\n=================================== PUESTOS REGISTRADOS ===================================\n";
				cout << left << setw(8) << "ID"
					<< setw(30) << "Puesto / Rol" << "\n";
				cout << "------------------------------------------------------------------------------------------\n";

				
				while (fila = mysql_fetch_row(resultado)) {
					
					cout << left << setw(8) << (fila[0] ? fila[0] : "N/A")
						<< setw(30) << (fila[1] ? fila[1] : "N/A") << "\n";
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
			string id_p = to_string(id_puesto);
			string consulta = "update puestos set puesto = '" + puesto + "'  where id_puesto = " + id_p + " ";
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
			string id_p = to_string(id_puesto);
			string consulta = "delete from puestos where id_puesto = " + id_p + " ";
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

