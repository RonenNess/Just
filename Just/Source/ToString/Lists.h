/*!
* \file	Source\ToString\Lists.h.
*
* \brief	Convert iterable lists to string.
*/
#pragma once
#include "Basics.h"


namespace Just
{
	namespace ToString
	{
		/*!
		 * \fn	template <class T> std::string ListToString(const T& data, const std::string& delimiter = ",")
		 *
		 * \brief	Convert this object into a string representation.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 *
		 * \tparam	T	Generic type parameter, must be iterable (list, vector, etc.).
		 * \param	data	 	The data to convert to list.
		 * \param	delimiter	(Optional) Delimiter to put between values.
		 *
		 * \return	The given data converted to a std::string.
		 */
		template <class T>
		std::string ListToString(const T& data, const std::string& delimiter = ",")
		{
			std::ostringstream contentBuff;
			for (auto iter = data.begin(); iter != data.end(); ++iter)
			{
				contentBuff << ToString(*iter) << delimiter;
			}
			auto content = contentBuff.str();
			return content.substr(0, content.size() - 1);
		}
	}
}
