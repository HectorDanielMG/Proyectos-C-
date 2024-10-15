 using System;
using System.Collections.Generic;

class Program
{
    static void Main()
    {
        List<string> tareas = new List<string>();
        string opcion = "";

        while (opcion != "4")
        {
            Console.WriteLine("\n--- Lista de Tareas ---");
            Console.WriteLine("1. Agregar tarea");
            Console.WriteLine("2. Eliminar tarea");
            Console.WriteLine("3. Mostrar todas las tareas");
            Console.WriteLine("4. Salir");
            Console.Write("Selecciona una opción: ");
            opcion = Console.ReadLine();

            switch (opcion)
            {
                case "1":
                    Console.Write("Escribe la nueva tarea: ");
                    string tarea = Console.ReadLine();
                    tareas.Add(tarea);
                    Console.WriteLine("Tarea agregada.");
                    break;

                case "2":
                    Console.Write("Escribe el número de la tarea que quieres eliminar: ");
                    int index = int.Parse(Console.ReadLine()) - 1;
                    if (index >= 0 && index < tareas.Count)
                    {
                        tareas.RemoveAt(index);
                        Console.WriteLine("Tarea eliminada.");
                    }
                    else
                    {
                        Console.WriteLine("Número inválido.");
                    }
                    break;

                case "3":
                    Console.WriteLine("\n--- Tareas ---");
                    for (int i = 0; i < tareas.Count; i++)
                    {
                        Console.WriteLine($"{i + 1}. {tareas[i]}");
                    }
                    break;

                case "4":
                    Console.WriteLine("Saliendo...");
                    break;

                default:
                    Console.WriteLine("Opción no válida.");
                    break;
            }
        }
    }
}

