using namespace System::Threading;
#pragma once
ref class MyProgram
{
    public:
        MyProgram();
        ~MyProgram();
        void InitializeConsoleThread();
    private:
        Thread^ consoleThread = nullptr;
        void ConsoleLoop();
};

