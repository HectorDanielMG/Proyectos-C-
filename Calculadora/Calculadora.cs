using System;

namespace CalculadoraApp
{
    public class Calculadora
    {
        public double Sumar(double a, double b)
        {
            return a + b;
        }

        public double Restar(double a, double b)
        {
            return a - b;
        }

        public double Multiplicar(double a, double b)
        {
            return a * b;
        }

        public double Dividir(double a, double b)
        {
            if (b == 0)
            {
                Console.WriteLine("Error: División entre cero no permitida.");
                return double.NaN;
            }
            return a / b;
        }

        public double Potencia(double baseNum, double exponente)
        {
            return Math.Pow(baseNum, exponente);
        }

        public double RaizCuadrada(double num)
        {
            if (num < 0)
            {
                Console.WriteLine("Error: No se puede calcular la raíz cuadrada de un número negativo.");
                return double.NaN;
            }
            return Math.Sqrt(num);
        }

        public static void Main(string[] args)
        {
            Calculadora calculadora = new Calculadora();

            Console.WriteLine("Calculadora básica en C#");
            Console.WriteLine("------------------------");

            Console.Write("Ingrese el primer número: ");
            double num1 = Convert.ToDouble(Console.ReadLine());

            Console.Write("Ingrese el segundo número: ");
            double num2 = Convert.ToDouble(Console.ReadLine());

            Console.WriteLine("Seleccione una operación:");
            Console.WriteLine("1. Sumar");
            Console.WriteLine("2. Restar");
            Console.WriteLine("3. Multiplicar");
            Console.WriteLine("4. Dividir");
            Console.WriteLine("5. Potencia");
            Console.WriteLine("6. Raíz cuadrada del primer número");

            int opcion = Convert.ToInt32(Console.ReadLine());
            double resultado = 0;

            switch (opcion)
            {
                case 1:
                    resultado = calculadora.Sumar(num1, num2);
                    break;
                case 2:
                    resultado = calculadora.Restar(num1, num2);
                    break;
                case 3:
                    resultado = calculadora.Multiplicar(num1, num2);
                    break;
                case 4:
                    resultado = calculadora.Dividir(num1, num2);
                    break;
                case 5:
                    Console.WriteLine("Calculando la potencia...");
                    resultado = calculadora.Potencia(num1, num2);
                    break;
                case 6:
                    Console.WriteLine("Calculando la raíz cuadrada...");
                    resultado = calculadora.RaizCuadrada(num1);
                    break;
                default:
                    Console.WriteLine("Opción inválida.");
                    break;
            }

            Console.WriteLine("Resultado: " + resultado);
        }
    }
}
