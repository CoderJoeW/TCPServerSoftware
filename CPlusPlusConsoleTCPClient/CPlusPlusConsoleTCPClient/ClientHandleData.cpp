#include "pch.h"
#include "ClientHandleData.h"
#include "Packages.h"

void ClientHandleData::InitializePacketListener()
{
	packetListener = gcnew Dictionary<int, Packet_^>();
	packetListener->Add((int)ServerPackages::SWelcomeMsg, gcnew Packet_(ClientHandleData::HandleWelcomeMsg));
}

void ClientHandleData::HandleData(array<Byte>^ data)
{
	//Copying our packet info into a temporary array to edit/peek
	array<Byte>^ buffer = (array<Byte>^)(data->Clone());

	//Check if connected player has an instance of the byte buffer
	if (playerBuffer == nullptr)
	{
		//If there is no instance create a new instance
		playerBuffer = gcnew ByteBuffer();
	}

	//Read package from player
	playerBuffer->WriteBytes(buffer);

	//Check if recieved package is empty, if so dont continue executing
	if (playerBuffer->Count() == 0)
	{
		playerBuffer->Clear();
		return;
	}

	//Check if package contains info
	if (playerBuffer->Length() >= 4)
	{
		//if so read full package length
		pLength = playerBuffer->ReadInteger(false);

		if (pLength <= 0)
		{
			//If there is no package or package is invalid close this method
			playerBuffer->Clear();
			return;
		}
	}

	while (pLength > 0 & pLength <= playerBuffer->Length() - 4)
	{
		if (pLength <= playerBuffer->Length() - 4)
		{
			playerBuffer->ReadInteger(true);
			data = playerBuffer->ReadBytes(pLength,true);
			HandleDataPackages(data);
		}

		pLength = 0;

		if (playerBuffer->Length() >= 4)
		{
			pLength = playerBuffer->ReadInteger(false);

			if (pLength <= 0)
			{
				//If there is no package or package is invalid close this method
				playerBuffer->Clear();
				return;
			}
		}

		if (pLength <= 1)
		{
			playerBuffer->Clear();
		}
	}
}

void ClientHandleData::HandleDataPackages(array<Byte>^ data)
{
	Packet_^ packet;
	ByteBuffer^ buffer = gcnew ByteBuffer();
	buffer->WriteBytes(data);
	int packageID = buffer->ReadInteger(true);

	if (packetListener->TryGetValue(packageID, packet))
	{
		packet->Invoke(data);
	}
}

void ClientHandleData::HandleWelcomeMsg(array<Byte>^ data)
{
	ByteBuffer^ buffer = gcnew ByteBuffer();
	buffer->WriteBytes(data);
	int packageID = buffer->ReadInteger(true);
	String^ msg = buffer->ReadString(true);

	Console::WriteLine(msg);

	//ClientTCP.PACKET_ThankYou();
}