#include "ByteBuffer.h"
using namespace System::Collections;
using namespace System::Collections::Generic;
#pragma once;
ref class ClientHandleData
{
private:
		static ByteBuffer^ playerBuffer = nullptr;
		static int pLength;
public:
		delegate void Packet_(array<Byte>^ data);
		static Dictionary<int, Packet_^>^ packetListener = nullptr;
		static void InitializePacketListener();
		static void HandleData(array<Byte>^ data);
		static void HandleDataPackages(array<Byte>^ data);
		static void HandleWelcomeMsg(array<Byte>^ data);
};

