using System;

namespace CalculadoraApp
{
    class Calculadora
    {
        static void Main(string[] args)
        {
            while (true)
            {
                Console.Clear();
                Console.WriteLine("Calculadora en C#");
                Console.WriteLine("Operaciones disponibles:");
                Console.WriteLine("1. Sumar (+)");
                Console.WriteLine("2. Restar (-)");
                Console.WriteLine("3. Multiplicar (*)");
                Console.WriteLine("4. Dividir (/)");
                Console.WriteLine("5. Potencia (^)");
                Console.WriteLine("6. Salir");
                
                Console.Write("Seleccione una operación: ");
                string operacion = Console.ReadLine();

                if (operacion == "6") break;

                Console.Write("Ingrese el primer número: ");
                double num1 = Convert.ToDouble(Console.ReadLine());

                Console.Write("Ingrese el segundo número: ");
                double num2 = Convert.ToDouble(Console.ReadLine());

                double resultado = 0;

                switch (operacion)
                {
                    case "+":
                        resultado = Sumar(num1, num2);
                        break;
                    case "-":
                        resultado = Restar(num1, num2);
                        break;
                    case "*":
                        resultado = Multiplicar(num1, num2);
                        break;
                    case "/":
                        resultado = Dividir(num1, num2);
                        break;
                    case "^":
                        resultado = Potencia(num1, num2);
                        break;
                    default:
                        Console.WriteLine("Operación no válida.");
                        continue;
                }

                Console.WriteLine($"Resultado: {resultado}");
                Console.WriteLine("Presione cualquier tecla para continuar...");
                Console.ReadKey();
            }
        }

        static double Sumar(double a, double b) => a + b;
        static double Restar(double a, double b) => a - b;
        static double Multiplicar(double a, double b) => a * b;
        
        static double Dividir(double a, double b)
        {
            if (b == 0)
            {
                Console.WriteLine("Error: División por cero no permitida.");
                return double.NaN;
            }
            return a / b;
        }
        
        static double Potencia(double a, double b) => Math.Pow(a, b);
    }
}
