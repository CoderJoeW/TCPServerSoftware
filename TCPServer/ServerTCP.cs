using System;
using System.Net;
using System.Net.Sockets;
using Newtonsoft.Json;

namespace Better_Server {
    class ServerTCP {
        private static TcpListener serverSocket;

        public static ClientObject[] clientObjects;

        public static void InitializeServer() {
            //InitializeMySQLServer();
            InitializeClientObjects();
            InitializeServerSocket();
        }

        private static void InitializeMySQLServer() {
            MySQL.mySQLSettings.user = "";
            MySQL.mySQLSettings.password = "";
            MySQL.mySQLSettings.server = "";
            MySQL.mySQLSettings.database = "";
        }

        private static void InitializeServerSocket() {
            serverSocket = new TcpListener(IPAddress.Any, Constants.PORT);
            serverSocket.Start();
            serverSocket.BeginAcceptTcpClient(new AsyncCallback(ClientConnectCallback), null);
        }

        private static void InitializeClientObjects() {
            clientObjects = new ClientObject[Constants.MAX_PLAYERS];

            for (int i = 1; i < Constants.MAX_PLAYERS; i++) {
                clientObjects[i] = new ClientObject(null, 0);
            }
        }

        private static void ClientConnectCallback(IAsyncResult result) {
            TcpClient tempClient = serverSocket.EndAcceptTcpClient(result);
            serverSocket.BeginAcceptTcpClient(new AsyncCallback(ClientConnectCallback), null);

            for (int i = 1; i < Constants.MAX_PLAYERS; i++) {
                if(clientObjects[i].socket == null) {
                    clientObjects[i] = new ClientObject(tempClient, i);

                    ServerTCP.PACKET_WelcomeMsg(i, "Welcome to the server");

                    return;
                }
            }
        }

        public static void SendDataTo(int connectionID, byte[] data) {
            ByteBuffer buffer = new ByteBuffer();

            buffer.WriteInteger((data.GetUpperBound(0) - data.GetLowerBound(0)) + 1);
            buffer.WriteBytes(data);
            clientObjects[connectionID].myStream.BeginWrite(buffer.ToArray(), 0, buffer.ToArray().Length, null, null);
            buffer.Dispose();
        }

        public static void PACKET_WelcomeMsg(int connectionID,string msg) {
            ByteBuffer buffer = new ByteBuffer();
            //add package id
            buffer.WriteInteger((int)ServerPackages.SWelcomeMsg);

            //send info
            buffer.WriteString(msg);

            SendDataTo(connectionID, buffer.ToArray());
        }
    }
}
