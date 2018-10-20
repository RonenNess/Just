/*!
 * \file	Source\Files\Folders.h.
 *
 * \brief	Folders utilities.
 */
#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <algorithm>
#include "../Misc/StringConvert.h"

namespace Just
{
	namespace Files
	{
		/*!
		 * \fn	bool CreatePath(const std::string& path)
		 *
		 * \brief	Creates a path recursively.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 *
		 * \param	path		Full path to create.
		 * \param	fixSlashes	(Optional) If true will fix all slashes to forward and add a trailing slash if needed.
		 *
		 * \return	True if succeeds, false otherwise.
		 */
		bool CreatePath(const std::string& path, bool fixSlashes = true)
		{
			// wide-char path
			std::wstring wpath;

			// fix all slashes to be the right direction and convert path to wchar
			if (fixSlashes) 
			{ 
				auto tpath = std::string(path);
				std::replace(tpath.begin(), tpath.end(), '\\', '/');
				if (*(tpath.end() - 1) != '/') tpath += '/';
				wpath = Just::Misc::StringToWide(tpath);
			}
			// convert path to wchar without fixing slashes
			else
			{
				wpath = Just::Misc::StringToWide(path);
			}

			// temp buffers to hold parts
			wchar_t folder[MAX_PATH];
			wchar_t *end;
			ZeroMemory(folder, MAX_PATH * sizeof(wchar_t));

			// get end
			end = (wchar_t *)wcschr(wpath.c_str(), L'/');

			// create folders
			while (end != NULL)
			{
				wcsncpy_s(folder, wpath.c_str(), end - wpath.c_str() + 1);
				if (!CreateDirectory(folder, NULL))
				{
					DWORD err = GetLastError();
					if (err != ERROR_ALREADY_EXISTS)
					{
						return false;
					}
				}
				end = wcschr(++end, L'/');
			}

			// success
			return true;
		}
	}
}
#endif