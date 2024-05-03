/*!
* \file	Source\Strings\To\Wide.h.
*
* \brief	Converting string to different types.
*/
#pragma once
#ifdef _WIN32
#include <string>
#include <windows.h>

namespace Just
{
	namespace String
	{
		namespace To
		{
			/*!
			 * \fn	std::wstring ToWide(const std::string& s)
			 *
			 * \brief	Convert string to wide string.
			 *
			 * \author	Ronen Ness
			 * \date	10/19/2018
			 *
			 * \param	s	A std::string to process.
			 *
			 * \return	A std::wstring.
			 */
			std::wstring Wide(const std::string& s)
			{
				int len;
				int slength = (int)s.length() + 1;
				len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
				wchar_t* buf = new wchar_t[len];
				MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
				auto ret = std::wstring(buf);
				delete[] buf;
				return ret;
			}
		}
	}
}
#endif