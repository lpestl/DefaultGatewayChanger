#include <stdio.h>
//#include <Windows.h>
#include <WinSock2.h>
#include <iostream>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <stdlib.h>
#include <string.h>

using namespace System::Drawing;
using namespace System::Xml;

#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

typedef DWORD(WINAPI *_SetAdapterIpAddress)(char *szAdapterGUID,
	DWORD dwDHCP,
	DWORD dwIP,
	DWORD dwMask,
	DWORD dwGateway);

#pragma once
ref class GatewayChanger : System::Object
{
public:
	static GatewayChanger^ GetInstance();
	void ResetInstance();

	System::Drawing::Icon^ getTrueIco();
	System::Drawing::Icon^ getFalseIco();
	void selectNetCard();
	void getInterfaceNetInfo();
	IP_ADDR_STRING* getIpList();
	IP_ADDR_STRING* getIpListReserve();
	IP_ADDR_STRING* getGatewayList();
	char* getAdapterName();
	char* getDescription();
	bool getXmlSettings();
	System::String^ getMainGateway();
	System::String^ getReserveGateway();
	int isMainChannel();
	bool pingGateway();
	bool setMainGateway(System::String^ _mainIP);
	bool setReserveGateway(System::String^ _reserveIP);
	void saveXmlSettings();
	void checkingMainChannel();
	bool setNetworkCardGateway(int _channel);
	bool setNetworkGateway(int _channel);

protected:
	GatewayChanger();
	~GatewayChanger();

private:
	System::String^ defaultConfig();

	static GatewayChanger^ m_instanse;

	System::Drawing::Icon^ checkTrueIco;
	System::Drawing::Icon^ checkFalseIco;

	DWORD m_indexNetCard;
	char *m_adapterName;
	char *m_descName;
	// Mac adess
	UINT m_lenMac;
	BYTE *m_mac;
	// IP, mask, gateway
	IP_ADDR_STRING *m_ipCurr;
	IP_ADDR_STRING *m_ipResCurr;
	IP_ADDR_STRING *m_gatewayCur;
	XmlDocument^ xmlParse;

	System::String^ m_ipOcan;
	System::String^ m_ipRcan;

	int m_isMain—hannel;
};

