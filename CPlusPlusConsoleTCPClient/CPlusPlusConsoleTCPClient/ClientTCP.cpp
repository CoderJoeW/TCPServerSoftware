#include "pch.h"
#include "ClientTCP.h"
#include "Packages.h"
#include "ByteBuffer.h"
#include "ClientHandleData.h"
void ClientTCP::InitializeClientSocket(String^ address, int port)
{
	clientSocket = gcnew TcpClient();
	clientSocket->ReceiveBufferSize = 4096;
	clientSocket->SendBufferSize = 4096;
	recieveBuffer = gcnew array<Byte>(4096 * 2);
	clientSocket->BeginConnect(address, port, gcnew AsyncCallback(ClientConnectCallback), clientSocket);
}

void ClientTCP::ClientConnectCallback(IAsyncResult^result)
{
	clientSocket->EndConnect(result);
	if (clientSocket->Connected == false)
	{
		return;
	}
	else
	{
		myStream = clientSocket->GetStream();
		myStream->BeginRead(recieveBuffer, 0, 4096 * 2, gcnew AsyncCallback(RecieveCallback),nullptr);
	}
}

void ClientTCP::RecieveCallback(IAsyncResult^ result)
{
	try
	{
		int readBytes = myStream->EndRead(result);

		if (readBytes <= 0)
		{
			return;
		}

		array<Byte>^newBytes = gcnew array<Byte>(readBytes);
		Buffer::BlockCopy(recieveBuffer, 0, newBytes, 0, readBytes);

		ClientHandleData::HandleData(newBytes);

		myStream->BeginRead(recieveBuffer, 0, 4096 * 2, gcnew AsyncCallback(RecieveCallback), nullptr);
	}
	catch (Exception^ ex)
	{
		throw ex;
	}
}

void ClientTCP::SendData(array<Byte>^data)
{
	ByteBuffer^ buffer = gcnew ByteBuffer();

	buffer->WriteInteger((data->GetUpperBound(0) - data->GetLowerBound(0)) + 1);
	buffer->WriteBytes(data);
	myStream->Write(buffer->ToArray(), 0, buffer->ToArray()->Length);
	//buffer->Dispose();
}

void ClientTCP::PACKET_ThankYou()
{
	ByteBuffer^ buffer = gcnew ByteBuffer();
	buffer->WriteInteger((int)ClientPackages::CThankYouMsg);
	buffer->WriteString("Thank You");
	SendData(buffer->ToArray());
}