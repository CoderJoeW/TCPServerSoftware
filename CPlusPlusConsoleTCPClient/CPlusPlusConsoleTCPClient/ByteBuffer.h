using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Numerics;
#pragma once
ref class ByteBuffer
{
	private:
		List<Byte>^ Buff = nullptr;
		array<Byte>^ readBuff = nullptr;
		int readPos;
		bool buffUpdated = false;
		bool disposedValue = false;
	public:
		ByteBuffer();
		~ByteBuffer();
		int GetReadPos();
		array<Byte>^ ToArray();
		int Count();
		int Length();
		void Clear();
		void WriteByte(Byte^ input);
		void WriteBytes(array<Byte>^ input);
		void WriteShort(short input);
		void WriteInteger(int input);
		void WriteLong(long input);
		void WriteFloat(float input);
		void WriteString(String^ input);
		void WriteVector3(Vector3 input);
		void WriteQuanternion(Quaternion input);
		/*
		Byte ReadByte(bool Peek = true);
		array<Byte>^ ReadBytes(int Length, bool Peek = true);
		short ReadShort(bool Peek = true);
		int ReadInteger(bool Peek = true);
		long ReadLong(bool Peek = true);
		float ReadFloat(bool Peek = true);
		String ReadString(bool Peek = true);
		Vector3 ReadVector3(bool Peek = true);;
		Quaternion ReadQuaternion(bool Peek = true);
		*/

		Byte^ ReadByte(bool Peek);
		array<Byte>^ ReadBytes(int Length, bool Peek);
		short ReadShort(bool Peek);
		int ReadInteger(bool Peek);
		long ReadLong(bool Peek);
		float ReadFloat(bool Peek);
		String^ ReadString(bool Peek);
		Vector3 ReadVector3(bool Peek);;
		Quaternion ReadQuaternion(bool Peek);
		virtual void Dispose2(bool disposing);
		virtual void Dispose2();
};

