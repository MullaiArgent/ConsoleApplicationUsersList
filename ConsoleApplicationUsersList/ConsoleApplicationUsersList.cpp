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

int main(array<System::String^>^ args)
{

	EventHandler<System::Management::Automation::DataAddedEventArgs^>^ DataAdded = nullptr;

	PowerShell^ ps = PowerShell::Create();

	ps->Create();

	ps->AddCommand("Get-ExecutionPolicy", true);

	Collection<CommandInfo^> result = ps->Invoke<CommandInfo>();
	for each (CommandInfo^ var in result)
	{
		Console::WriteLine(var);
	}

	return 0;
}


// https://docs.microsoft.com/en-us/dotnet/api/system.management.automation.powershell.invoke?view=powershellsdk-7.0.0#System_Management_Automation_PowerShell_Invoke__2_System_Management_Automation_PSDataCollection___0__System_Management_Automation_PSDataCollection___1__System_Management_Automation_PSInvocationSettings_