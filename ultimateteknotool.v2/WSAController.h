#pragma once
#include <windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdint.h>
#include <memory>
#include <mutex>
#pragma comment (lib, "Ws2_32.lib")

class WSAController
{
private:
	WSAController();
	static std::once_flag m_createonceflag;
	static std::unique_ptr<WSAController> m_pInstance;
	WSAController(const WSAController&) = delete;
	WSAController(WSAController&&) = delete;
	WSAController& operator=(const WSAController&) = delete;
	WSAController& operator=(WSAController&&) = delete;
	static WSADATA wsa_data;
	static bool isValid;
public:
	~WSAController();
	static WSAController& WSAC0ntroller();
	bool IsValid();
};

