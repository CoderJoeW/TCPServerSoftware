#include "pch.h"
#include "MyProgram.h"

using namespace System::Threading;

MyProgram::MyProgram()
{
}

MyProgram::~MyProgram()
{
}
void MyProgram::InitializeConsoleThread()
{
    consoleThread = gcnew Thread(gcnew ThreadStart(this, &MyProgram::ConsoleLoop));
    consoleThread->Name = "ConsoleThread";
    consoleThread->Start();
}

void MyProgram::ConsoleLoop()
{
    while (true)
    {

    }
}