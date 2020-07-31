#pragma once
using namespace System;
using namespace System::Net::Sockets;
ref class ClientTCP
{
private:
	static TcpClient^ clientSocket = nullptr;
	static NetworkStream^ myStream = nullptr;
	static array<Byte>^ recieveBuffer = nullptr;
public:
	static void InitializeClientSocket(String^ address, int port);
	static void ClientConnectCallback(IAsyncResult^ result);
	static void RecieveCallback(IAsyncResult^ result);
	static void SendData(array<Byte>^ data);
	static void PACKET_ThankYou();
};

