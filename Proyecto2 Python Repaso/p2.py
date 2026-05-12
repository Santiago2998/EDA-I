import random
cantidadBase = 1

productos = {}

def ingresarProducto(name, precio):
    for j in productos:
        if productos[j]["nombre"] == name:
            productos[j]["cantidad"] += 1
            print("El producto ya estaba en el carrito, se aumenta la cantidad de este\n")
            return
    id = random.randint(100, 1000)
    productos[id] = {"nombre": name, "precioP": precio, "cantidad": cantidadBase}
    print("Producto agregado al carrito.\n")

def eliminarProducto(idDelete):
    if idDelete in productos:
        del productos[idDelete]
        print("Producto eliminado\n")
    else:
        print("ID no encontrado")

def mostrarCarritoFrente():
    if not productos:
        print("El carrito está vacío")
        return

    print(f"|\tID:\t|\tNombre\t|\tPrecio\t|\tCantidad\t|")    
    for n in productos:
        print(f"\n|\t{n}\t|\t{productos[n]["nombre"]}\t|\t{productos[n]["precioP"]}\t|\t{productos[n]["cantidad"]}\t\t|")
    
def mostrarCarritoFinal():
    if not productos:
        print("El carrito está vacío\n")
        return
    llaves_invertidas = list(productos.keys())
    llaves_invertidas.reverse() 

    print(f"|\tID:\t|\tNombre\t|\tPrecio\t|\tCantidad\t|")
    for n in llaves_invertidas:
        print(f"\n|\t{n}\t|\t{productos[n]["nombre"]}\t|\t{productos[n]["precioP"]}\t|\t{productos[n]["cantidad"]}\t\t|")

while True:
    print("\n------Carrito--------")
    print("\n1. Ingresar Producto\n2. Eliminar Producto\n3. Mostrar Carrito por el Frente\n4. Mostrar Carrito por el Final\n5. Salir\n")
    opcion = int(input("Selecciona una opción: "))
    if opcion == 1:
        nombre_Producto = input("Ingresa el Nombre del Producto: ")
        name = nombre_Producto.lower()
        precio_Producto = float(input("Ingresa el Precio del Producto: "))
        ingresarProducto(name, precio_Producto)
    elif opcion == 2:
        mostrarCarritoFrente()
        id_eliminar = int(input("Ingresa un id a eliminar: "))
        eliminarProducto(id_eliminar)
    elif opcion == 3:
        print("El carrito por el frente es:\n")
        mostrarCarritoFrente()
    elif opcion == 4:
        print("El carrito por el final es: ")
        mostrarCarritoFinal()
    elif opcion == 5:
        print("Saliendo....\n")
        break
    else:
        print("Opción inválida")
