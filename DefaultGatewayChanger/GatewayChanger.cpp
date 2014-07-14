#include "GatewayChanger.h"

// Пулучить ссылку на объект класса
GatewayChanger^ GatewayChanger::GetInstance() {
	if (!GatewayChanger::m_instanse) GatewayChanger::m_instanse = gcnew GatewayChanger();
	return m_instanse;
}

// Удалить объект
void GatewayChanger::ResetInstance() {
	delete m_instanse;
}

GatewayChanger::GatewayChanger() {
	checkTrueIco = gcnew System::Drawing::Icon("24-em-check.ico");
	checkFalseIco = gcnew System::Drawing::Icon("24-em-cross.ico");

	m_isMainСhannel = 0;

	m_ip = gcnew List<System::String^>();
	m_masks = gcnew List<System::String^>();
	m_gateways = gcnew List<System::String^>();

	m_ipOcan = nullptr;
	m_ipRcan = nullptr;
	xmlParse = nullptr;
	getXmlSettings();

	m_hostName = nullptr;
	m_domainName = nullptr;
	m_adapter = nullptr;

	choiceOfAdapter();
	isMainChannel();
}

GatewayChanger::~GatewayChanger() {

}

System::Drawing::Icon^ GatewayChanger::getTrueIco() {
	return checkTrueIco;
}

System::Drawing::Icon^ GatewayChanger::getFalseIco() {
	return checkFalseIco;
}

bool GatewayChanger::getXmlSettings() {
	bool isLoad = false;
	xmlParse = gcnew XmlDocument();

	try{
		xmlParse->Load("config.xml");
		isLoad = true;
	}
	catch (...){
		xmlParse->LoadXml(defaultConfig());
		isLoad = false;
	}

	using namespace System::Runtime::InteropServices;

	m_ipOcan = xmlParse->GetElementsByTagName("main")->Item(0)->InnerText;
	m_ipRcan = xmlParse->GetElementsByTagName("reserve")->Item(0)->InnerText;

	return isLoad;
}

System::String^ GatewayChanger::defaultConfig() {
	return "<config><main>192.168.10.1</main><reserve>192.168.11.3</reserve></config>";
}

System::String^ GatewayChanger::getMainGateway() {
	return m_ipOcan;
}

System::String^ GatewayChanger::getReserveGateway() {
	return m_ipRcan;
}

int GatewayChanger::isMainChannel() {
	if (m_ipOcan == m_gateways[0]) {
		m_isMainСhannel = 1;
	}
	else {
		if (m_ipRcan == m_gateways[0]) {
			m_isMainСhannel = 2;
		}
		else {
			m_isMainСhannel = 0;
		}
	}

	return m_isMainСhannel;
}

void GatewayChanger::saveXmlSettings() {
	xmlParse->GetElementsByTagName("main")->Item(0)->InnerText = m_ipOcan;
	xmlParse->GetElementsByTagName("reserve")->Item(0)->InnerText = m_ipRcan;
	xmlParse->Save("config.xml");
}


void GatewayChanger::choiceOfAdapter() {
	IPGlobalProperties ^ computerProperties = IPGlobalProperties::GetIPGlobalProperties();
	array<NetworkInterface^>^nics = NetworkInterface::GetAllNetworkInterfaces();
	
	m_hostName = computerProperties->HostName;
	m_domainName = computerProperties->DomainName;
	Console::WriteLine("Interface information for {0}.{1} :", m_hostName, m_domainName);
	
	m_ip->Clear();
	m_masks->Clear();
	m_gateways->Clear();

	System::Collections::IEnumerator^ myEnum27 = nics->GetEnumerator();
	while (myEnum27->MoveNext())
	{
		NetworkInterface ^ adapter = safe_cast<NetworkInterface ^>(myEnum27->Current);
		//IPInterfaceProperties ^ properties = adapter->GetIPProperties();
		if (adapter->NetworkInterfaceType.ToString() == "Ethernet") {
			m_adapter = adapter;
			Console::WriteLine();
			Console::WriteLine(m_adapter->Description);
			Console::WriteLine(String::Empty->PadLeft(m_adapter->Description->Length, '='));
			Console::WriteLine("  Interface type .......................... : {0}",
				m_adapter->NetworkInterfaceType);
			Console::WriteLine("  Physical Address ........................ : {0}",
				m_adapter->GetPhysicalAddress());
			Console::WriteLine("  Operation status ........................ : {0}",
				m_adapter->OperationalStatus);

			Console::WriteLine("Ip addreses :");
			IPInterfaceProperties ^ adapterProperties = adapter->GetIPProperties();

			UnicastIPAddressInformationCollection ^ uniCast = adapterProperties->UnicastAddresses;
			if (uniCast->Count > 0)
			{
				System::Collections::IEnumerator^ uniEnum = uniCast->GetEnumerator();
				while (uniEnum->MoveNext())
				{
					UnicastIPAddressInformation ^ uni = safe_cast<UnicastIPAddressInformation ^>(uniEnum->Current);
					if (uni->IPv4Mask->Address) {
						m_ip->Add(uni->Address->ToString());
						m_masks->Add(uni->IPv4Mask->ToString());
						Console::WriteLine("  IP Address .............................. : {0} {1}",
							uni->Address, uni->IPv4Mask);
					}
				}
				Console::WriteLine();
			}

			GatewayIPAddressInformationCollection^ gateways = adapterProperties->GatewayAddresses;
			if (gateways->Count > 0)
			{
				System::Collections::IEnumerator^ gatewayEnum = gateways->GetEnumerator();
				while (gatewayEnum->MoveNext())
				{
					GatewayIPAddressInformation ^ gw = safe_cast<GatewayIPAddressInformation ^>(gatewayEnum->Current);
					m_gateways->Add(gw->Address->ToString());
					Console::WriteLine("  Gateway ................................. : {0}",
						gw->Address);
					
				}
				Console::WriteLine();
			}
		}
	}
}

List<System::String^>^ GatewayChanger::getIpAddresses(){
	return m_ip;
}

List<System::String^>^ GatewayChanger::getMaskIpAddresses() {
	return m_masks;
}

List<System::String^>^ GatewayChanger::getGateways() {
	return m_gateways;
}


System::String^ GatewayChanger::getNameAdapter() {
	return m_adapter->Description;
}

System::String^ GatewayChanger::getMacAdapter() {
	return m_adapter->GetPhysicalAddress()->ToString();
}

bool GatewayChanger::checkIpString(System::String^ _IpString) {
	try
	{
		// Create an instance of IPAddress for the specified address string (in 
		// dotted-quad, or colon-hexadecimal notation).
		IPAddress^ address = IPAddress::Parse(_IpString);

		return true;
	}
	catch (ArgumentNullException^ e)
	{
		System::String^ message = "ArgumentNullException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, _IpString,
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
	catch (FormatException^ e)
	{
		System::String^ message = "FormatException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, _IpString,
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
	catch (Exception^ e)
	{
		System::String^ message = "FormatException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, _IpString,
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}

	return true;
}

void GatewayChanger::setMainCanIpGateway(System::String^ _mainIp) {
	m_ipOcan = _mainIp;
}

void GatewayChanger::setReserveCanIpGateway(System::String^ _reserveIp) {
	m_ipRcan = _reserveIp;
}

bool GatewayChanger::pingGateway() {
	bool isPing = false;
	Ping ^ pingSender = gcnew Ping;
	PingOptions ^ options = gcnew PingOptions;

	// Use the default Ttl value which is 128,
	// but change the fragmentation behavior.
	options->DontFragment = true;

	// Create a buffer of 32 bytes of data to be transmitted.
	String^ data = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	array<Byte>^buffer = Encoding::ASCII->GetBytes(data);
	int timeout = 120;
	for (int i = 0; i < m_gateways->Count; i++) {
		PingReply ^ reply = pingSender->Send(m_gateways[i], timeout, buffer, options);

		if (reply->Status == IPStatus::Success)
		{
			Console::WriteLine("Ping gateway:");
			Console::WriteLine("\tAddress: {0}", reply->Address->ToString());
			Console::WriteLine("\tRoundTrip time: {0}", reply->RoundtripTime);
			Console::WriteLine("\tTime to live: {0}", reply->Options->Ttl);
			Console::WriteLine("\tDon't fragment: {0}", reply->Options->DontFragment);
			Console::WriteLine("\tBuffer size: {0}", reply->Buffer->Length);
			Console::WriteLine();

			isPing = true;
			//return true;
		}
		else {
			Console::WriteLine("Dont ping gateway...");

			//return false;
		}
	}
	return isPing;
}

bool GatewayChanger::changeDefaultGateway(int _channel) {
	using namespace System::Runtime::InteropServices;
	System::String^ command;
	System::String^ netshInterfaceIp = "netsh interface ip ";
	System::String^ setAdr = "set address name=\"";
	System::String^ addAdr = "add address name=\"";
	System::String^ adapName = m_adapter->Name;
	System::String^ statAdr = " static ";
	System::String^ ipOk = m_ip[0];
	System::String^ mask = m_masks[0];
	System::String^ ipRk;
	if (m_ip->Count > 1) ipRk = m_ip[1];
	System::String^ toLog = " > defgateway.log";

	System::String^ msg;

	switch (_channel)
	{
	case 1:
		msg = netshInterfaceIp + setAdr + adapName + "\"" + statAdr + ipOk + " " + mask + " " + m_ipOcan + " 1";
		printf("System cmd: %s\n", msg);
		WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);
		
		Sleep(5000);
		if (m_ip->Count > 1) {
			msg = netshInterfaceIp + addAdr + adapName + "\"" + " " + ipRk + " " + mask;
			printf("System cmd: %s\n", msg);
			WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);
		}
		break;
	case 2:
		msg = netshInterfaceIp + setAdr + adapName + "\"" + statAdr + ipOk + " " + mask + " " + m_ipRcan + " 1";
		printf("System cmd: %s\n", msg);
		WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);

		Sleep(5000);
		if (m_ip->Count > 1) {
			msg = netshInterfaceIp + addAdr + adapName + "\"" + " " + ipRk + " " + mask;
			printf("System cmd: %s\n", msg);
			WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);
		}
		break;
	default:
		return false;
		break;
	}

	Sleep(5000);
	choiceOfAdapter(); 

	return true;
}