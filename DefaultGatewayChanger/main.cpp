#include <stdio.h>
#include <Windows.h>
#include <locale.h>
#include "Settings.h"
#include "GatewayChanger.h"

using namespace DefaultGatewayChanger;
using namespace System;
using namespace System::Windows::Forms;
using namespace std;

int main() {	
	// ������������� ����������� �������� �����
	setlocale(LC_ALL, "Russian");

	GatewayChanger^ core;
	core = GatewayChanger::GetInstance();

	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// �������� �������� ���� � ��� ������
	Settings^ form = gcnew Settings();
	Application::Run(form);

	return 0;
}