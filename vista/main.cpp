#include <iostream>
#include "ConexionBD.h"
#include "Puestos.h"
#include "Marcas.h"
#include "Proveedores.h"
#include "Clientes.h"
#include "Productos.h"
#include "Empleados.h"
#include "Venta.h"
using namespace std;

void menuPuestos();
void menuMarcas();
void menuProveedores();
void menuClientes();
void menuProductos();
void menuEmpleados();
void menuVenta_Ventadetalle();

int main()
{
	bool nombreValido = false;
	bool apellidoValido = false;
	regex formatoNombre("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");
	bool direccionValida = false;
	regex formatoDireccion("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");
	string inputTel;
	bool telValido = false;
	regex formatoTel("^[0-9]{8}$");
	string fechaNac;
	string fechaIng;
	bool fechaValida = false;
	regex formatoFecha("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$");


	int opcion;

	do {
		system("cls");
		cout << "========================================" << endl;
		cout << "   SISTEMA DE INVENTARIO - SUPERMERCADO " << endl;
		cout << "========================================" << endl;
		cout << "1. Mantenimiento de puestos" << endl;
		cout << "2. Mantenimiento de marcas" << endl;
		cout << "3. Mantenimiento de proveedores" << endl;
		cout << "4. Mantenimiento de clientes" << endl;
		cout << "5. Mantenimiento de productos" << endl;
		cout << "6. Mantenimiento de empleados" << endl;
		cout << "7. Creacion de Factura compra-venta" << endl;
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
		case 5:
			menuProductos();
			break;
		case 6:
			menuEmpleados();
			break;
		case 7:
			menuVenta_Ventadetalle();
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
	bool nombreValido = false;
	regex formatoNombre("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");

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
			do {
				cout << "Ingrese el nombre del proveedor (ej. Pepsi): ";
				getline(cin, proveedor);
				if (!proveedor.empty() && proveedor.length() <= 60 && regex_match(proveedor, formatoNombre)) {
					nombreValido = true;
				}
				else {
					cout << "El nombre solo puede llevar letras, espacios y un maximo de 60 caracteres" << endl;
				}
			} while (!nombreValido);

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
	int opcion_c, id_cliente, telefono = 0, genero = 0, nit = 0;
	string nombres, apellidos, inputNit, inputTel, correo_electronico, fecha_ingreso;
	string nitFinal;
	bool nombreValido = false;
	bool apellidoValido = false;

	regex formatoNombre("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");
	bool telValido = false;
	bool nitValido = false;
	regex formatoTel("^[0-9]{8}$");
	regex formatoNit("^[0-9]{1,11}-[0-9Kk]$|^[0-9]{1,12}$");

	Clientes c = Clientes(0, nombres, apellidos, inputNit, genero, inputTel, correo_electronico, fecha_ingreso);

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
			do {
				cout << "Ingrese el nombre del cliente : ";
				getline(cin, nombres);
				if (!nombres.empty() && nombres.length() <= 60 && regex_match(nombres, formatoNombre)) {
					nombreValido = true;
				}
				else {
					cout << "El nombre solo puede llevar letras, espacios y un maximo de 60 caracteres" << endl;
				}
			} while (!nombreValido);
			//apellidos
			do {
				cout << "Ingrese el apellido del cliente: ";
				getline(cin, apellidos);
				if (!apellidos.empty() && apellidos.length() <= 60 && regex_match(apellidos, formatoNombre)) {
					apellidoValido = true;
				}
				else {
					cout << "Los apellidos solo pueden llevar letras , espacios y un maximo de 60 caracteres" << endl;
				}
			} while (!apellidoValido);

			//nit

			do {
				cout << "Ingrese el NIT del cliente (o enter para CF): ";
				getline(cin, inputNit);
				if (inputNit.empty() or inputNit == "cf" or inputNit == "CF") {
					nitFinal = "C/F";
					nitValido = true;
				}
				else {
					if (regex_match(inputNit, formatoNit)) {
						nitFinal = inputNit;
						nitValido = true;
					}
					else {
						cout << "NIT invalido, ingrese un formato correcto (ej. 1234567K) o presione Enter para C/F.\n\n" << endl;
					}
				}
			} while (!nitValido);




			//genero
			cout << "Ingrese el genero del cliente(0: Masculino / 1: Femenino): ";
			cin >> genero;
			cin.ignore(256, '\n');


			//telefono
			do {
				cout << "Ingrese el numero de telefono del cliente: ";
				getline(cin, inputTel);
				if (regex_match(inputTel, formatoTel)) {
					telefono = stoi(inputTel);
					telValido = true;
				}
				else {
					cout << "Numero de telefono invalido, el telefono debe contener exactamente 8 digitos numericos, no se permiten letras, espacios o simbolos" << endl;
				}
			} while (!telValido);
			//correo
			cout << "Ingrese el correo electronico del cliente: ";
			getline(cin, correo_electronico);


			c.setNombres(nombres);
			c.setApellidos(apellidos);
			c.setNit(inputNit);
			c.setGenero(genero);
			c.setTelefono(inputTel);
			c.setCorreo_electronico(correo_electronico);

			c.crear();
			c.leer();

			nombres = ""; apellidos = ""; inputNit = ""; inputTel = ""; correo_electronico = "";
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
			getline(cin, inputNit);
			cout << "Ingrese el genero del cliente(0: Masculino / 1: Femenino): ";
			cin >> genero;
			cin.ignore(256, '\n');
			cout << "Ingrese el numero de telefono del cliente: ";
			getline(cin, inputTel);
			cout << "Ingrese el correo electronico del cliente: ";
			getline(cin, correo_electronico);

			c.setId_cliente(id_cliente);
			c.setNombres(nombres);
			c.setApellidos(apellidos);
			c.setNit(inputNit);
			c.setGenero(genero);
			c.setTelefono(inputTel);
			c.setCorreo_electronico(correo_electronico);

			c.actualizar();
			c.leer();

			nombres = ""; apellidos = ""; inputNit = ""; inputTel = ""; correo_electronico = "";
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

void menuProductos() {

	int opcion_pp, id_producto, id_marca, existencia = 0;
	string producto_nom, descripcion, imagen;
	double precio_costo, precio_venta = 0;

	Producto pp = Producto(0, "", 0, "", "", 0.0, 0.0, 0);

	do {
		system("cls");
		cout << ">>> MENU: MANTENIMIENTO PRODUCTOS <<<" << endl;
		cout << "1. Listar productos" << endl;
		cout << "2. Agregar nuevo producto" << endl;
		cout << "3. Actualizar producto" << endl;
		cout << "4. Eliminar producto" << endl;
		cout << "0. Volver al menu principal" << endl;
		cout << "Seleccione: ";
		cin >> opcion_pp;
		cin.ignore(256, '\n');

		switch (opcion_pp) {
		case 1:
			pp.leer();
			break;

		case 2:

			//crear
			cout << "Ingrese el nombre del producto: ";
			getline(cin, producto_nom);

			cout << "Ingrese el ID de la marca: ";
			cin >> id_marca;
			cin.ignore(256, '\n');

			cout << "Ingrese la descripcion del producto: ";
			getline(cin, descripcion);

			cout << "Ingrese la ruta o nombre de la imagen: ";
			getline(cin, imagen);

			cout << "Ingrese el precio costo (use punto para decimales): ";
			cin >> precio_costo;

			cout << "Ingrese el precio venta (use punto para decimales): ";
			cin >> precio_venta;

			cout << "Ingrese la existencia inicial: ";
			cin >> existencia;
			cin.ignore(256, '\n');


			pp = Producto(producto_nom, (short)id_marca, descripcion, imagen, precio_costo, precio_venta, existencia);
			pp.crear();
			pp.leer();


			producto_nom = ""; descripcion = ""; imagen = "";
			break;
			cout << "------------------------------------" << endl;
			break;


		case 3:
			//actualizar
			cout << "Ingrese el ID del producto que desea modificar: ";
			cin >> id_producto;
			cin.ignore(256, '\n');

			cout << "Ingrese el nuevo nombre del producto: ";
			getline(cin, producto_nom);

			cout << "Ingrese el nuevo ID de la marca: ";
			cin >> id_marca;
			cin.ignore(256, '\n');

			cout << "Ingrese la nueva descripcion: ";
			getline(cin, descripcion);

			cout << "Ingrese la nueva ruta de imagen: ";
			getline(cin, imagen);

			cout << "Ingrese el nuevo precio costo: ";
			cin >> precio_costo;

			cout << "Ingrese el nuevo precio venta: ";
			cin >> precio_venta;

			cout << "Ingrese la nueva existencia: ";
			cin >> existencia;
			cin.ignore(256, '\n');

			pp = Producto(id_producto, producto_nom, (short)id_marca, descripcion, imagen, precio_costo, precio_venta, existencia);
			pp.actualizar();
			pp.leer();

			producto_nom = ""; descripcion = ""; imagen = "";
			break;


		case 4:
			//eliminar
			cout << "Ingrese el ID a eliminar: ";
			cin >> id_producto;
			pp = Producto(id_producto, "", 0, "", "", 0.0, 0.0, 0);
			pp.eliminar();
			pp.leer();
			break;
		}
		if (opcion_pp != 0) system("pause");
	} while (opcion_pp != 0);
}

void menuEmpleados() {
	int opcion_e, id_empleado, genero = 0, id_puesto = 0;
	string nombres, apellidos, direccion, telefono, dpi, fecha_nacimiento, fecha_inicio_labores;
	string inputGenero;
	bool nombreValido = false;
	bool apellidoValido = false;
	bool dpiValido = false;
	bool telefonoValido = false;
	bool generoValido = false;
	bool fechaValida = false;
	regex formatoFecha("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$");
	regex formatoNombre("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");
	regex formatoDpi("^[0-9]{13}$");
	regex formatoNumero("^[0-9]{8}$");
	regex formatoGenero("^[0-1]{1}$");

	Empleado e = Empleado(0, "", "", "", "", "", 0, "", 0, "");

	do {
		system("cls");
		cout << ">>> MENU: MANTENIMIENTO EMPLEADOS <<<" << endl;
		cout << "1. Listar empleados" << endl;
		cout << "2. Crear nuevo empleado" << endl;
		cout << "3. Actualizar empleado" << endl;
		cout << "4. Eliminar empleado" << endl;
		cout << "0. Volver al menu principal" << endl;
		cout << "Seleccione: ";
		cin >> opcion_e;
		cin.ignore(256, '\n');

		switch (opcion_e) {
		case 1:
			e.leer();
			break;

		case 2:
			//nombre

			do {
				cout << "Ingrese el nombre del empleado: ";
				nombres = Validar::texto(60);
				if (regex_match(nombres, formatoNombre))
				{
					nombreValido = true;
				}
				else {
					cout << "Los nombres solo pueden llevar letras, espacios y un maximo de 60 caracteres" << endl;
					nombreValido = false;
				}
			} while (!nombreValido);

			//apellidos
			do {
				cout << "Ingrese el apellido del empleado: ";
				apellidos = Validar::texto(60);
				if (regex_match(apellidos, formatoNombre))
				{
					apellidoValido = true;
				}
				else {
					cout << "Los apellidos solo pueden llevar letras, espacios y un maximo de 60 caracteres" << endl;
					apellidoValido = false;
				}
			} while (!apellidoValido);

			//direccion
			cout << "Ingrese la direccion de residencia: ";
			direccion = Validar::texto(80);

			//telefono
			do {
				cout << "Ingrese el numero de telefono: ";
				telefono = Validar::texto(25);
				if (regex_match(telefono, formatoNumero)) {
					telefonoValido = true;
				}
				else {
					cout << "Numero de telefono invalido, el telefono debe contener exactamente 8 digitos numericos" << endl;
					telefonoValido = false;
				}
			} while (!telefonoValido);

			//dpi
			do {
				cout << "Ingrese el DPI del empleado: ";
				dpi = Validar::texto(13);
				if (regex_match(dpi, formatoDpi)) {
					dpiValido = true;
				}
				else {
					cout << "Ingreso de DPI invalido, el dpi debe contener exactamente 13 digitos" << endl;
					dpiValido = false;
				}
			} while (!dpiValido);

			//gen
			do {
				cout << "Ingrese el genero (0: Masculino / 1: Femenino): ";
				inputGenero = Validar::texto(1);
				if (regex_match(inputGenero, formatoGenero)) {
					generoValido = true;
				}
				else {
					cout << "Entrada invalida, ingrese 0 para Masculino y 1 para Femenino" << endl;
					generoValido = false;
				}
			} while (!generoValido);

			//fechanacimiento
			do {
				cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
				fecha_nacimiento = Validar::texto(10);
				if (regex_match(fecha_nacimiento, formatoFecha)) {
					fechaValida = true;
				}
				else {
					cout << "Formato de fecha invalido, ingrese la nueva fecha basandose en el siguiente formato (YYYY-MM-DD)" << endl;
					fechaValida = false;
				}
			} while (!fechaValida);


			//id
			cout << "Ingrese el ID del puesto de trabajo: ";
			id_puesto = Validar::entero();

			//fechaingreso
			do {
				cout << "Ingrese la fecha de inicio de labores (YYYY-MM-DD): ";
				fecha_inicio_labores = Validar::texto(10);
				if (regex_match(fecha_inicio_labores, formatoFecha)) {
					fechaValida = true;
				}
				else {
					cout << "Formato de fecha invalido, ingrese la nueva fecha basandose en el siguiente formato (YYYY-MM-DD)" << endl;
					fechaValida = false;
				}
			} while (!fechaValida);

			//
			e = Empleado(nombres, apellidos, direccion, telefono, dpi, genero, fecha_nacimiento, (short)id_puesto, fecha_inicio_labores);
			e.crear();
			e.leer();

			nombres = ""; apellidos = ""; direccion = ""; telefono = ""; dpi = ""; fecha_nacimiento = ""; fecha_inicio_labores = "";
			break;

		case 3:
			cout << "Ingrese el ID del empleado que desea modificar: ";
			id_empleado = Validar::entero();
			cout << "Ingrese el nuevo nombre del empleado: ";
			nombres = Validar::texto(50);
			cout << "Ingrese el nuevo apellido del empleado: ";
			apellidos = Validar::texto(60);
			cout << "Ingrese la nueva direccion: ";
			direccion = Validar::texto(80);
			cout << "Ingrese el nuevo telefono: ";
			telefono = Validar::texto(25);
			cout << "Ingrese el nuevo DPI: ";
			dpi = Validar::texto(15);
			cout << "Ingrese el nuevo genero (1: Masculino / 0: Femenino): ";
			genero = Validar::entero();
			cout << "Ingrese la nueva fecha de nacimiento (YYYY-MM-DD): ";
			fecha_nacimiento = Validar::texto(10);
			cout << "Ingrese el nuevo ID del puesto: ";
			id_puesto = Validar::entero();
			cout << "Ingrese la nueva fecha de inicio de labores (YYYY-MM-DD): ";
			fecha_inicio_labores = Validar::texto(10);

			e = Empleado(id_empleado, nombres, apellidos, direccion, telefono, dpi, genero, fecha_nacimiento, (short)id_puesto, fecha_inicio_labores);
			e.actualizar();
			e.leer();

			nombres = ""; apellidos = ""; direccion = ""; telefono = ""; dpi = ""; fecha_nacimiento = ""; fecha_inicio_labores = "";
			break;

		case 4:
			cout << "Ingrese el ID del empleado a eliminar: ";
			id_empleado = Validar::entero();

			e = Empleado(id_empleado, "", "", "", "", "", 0, "", 0, "");
			e.eliminar();
			e.leer();
			break;
		}
		if (opcion_e != 0) system("pause");
	} while (opcion_e != 0);
}

void menuVenta_Ventadetalle() {
	int opcionn;

	do {
		system("cls");
		cout << "===== MODULO DE VENTAS (Maestro-Detalle) ======" << endl;
		cout << "1.Ingresar Nueva venta" << endl;
		cout << "2.Ver historial de ventas" << endl;
		cout << "3.Anular factura" << endl;
		cout << "0.Regresar al Menu Principal" << endl;
		cout << "Seleccione una opcion: ";
		cin >> opcionn;
		cin.ignore(256, '\n');

		switch (opcionn) {
		case 1: {
			system("cls");
			Venta v;
			string serie, no_factura;
			int id_cliente, id_empleado;

			cout << "--- Datos de la Factura (CABECERA) ---" << endl;
			cout << "Ingrese la serie: ";
			getline(cin, serie);
			v.setSerie(serie);

			cout << "Ingrese el No. de Factura: ";
			getline(cin, no_factura);
			v.setNo_factura(no_factura);

			cout << "Ingrese el ID del Cliente: ";
			cin >> id_cliente;
			v.setId_cliente(id_cliente);

			cout << "Ingrese el ID del Empleado: ";
			cin >> id_empleado;
			v.setId_empleado(id_empleado);
			cin.ignore(256, '\n');

			v.crear();
			system("pause");
			break;
		} 

		case 2: {
			system("cls");
			int id_buscar;
			Venta v;

			
			cout << "       CONSULTAR FACTURA EXISTENTE      " << endl;
			cout << "========================================" << endl;
			cout << "Ingrese el ID de la factura que desea buscar: ";
			cin >> id_buscar;

			v.leer_factura(id_buscar);

			cout << "\nPresione una tecla para volver al menu..." << endl;
			system("pause");
			break;
		} 
		case 3: {
			system("cls");
			int id_borrar;
			Venta v; 

			
			cout << "           ELIMINAR FACTURA             " << endl;
			cout << "========================================" << endl;
			cout << "Ingrese el ID de la factura a eliminar: ";
			cin >> id_borrar;
			cin.ignore(256, '\n');

			
			char confirmacion;
			cout << "Esta seguro que desea eliminar la factura #" << id_borrar << "? (s/n): ";
			cin >> confirmacion;
			cin.ignore(256, '\n');

			if (confirmacion == 's' || confirmacion == 'S') {
				
				v.eliminar_factura(id_borrar);
			}
			else {
				cout << "\nOperacion cancelada. No se realizo ningun cambio." << endl;
			}

			cout << "\nPresione una tecla para volver al menu..." << endl;
			system("pause");
			break;
		}

		default:
			if (opcionn != 0) {
				cout << "Opcion no valida" << endl;
				system("pause");
			}
			break;
		} 

	} while (opcionn != 0); 

} 