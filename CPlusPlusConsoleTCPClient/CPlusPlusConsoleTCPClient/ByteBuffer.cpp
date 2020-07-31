#include "pch.h"
#include "ByteBuffer.h"

ByteBuffer::ByteBuffer()
{
	Buff = gcnew List<Byte>();
	readPos = 0;
}

ByteBuffer::~ByteBuffer()
{
	Dispose2();
}

int ByteBuffer::GetReadPos()
{
	return readPos;
}
array<Byte>^ ByteBuffer::ToArray()
{
	return Buff->ToArray();
}
int ByteBuffer::Count()
{
	return Buff->Count;
}
int ByteBuffer::Length()
{
	return Count() - readPos;
}
void ByteBuffer::Clear()
{
	Buff->Clear();
	readPos = 0;
}

void ByteBuffer::WriteByte(Byte^ input)
{
	Buff->Add(*input);
	buffUpdated = true;
}
void ByteBuffer::WriteBytes(array<Byte>^ input)
{
	Buff->AddRange(input);
	buffUpdated = true;
}
void ByteBuffer::WriteShort(short input)
{
	Buff->AddRange(BitConverter::GetBytes(input));
	buffUpdated = true;
}
void ByteBuffer::WriteInteger(int input)
{
	Buff->AddRange(BitConverter::GetBytes(input));
	buffUpdated = true;
}
void ByteBuffer::WriteLong(long input)
{
	Buff->AddRange(BitConverter::GetBytes(input));
	buffUpdated = true;
}
void ByteBuffer::WriteFloat(float input)
{
	Buff->AddRange(BitConverter::GetBytes(input));
	buffUpdated = true;
}
void ByteBuffer::WriteString(String^ input)
{
	Buff->AddRange(BitConverter::GetBytes(input->Length));
	Buff->AddRange(Encoding::ASCII->GetBytes(input));
	buffUpdated = true;
}
void ByteBuffer::WriteVector3(Vector3 input)
{
	array<Byte>^ vectorArray = gcnew array<Byte>(sizeof(float) * 3);

	Buffer::BlockCopy(BitConverter::GetBytes(input.X), 0, vectorArray, 0 * sizeof(float), sizeof(float));
	Buffer::BlockCopy(BitConverter::GetBytes(input.Y), 1, vectorArray, 0 * sizeof(float), sizeof(float));
	Buffer::BlockCopy(BitConverter::GetBytes(input.Z), 2, vectorArray, 0 * sizeof(float), sizeof(float));

	Buff->AddRange(vectorArray);
	buffUpdated = true;
}
void ByteBuffer::WriteQuanternion(Quaternion input)
{
	array<Byte>^ vectorArray = gcnew array<Byte>(sizeof(float) * 4);

	Buffer::BlockCopy(BitConverter::GetBytes(input.X), 0, vectorArray, 0 * sizeof(float), sizeof(float));
	Buffer::BlockCopy(BitConverter::GetBytes(input.Y), 1, vectorArray, 0 * sizeof(float), sizeof(float));
	Buffer::BlockCopy(BitConverter::GetBytes(input.Z), 2, vectorArray, 0 * sizeof(float), sizeof(float));
	Buffer::BlockCopy(BitConverter::GetBytes(input.W), 3, vectorArray, 0 * sizeof(float), sizeof(float));

	Buff->AddRange(vectorArray);
	buffUpdated = true;
}

Byte^ ByteBuffer::ReadByte(bool Peek)
{
	if (Buff->Count > readPos)
	{
		if (buffUpdated)
		{
			readBuff = Buff->ToArray();
			buffUpdated = false;
		}

		Byte^value = readBuff[readPos];

		if (Peek & Buff->Count > readPos)
		{
			readPos += 1;
		}

		return value;
	}
	else
	{
		throw gcnew Exception("[BYTE] Error");
	}
}
array<Byte>^ ByteBuffer::ReadBytes(int Length, bool Peek)
{
	if (Buff->Count > readPos)
	{
		if (buffUpdated)
		{
			readBuff = Buff->ToArray();
			buffUpdated = false;
		}

		array<Byte>^ value = Buff->GetRange(readPos, Length)->ToArray();

		if (Peek)
		{
			readPos += Length;
		}

		return value;
	}
	else
	{
		throw gcnew Exception("[BYTE[]] Error");
	}
}
short ByteBuffer::ReadShort(bool Peek)
{
	if (Buff->Count > readPos)
	{
		if (buffUpdated)
		{
			readBuff = Buff->ToArray();
			buffUpdated = false;
		}

		short value = BitConverter::ToInt16(readBuff, readPos);

		if (Peek & Buff->Count > readPos)
		{
			readPos += 2;
		}

		return value;
	}
	else
	{
		throw gcnew Exception("[SHORT] Error");
	}
}
int ByteBuffer::ReadInteger(bool Peek)
{
	if (Buff->Count > readPos)
	{
		if (buffUpdated)
		{
			readBuff = Buff->ToArray();
			buffUpdated = false;
		}

		int value = BitConverter::ToInt32(readBuff, readPos);

		if (Peek & Buff->Count > readPos)
		{
			readPos += 4;
		}

		return value;
	}
	else
	{
		throw gcnew Exception("[INT] Error");
	}
}
long ByteBuffer::ReadLong(bool Peek)
{
	if (Buff->Count > readPos)
	{
		if (buffUpdated)
		{
			readBuff = Buff->ToArray();
			buffUpdated = false;
		}

		long value = BitConverter::ToInt64(readBuff, readPos);

		if (Peek & Buff->Count > readPos)
		{
			readPos += 8;
		}

		return value;
	}
	else
	{
		throw gcnew Exception("[LONG] Error");
	}
}
float ByteBuffer::ReadFloat(bool Peek)
{
	if (Buff->Count > readPos)
	{
		if (buffUpdated)
		{
			readBuff = Buff->ToArray();
			buffUpdated = false;
		}

		float value = BitConverter::ToSingle(readBuff, readPos);

		if (Peek & Buff->Count > readPos)
		{
			readPos += 4;
		}

		return value;
	}
	else
	{
		throw gcnew Exception("[FLOAT] Error");
	}
}
String^ ByteBuffer::ReadString(bool Peek)
{
	int length = ReadInteger(true);

	if (buffUpdated)
	{
		readBuff = Buff->ToArray();
		buffUpdated = false;
	}

	String^ value = Encoding::ASCII->GetString(readBuff, readPos, length);

	if (Peek & Buff->Count > readPos)
	{
		readPos += length;
	}

	return value;
}
Vector3 ByteBuffer::ReadVector3(bool Peek)
{
	if (buffUpdated)
	{
		readBuff = Buff->ToArray();
		buffUpdated = false;
	}

	array<Byte>^ value = Buff->GetRange(readPos, sizeof(float) * 3)->ToArray();
	Vector3 vector3;
	vector3.X = BitConverter::ToSingle(value, 0 * sizeof(float));
	vector3.Y = BitConverter::ToSingle(value, 1 * sizeof(float));
	vector3.Z = BitConverter::ToSingle(value, 2 * sizeof(float));

	if (Peek)
	{
		readPos += sizeof(float) * 3;
	}

	return vector3;
}
Quaternion ByteBuffer::ReadQuaternion(bool Peek)
{
	if (buffUpdated)
	{
		readBuff = Buff->ToArray();
		buffUpdated = false;
	}

	array<Byte>^ value = Buff->GetRange(readPos, sizeof(float) * 4)->ToArray();
	Quaternion quaternion;
	quaternion.X = BitConverter::ToSingle(value, 0 * sizeof(float));
	quaternion.Y = BitConverter::ToSingle(value, 1 * sizeof(float));
	quaternion.Z = BitConverter::ToSingle(value, 2 * sizeof(float));
	quaternion.W = BitConverter::ToSingle(value, 3 * sizeof(float));

	if (Peek)
	{
		readPos += sizeof(float) * 4;
	}

	return quaternion;
}

void ByteBuffer::Dispose2 (bool disposing)
{
	if (!disposing)
	{
		if (disposing)
		{
			Buff->Clear();
			readPos = 0;
		}
		disposedValue = true;
	}
}

void ByteBuffer::Dispose2()
{
	Dispose2(true);
	GC::SuppressFinalize(this);
}