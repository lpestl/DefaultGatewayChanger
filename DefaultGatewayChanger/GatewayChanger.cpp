#include "GatewayChanger.h"

// œÛÎÛ˜ËÚ¸ ÒÒ˚ÎÍÛ Ì‡ Ó·˙ÂÍÚ ÍÎ‡ÒÒ‡
GatewayChanger^ GatewayChanger::GetInstance() {
	if (!GatewayChanger::m_instanse) GatewayChanger::m_instanse = gcnew GatewayChanger();
	return m_instanse;
}

// ”‰‡ÎËÚ¸ Ó·˙ÂÍÚ
void GatewayChanger::ResetInstance() {
	delete m_instanse;
}

GatewayChanger::GatewayChanger() {
	printf("#=========================#\nGatewayChanger init.\n");
	
	checkTrueIco = gcnew System::Drawing::Icon("24-em-check.ico");
	checkFalseIco = gcnew System::Drawing::Icon("24-em-cross.ico");

	selectNetCard();

	getXmlSettings();

	m_isMain—hannel = 0;
	checkingMainChannel();

}

GatewayChanger::~GatewayChanger() {
	delete[] m_adapterName;
	delete[] m_descName;
	delete[] m_mac;
	printf("GatewayChanger delete.\n#=========================#\n");
}

System::Drawing::Icon^ GatewayChanger::getTrueIco() {
	return checkTrueIco;
}

System::Drawing::Icon^ GatewayChanger::getFalseIco() {
	return checkFalseIco;
}

void GatewayChanger::getInterfaceNetInfo() {
	using namespace System;
	using namespace System::Net;
	using namespace System::Net::NetworkInformation;
	IPGlobalProperties^ computerProperties = IPGlobalProperties::GetIPGlobalProperties();
	array<NetworkInterface^>^nics = NetworkInterface::GetAllNetworkInterfaces();
	Console::WriteLine("Interface information for {0}.{1}     ", computerProperties->HostName, computerProperties->DomainName);
	if (nics == nullptr || nics->Length < 1)
	{
		Console::WriteLine("  No network interfaces found.");
		return;
	}

	System::String^ adapName = gcnew System::String(m_adapterName);
	Console::WriteLine("  Number of interfaces .................... : {0}", nics->Length);
	System::Collections::IEnumerator^ myEnum4 = nics->GetEnumerator();
	while (myEnum4->MoveNext())
	{
		NetworkInterface ^ adapter = safe_cast<NetworkInterface ^>(myEnum4->Current);
		if (adapter->Id == adapName) {
			using namespace System::Runtime::InteropServices;
			strcpy(m_adapterName, (const char*)(void*)Marshal::StringToHGlobalAnsi(adapter->Name));
			IPInterfaceProperties ^ properties = adapter->GetIPProperties();
			Console::WriteLine();
			Console::WriteLine(adapter->Description);
			Console::WriteLine(String::Empty->PadLeft(adapter->Description->Length, '='));
			Console::WriteLine("  Interface type .......................... : {0}",
				adapter->NetworkInterfaceType);
			Console::WriteLine("  Physical Address ........................ : {0}",
				adapter->GetPhysicalAddress());
			Console::WriteLine("  Operational status ...................... : {0}",
				adapter->OperationalStatus);
			Console::WriteLine("  Interface name .......................... : {0}",
				adapter->Name);
			String^ versions = "";

			// Create a display string for the supported IP versions. 
			if (adapter->Supports(NetworkInterfaceComponent::IPv4))
			{
				versions = "IPv4";
			}
			if (adapter->Supports(NetworkInterfaceComponent::IPv6))
			{
				if (versions->Length > 0)
				{
					versions = String::Concat(versions, " ");
				}
				versions = String::Concat(versions, "IPv6");
			}
			Console::WriteLine("  IP version .............................. : {0}",
				versions);
			//ShowIPAddresses(properties);

			// The following information is not useful for loopback adapters. 
			if (adapter->NetworkInterfaceType == NetworkInterfaceType::Loopback)
			{
				continue;
			}
			Console::WriteLine("  DNS suffix .............................. : {0}",
				properties->DnsSuffix);
			String^ label;

			if (adapter->Supports(NetworkInterfaceComponent::IPv4))
			{
				IPv4InterfaceProperties ^ ipv4 = properties->GetIPv4Properties();
				Console::WriteLine("  MTU...................................... : {0}",
					ipv4->Mtu);
				if (ipv4->UsesWins)
				{
					IPAddressCollection ^ winsServers = properties->WinsServersAddresses;
					if (winsServers->Count > 0)
					{
						label = "  WINS Servers ............................ :";
						//ShowIPAddresses(label, winsServers);
					}
				}
			}
			Console::WriteLine("  DNS enabled ............................. : {0}",
				properties->IsDnsEnabled);
			Console::WriteLine("  Dynamically configured DNS .............. : {0}",
				properties->IsDynamicDnsEnabled);
			Console::WriteLine("  Receive Only ............................ : {0}",
				adapter->IsReceiveOnly);
			Console::WriteLine("  Multicast ............................... : {0}",
				adapter->SupportsMulticast);
			//ShowInterfaceStatistics(adapter);
			Console::WriteLine();
		}
	}
}

void GatewayChanger::selectNetCard() {
	/* Declare and initialize variables */

	// It is possible for an adapter to have multiple
	// IPv4 addresses, gateways, and secondary WINS servers
	// assigned to the adapter. 
	//
	// Note that this sample code only prints out the 
	// first entry for the IP address/mask, and gateway, and
	// the primary and secondary WINS server for each adapter. 

	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;
	UINT i;

	/* variables used to print DHCP time info */
	struct tm newtime;
	char buffer[32];
	errno_t error;

	ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(sizeof (IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL) {
		printf("Error allocating memory needed to call GetAdaptersinfo\n");
		return;
	}
	
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
		FREE(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)MALLOC(ulOutBufLen);
		if (pAdapterInfo == NULL) {
			printf("Error allocating memory needed to call GetAdaptersinfo\n");
			return;
		}
	}

	printf("Selected working Network Card:\n");

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
		pAdapter = pAdapterInfo;
		while (pAdapter) {
			// ¬˚·Ó ÔÓ ‚ÒÚÓÂÌÌÓÈ ÒÂÚÂ‚ÓÈ ÔÎ‡ÚÂ
			if (pAdapter->Type == MIB_IF_TYPE_ETHERNET) {
				m_indexNetCard = pAdapter->ComboIndex;
				printf("\tComboIndex: \t%d\n", /*pAdapter->ComboIndex*/m_indexNetCard);
				if (m_adapterName) delete[] m_adapterName;
				m_adapterName = new char[260];
				strcpy(m_adapterName, pAdapter->AdapterName);
				printf("\tAdapter Name: \t%s\n", /*pAdapter->AdapterName*/m_adapterName);
				if (m_descName) delete[] m_descName;
				m_descName = new char[132];
				strcpy(m_descName, pAdapter->Description);
				printf("\tAdapter Desc: \t%s\n", /*pAdapter->Description*/m_descName);
				m_lenMac = pAdapter->AddressLength;
				if (m_mac) delete[] m_mac;
				m_mac = new BYTE[8];
				printf("\tAdapter Addr: \t");
				for (i = 0; i < pAdapter->AddressLength; i++) {
					m_mac[i] = pAdapter->Address[i];
					if (i == (pAdapter->AddressLength - 1))
						printf("%.2X\n", (int)/*pAdapter->Address[i]*/m_mac[i]);
					else
						printf("%.2X-", (int)/*pAdapter->Address[i]*/m_mac[i]);
				}
				m_indexNetCard = pAdapter->Index;
				printf("\tIndex: \t%d\n", /*pAdapter->Index*/m_indexNetCard);
				printf("\tType: \t");
				switch (pAdapter->Type) {
				case MIB_IF_TYPE_OTHER:
					printf("Other\n");
					break;
				case MIB_IF_TYPE_ETHERNET:
					printf("Ethernet\n");
					break;
				case MIB_IF_TYPE_TOKENRING:
					printf("Token Ring\n");
					break;
				case MIB_IF_TYPE_FDDI:
					printf("FDDI\n");
					break;
				case MIB_IF_TYPE_PPP:
					printf("PPP\n");
					break;
				case MIB_IF_TYPE_LOOPBACK:
					printf("Lookback\n");
					break;
				case MIB_IF_TYPE_SLIP:
					printf("Slip\n");
					break;
				default:
					printf("Unknown type %ld\n", pAdapter->Type);
					break;
				}

				if (m_ipCurr) delete m_ipCurr;
				m_ipCurr = new IP_ADDR_STRING( pAdapter->IpAddressList );
				printf("\tIP Address: \t%s\n", /*pAdapter->IpAddressList.IpAddress.String*/m_ipCurr->IpAddress.String);

				IP_ADDR_STRING *ipCurr2 = pAdapter->IpAddressList.Next;
				if (ipCurr2 != NULL) {
					if (m_ipResCurr) delete m_ipResCurr;
					m_ipResCurr = new IP_ADDR_STRING(*ipCurr2);
					printf("\tIP Addres 2: \t%s\n", m_ipResCurr->IpAddress.String);
				}
				printf("\tIP Mask: \t%s\n", /*pAdapter->IpAddressList.IpMask.String*/m_ipCurr->IpMask.String);

				if (m_gatewayCur) delete m_gatewayCur;
				m_gatewayCur = new IP_ADDR_STRING(pAdapter->GatewayList);
				printf("\tGateway: \t%s\n", /*pAdapter->GatewayList.IpAddress.String*/m_gatewayCur->IpAddress.String);
				printf("\t***\n");

				if (pAdapter->DhcpEnabled) {
					printf("\tDHCP Enabled: Yes\n");
					printf("\t  DHCP Server: \t%s\n",
						pAdapter->DhcpServer.IpAddress.String);

					printf("\t  Lease Obtained: ");
					/* Display local time */
					error = _localtime32_s(&newtime, (__time32_t*)&pAdapter->LeaseObtained);
					if (error)
						printf("Invalid Argument to _localtime32_s\n");
					else {
						// Convert to an ASCII representation 
						error = asctime_s(buffer, 32, &newtime);
						if (error)
							printf("Invalid Argument to asctime_s\n");
						else
							/* asctime_s returns the string terminated by \n\0 */
							printf("%s", buffer);
					}

					printf("\t  Lease Expires:  ");
					error = _localtime32_s(&newtime, (__time32_t*)&pAdapter->LeaseExpires);
					if (error)
						printf("Invalid Argument to _localtime32_s\n");
					else {
						// Convert to an ASCII representation 
						error = asctime_s(buffer, 32, &newtime);
						if (error)
							printf("Invalid Argument to asctime_s\n");
						else
							/* asctime_s returns the string terminated by \n\0 */
							printf("%s", buffer);
					}
				}
				else
					printf("\tDHCP Enabled: No\n");

				if (pAdapter->HaveWins) {
					printf("\tHave Wins: Yes\n");
					printf("\t  Primary Wins Server:    %s\n",
						pAdapter->PrimaryWinsServer.IpAddress.String);
					printf("\t  Secondary Wins Server:  %s\n",
						pAdapter->SecondaryWinsServer.IpAddress.String);
				}
				else
					printf("\tHave Wins: No\n");
				printf("\n");
			}
			pAdapter = pAdapter->Next;
		}
	}
	else {
		printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);

	}
	if (pAdapterInfo)
		FREE(pAdapterInfo);

	getInterfaceNetInfo();
}

IP_ADDR_STRING* GatewayChanger::getIpList(){
	return m_ipCurr;
}


IP_ADDR_STRING* GatewayChanger::getIpListReserve() {
	return m_ipResCurr;
}

IP_ADDR_STRING* GatewayChanger::getGatewayList() {
	return m_gatewayCur;
}

char* GatewayChanger::getAdapterName() {
	return m_adapterName;
}

char* GatewayChanger::getDescription() {
	return m_descName;
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
	return m_isMain—hannel;
}

bool GatewayChanger::pingGateway() {
	// Declare and initialize variables
	HANDLE hIcmpFile;
	unsigned long ipaddr = INADDR_NONE;
	DWORD dwRetVal = 0;
	DWORD dwError = 0;
	char SendData[] = "Data Buffer";
	LPVOID ReplyBuffer = NULL;
	DWORD ReplySize = 0;

	using namespace System::Runtime::InteropServices;
	switch (m_isMain—hannel)
	{
	case 1:
		ipaddr = inet_addr((const char*)(void*)Marshal::StringToHGlobalAnsi(m_ipOcan));
		break;
	case 2:
		ipaddr = inet_addr((const char*)(void*)Marshal::StringToHGlobalAnsi(m_ipRcan));
		break;
	default:
		ipaddr = inet_addr(m_gatewayCur->IpAddress.String);
		break;
	}

	//ipaddr = inet_addr(m_ip);
	if (ipaddr == INADDR_NONE) {
		printf("[error] INADDR_NONE\n");
		return false;
	}

	hIcmpFile = IcmpCreateFile();
	if (hIcmpFile == INVALID_HANDLE_VALUE) {
		printf("\tUnable to open handle.\n");
		printf("IcmpCreatefile returned error: %ld\n", GetLastError());

		return false;
	}

	// Allocate space for at a single reply
	ReplySize = sizeof (ICMP_ECHO_REPLY)+sizeof (SendData)+8;
	ReplyBuffer = (VOID *)malloc(ReplySize);
	if (ReplyBuffer == NULL) {
		printf("\tUnable to allocate memory for reply buffer\n");

		return false;
	}

	dwRetVal = IcmpSendEcho2(hIcmpFile, NULL, NULL, NULL,
		ipaddr, SendData, sizeof (SendData), NULL,
		ReplyBuffer, ReplySize, 1000);
	if (dwRetVal != 0) {
		PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
		struct in_addr ReplyAddr;
		ReplyAddr.S_un.S_addr = pEchoReply->Address;
		printf("\tSent icmp message to %s\n", m_gatewayCur->IpAddress.String);
		if (dwRetVal > 1) {
			printf("\tReceived %ld icmp message responses\n", dwRetVal);
			printf("\tInformation from the first response:\n");
		}
		else {
			printf("\tReceived %ld icmp message response\n", dwRetVal);
			printf("\tInformation from this response:\n");
		}
		printf("\t  Received from %s\n", inet_ntoa(ReplyAddr));
		printf("\t  Status = %ld  ", pEchoReply->Status);
		switch (pEchoReply->Status) {
		case IP_DEST_HOST_UNREACHABLE:
			printf("(Destination host was unreachable)\n");
			break;
		case IP_DEST_NET_UNREACHABLE:
			printf("(Destination Network was unreachable)\n");
			break;
		case IP_REQ_TIMED_OUT:
			printf("(Request timed out)\n");
			break;
		default:
			printf("\n");
			break;
		}

		printf("\t  Roundtrip time = %ld milliseconds\n",
			pEchoReply->RoundTripTime);
	}
	else {
		printf("Call to IcmpSendEcho2 failed.\n");
		dwError = GetLastError();
		switch (dwError) {
		case IP_BUF_TOO_SMALL:
			printf("\tReplyBufferSize to small\n");
			break;
		case IP_REQ_TIMED_OUT:
			printf("\tRequest timed out\n");
			break;
		default:
			printf("\tExtended error returned: %ld\n", dwError);
			break;
		}

		return false;
	}

	return true;
}

bool GatewayChanger::setMainGateway(System::String^ _mainIP) {
	using namespace System;
	using namespace System::Net;
	try
	{

		// Create an instance of IPAddress for the specified address string (in 
		// dotted-quad, or colon-hexadecimal notation).
		IPAddress^ address = IPAddress::Parse(_mainIP);

		m_ipOcan = _mainIP;
		return true;
	}
	catch (ArgumentNullException^ e)
	{
		//Console::WriteLine("ArgumentNullException caught!!!");
		//Console::WriteLine("Source : {0}", e->Source);
		//Console::WriteLine("Message : {0}", e->Message);
		System::String^ message = "ArgumentNullException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, "Œ¯Ë·Í‡ ¯Î˛Á‡!",
			System::Windows::Forms::MessageBoxButtons::OK, 
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
	catch (FormatException^ e)
	{
		//Console::WriteLine("FormatException caught!!!");
		//Console::WriteLine("Source : {0}", e->Source);
		//Console::WriteLine("Message : {0}", e->Message);
		System::String^ message = "FormatException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, "Œ¯Ë·Í‡ ¯Î˛Á‡!",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
	catch (Exception^ e)
	{
		//Console::WriteLine("Exception caught!!!");
		//Console::WriteLine("Source : {0}", e->Source);
		//Console::WriteLine("Message : {0}", e->Message);
		System::String^ message = "FormatException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, "Œ¯Ë·Í‡ ¯Î˛Á‡!",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}

	return true;
}

bool GatewayChanger::setReserveGateway(System::String^ _reserveIP) {
	using namespace System;
	using namespace System::Net;
	try
	{

		// Create an instance of IPAddress for the specified address string (in 
		// dotted-quad, or colon-hexadecimal notation).
		IPAddress^ address = IPAddress::Parse(_reserveIP);

		m_ipRcan = _reserveIP;
		return true;
	}
	catch (ArgumentNullException^ e)
	{
		//Console::WriteLine("ArgumentNullException caught!!!");
		//Console::WriteLine("Source : {0}", e->Source);
		//Console::WriteLine("Message : {0}", e->Message);
		System::String^ message = "ArgumentNullException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, "Œ¯Ë·Í‡ ¯Î˛Á‡!",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
	catch (FormatException^ e)
	{
		//Console::WriteLine("FormatException caught!!!");
		//Console::WriteLine("Source : {0}", e->Source);
		//Console::WriteLine("Message : {0}", e->Message);
		System::String^ message = "FormatException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, "Œ¯Ë·Í‡ ¯Î˛Á‡!",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
	catch (Exception^ e)
	{
		//Console::WriteLine("Exception caught!!!");
		//Console::WriteLine("Source : {0}", e->Source);
		//Console::WriteLine("Message : {0}", e->Message);
		System::String^ message = "FormatException caught!!!\n";
		message += "Source : " + e->Source + "\n";
		message += "Message : " + e->Message;
		System::Windows::Forms::MessageBox::Show(message, "Œ¯Ë·Í‡ ¯Î˛Á‡!",
			System::Windows::Forms::MessageBoxButtons::OK,
			System::Windows::Forms::MessageBoxIcon::Error);
		return false;
	}
	return true;
}

void GatewayChanger::saveXmlSettings() {
	xmlParse->GetElementsByTagName("main")->Item(0)->InnerText = m_ipOcan;
	xmlParse->GetElementsByTagName("reserve")->Item(0)->InnerText = m_ipRcan;
	xmlParse->Save("config.xml");
}

void GatewayChanger::checkingMainChannel() {
	System::String^ ipCur = gcnew System::String(m_gatewayCur->IpAddress.String);
	if (ipCur == m_ipOcan) {
		m_isMain—hannel = 1;
		return;
	}
	if (ipCur == m_ipRcan) {
		m_isMain—hannel = 2;
		return;
	}
	m_isMain—hannel = 0;
}

bool GatewayChanger::setNetworkCardGateway(int _channel) {
	using namespace System::Runtime::InteropServices;
	switch (_channel)
	{
	case 1:
		if (strcmp(m_gatewayCur->IpAddress.String, (const char*)(void*)Marshal::StringToHGlobalAnsi(m_ipOcan)) == 0) {
			return true;
		}
		break;
	case 2:
		if (strcmp(m_gatewayCur->IpAddress.String, (const char*)(void*)Marshal::StringToHGlobalAnsi(m_ipRcan)) == 0) {
			   return true;
		}
		break;
	default:
		return true;
		break;
	}
	
	HINSTANCE lib = (HINSTANCE)LoadLibrary(L"iphlpapi.dll");
	_SetAdapterIpAddress SetAdapterIpAddress = (_SetAdapterIpAddress)GetProcAddress(lib, "SetAdapterIpAddress");
	if (SetAdapterIpAddress == NULL)
	{
		printf("GetProcAddress for SetAdapterIpAddress Failed.\n");
		return false;
	}

	PWSTR pszGUID = NULL;
	char *szGUID;//(const char*)(void*)Marshal::StringToHGlobalAnsi(m_adapterName);
	szGUID = new char[260];
	strcpy(szGUID, m_adapterName);
	DWORD dwSize = 0;
	WideCharToMultiByte(CP_ACP, 0, pszGUID, -1, szGUID, sizeof(szGUID), NULL, NULL);
	
	m_isMain—hannel = _channel;
	switch (m_isMain—hannel)
	{
	case 1:
		SetAdapterIpAddress(szGUID,
			0,
			inet_addr(m_ipCurr->IpAddress.String),
			inet_addr(m_ipCurr->IpMask.String),
			inet_addr((const char*)(void*)Marshal::StringToHGlobalAnsi(m_ipOcan)));
		break;
	case 2:
		SetAdapterIpAddress(szGUID,
			0,
			inet_addr(m_ipCurr->IpAddress.String),
			inet_addr(m_ipCurr->IpMask.String),
			inet_addr((const char*)(void*)Marshal::StringToHGlobalAnsi(m_ipRcan)));
		break;
	default:
		delete[] szGUID;
		return false;
		break;
	}
	
	delete[] szGUID;
	return true;
}

bool GatewayChanger::setNetworkGateway(int _channel) {
	using namespace System::Runtime::InteropServices;
	System::String^ command;
	System::String^ netshInterfaceIp = "netsh interface ip ";
	System::String^ setAdr = "set address name=\"";
	System::String^ addAdr = "add address name=\"";
	System::String^ adapName = gcnew System::String(m_adapterName);
	System::String^ statAdr = " static ";
	System::String^ ipOk = gcnew System::String(m_ipCurr->IpAddress.String);
	System::String^ mask = gcnew System::String(m_ipCurr->IpMask.String);
	System::String^ ipRk;
	if (m_ipResCurr != NULL) ipRk = gcnew System::String(m_ipResCurr->IpAddress.String);
	System::String^ toLog = " > defgateway.log";

	System::String^ msg;

	m_isMain—hannel = _channel;
	switch (m_isMain—hannel)
	{
	case 1:
		msg = netshInterfaceIp + setAdr + /*(int)m_indexNetCard*/adapName + "\"" + statAdr + ipOk + " " + mask + " " + m_ipOcan;
		//system((const char*)(void*)Marshal::StringToHGlobalAnsi(msg));
		printf("System cmd: %s\n", msg);
		WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);
		msg = netshInterfaceIp + addAdr + /*(int)m_indexNetCard*/adapName + "\"" + " " + ipRk + " " + mask;
		//system((const char*)(void*)Marshal::StringToHGlobalAnsi(msg));
		printf("System cmd: %s\n", msg);
		WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);
		break;
	case 2:
		msg = netshInterfaceIp + setAdr + /*(int)m_indexNetCard*/adapName + "\"" + statAdr + ipOk + " " + mask + " " + m_ipRcan;
		//system((const char*)(void*)Marshal::StringToHGlobalAnsi(msg));
		printf("System cmd: %s\n", msg);
		WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);
		msg = netshInterfaceIp + addAdr + /*(int)m_indexNetCard*/adapName + "\"" + " " + ipRk + " " + mask;
		//system((const char*)(void*)Marshal::StringToHGlobalAnsi(msg));
		printf("System cmd: %s\n", msg);
		WinExec((const char*)(void*)Marshal::StringToHGlobalAnsi(msg), SW_HIDE);
		break;
	default:
		return false;
		break;
	}

	return true;
}