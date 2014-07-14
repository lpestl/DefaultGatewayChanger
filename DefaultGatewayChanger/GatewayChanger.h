#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>

using namespace System;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::NetworkInformation;
using namespace System::Collections::Generic;
using namespace System::Text;

#pragma once
ref class GatewayChanger : System::Object
{
public:
	static GatewayChanger^ GetInstance();
	void ResetInstance();

	System::Drawing::Icon^ getTrueIco();
	System::Drawing::Icon^ getFalseIco();
	bool getXmlSettings();
	System::String^ getMainGateway();
	System::String^ getReserveGateway();
	int isMainChannel();
	void saveXmlSettings();
	void choiceOfAdapter();
	List<System::String^>^ getIpAddresses();
	List<System::String^>^ getMaskIpAddresses();
	List<System::String^>^ getGateways();
	System::String^ getNameAdapter();
	System::String^ getMacAdapter();
	bool checkIpString(System::String^ _IpString);
	void setMainCanIpGateway(System::String^ _mainIp);
	void setReserveCanIpGateway(System::String^ _reserveIp);
	bool pingGateway();
	bool changeDefaultGateway(int _channel);

protected:
	GatewayChanger();
	~GatewayChanger();

private:
	System::String^ defaultConfig();

	static GatewayChanger^ m_instanse;

	System::Drawing::Icon^ checkTrueIco;
	System::Drawing::Icon^ checkFalseIco;
	XmlDocument^ xmlParse;

	// Net settings
	System::String^ m_hostName;
	System::String^ m_domainName;
	NetworkInterface^ m_adapter;
	List<System::String^>^ m_ip;
	List<System::String^>^ m_masks;
	List<System::String^>^ m_gateways;
	
	System::String^ m_ipOcan;
	System::String^ m_ipRcan;

	int m_isMain—hannel;
};

