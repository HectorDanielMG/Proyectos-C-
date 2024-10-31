using System;
using System.Collections.Generic;
using System.Linq;

class Tarea
{
    public int Id { get; set; }
    public string Descripcion { get; set; }
    public bool Completada { get; set; }

    public Tarea(int id, string descripcion)
    {
        Id = id;
        Descripcion = descripcion;
        Completada = false;
    }

    public override string ToString()
    {
        return $"[{(Completada ? "X" : " ")}] {Id}. {Descripcion}";
    }
}

class ToDoList
{
    private List<Tarea> tareas;
    private int contadorId;

    public ToDoList()
    {
        tareas = new List<Tarea>();
        contadorId = 1;
    }

    public void AgregarTarea(string descripcion)
    {
        tareas.Add(new Tarea(contadorId++, descripcion));
        Console.WriteLine("Tarea agregada correctamente.");
    }

    public void EditarTarea(int id, string nuevaDescripcion)
    {
        var tarea = tareas.FirstOrDefault(t => t.Id == id);
        if (tarea != null)
        {
            tarea.Descripcion = nuevaDescripcion;
            Console.WriteLine("Tarea editada correctamente.");
        }
        else
        {
            Console.WriteLine("Tarea no encontrada.");
        }
    }

    public void MarcarComoCompletada(int id)
    {
        var tarea = tareas.FirstOrDefault(t => t.Id == id);
        if (tarea != null)
        {
            tarea.Completada = true;
            Console.WriteLine("Tarea marcada como completada.");
        }
        else
        {
            Console.WriteLine("Tarea no encontrada.");
        }
    }

    public void EliminarTarea(int id)
    {
        var tarea = tareas.FirstOrDefault(t => t.Id == id);
        if (tarea != null)
        {
            tareas.Remove(tarea);
            Console.WriteLine("Tarea eliminada correctamente.");
        }
        else
        {
            Console.WriteLine("Tarea no encontrada.");
        }
    }

    public void MostrarTareas(bool soloCompletadas = false, bool soloIncompletas = false)
    {
        Console.WriteLine("\nLista de Tareas:");
        var tareasFiltradas = tareas;

        if (soloCompletadas)
            tareasFiltradas = tareas.Where(t => t.Completada).ToList();
        else if (soloIncompletas)
            tareasFiltradas = tareas.Where(t => !t.Completada).ToList();

        foreach (var tarea in tareasFiltradas)
            Console.WriteLine(tarea);

        if (!tareasFiltradas.Any())
            Console.WriteLine("No hay tareas para mostrar.");
    }
}

class Program
{
    static void Main()
    {
        ToDoList listaTareas = new ToDoList();
        int opcion;

        do
        {
            Console.WriteLine("\nOpciones:");
            Console.WriteLine("1. Agregar tarea");
            Console.WriteLine("2. Editar tarea");
            Console.WriteLine("3. Marcar tarea como completada");
            Console.WriteLine("4. Eliminar tarea");
            Console.WriteLine("5. Mostrar todas las tareas");
            Console.WriteLine("6. Mostrar solo tareas completadas");
            Console.WriteLine("7. Mostrar solo tareas incompletas");
            Console.WriteLine("8. Salir");
            Console.Write("Elige una opción: ");
            opcion = Convert.ToInt32(Console.ReadLine());

            switch (opcion)
            {
                case 1:
                    Console.Write("Descripción de la tarea: ");
                    string descripcion = Console.ReadLine();
                    listaTareas.AgregarTarea(descripcion);
                    break;
                case 2:
                    Console.Write("ID de la tarea a editar: ");
                    int idEditar = Convert.ToInt32(Console.ReadLine());
                    Console.Write("Nueva descripción de la tarea: ");
                    string nuevaDescripcion = Console.ReadLine();
                    listaTareas.EditarTarea(idEditar, nuevaDescripcion);
                    break;
                case 3:
                    Console.Write("ID de la tarea a marcar como completada: ");
                    int idCompletar = Convert.ToInt32(Console.ReadLine());
                    listaTareas.MarcarComoCompletada(idCompletar);
                    break;
                case 4:
                    Console.Write("ID de la tarea a eliminar: ");
                    int idEliminar = Convert.ToInt32(Console.ReadLine());
                    listaTareas.EliminarTarea(idEliminar);
                    break;
                case 5:
                    listaTareas.MostrarTareas();
                    break;
                case 6:
                    listaTareas.MostrarTareas(soloCompletadas: true);
                    break;
                case 7:
                    listaTareas.MostrarTareas(soloIncompletas: true);
                    break;
                case 8:
                    Console.WriteLine("Saliendo...");
                    break;
                default:
                    Console.WriteLine("Opción no válida.");
                    break;
            }
        } while (opcion != 8);
    }
}
