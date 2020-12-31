#include "pch.h"
#include "Winsock_Client.h"

Winsock_Client::Winsock_Client()
{
	this->bdSecurityID.Init(0x31);
}

Winsock_Client::~Winsock_Client()
{
	::closesocket(this->m_Socket);
}

void Winsock_Client::doDTLSconnect(sockaddr_in* address)
{
	if (WSAController::WSAC0ntroller().IsValid() == false) { return; }
	this->m_Socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	this->m_ServerAddr.sin_addr = address->sin_addr;
	this->m_ServerAddr.sin_family = AF_INET;
	this->m_ServerAddr.sin_port = address->sin_port;

	DWORD timeout = 2 * 1000;
	setsockopt(this->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

	this->buffer_for_dtls.Flush();
	this->Send_Init();
	WCWOUT("Winsock_Client::doDTLSconnect: sent init");
	if (NO_ERROR != this->RecvFrom(this->buffer_for_dtls.Data(), this->buffer_for_dtls.Size())) { 
		return;
	}
	else
	{
		memcpy((char*)&this->initialACK, this->buffer_for_dtls.Data(), sizeof(this->initialACK));
		this->buffer_for_dtls.Flush();
		this->Send_CookieAck();
		WCWOUT("Winsock_Client::doDTLSconnect: sent cookieack");
		/* next steps are not released */
	}
}

void Winsock_Client::SetPlayerNetData(iw5mp_structs::playerNetData& ppp)
{
	WCWOUT("Winsock_Client::SetPlayerNetData()");
	this->playernetdata = ppp;

}

long Winsock_Client::SendTo(const char* buf, int len, int flags)
{
	int sendret = 0; // SOCKET_ERROR, etc ...
	sendret = ::sendto(this->m_Socket, buf, len, flags, reinterpret_cast<const ::SOCKADDR*>(&this->m_ServerAddr), sizeof(this->m_ServerAddr));
	if (sendret <= 0)
	{
		//wsaerror = ::WSAGetLastError();
		//std::cout << "error/socket/::sendto wsaerror: " << wsaerror << '\n';
		//switch (wsaerror)
		//{
		//case WSAETIMEDOUT:
		//case WSAEHOSTUNREACH:
		//case WSAECONNABORTED:
		//	return WSABASEERR - WSAECONNABORTED;
		//default:
		//	return WSABASEERR;
		//}
		WCWOUT("Winsock_Client::SendTo failed");
		return WSABASEERR;
	}
	return NO_ERROR;
}

long Winsock_Client::RecvFrom(char* buf, int len, int flags)
{
	this->m_recvbytes = 0;
	int wsaerror = 0;
	int recvret = 0; // SOCKET_ERROR, etc ...
	int fromlen = sizeof(this->m_ServerAddr);
	recvret = ::recvfrom(this->m_Socket, buf, len, flags, reinterpret_cast<::SOCKADDR*>(&this->m_ServerAddr), &fromlen);
	if (recvret > 0) {
		this->m_recvbytes = recvret;
	}
	else
	{
		wsaerror = ::WSAGetLastError();
		WCWOUT("this->RecvFrom failed", wsaerror);
		//std::cout << "error/socket/::recvfrom wsaerror: " << wsaerror << '\n';
		//switch (wsaerror)
		//{
		//case WSAETIMEDOUT:
		//case WSAEHOSTUNREACH:
		//case WSAECONNABORTED:
		//	return WSAECONNABORTED - WSABASEERR;
		//default:
		//	return WSABASEERR;
		//}
		return WSABASEERR;
	}
	return NO_ERROR;
}

void Winsock_Client::FlushStruct(char* dst, size_t sz)
{
	char crypt = RANDBYTE;
	for (size_t i = 0; i < sz; i++)
	{
		dst[i] = (dst[i] + 1) ^ crypt;
		crypt++;
	}
}


void Winsock_Client::Send_Init()
{
	iw5mp_structs::DTLS::InitPacket initial;
	initial.header_high = 0x01;
	initial.header_low = 0x02;
	initial.unknown = 0;
	initial.m_initTag = MAKEWORD(RANDBYTEH1, RANDBYTEH0);
	initial.bdSecurityID.Set(&(this->bdSecurityID));
	this->SendTo((char*)&initial, sizeof(iw5mp_structs::DTLS::InitPacket));
}

void Winsock_Client::Send_CookieAck()
{
	this->CookieAckPacket.header_high = 0x03;
	this->CookieAckPacket.header_low = 0x02;
	/* initack part */
	this->CookieAckPacket.initack = this->initialACK;
	this->initialACK.cookie.localTag = 0;
	this->CookieAckPacket.cookie = this->initialACK.cookie;
	this->FlushStruct((char*)&this->initialACK, sizeof(this->initialACK));
	/* netdata */
	this->CookieAckPacket.pND = this->playernetdata;
	/* bdsecurity */
	this->CookieAckPacket.bdSecurityID.Set(&this->bdSecurityID);
	/* ecckey */
	TomLibKeyGen::GetT0mLibKeyGen().ECC_GetExportKey(this->CookieAckPacket.ECCkey_exportkey, sizeof(this->CookieAckPacket.ECCkey_exportkey));

	this->SendTo((char*)&this->CookieAckPacket, sizeof(this->CookieAckPacket));
	this->FlushStruct((char*)&this->CookieAckPacket, sizeof(this->CookieAckPacket));
}


