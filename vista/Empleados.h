#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream> 
#include "ConexionBD.h" 
#include "Productos.h"

using namespace std;


class Empleado : public Catalogo {
private:
    int id_empleado;
    string nombres;
    string apellidos;
    string direccion;
    string telefono;
    string dpi;
    int genero;
    string fecha_nacimiento;
    short id_puesto;
    string fecha_inicio_labores;
    string fecha_ingreso;

public:
    Empleado() : id_empleado(0), nombres(""), apellidos(""), direccion(""), telefono(""), dpi(""), genero(0), fecha_nacimiento(""), id_puesto(0), fecha_inicio_labores(""), fecha_ingreso("") {}

    Empleado(string nom, string ape, string dir, string tel, string d_p_i, int gen, string f_nac, short puesto, string f_lab)
        : id_empleado(0), nombres(nom), apellidos(ape), direccion(dir), telefono(tel), dpi(d_p_i), genero(gen), fecha_nacimiento(f_nac), id_puesto(puesto), fecha_inicio_labores(f_lab), fecha_ingreso("") {
    }

    Empleado(int id, string nom, string ape, string dir, string tel, string d_p_i, int gen, string f_nac, short puesto, string f_lab)
        : id_empleado(id), nombres(nom), apellidos(ape), direccion(dir), telefono(tel), dpi(d_p_i), genero(gen), fecha_nacimiento(f_nac), id_puesto(puesto), fecha_inicio_labores(f_lab), fecha_ingreso("") {
    }

    
    void crear() override {
        ConexionBD db;
        db.abrir_conexion();

        if (db.getConector()) {
            stringstream ss;
            ss << "INSERT INTO empleados (nombres, apellidos, direccion, telefono, cui, genero, fecha_nacimiento, id_puesto, fecha_inicio_labores, fecha_ingreso) VALUES ('"
                << nombres << "', '" << apellidos << "', '" << direccion << "', '" << telefono << "', '"
                << dpi << "', " << genero << ", '" << fecha_nacimiento << "', " << id_puesto << ", '" << fecha_inicio_labores << "', NOW())";

            string consulta = ss.str();
            int q_estado = mysql_query(db.getConector(), consulta.c_str());

            if (!q_estado) {
                cout << "\n[OK] Empleado registrado exitosamente.\n";
            }
            else {
                cout << "\n[ERROR] MySQL dice: " << mysql_error(db.getConector()) << "\n";
            }
        }
        else {
            cout << "\n[ERROR] Fallo la conexion con la base de datos.\n";
        }
        db.cerrar_conexion();
    }

    void leer() override {
        ConexionBD db;
        db.abrir_conexion();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        if (db.getConector()) {
            string consulta = "SELECT e.id_empleado, e.nombres, e.apellidos, e.telefono, e.cui, p.puesto, CAST(e.genero AS UNSIGNED) FROM empleados e INNER JOIN puestos p ON e.id_puesto = p.id_puesto";
            int q_estado = mysql_query(db.getConector(), consulta.c_str());

            if (!q_estado) {
                resultado = mysql_store_result(db.getConector());

                cout << "\n======================================================== EMPLEADOS REGISTRADOS ========================================================\n";
                cout << left << setw(6) << "ID"
                    << setw(18) << "Nombres"
                    << setw(18) << "Apellidos"
                    << setw(12) << "Telefono"
                    << setw(15) << "DPI"
                    << setw(12) << "Genero"
                    << setw(20) << "Puesto / Rol" << "\n";
                cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";

                while ((fila = mysql_fetch_row(resultado))) {
                    string txt_genero = "N/A";
                    if (fila[6]) {
                        txt_genero = (string(fila[6]) == "0") ? "Masculino" : "Femenino";
                    }

                    cout << left << setw(6) << (fila[0] ? fila[0] : "N/A")
                        << setw(18) << (fila[1] ? fila[1] : "N/A")
                        << setw(18) << (fila[2] ? fila[2] : "N/A")
                        << setw(12) << (fila[3] ? fila[3] : "N/A")
                        << setw(15) << (fila[4] ? fila[4] : "N/A")
                        << setw(12) << txt_genero
                        << setw(20) << (fila[5] ? fila[5] : "N/A") << "\n";
                }
                cout << "=======================================================================================================================================\n";
                mysql_free_result(resultado);
            }
            else {
                cout << "\n[ERROR] MySQL dice: " << mysql_error(db.getConector()) << "\n";
            }
        }
        else {
            cout << "\n[ERROR] Fallo la conexion con la base de datos.\n";
        }
        db.cerrar_conexion();
    }

    void actualizar() override {
        ConexionBD db;
        db.abrir_conexion();

        if (db.getConector()) {
            stringstream ss;
            ss << "UPDATE empleados SET nombres = '" << nombres << "', apellidos = '" << apellidos
                << "', direccion = '" << direccion << "', telefono = '" << telefono << "', cui = '" << dpi
                << "', genero = " << genero << ", fecha_nacimiento = '" << fecha_nacimiento
                << "', id_puesto = " << id_puesto << ", fecha_inicio_labores = '" << fecha_inicio_labores
                << "' WHERE id_empleado = " << id_empleado;

            string consulta = ss.str();
            int q_estado = mysql_query(db.getConector(), consulta.c_str());

            if (!q_estado) {
                cout << "\n[OK] Empleado actualizado de forma correcta.\n";
            }
            else {
                cout << "\n[ERROR] MySQL dice: " << mysql_error(db.getConector()) << "\n";
            }
        }
        else {
            cout << "\n[ERROR] Fallo la conexion con la base de datos.\n";
        }
        db.cerrar_conexion();
    }

    void eliminar() override {
        ConexionBD db;
        db.abrir_conexion();

        if (db.getConector()) {
            string consulta = "DELETE FROM empleados WHERE id_empleado = " + to_string(id_empleado);
            int q_estado = mysql_query(db.getConector(), consulta.c_str());

            if (!q_estado) {
                cout << "\n[OK] Empleado eliminado de la base de datos.\n";
            }
            else {
                cout << "\n[ERROR] No se puede eliminar. Verifica las restricciones de llaves foraneas.\n";
            }
        }
        else {
            cout << "\n[ERROR] Fallo la conexion con la base de datos.\n";
        }
        db.cerrar_conexion();
    }
};

