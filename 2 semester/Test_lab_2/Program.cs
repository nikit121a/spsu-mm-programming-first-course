using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine();
            Console.WriteLine("Here we go !");
            Console.WriteLine();
            Info_Lib.SetInfo();
            Console.WriteLine("Name?");
            string name = Console.ReadLine();
            Info_Lib.ShowInfo(name);

            // Ожидание нажатия клавиши Enter перед завершением работы
            Console.ReadLine();
        }
    }

    class Tank
    {
        public string Name { get; private set; }
        string weapon;
        uint[] armor = new uint[3];
        uint year;
        string country;

        public void WriteInfo()
        {
            Console.WriteLine("Name ---- {0}", this.Name);
            Console.WriteLine("Weapon -- {0}", this.weapon);
            Console.WriteLine("Armor --- {0}/{1}/{2}", this.armor[0], this.armor[1], this.armor[2]);
            Console.WriteLine("Year ---- {0}", this.year);
            Console.WriteLine("Country - {0}", this.country);
        }

        public Tank(string n, string w, uint arm0, uint arm1, uint arm2, uint y, string c)
        {
            this.Name = n;
            this.weapon = w;
            this.armor[0] = arm0;
            this.armor[1] = arm1;
            this.armor[2] = arm2;
            this.year = y;
            this.country = c;
        }
        public Tank()
        {
        }
    }

    class Info_Lib
    {
        static Tank[] arr = new Tank[4];
        public static void SetInfo()
        {
            arr[0] = new Tank("T-34",
                              "76-mm cannon",
                               45, 45, 40, 1940, "USSR");
            arr[1] = new Tank("IS-3",
                              "122-mm D-25T",
                              110, 90, 60, 1945, "USSR");
            arr[2] = new Tank("Tiger",
                              "88-mm KwK 36 L/56",
                              100, 80, 80, 1942, "Germany");
            arr[3] = new Tank("Baneblade",
                              "Battle cannon, Autocannon, Demolisher cannon, x2 Lascannon,\n\t  x6 twin-linked heavy bolters.",
                              320, 200, 100, 40000, "Mars");
            Console.WriteLine("Set info for:");
            for (int i = 0; i < 4; i++)
            {
            Console.WriteLine("{0}", arr[i].Name);
            }

        }
        public static void ShowInfo(string searhigName)
        {
            bool z = true;
            for (int i = 0; i < 4; i++)
            {
                if(arr[i].Name == searhigName)
                {
                    arr[i].WriteInfo();
                    z = false;
                }
            }
            if (z)
                Console.WriteLine("Not exist");
        }
    }
}