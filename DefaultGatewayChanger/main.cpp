#include <stdio.h>
//#include <Windows.h>
#include "Settings.h"
#include "GatewayChanger.h"

using namespace DefaultGatewayChanger;
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main() {	
	// Устанавливаем локализацию русского языка
	setlocale(LC_ALL, "Russian");

	GatewayChanger^ core;
	core = GatewayChanger::GetInstance();

	// Включение визуальных эффектов Windows XP до создания каких-либо элементов управления
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Создание главного окна и его запуск
	Settings^ form = gcnew Settings();
	Application::Run(form);

	return 0;
}