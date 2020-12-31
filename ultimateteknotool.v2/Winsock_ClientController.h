#pragma once
#include <memory>
#include <mutex>
#include "Winsock_Client.h"

class Winsock_ClientController
{
private:
	Winsock_ClientController();
	static std::once_flag m_createonceflag;
	static std::unique_ptr<Winsock_ClientController> m_pInstance;
	Winsock_ClientController(const Winsock_ClientController&) = delete;
	Winsock_ClientController(Winsock_ClientController&&) = delete;
	Winsock_ClientController& operator=(const Winsock_ClientController&) = delete;
	Winsock_ClientController& operator=(Winsock_ClientController&&) = delete;

	Winsock_Client* ptrClient = nullptr;
public:
	~Winsock_ClientController();
	static Winsock_ClientController& Winsock_ClientC0ntroller();
	Winsock_Client* GetClient();
};