#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"
using namespace std;

class Clientes
{
private:
	int genero, id_cliente = 0;
	string nombres, apellidos, nit, telefono, correo_electronico,fecha_ingreso;

	//constructor
public:
	Clientes();
	Clientes(int idcli, string nom, string ape, string n, int gen, string tel, string corr, string fechin) {
		id_cliente = idcli;
		genero = gen;
		nombres = nom;
		apellidos = ape;
		nit = n;
		telefono = tel;
		correo_electronico = corr;
		fecha_ingreso = fechin;


	}
	//metodos get y set
	void setId_cliente(int idcli) { id_cliente = idcli; }
	void setGenero(int gen) { genero = gen; }
	void setNombres(string nom) { nombres = nom; }
	void setApellidos(string ape) { apellidos = ape; }
	void setNit(string n) { nit = n; }
	void setTelefono(string tel) { telefono = tel; }
	void setCorreo_electronico(string corr) { correo_electronico = corr; }
	void setFecha_ingreso(string fechin) { fecha_ingreso = fechin; }

	//get
	int getId_cliente() { return id_cliente; }
	int getGenero() { return genero; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getNit() { return nit; }
	string getTelefono() { return telefono; }
	string getCorreo_electronico() { return correo_electronico; }
	string getFecha_ingreso() { return fecha_ingreso; }

	//CRUD
	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string gen_string = to_string(genero);
			string consulta = "INSERT INTO clientes(nombres,apellidos,nit,genero,telefono,correo_electronico,fecha_ingreso) VALUES ('" + nombres + "','" + apellidos + "','" + nit + "'," + gen_string + ",'" + telefono + "','" + correo_electronico + "',NOW())";
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

			string consulta = "SELECT id_cliente, nombres, apellidos, nit, CAST(genero AS UNSIGNED), telefono, correo_electronico, fecha_ingreso FROM clientes";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());

				cout << "--------- PROVEEDORES REGISTRADOS ---------" << endl;
				cout << "ID   |   Nombres   |  Apellidos  |  Nit  |  Genero  |   Telefono  |  Correo Electronico  |  Fecha de ingreso  | " << endl;
				cout << "---------------------------------------" << endl;

				while (fila = mysql_fetch_row(resultado)) {
					// fila[0] es el id y asi sucesivamente
					cout << fila[0] << " | " << fila[1] << " | " << fila[2] << "|" << fila[3] << "|" << fila[4] <<" | " << fila[5] << " | " << fila[6] << " | " << fila[7] <<  endl;
				}
				cout << "---------------------------------------" << endl;
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
			string gen_string = to_string(genero);
			string id_cc = to_string(id_cliente);
			string consulta = "UPDATE clientes SET "
				"nombres = '" + nombres + "', "
				"apellidos = '" + apellidos + "', "
				"nit = '" + nit + "', "
				"genero = " + gen_string + ", "
				"telefono = '" + telefono + "', "
				"correo_electronico = '" + correo_electronico + "' "
				"WHERE id_cliente = " + (id_cc);
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
			string id_cc = to_string(id_cliente);
			string consulta = "delete from clientes where id_cliente = " + id_cc + " ";
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

