#pragma once
#include "iw5mp_structs.h"
#include "Randomizer.h"
#include "debugconsole.h"
#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdint.h>
#pragma comment (lib, "Ws2_32.lib")
#include "TomLibKeyGen.h"
#include "WSAController.h"

/* only dynamic alloc */
class Winsock_Client
{
public:
	Winsock_Client();
	~Winsock_Client();
	void doDTLSconnect(sockaddr_in* address);
	void SetPlayerNetData(iw5mp_structs::playerNetData& playernetdata);
private:
	template<size_t SZ>
	class MemBuffer
	{
	private:
		char _mem[SZ] = { 0 };
	public:
		MemBuffer()
		{
			for (size_t i = 0; i < SZ; i++)
			{
				_mem[i] = 0;
			}
		}
		~MemBuffer() = default;
		void Flush()
		{
			for (size_t i = 0; i < SZ; i++)
			{
				_mem[i] = 0;
			}
		}
		char* Data() { return this->_mem; }
		size_t Size() const { return SZ; }
	};

	SOCKET m_Socket = { 0 };
	sockaddr_in m_ServerAddr = { 0 };
	MemBuffer<256> buffer_for_dtls;

	int m_recvbytes = 0x00;
	long SendTo(const char* buf, int len, int flags = 0);
	long RecvFrom(char* buf, int len, int flags = 0);
	void FlushStruct(char* dst, size_t sz);
	iw5mp_structs::bdSecurityKeyMap_bdSecurityID bdSecurityID;

	void Send_Init();
	iw5mp_structs::DTLS::InitAck initialACK = { 0 };
	iw5mp_structs::DTLS::CookieAckPacket CookieAckPacket = { 0 };
	iw5mp_structs::playerNetData playernetdata = { 0 };
	void Send_CookieAck();
};