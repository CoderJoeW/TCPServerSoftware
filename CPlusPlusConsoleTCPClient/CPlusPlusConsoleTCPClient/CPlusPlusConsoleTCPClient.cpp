#include "pch.h"
#include "MyProgram.h"
#include "ClientHandleData.h"
#include "ClientTCP.h"

using namespace System::Threading;
using namespace System;


int main(array<System::String^>^ args)
{
    MyProgram^ p = gcnew MyProgram();

    p->InitializeConsoleThread();
    ClientHandleData::InitializePacketListener();
    ClientTCP::InitializeClientSocket("34.72.41.136", 19132);

    return 0;
}
