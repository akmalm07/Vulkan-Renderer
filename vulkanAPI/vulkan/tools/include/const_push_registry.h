#pragma once

#include "config.h"


namespace tools {

	class PushConstRegistery
	{
	public:

		static PushConstRegistery& get_instance();

		void initalize(std::vector<vkType::PushConst>& pushConst);// added before the invoking main function

		std::vector<vkType::PushConst> get_push_consts() const;

	private:
		std::vector<vkType::PushConst> _pushConsts;
		PushConstRegistery();
	};

}