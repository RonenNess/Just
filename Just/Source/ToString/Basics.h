/*!
* \file	Source\ToString\Basics.h.
*
* \brief	Used internally, convert some basic types to string.
*/
#pragma once
#include <string>

namespace Just
{
	namespace ToString
	{
		/*!
		* \fn	std::string ToString(const std::string& str)
		*
		* \brief	Convert this object into a string representation.
		* 			Note: this function is absolutely useless, its used as a trick to handle
		* 			unordered maps with strings when we try to serialize them.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \param	str	The string to convert.
		*
		* \return	A std::string that represents this object.
		*/
		inline std::string ToString(const std::string& str)
		{
			return str;
		}

		/*!
		* \fn	std::string ToString(const char* str)
		*
		* \brief	Convert this object into a string representation.
		* 			Note: this function is absolutely useless, its used as a trick to handle
		* 			unordered maps with strings when we try to serialize them.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \param	str	The string to convert.
		*
		* \return	A std::string that represents this object.
		*/
		inline std::string ToString(const char* str)
		{
			return std::string(str);
		}

		/*!
		* \fn	template <class T> inline std::string ToString(const T& str)
		*
		* \brief	Convert this object into a string representation.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \tparam	T	Generic type parameter.
		* \param	obj	The object to convert.
		*
		* \return	obj as an std::string.
		*/
		template <class T>
		inline std::string ToString(const T& obj)
		{
			return std::to_string(obj);
		}
	}
}
