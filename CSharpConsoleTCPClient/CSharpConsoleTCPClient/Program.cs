using System;
using System.Threading;
using System.Threading.Tasks;

namespace CSharpConsoleTCPClient
{
    class Program
    {
        private static Thread consoleThread;

        static void Main(string[] args)
        {
            InitializeConsoleThread();
            ClientHandleData.InitializePacketListener();
            ClientTCP.InitializeClientSocket("34.72.41.136", 19132);
        }

        private static void InitializeConsoleThread()
        {
            consoleThread = new Thread(ConsoleLoop);
            consoleThread.Name = "ConsoleThread";
            consoleThread.Start();
        }

        private static void ConsoleLoop()
        {
            while (true)
            {

            }
        }
    }
}
