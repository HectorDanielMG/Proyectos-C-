using System;
using System.Collections.Generic;
using System.Linq;

class ToDoItem
{
    public string Description { get; set; }
    public bool IsCompleted { get; set; }
    public int Priority { get; set; } // Nueva propiedad para prioridad

    public ToDoItem(string description, int priority)
    {
        Description = description;
        IsCompleted = false;
        Priority = priority;
    }

    public override string ToString()
    {
        return $"[{(IsCompleted ? "X" : " ")}] {Description} (Prioridad: {Priority})";
    }
}

class ToDoList
{
    private List<ToDoItem> items;

    public ToDoList()
    {
        items = new List<ToDoItem>();
    }

    public void AddItem(string description, int priority)
    {
        items.Add(new ToDoItem(description, priority));
        Console.WriteLine("Tarea añadida.");
    }

    public void MarkAsCompleted(int index)
    {
        if (index < 1 || index > items.Count)
        {
            Console.WriteLine("Índice inválido.");
            return;
        }

        items[index - 1].IsCompleted = true;
        Console.WriteLine("Tarea marcada como completada.");
    }

    public void ListItems(bool showCompleted = true)
    {
        var sortedItems = items.OrderBy(item => item.Priority).ToList();
        for (int i = 0; i < sortedItems.Count; i++)
        {
            if (showCompleted || !sortedItems[i].IsCompleted)
                Console.WriteLine($"{i + 1}. {sortedItems[i]}");
        }
    }

    public void RemoveItem(int index)
    {
        if (index < 1 || index > items.Count)
        {
            Console.WriteLine("Índice inválido.");
            return;
        }

        items.RemoveAt(index - 1);
        Console.WriteLine("Tarea eliminada.");
    }
}

class Program
{
    static void Main()
    {
        var toDoList = new ToDoList();

        while (true)
        {
            Console.WriteLine("\nSeleccione una opción:");
            Console.WriteLine("1. Añadir tarea");
            Console.WriteLine("2. Marcar tarea como completada");
            Console.WriteLine("3. Ver tareas");
            Console.WriteLine("4. Eliminar tarea");
            Console.WriteLine("5. Salir");

            var input = Console.ReadLine();

            switch (input)
            {
                case "1":
                    Console.Write("Descripción de la tarea: ");
                    var description = Console.ReadLine();
                    Console.Write("Prioridad de la tarea (1-5): ");
                    if (int.TryParse(Console.ReadLine(), out int priority) && priority >= 1 && priority <= 5)
                    {
                        toDoList.AddItem(description, priority);
                    }
                    else
                    {
                        Console.WriteLine("Prioridad inválida.");
                    }
                    break;

                case "2":
                    Console.Write("Número de tarea a marcar como completada: ");
                    if (int.TryParse(Console.ReadLine(), out int index1))
                    {
                        toDoList.MarkAsCompleted(index1);
                    }
                    else
                    {
                        Console.WriteLine("Entrada inválida.");
                    }
                    break;

                case "3":
                    Console.WriteLine("¿Mostrar tareas completadas? (s/n): ");
                    bool showCompleted = Console.ReadLine()?.ToLower() == "s";
                    toDoList.ListItems(showCompleted);
                    break;

                case "4":
                    Console.Write("Número de tarea a eliminar: ");
                    if (int.TryParse(Console.ReadLine(), out int index2))
                    {
                        toDoList.RemoveItem(index2);
                    }
                    else
                    {
                        Console.WriteLine("Entrada inválida.");
                    }
                    break;

                case "5":
                    Console.WriteLine("Saliendo de la aplicación.");
                    return;

                default:
                    Console.WriteLine("Opción inválida.");
                    break;
            }
        }
    }
}
