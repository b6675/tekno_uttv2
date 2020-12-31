#include "pch.h"
#include "Winsock_ClientController.h"
 std::once_flag Winsock_ClientController::m_createonceflag;
 std::unique_ptr<Winsock_ClientController> Winsock_ClientController::m_pInstance;

 Winsock_ClientController::Winsock_ClientController()
 {
     this->ptrClient = nullptr;
 }

Winsock_ClientController::~Winsock_ClientController()
{
    if (this->ptrClient != nullptr)
    {
        delete this->ptrClient;
    }
}

Winsock_ClientController& Winsock_ClientController::Winsock_ClientC0ntroller()
{
	std::call_once(Winsock_ClientController::m_createonceflag, [] {
		Winsock_ClientController::m_pInstance.reset(new Winsock_ClientController);
		});
	return *Winsock_ClientController::m_pInstance.get();
}

Winsock_Client* Winsock_ClientController::GetClient()
{
    if (this->ptrClient == nullptr)
    {
        this->ptrClient = new Winsock_Client();
    }
    return this->ptrClient;
}
