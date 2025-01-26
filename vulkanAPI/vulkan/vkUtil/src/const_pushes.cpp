#include "pch.h"
#include "const_pushes.h"


namespace vkUtil {

	PushConstRegistery::PushConstRegistery() = default;

	std::vector<vkType::PushConst> PushConstRegistery::_pushConsts;

	PushConstRegistery& PushConstRegistery::get_instance()
	{
		static PushConstRegistery instance;
		return instance;
	}

	void PushConstRegistery::add_push_const(const vkType::PushConst& pushConst)
	{
		_pushConsts.push_back(pushConst); 
	}

	std::vector<vkType::PushConst> PushConstRegistery::get_push_consts() const
	{
		return _pushConsts;
	}


	uint32_t evaluate_offset_push_const(const vkType::PushConst& item)
	{
		static uint32_t offset = 0;
		static uint32_t size = 0;

		offset += size;

		size = item._size;

		if (offset == 0)
		{
			return 0;
		}

		return offset;
	}

} // namespace vkUtil