#include "netvars.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "dt_recv.hpp"

std::unique_ptr<netvar> g_netvar;

netvar::netvar()
{
	const c_client_class* c_client_class = interfaces::client_dll->get_all_classes();

	while (c_client_class != nullptr)
	{
		const auto classInfo = std::make_shared<Node>(0);
		RecvTable* recvTable = c_client_class->rtTable;

		this->PopulateNodes(recvTable, &classInfo->nodes);
		nodes.emplace(recvTable->GetName(), classInfo);

		c_client_class = c_client_class->pNextClass;
	}
}

void netvar::PopulateNodes(RecvTable* recvTable, MapType* mapType)
{
	for (auto i = 0; i < recvTable->GetNumProps(); i++)
	{
		const RecvProp* prop = recvTable->GetProp(i);
		const auto  propInfo = std::make_shared<Node>(prop->get_offset());

		if (prop->GetType() == SendPropType::DPT_DataTable)
			this->PopulateNodes(prop->GetDataTable(), &propInfo->nodes);

		mapType->emplace(prop->GetName(), propInfo);
	}
}