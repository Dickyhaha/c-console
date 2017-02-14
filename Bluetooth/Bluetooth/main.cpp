#include <winsock2.h>
#include <ws2bth.h>
#include <BluetoothAPIs.h>
#include <cstdlib>
#include <conio.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "irprops.lib")

using namespace std;

void setpos(int i, int j)
{
	COORD coor;
	coor.X = j;
	coor.Y = i;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}

int main()
{
	cout << "Initializing bluetooth" << endl;
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data))
	{
		cout << "Startup error: " << WSAGetLastError() << endl;
		_getch();
		WSACleanup();
		return 0;
	}

	WSAQUERYSET queryset;
	memset(&queryset, 0, sizeof(WSAQUERYSET));
	queryset.dwSize = sizeof(WSAQUERYSET);
	queryset.dwNameSpace = NS_BTH;

	HANDLE hLookup;
	if (WSALookupServiceBegin(&queryset, LUP_CONTAINERS, &hLookup))
	{
		cout << "Lookup error: " << WSAGetLastError() << endl;
		_getch();
		WSACleanup();
		return 0;
	}

	BYTE buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	DWORD bufferLength = sizeof(buffer);
	WSAQUERYSET *pResults = (WSAQUERYSET*)&buffer;
	if (WSALookupServiceNext(hLookup, LUP_RETURN_NAME | LUP_CONTAINERS | LUP_RETURN_ADDR | LUP_FLUSHCACHE | LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RES_SERVICE, &bufferLength, pResults))
	{
		cout << "Lookup error: " << WSAGetLastError() << endl;
		_getch();
		WSACleanup();
		return 0;
	}
	LPTSTR name = pResults->lpszServiceInstanceName;
	wcout << name << " found. Quering for services" << endl;
	WSAQUERYSET queryset2;
	memset(&queryset2, 0, sizeof(queryset2));
	queryset2.dwSize = sizeof(queryset2);
	queryset2.dwNameSpace = NS_BTH;
	queryset2.dwNumberOfCsAddrs = 0;
	CSADDR_INFO * addr = (CSADDR_INFO *)pResults->lpcsaBuffer;
	WCHAR addressAsString[1000];
	DWORD addressSize = sizeof(addressAsString);
	WSAAddressToString(addr->RemoteAddr.lpSockaddr, addr->RemoteAddr.iSockaddrLength, NULL, addressAsString, &addressSize);
	queryset2.lpszContext = addressAsString;
	GUID protocol = L2CAP_PROTOCOL_UUID;
	queryset2.lpServiceClassId = &protocol;
	HANDLE hLookup2;

	if (WSALookupServiceBegin(&queryset2, LUP_FLUSHCACHE | LUP_RETURN_NAME | LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RETURN_COMMENT, &hLookup2))
	{
		cout << "Disconncted";
		_getch();
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "Connected" << endl;
		//Start quering for device services
		BYTE buffer2[4096];
		memset(buffer2, 0, sizeof(buffer2));
		DWORD bufferLength2 = sizeof(buffer2);
		WSAQUERYSET *pResults2 = (WSAQUERYSET*)&buffer2;

		if (WSALookupServiceNext(hLookup2, LUP_FLUSHCACHE | LUP_RETURN_NAME | LUP_RETURN_TYPE | LUP_RETURN_ADDR | LUP_RETURN_BLOB | LUP_RETURN_COMMENT, &bufferLength2, pResults2))
		{
			cout << "Lookup next error: " << WSAGetLastError();
			_getch();
			WSACleanup();
			return 0;
		}

		cout << "Device Address: " << pResults2->lpcsaBuffer->RemoteAddr.lpSockaddr << endl;

		unsigned char* p;
		ULONGLONG ulladdr;
		p = (unsigned char*)pResults2->lpcsaBuffer->RemoteAddr.lpSockaddr;
		memcpy(&ulladdr, &p[2], 8);

		SOCKADDR_BTH addr;
		SOCKET s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
		memset(&addr, 0, sizeof(addr));
		addr.addressFamily = AF_BTH;
		addr.serviceClassId = RFCOMM_PROTOCOL_UUID;
		addr.port = BT_PORT_ANY;
		addr.btAddr = (BTH_ADDR)ulladdr;
		if (connect(s, (SOCKADDR*)&addr, sizeof(addr)))
		{
			cout << "Connect Error: " << WSAGetLastError() << endl;
			_getch();
			WSACleanup();
			return 0;
		}

		cout << "Press any key to start sending" << endl;
		_getch();

		int num;

		while (!_kbhit())
		{
			num = send(s, "a", 11, MSG_DONTROUTE);
			if (num==SOCKET_ERROR)
			{
				cout << "Send Error: " << WSAGetLastError();
				_getch();
				WSACleanup();
				return 0;
			}
			cout << "Characters sent: " << num << endl;
			Sleep(100);
		}
		cout << "Stopped" << endl;
	}
	_getch();
	_getch();
	WSACleanup();
	return 0;
}