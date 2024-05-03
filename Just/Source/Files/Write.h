/*!
 * \file	Source\Files\Write.h.
 *
 * \brief	Writing-files utilities.
 */
#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace Just
{
	namespace Files
	{
		/*!
		 * \fn	void WriteText(std::string path, std::string text)
		 *
		 * \brief	Writes a text file.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	path	Full path of the file.
		 * \param	text	The text to write.
		 * \param	append	If true, will append data to file if already exists.
		 * \return	If succeed writing file.
		 */
		bool WriteText(const std::string& path, const std::string& text, bool append = false)
		{
			// open output file
			std::ofstream outfile;
			unsigned int mode = std::ios_base::out;
			if (append) { mode |= std::ios_base::app; }
			outfile.open(path, mode);

			// if failed return false
			if (outfile.fail())
			{
				return false;
			}

			// write and close file
			outfile << text.c_str();
			outfile.close();
			return true;
		}

		/*!
		 * \fn	void WriteBinary(const std::string& path, const char* data, size_t size)
		 *
		 * \brief	Writes a binary file.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	path	Full path of the file.
		 * \param	data	The data to write.
		 * \param	size	The data buffer size.
		 * \param	append	If true, will append data to file if already exists.
		 * \return	If succeed writing file.
		 */
		bool WriteBinary(const std::string& path, const char* data, size_t size, bool append = false)
		{
			// open output file
			std::ofstream outfile;
			unsigned int mode = std::ios::out | std::fstream::binary;
			if (append) { mode |= std::ios_base::app; }
			outfile.open(path, std::fstream::binary);

			// if failed return false
			if (outfile.fail())
			{
				return false;
			}

			// write and close file
			outfile.write(data, size);
			outfile.close();
			return true;
		}
	}
}