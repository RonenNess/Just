/*!
 * \file	Source\Files\Manage.h.
 *
 * \brief	Manage files utilities (delete, move, etc.).
 */
#pragma once

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

namespace Just
{
	namespace Files
	{
		/*!
		 * \fn	int RemoveFile(const std::string path)
		 *
		 * \brief	Removes the file described by path.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	path	Full path of the file.
		 *
		 * \return	If succeed (if failed, it error code will be set to errno).
		 */
		bool Remove(const std::string path)
		{
			return remove(path.c_str()) == 0;
		}

		/*!
		 * \fn	int Rename(const std::string from, const std::string to)
		 *
		 * \brief	Rename a file.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	from	Source file path.
		 * \param	to  	New file path.
		 *
		 * \return	If succeed (if failed, it error code will be set to errno).
		 */
		bool Rename(const std::string from, const std::string to)
		{
			return rename(from.c_str(), to.c_str()) == 0;
		}

		/*!
		 * \fn	inline bool Exists(const std::string& name)
		 *
		 * \brief	Determine if file exists
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	path	File path to check.
		 *
		 * \return	True if file exists, false otherwise.
		 */
		inline bool FileExists(const std::string& path) 
		{
			std::ifstream temp(path);
			bool ret = temp.good();
			temp.close();
			return ret;
		}

		/*!
		 * \fn	unsigned int SizeOf(const std::string& path)
		 *
		 * \brief	Size of the given file.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	path	Full path of the file.
		 *
		 * \return	File size or 0 if not found.
		 */
		unsigned int SizeOf(const std::string& path)
		{
			std::ifstream temp(path, std::ifstream::ate | std::ifstream::binary);
			if (!temp.good()) return 0;
			unsigned int ret = (unsigned int)temp.tellg();
			temp.close();
			return ret;
		}
	}
}