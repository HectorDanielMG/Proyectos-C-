 
using System;

class Program
{
    static void Main()
    {
        double num1, num2, resultado;
        string operacion;

        Console.WriteLine("Calculadora básica en C#");

        Console.Write("Ingresa el primer número: ");
        num1 = Convert.ToDouble(Console.ReadLine());

        Console.Write("Ingresa el segundo número: ");
        num2 = Convert.ToDouble(Console.ReadLine());

        Console.WriteLine("Selecciona la operación: + (suma), - (resta), * (multiplicación), / (división)");
        operacion = Console.ReadLine();

        switch (operacion)
        {
            case "+":
                resultado = num1 + num2;
                Console.WriteLine($"Resultado: {num1} + {num2} = {resultado}");
                break;

            case "-":
                resultado = num1 - num2;
                Console.WriteLine($"Resultado: {num1} - {num2} = {resultado}");
                break;

            case "*":
                resultado = num1 * num2;
                Console.WriteLine($"Resultado: {num1} * {num2} = {resultado}");
                break;

            case "/":
                if (num2 != 0)
                {
                    resultado = num1 / num2;
                    Console.WriteLine($"Resultado: {num1} / {num2} = {resultado}");
                }
                else
                {
                    Console.WriteLine("Error: No se puede dividir por 0.");
                }
                break;

            default:
                Console.WriteLine("Operación no válida.");
                break;
        }
    }
}
