#include "headers.h"
#include "tools\include\const_push_registry.h"

namespace tools
{

	PushConstRegistery::PushConstRegistery() = default;

	PushConstRegistery& PushConstRegistery::get_instance()
	{
		static PushConstRegistery instance;
		return instance;
	}

	void PushConstRegistery::initalize(std::vector<vkType::PushConst>& pushConst)
	{
		_pushConsts = std::move(pushConst);
	}

	std::vector<vkType::PushConst> PushConstRegistery::get_push_consts() const
	{
		return _pushConsts;
	}
}