#include "netvars.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "dt_recv.hpp"

std::unique_ptr<netvar> g_netvar;

netvar::netvar()
{
	const ClientClass* clientClass = interfaces::client_dll->get_all_classes();

	while (clientClass != nullptr)
	{
		const auto classInfo = std::make_shared<Node>(0);
		RecvTable* recvTable = clientClass->rtTable;

		this->PopulateNodes(recvTable, &classInfo->nodes);
		nodes.emplace(recvTable->GetName(), classInfo);

		clientClass = clientClass->pNextClass;
	}
}

void netvar::PopulateNodes(RecvTable* recvTable, MapType* mapType)
{
	for (auto i = 0; i < recvTable->GetNumProps(); i++)
	{
		const RecvProp* prop = recvTable->GetProp(i);
		const auto  propInfo = std::make_shared<Node>(prop->GetOffset());

		if (prop->GetType() == SendPropType::DPT_DataTable)
			this->PopulateNodes(prop->GetDataTable(), &propInfo->nodes);

		mapType->emplace(prop->GetName(), propInfo);
	}
}