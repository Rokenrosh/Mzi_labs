using System;

namespace HMAC
{
    class Program
    {
        static void Main(string[] args)
        {
            Hmac hmac = new Hmac();
            Console.WriteLine("Enter a message");
            String msg = Console.ReadLine();
            String result = hmac.Hmac_func(hmac.randomGenerator(), msg);
            Console.WriteLine("result: {0}", result);
        }
    }
}
