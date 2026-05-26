#pragma once
#include <iostream>
#include <iomanip>
#include "ConexionBD.h"
#include "Productos.h"
#include "Clientes.h"

using namespace std;
class Venta{
private : 
	int id_venta = 0, id_cliente = 0, id_empleado = 0;
	string no_factura, serie, fecha_factura, fecha_ingreso;

//constructor
public : 
	Venta() {};
	Venta(int idven, string nofac, string ser, string fechfac, int idcli, int idemp, string feching) {
		id_venta = idven;
		no_factura = nofac;
		serie = ser;
		fecha_factura = fechfac;
		id_cliente = idcli;
		id_empleado = idemp;
		fecha_ingreso = feching;
	}

//metodo set
	void setId_venta(int idven) { id_venta = idven; }
	void setNo_factura(string nofac) { no_factura = nofac; }
	void setSerie(string ser) { serie = ser; }
	void setFecha_factura(string fechfac) { fecha_factura = fechfac; }
	void setId_cliente(int idcli) { id_cliente = idcli; }
	void setId_empleado(int idemp) { id_empleado = idemp; }
	void setFecha_ingreso(string feching) { fecha_ingreso = feching; }

//get
	int getId_venta() { return id_venta; }
	string getNo_factura() { return no_factura; }
	string getSerie() { return serie; }
	string getFecha_factura() { return fecha_factura; }
	int getId_cliente() {return id_cliente;}
	int getId_empleado() { return id_empleado; }
	string getFecha_ingreso() { return fecha_ingreso; }

//CRUD
	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string idcliente = to_string(id_cliente);
			string idempleado = to_string(id_empleado);
			string consulta = "INSERT INTO ventas(no_factura,serie,fecha_factura,id_cliente,id_empleado,fecha_ingreso) VALUES ('" + no_factura + "','" + serie + "',NOW()," + idcliente + "," + idempleado + ",NOW() )";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				long long id_venta_detalle = mysql_insert_id(cn.getConector());

				cout << "\n=================================================" << endl;
				cout << "Ingreso de cabecera exitoso. Factura #" << id_venta_detalle << endl;
				cout << ">>> INICIALIZANDO EL REGISTRO DE PRODUCTOS <<<" << endl;
				cout << "=================================================" << endl;

				int id_producto, cantidad;
				double precio_unitario;
				char continuar;

				do {
					cout << "\nIngrese el ID del producto a vender : ";
					cin >> id_producto;
					cout << "Ingrese la cantidad : ";
					cin >> cantidad;
					cout << "Ingrese el precio unitario : ";
					cin >> precio_unitario;
					cin.ignore(256, '\n');

					string consulta_d = "INSERT INTO ventas_detalle(id_venta, id_producto, cantidad, precio_unitario) VALUES ("
						+ to_string(id_venta_detalle) + "," + to_string(id_producto) + "," + to_string(cantidad) + "," + to_string(precio_unitario) + ")";

					int q_estado_d = mysql_query(cn.getConector(), consulta_d.c_str());

					if (!q_estado_d) {
						cout << " Articulo agregado al detalle correctamente " << endl;

						string consulta_u = "UPDATE productos SET existencia = existencia - " + to_string(cantidad) + " WHERE id_producto = " + to_string(id_producto);
						mysql_query(cn.getConector(), consulta_u.c_str());
					}
					else {
						cout << "Error al agregar al detalle: " << mysql_error(cn.getConector()) << endl;
					}

					cout << "\n¿Desea agregar otro producto a esta factura? (s/n): ";
					cin >> continuar;
					cin.ignore(256, '\n');

				} while (continuar == 's' || continuar == 'S');

				cout << "   FACTURA #" << id_venta_detalle << " CERRADA CON EXITO" << endl;
				cout << "=================================================" << endl;

				leer_factura((int)id_venta_detalle);
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

	void leer_factura(int id_venta_buscar) {
		 
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConector()) {
			MYSQL_ROW row;
			MYSQL_RES* res;

			
			string consulta_cabecera = "SELECT v.serie, v.no_factura, v.fecha_factura, "
				"c.nombres, c.apellidos, c.nit, "
				"e.nombres, e.apellidos "
				"FROM ventas v "
				"INNER JOIN clientes c ON v.id_cliente = c.id_cliente "
				"INNER JOIN empleados e ON v.id_empleado = e.id_empleado "
				"WHERE v.id_venta = " + to_string(id_venta_buscar);

			q_estado = mysql_query(cn.getConector(), consulta_cabecera.c_str());

			if (!q_estado) {
				res = mysql_store_result(cn.getConector());
				if (row = mysql_fetch_row(res)) {
					cout << "\n================= FACTURA ================\n";
					cout << "Serie: " << row[0] << " | Factura: " << row[1] << "\n";
					cout << "Fecha: " << row[2] << "\n";
					cout << "Cliente: " << row[3] << " " << row[4] << "\n";
					
					cout << "NIT: " << (row[5] ? row[5] : "C/F") << "\n";
					cout << "Atendido por: " << row[6] << " " << row[7] << "\n";
					cout << "------------------------------------------\n";
				}
				else {
					cout << "No se encontro la factura con ID: " << id_venta_buscar << endl;
					cn.cerrar_conexion();
					return;
				}
			}

			
			string consulta_detalle = "SELECT vd.cantidad, p.productos, vd.precio_unitario, "
				"(vd.cantidad * vd.precio_unitario) AS subtotal "
				"FROM ventas_detalle vd "
				"INNER JOIN productos p ON vd.id_producto = p.id_producto "
				"WHERE vd.id_venta = " + to_string(id_venta_buscar);

			q_estado = mysql_query(cn.getConector(), consulta_detalle.c_str());
			if (!q_estado) {
				res = mysql_store_result(cn.getConector());
				double total = 0;
				while (row = mysql_fetch_row(res)) {
					cout << "Cant: " << row[0] << " | " << row[1] << " | Precio: Q" << row[2] << " | Sub: Q" << row[3] << "\n";
					total += stod(row[3]);
				}
				cout << "------------------------------------------\n";
				cout << "TOTAL A PAGAR: Q" << total << "\n";
				cout << "==========================================\n";
			}
		}
		cn.cerrar_conexion();
	}

	void eliminar_factura(int id_venta) {
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConector()) {
			
			string query_consulta = "SELECT id_producto, cantidad FROM ventas_detalle WHERE id_venta = " + to_string(id_venta);

			if (!mysql_query(cn.getConector(), query_consulta.c_str())) {
				MYSQL_RES* res = mysql_store_result(cn.getConector());
				MYSQL_ROW fila;

				
				while ((fila = mysql_fetch_row(res))) {
					string id_prod = fila[0];
					string cantidad_vendida = fila[1];

					
					string query_update = "UPDATE productos SET existencia = existencia + " + cantidad_vendida +
						" WHERE id_producto = " + id_prod;
					mysql_query(cn.getConector(), query_update.c_str());
				}
				mysql_free_result(res);
			}

			
			string query_delete_detalles = "DELETE FROM ventas_detalle WHERE id_venta = " + to_string(id_venta);
			mysql_query(cn.getConector(), query_delete_detalles.c_str());

			
			string query_delete_venta = "DELETE FROM ventas WHERE id_venta = " + to_string(id_venta);

			if (!mysql_query(cn.getConector(), query_delete_venta.c_str())) {
				cout << "Factura #" << id_venta << " anulada y productos devueltos al inventario." << endl;
			}
			else {
				cout << "Error al eliminar: " << mysql_error(cn.getConector()) << endl;
			}
		}
		cn.cerrar_conexion();
	}

           

	
};

