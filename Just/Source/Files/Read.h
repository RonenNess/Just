/*!
 * \file	Source\Files\Read.h.
 *
 * \brief	Reading-files utilities.
 */
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Just
{
	namespace Files
	{
		/*!
		 * \fn	std::string ReadText(const std::string& path, const std::string& text)
		 *
		 * \brief	Reads a whole text file.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	path	Full path of the file.
		 * \param	out		String that will contain the text read from file.
		 *
		 * \return	True if successfully read the file.
		 */
		bool ReadText(const std::string& path, std::string& out)
		{
			// open file
			std::ifstream infile;
			infile.open(path);

			// if failed return empty string
			if (infile.fail())
			{
				return false;
			}

			// read and return file content
			out = std::string((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
			infile.close();
			return true;
		}

		/*!
		 * \fn	std::vector<char> ReadBinary(const std::string& path, const char* data, size_t size)
		 *
		 * \brief	Reads a whole binary file.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	path	Full path of the file.
		 * \param	out		Out read buffer.
		 *
		 * \return	True if successfully read the file.
		 */
		bool ReadBinary(const std::string& path, std::vector<char>& out)
		{
			// open file
			std::ifstream infile;
			infile.open(path, std::ios::binary | std::ios::ate);

			// if failed to open return empty vector
			if (infile.fail())
			{
				return false;
			}

			// read data and return buffer on success
			std::streamsize size = infile.tellg();
			infile.seekg(0, std::ios::beg);
			out = std::vector<char>((int)size);
			if (infile.read(out.data(), size))
			{
				infile.close();
				return true;
			}

			// return empty vector if failed
			infile.close();
			return false;
		}
	}
}