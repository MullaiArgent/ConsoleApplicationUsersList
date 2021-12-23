#pragma managed
#include "pch.h"
#include "ConsoleApplicationUsersList.h"
#include <type_traits>
#include <iostream>
#include <fstream>
#include <string>

using namespace System;
using namespace System::Runtime;
using namespace System::Collections::ObjectModel;
using namespace System::Management::Automation;
using namespace System::Management::Automation::Runspaces;
using namespace System::Runtime::InteropServices;

public delegate void MyDelegate(System::Object^ sender, DataAddedEventArgs^ e);

ref class _PowerShell {

private:
    PowerShell^ _powershell;

public:
    _PowerShell() {
        _powershell = PowerShell::Create();

    }
    void AddArgument(String^ parameter)
    {
        _powershell->AddArgument(parameter);
    }

    void AddCommand(String^ command) {
        _powershell->AddCommand(command);
    }

    Collection<PSObject^ >^ Run() {
        Console::WriteLine("Running the Command...");
        Collection<PSObject^>^ psResults = _powershell->Invoke();
        for each (PSObject ^result in psResults) {
            Console::WriteLine(result->ToString());
        }
        return psResults;
    }
    Collection<String^>^ RunAsync() {

        Console::WriteLine("Running Commands Asyncronously...");

        PSDataCollection<PSObject^>^ outputCollection = gcnew PSDataCollection<PSObject^>();

        outputCollection->DataAdded += gcnew MyDelegate(this , &_PowerShell::Output_DataAdded);

        IAsyncResult^ result = _powershell->BeginInvoke<PSObject^, PSObject^>(nullptr, outputCollection);

        Collection<String^>^ outputResults = gcnew Collection<String^>();

        for each (PSObject ^ outputItem in outputCollection)
        {
            String^ outputLine = outputItem->BaseObject->ToString();

            outputResults->Add(outputLine);

            Console::Write(outputLine);
        }
        return outputResults;
    }

    void Output_DataAdded(System::Object^ sender, DataAddedEventArgs^ e)
    {
        PSDataCollection<PSObject^>^ outputCollection = (PSDataCollection<PSObject^>^)(sender);

        PSObject^ psObject = outputCollection[e->Index];

        Console::Write("Output: {0}", psObject->BaseObject->ToString());
    }
};

int main(array<System::String^>^ args)
{
    _PowerShell^ _powershell = gcnew _PowerShell();
    _powershell->AddCommand("Net");
    _powershell->AddArgument("Users");
    _powershell->Run();
    
}