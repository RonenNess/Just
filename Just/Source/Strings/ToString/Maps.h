/*!
* \file	Source\Strings\ToString\Maps.h.
*
* \brief	Convert maps to string.
*/
#pragma once
#include "Basics.h"

namespace Just
{
	namespace ToString
	{	
		/*!
		 * \fn	template <class T> std::string MapToString(const T& data, const std::string& equalSign = ":", const std::string& delimiter = ",")
		 *
		 * \brief	Convert unordered map to a string.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 *
		 * \tparam	T			Map type, must be iterable and have key - value pairs.
		 * \param	data		The unordered map to convert.
		 * \param	equalSign	(Optional) The equal sign to use.
		 * \param	delimiter	(Optional) The delimiter to use.
		 *
		 * \return	A std::string representing the dictionary with all its values.
		 */
		template <class T>
		std::string MapToString(const T& data, const std::string& equalSign = ":", const std::string& delimiter = ",")
		{
			std::ostringstream contentBuff;
			for (auto iter = data.begin(); iter != data.end(); ++iter)
			{
				contentBuff << ToString(iter->first) << equalSign << ToString(iter->second) << delimiter;
			}
			auto content = contentBuff.str();
			return content.substr(0, content.size() - 1);
		}
	}
}
