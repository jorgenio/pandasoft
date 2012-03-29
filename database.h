#ifndef DATABASE_H
#define DATABASE_H

#include "qmessagebox.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("pandasoft.db");
 //   db.setDatabaseName(":memory:");

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("no se puede abrir la base de datos"),
            qApp->tr("No se puede conectar a la base de datos.\n"
                     "Hacer clic para cancelar."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE Usuario (Ci INTEGER NOT NULL PRIMARY KEY, Nombre varchar(30), Ap varchar(30), Am varchar(30), Direccion varchar(30), Telefono INTEGER, Rol INTEGER, Contrasena varchar(30))");
    query.exec("CREATE TABLE Empleado (Ci INTEGER NOT NULL PRIMARY KEY, Nombre varchar(30), Ap varchar(30), Am varchar(30), Direccion varchar(30), Telefono INTEGER, Cargo varchar(30))");
    query.exec("CREATE TABLE Producto (Id_pro INTEGER NOT NULL PRIMARY KEY, Nombre varchar(30), Pconsig DOUBLE, Punitario DOUBLE, Cantidad INTEGER, Lim_stock INTEGER, Foto varchar(30), Descripcion varchar(30))");
    query.exec("CREATE TABLE Sucursal (Id_suc INTEGER NOT NULL PRIMARY KEY, Departamento varchar(30), Provincia varchar(30), Seccion varchar(30), Nombre varchar(30), Direccion varchar(30), Nit INTEGER, Telefono INTEGER)");
    query.exec("CREATE TABLE Zona (Id_zon INTEGER NOT NULL PRIMARY KEY, Nombre varchar(30), Alcance INTEGER)");
    query.exec("CREATE TABLE Consignatario (Id_con INTEGER NOT NULL PRIMARY KEY, Nombre varchar(30), Ap varchar(30), Am varchar(30), Telefono INTEGER, Id_zon INTEGER NOT NULL)");
    query.exec("CREATE TABLE Venta (Id_ven INTEGER NOT NULL PRIMARY KEY, Fecha DATE, Total DOUBLE)");
    query.exec("CREATE TABLE dventas (Id_ven INTEGER NOT NULL, Id_pro INTEGER NOT NULL, Cantidad INTEGER, Costo DOUBLE)");
    query.exec("CREATE TABLE Asignar (Id_asig INTEGER NOT NULL PRIMARY KEY, Estado varchar(30), Fecha DATE,  Total DOUBLE, Id_con INTEGER NOT NULL)");
    query.exec("CREATE TABLE Dasignar ( Id_asig INTEGER NOT NULL, Id_pro INTEGER NOT NULL, Cantidad INTEGER, Costo DOUBLE)");

    query.exec("insert into Sucursal values(1, 'tarija', 'cercado', 'tarija', 'terminal','la terminal', '12345', '12345')");

    query.exec("insert into Usuario values(5043479, 'admin', 'gutierrez', 'g', 'terminal4', '1', '0', 'admin')");
    query.exec("insert into Usuario values(504349, 'j', 'gutierrez', 'g', 'terminal4', '1', '1', 'j')");

    query.exec("insert into Empleado values(0, 'enzo', 'enzo', 'enzo', 'tabladita1', '75466', 'cargador')");

    query.exec("insert into Producto values(1, 'Tortas Grandes', '50.00', '55.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(2, 'Tortas Medianas', '35.00', '40.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(3, 'Cassatas', '11.00', '13.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(4, 'Familiares', '10.00', '12.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(5, 'Pandi - Panda', '2.50', '3.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(6, 'Pandi - Cono', '2.50', '3.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(7, 'Golazo', '2.50', '3.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(8, 'Pandi - Krok', '1.80', '2.50', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(9, 'Chocopanda', '1.70', '2.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(10, 'Vampiro', '1.70', '2.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(11, 'Escolino', '1.50', '2.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(12, 'Capuchino', '1.00', '1.50', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(13, 'Cremisimo', '1.00', '1.50', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(14, 'Cocoso', '1.00', '1.50', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(15, 'Mister – Yo', '1.00', '1.50', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(16, 'Granzado', '1.00', '1.50', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(17, 'Baby', '0.80', '1.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(18, 'Tropical', '0.80', '1.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(19, 'Muy Rico', '0.80', '1.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(20, 'Gusanito', '0.80', '1.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(21, 'Canela', '0.80', '1.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(22, 'Kremoso', '0.80', '1.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(23, 'Vasito Panda', '0.80', '1.00', '50', '50', '', 'helado')");
    query.exec("insert into Producto values(24, 'Picaron', '0.80', '1.00', '10', '50', '', 'helado')");

    query.exec("insert into Zona values(0, 'barrio a', '3')");

     return true;
}

#endif


