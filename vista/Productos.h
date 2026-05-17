#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include "ConexionBD.h"

class Catalogo {
public:
    virtual void crear() = 0;
    virtual void leer() = 0;
    virtual void actualizar() = 0;
    virtual void eliminar() = 0;
    virtual ~Catalogo() {}
};
class Validar {
public:
    static int entero() {
        int valor;
        while (!(std::cin >> valor)) {
            std::cout << "[!] Entrada invalida. Ingrese un numero: ";
            std::cin.clear();
            
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return valor;
    }

    static std::string texto(size_t longitudMax) {
        std::string cadena;
        std::getline(std::cin, cadena);
        while (cadena.length() > longitudMax || cadena.empty()) {
            std::cout << "[!] El texto no puede estar vacio ni superar los " << longitudMax << " caracteres: ";
            std::getline(std::cin, cadena);
        }
        return cadena;
    }
}; 
class Producto : public Catalogo {
private:
    int id_producto;
    std::string producto;
    short id_marca;
    std::string descripcion;
    std::string imagen;
    double precio_costo;
    double precio_venta;
    int existencia;
    std::string fecha_ingreso;

public:
    Producto() : id_producto(0), producto(""), id_marca(0), descripcion(""), imagen(""), precio_costo(0.0), precio_venta(0.0), existencia(0), fecha_ingreso("") {}

    Producto(std::string prod, short marca, std::string desc, std::string img, double costo, double venta, int exist)
        : id_producto(0), producto(prod), id_marca(marca), descripcion(desc), imagen(img), precio_costo(costo), precio_venta(venta), existencia(exist), fecha_ingreso("") {
    }

    Producto(int id, std::string prod, short marca, std::string desc, std::string img, double costo, double venta, int exist)
        : id_producto(id), producto(prod), id_marca(marca), descripcion(desc), imagen(img), precio_costo(costo), precio_venta(venta), existencia(exist), fecha_ingreso("") {
    }


    void crear() override {
        ConexionBD db;
        db.abrir_conexion();

        if (db.getConector()) {
            
            std::stringstream ss;
            ss << "INSERT INTO productos (productos, id_marca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES ('"
                << producto << "', " << id_marca << ", '" << descripcion << "', '" << imagen << "', "
                << precio_costo << ", " << precio_venta << ", " << existencia << ", NOW())";

            std::string consulta = ss.str();
            int q_estado = mysql_query(db.getConector(), consulta.c_str());

            if (!q_estado) {
                std::cout << "\n[OK] Producto registrado exitosamente.\n";
            }
            else {
                
                std::cout << "\n[ERROR] MySQL dice: " << mysql_error(db.getConector()) << "\n";
            }
        }
        db.cerrar_conexion();
    }


    void leer() override {
        ConexionBD db;
        db.abrir_conexion();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        if (db.getConector()) {
            std::string consulta = "SELECT p.id_producto, p.productos, m.marca, p.descripcion, p.precio_venta, p.existencia FROM productos p INNER JOIN marcas m ON p.id_marca = m.id_marca";
            int q_estado = mysql_query(db.getConector(), consulta.c_str());

            if (!q_estado) {
                resultado = mysql_store_result(db.getConector());
                std::cout << "\n=================================== LISTADO DE PRODUCTOS ===================================\n";
                std::cout << std::left << std::setw(6) << "ID"
                    << std::setw(20) << "Producto"
                    << std::setw(15) << "Marca"
                    << std::setw(25) << "Descripcion"
                    << std::setw(12) << "P. Venta"
                    << std::setw(10) << "Stock" << "\n";
                std::cout << "--------------------------------------------------------------------------------------------\n";

                while ((fila = mysql_fetch_row(resultado))) {
                    std::cout << std::left << std::setw(6) << (fila[0] ? fila[0] : "N/A")
                        << std::setw(20) << (fila[1] ? fila[1] : "N/A")
                        << std::setw(15) << (fila[2] ? fila[2] : "N/A")
                        << std::setw(25) << (fila[3] ? fila[3] : "N/A")
                        << "Q " << std::setw(10) << (fila[4] ? fila[4] : "0.00")
                        << std::setw(10) << (fila[5] ? fila[5] : "0") << "\n";
                }
                std::cout << "============================================================================================\n";
                mysql_free_result(resultado); 
            }
            else {
                std::cout << "\n[ERROR] MySQL dice: " << mysql_error(db.getConector()) << "\n";
            }
        }
        db.cerrar_conexion();
    }

    
    void actualizar() override {
        ConexionBD db;
        db.abrir_conexion();

        if (db.getConector()) {
            std::stringstream ss;
            ss << "UPDATE productos SET productos = '" << producto << "', id_marca = " << id_marca
                << ", descripcion = '" << descripcion << "', imagen = '" << imagen << "', precio_costo = " << precio_costo
                << ", precio_venta = " << precio_venta << ", existencia = " << existencia
                << " WHERE id_producto = " << id_producto;

            std::string consulta = ss.str();
            int q_estado = mysql_query(db.getConector(), consulta.c_str());
            if (!q_estado) {
                std::cout << "\n[OK] Producto actualizado de forma correcta.\n";
            }
            else {
                std::cout << "\n[ERROR] MySQL dice: " << mysql_error(db.getConector()) << "\n";
            }
        }
        db.cerrar_conexion();
    }
    void eliminar() override {
        ConexionBD db;
        db.abrir_conexion();

        if (db.getConector()) {
            std::string consulta = "DELETE FROM productos WHERE id_producto = " + std::to_string(id_producto);
            int q_estado = mysql_query(db.getConector(), consulta.c_str());
            if (!q_estado) {
                std::cout << "\n[OK] Producto eliminado de la base de datos.\n";
            }
            else {
                std::cout << "\n[ERROR] No se pudo eliminar el producto. Verifique si tiene historial.\n";
            }
        }
        db.cerrar_conexion();
    }
};

