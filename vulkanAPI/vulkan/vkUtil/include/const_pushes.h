#pragma once

#include "config.h"


namespace vkUtil {

	class PushConstRegistery
	{
	public:

		static PushConstRegistery& get_instance();

		static void add_push_const(const vkType::PushConst& pushConst);// added before the invoking main function

		std::vector<vkType::PushConst> get_push_consts() const;

	private:
		static std::vector<vkType::PushConst> _pushConsts;
		PushConstRegistery();
	};

	uint32_t evaluate_offset_push_const(size_t size);



}