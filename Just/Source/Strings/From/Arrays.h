/*!
* \file	Source\Strings\ToString\Arrays.h.
*
* \brief	Convert arrays to string.
*/
#pragma once
#include "Basics.h"


namespace Just
{
	namespace String
	{
		/*!
		* \fn	template <class T> std::string ParseArray(const T& data, const std::string& delimiter = ",")
		*
		* \brief	Convert this object into a string representation.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \tparam	T	Generic type parameter, must be iterable (list, vector, etc.).
		* \param	data	 	The data to convert to list.
		* \param	arrSize		How many items in array.
		* \param	delimiter	(Optional) Delimiter to put between values.
		*
		* \return	The given data converted to a std::string.
		*/
		template <class T>
		std::string ParseArray(const T* data, int arrSize, const std::string& delimiter = ",")
		{
			std::ostringstream contentBuff;
			for (int i = 0; i < arrSize; ++i)
			{
				contentBuff << ParseType(data[i]);
				if (i < arrSize - 1) contentBuff << delimiter;
			}
			return contentBuff.str();
		}
		
	}
}
