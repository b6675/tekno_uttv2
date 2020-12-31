#include "pch.h"
#include "WSAController.h"
std::once_flag WSAController::m_createonceflag;
std::unique_ptr<WSAController> WSAController::m_pInstance;
WSADATA WSAController::wsa_data;
bool WSAController::isValid;

WSAController::WSAController()
{
	this->isValid = false;
	this->wsa_data.wVersion = 0;
	int error = 0;
	error = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (error)
	{
		this->isValid = false;
	}
	else
	{
		if (LOBYTE(this->wsa_data.wVersion) != 2 || HIBYTE(this->wsa_data.wVersion) != 2)
		{
			this->isValid = false;
		}
		this->isValid = true;
	}
}

WSAController::~WSAController()
{
    if (LOBYTE(this->wsa_data.wVersion) != 2 || HIBYTE(this->wsa_data.wVersion) != 2) {
        ::WSACleanup();
    }
}

WSAController& WSAController::WSAC0ntroller()
{
	std::call_once(WSAController::m_createonceflag, [] {
		WSAController::m_pInstance.reset(new WSAController);
		});
	return *WSAController::m_pInstance.get();
}

bool WSAController::IsValid()
{
	return this->isValid;
}
