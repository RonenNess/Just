#pragma once



// ::Strings\From\Basics.h::

/*!
* \file	Source\Strings\From\Basics.h.
*
* \brief	Used internally, convert some basic types to string.
*/
// #pragma once
#include <string>

namespace Just
{
	namespace String
	{
		namespace From
		{
			/*!
			* \fn	std::string CStr(const char* str)
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
			inline std::string CStr(const char* str)
			{
				return std::string(str);
			}

			/*!
			* \fn	template <class T> inline std::string Any(const T& str)
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
			inline std::string Any(const T& obj)
			{
				std::ostringstream outstream;
				outstream << obj;
				return outstream.str();
			}
		}
	}
}




// ::Strings\From\Arrays.h::

/*!
* \file	Source\Strings\From\Arrays.h.
*
* \brief	Convert arrays to string.
*/
// #pragma once
#include <string>
#include <sstream>
// #include "Basics.h"


namespace Just
{
	namespace String
	{
		namespace From
		{
			/*!
			* \fn	template <class T> std::string Array(const T& data, const std::string& delimiter = ",")
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
			std::string Array(const T* data, int arrSize, const std::string& delimiter = ",")
			{
				std::ostringstream contentBuff;
				for (int i = 0; i < arrSize; ++i)
				{
					contentBuff << Any(data[i]);
					if (i < arrSize - 1) { contentBuff << delimiter; }
				}
				return contentBuff.str();
			}
		}
	}
}




// ::Strings\From\Iterable.h::

/*!
* \file	Source\Strings\From\Iterable.h.
*
* \brief	Convert iterable lists to string.
*/
// #pragma once
#include <string>
// #include "Basics.h"


namespace Just
{
	namespace String
	{
		namespace From
		{
			/*!
			* \fn	template <class T> std::string Iterable(const T& data, const std::string& delimiter = ",")
			*
			* \brief	Convert iterable object into a string representation.
			*
			* \author	Ronen Ness
			* \date	10/19/2018
			*
			* \tparam	T			Generic type parameter, must be iterable (list, vector, etc.).
			* \param	data	 	The data to convert to list.
			* \param	delimiter	(Optional) Delimiter to put between values.
			*
			* \return	The given data converted to a std::string.
			*/
			template <class T>
			std::string Iterable(const T& data, const std::string& delimiter = ",")
			{
				std::ostringstream contentBuff;
				for (auto iter = data.begin(); iter != data.end(); ++iter)
				{
					contentBuff << Any(*iter) << delimiter;
				}
				auto content = contentBuff.str();
				return content.substr(0, content.size() - 1);
			}
		}
	}
}




// ::Strings\From\Maps.h::

/*!
* \file	Source\Strings\From\Maps.h.
*
* \brief	Convert maps to string.
*/
// #pragma once
#include <string>
// #include "Basics.h"

namespace Just
{
	namespace String
	{
		namespace From
		{
			/*!
			* \fn	template <class T> std::string Map(const T& data, const std::string& equalSign = ":", const std::string& delimiter = ",")
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
			std::string Map(const T& data, const std::string& equalSign = ":", const std::string& delimiter = ",")
			{
				std::ostringstream contentBuff;
				for (auto iter = data.begin(); iter != data.end(); ++iter)
				{
					contentBuff << iter->first << equalSign << iter->second << delimiter;
				}
				auto content = contentBuff.str();
				return content.substr(0, content.size() - 1);
			}
		}
	}
}




// ::Strings\To\LPWSTR.h::

/*!
* \file	Source\Strings\To\LPWSTR.h.
*
* \brief	Converting string to different types.
*/
// #pragma once
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
			* \fn	void LpcwStr(const std::string& s)
			*
			* \brief	Convert String to LPCWSTR.
			*
			* \author	Ronen Ness
			* \date	10/19/2018
			*
			* \param	s	A std::string to process.
			* \param	out	Out LPCWSTR string. Must be deleted via delete[]!!!
			*/
			void LpcwStr(const std::string& s, LPCWSTR& out)
			{
				int len;
				int slength = (int)s.length() + 1;
				len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
				wchar_t* buf = new wchar_t[len];
				MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
				out = LPCWSTR(buf);
			}

			/*!
			* \fn	void LpwStr(const std::string& s)
			*
			* \brief	Convert String to LPCWSTR.
			*
			* \author	Ronen Ness
			* \date	10/19/2018
			*
			* \param	s	A std::string to process.
			* \param	out	Out LPWSTR string. Must be deleted via delete[]!!!
			*/
			void LpwStr(const std::string& s, LPWSTR& out)
			{
				int len;
				int slength = (int)s.length() + 1;
				len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
				wchar_t* buf = new wchar_t[len];
				MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
				out = LPWSTR(buf);
			}
		}
	}
}
#endif



// ::Strings\To\Wide.h::

/*!
* \file	Source\Strings\To\Wide.h.
*
* \brief	Converting string to different types.
*/
// #pragma once
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



// ::Files\Folders.h::

/*!
 * \file	Source\Files\Folders.h.
 *
 * \brief	Folders utilities.
 */
// #pragma once
#ifdef _WIN32
#include <Windows.h>
#include <algorithm>
// #include "../Strings/To/All.h"

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
				wpath = Just::String::To::Wide(tpath);
			}
			// convert path to wchar without fixing slashes
			else
			{
				wpath = Just::String::To::Wide(path);
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



// ::Files\Manage.h::

/*!
 * \file	Source\Files\Manage.h.
 *
 * \brief	Manage files utilities (delete, move, etc.).
 */
// #pragma once

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
		inline bool Exists(const std::string& path) 
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



// ::Files\Read.h::

/*!
 * \file	Source\Files\Read.h.
 *
 * \brief	Reading-files utilities.
 */
// #pragma once

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



// ::Files\Write.h::

/*!
 * \file	Source\Files\Write.h.
 *
 * \brief	Writing-files utilities.
 */
// #pragma once

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



// ::Execute\Command.h::

/*!
 * \file	Source\Execute\Command.h.
 *
 * \brief	Execute exe files.
 */
// #pragma once

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <cassert>

namespace Just
{
	namespace Execute
	{
		/*!
		 * \struct	ProcessOutput
		 *
		 * \brief	Executed processes output.
		 *
		 * \author	Ronen Ness
		 * \date	10/20/2018
		 */
		struct ProcessOutput
		{
			// output text
			std::string Output;

			// return code from process
			int ReturnCode = -1;

			// did process finish executing
			bool DidFinish = false;

			// return if executed successfully and was a success
			inline bool IsSuccess() const { return DidFinish && ReturnCode == 0; }
		};

		/*!
		 * \fn	ProcessOutput Command(const std::string& command)
		 *
		 * \brief	Executes a command.
		 *
		 * \author	Ronen Ness
		 * \date	10/20/2018
		 *
		 * \param	command	The command to execute.
		 *
		 * \return	A ProcessOutput.
		 */
		ProcessOutput Command(const std::string& command)
		{
			ProcessOutput ret;
			char   psBuffer[128];
			FILE   *pPipe;

			// run the command
			if ((pPipe = _popen(command.c_str(), "rt")) == NULL)
			{
				return ret;
			}

			// read output
			while (fgets(psBuffer, 128, pPipe))
			{
				ret.Output += psBuffer;
			}

			// close pipe and print return value of pPipe.
			if (feof(pPipe))
			{
				ret.ReturnCode = _pclose(pPipe);
				ret.DidFinish = true;
			}

			// return data on execution
			return ret;
		}
	}
}
#endif



// ::Execute\Scripts.h::

/*!
 * \file	Source\Execute\Scripts.h.
 *
 * \brief	Execute different scripts.
 */
// #pragma once

#ifdef _WIN32
// #include "Command.h"

namespace Just
{
	namespace Execute
	{
		/*!
		 * \fn	ProcessOutput Script(const std::string& scriptType, const std::string& scriptPath, const std::string& params = std::string())
		 *
		 * \brief	Executes the script operation
		 *
		 * \author	Ronen Ness
		 * \date	10/20/2018
		 *
		 * \param	scriptType	Type of the script (python / ruby / perl / ...).
		 * \param	scriptPath	Full path of the script file to execute.
		 * \param	params	  	(Optional) Script params.
		 *
		 * \return	A ProcessOutput.
		 */
		ProcessOutput Script(const std::string& scriptType, const std::string& scriptPath, const std::string& params = std::string())
		{
			return Command(scriptType + " \"" + scriptPath + "\" " + params);
		}

		/*!
		 * \fn	ProcessOutput PythonScript(const std::string& scriptPath, const std::string& params = std::string())
		 *
		 * \brief	Executes Python script.
		 *
		 * \author	Ronen Ness
		 * \date	10/20/2018
		 *
		 * \param	scriptPath	Full path of the script file to execute.
		 * \param	params	  	(Optional) Params to pass to script.
		 *
		 * \return	A ProcessOutput.
		 */
		ProcessOutput PythonScript(const std::string& scriptPath, const std::string& params = std::string())
		{
			static std::string type = "python";
			return Script(type, scriptPath, params);
		}

		/*!
		* \fn	ProcessOutput PerlScript(const std::string& scriptPath, const std::string& params = std::string())
		*
		* \brief	Executes Perl script.
		*
		* \author	Ronen Ness
		* \date	10/20/2018
		*
		* \param	scriptPath	Full path of the script file to execute.
		* \param	params	  	(Optional) Params to pass to script.
		*
		* \return	A ProcessOutput.
		*/
		ProcessOutput PerlScript(const std::string& scriptPath, const std::string& params = std::string())
		{
			static std::string type = "perl";
			return Script(type, scriptPath, params);
		}

		/*!
		* \fn	ProcessOutput RubyScript(const std::string& scriptPath, const std::string& params = std::string())
		*
		* \brief	Executes Ruby script.
		*
		* \author	Ronen Ness
		* \date	10/20/2018
		*
		* \param	scriptPath	Full path of the script file to execute.
		* \param	params	  	(Optional) Params to pass to script.
		*
		* \return	A ProcessOutput.
		*/
		ProcessOutput RubyScript(const std::string& scriptPath, const std::string& params = std::string())
		{
			static std::string type = "ruby";
			return Script(type, scriptPath, params);
		}
	}
}
#endif



// ::Http\HttpRequests.h::

/*!
* \file	Source\Http\HttpRequests.h.
*
* \brief	Send HTTP requests.
*/
// #pragma once

#ifdef _WIN32

#include <string.h>
#include <windows.h>
#include <sstream>
#include <unordered_map>
#include <winhttp.h>
// #include "../Strings/To/All.h"
// #include "../Strings/From/Maps.h"

#pragma comment(lib, "winhttp.lib")

namespace Just
{
	namespace Http
	{
		/*!
		 * \enum	HttpConnectionErrors
		 *
		 * \brief	Values that represent HTTP connection errors.
		 */
		enum HttpConnectionErrors
		{
			NoError,
			FailedToConnect,
			FailedToOpenSession,
			FailedToOpenRequest,
			FailedToSendRequest,
			FailedToReceiveResponse,
			NoHttpDataAvailable,
			FailedToReadHttpData,
			ResponseError,
		};

		/*!
		 * \struct	HttpResponse
		 *
		 * \brief	An HTTP response.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 */
		struct HttpResponse
		{
		public:
			// returned text
			std::string Text;

			// how many bytes we read in total from response
			unsigned int TotalBytesRead = 0;

			// return if response was OK.
			inline bool good() const { return Error == NoError; }

			// error types we can get
			HttpConnectionErrors Error = NoError;

			// error code / details (or 0 if no errors).
			// not: this is not HTTP error codes you could get from server, its from errors you get from OS.
			DWORD ErrorCode = 0;
		};

		// useragent string
		std::string _useragent = "JUST Program/1.0";

		// To automatically release handles when out of scope.
		class __HandlesReleaser
		{
			HINTERNET _handle;
		public:
			__HandlesReleaser(HINTERNET handle)
			{
				_handle = handle;
			}
			virtual ~__HandlesReleaser()
			{
				WinHttpCloseHandle(_handle);
			}
		};

		/*!
		 * \fn	void SetUserAgent(const std::string& ua)
		 *
		 * \brief	Sets useragent for all HTTP requests.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 *
		 * \param	ua	New useragent text.
		 */
		void SetUserAgent(const std::string& ua)
		{
			_useragent = ua;
		}

		/*!
		 * \fn	HttpResponse Send(std::string url, int port = 80)
		 *
		 * \brief	Send an Http request.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 *
		 * \param	host 				Host to send request to.
		 * \param	method				Request type (GET / POST / PUT /...)
		 * \param	action				Url under host for request.
		 * \param	content				(Optional) Content to send.
		 * \param	additionalHeaders	(Optional) Additional headers.
		 * \param	port				(Optional) Port to connect to.
		 *
		 * \return	A HttpResponse.
		 */
		HttpResponse Send(const std::string& host, 
			const std::string& method = "GET",
			const std::string& action = "/", 
			const std::string& content = std::string(), 
			const std::string& additionalHeaders = std::string(),
			USHORT port = INTERNET_DEFAULT_HTTP_PORT)
		{
			// internal macro to stop and return in case of errors
			#define __ReturnHttpErrorIfFailed(condition, ErrType) \
			if (!condition) { \
				ret.Error = ErrType; \
				ret.ErrorCode = GetLastError(); \
				return ret; }

			// return value
			HttpResponse ret;

			// some params
			BOOL  bResults = FALSE;
			HINTERNET hSession = NULL,
				hConnect = NULL,
				hRequest = NULL;

			// use WinHttpOpen to obtain a session handle.
			LPCWSTR useragent; Just::String::To::LpcwStr(_useragent, useragent);
			hSession = WinHttpOpen(useragent,
				WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
				WINHTTP_NO_PROXY_NAME,
				WINHTTP_NO_PROXY_BYPASS, 
				0);
			delete[] useragent;
			__ReturnHttpErrorIfFailed(hSession, FailedToOpenSession);

			// to make sure session is cleared
			__HandlesReleaser hSessionR(hSession);

			// specify an HTTP server.
			LPCWSTR lphost; Just::String::To::LpcwStr(host, lphost);
			hConnect = WinHttpConnect(hSession, lphost, port, 0);
			delete[] lphost;
			__ReturnHttpErrorIfFailed(hConnect, FailedToConnect);

			// to make sure connection is cleared
			__HandlesReleaser hConnectR(hConnect);

			// create an HTTP Request handle.
			LPCWSTR wmethod; Just::String::To::LpcwStr(method, wmethod);
			LPCWSTR waction; Just::String::To::LpcwStr(action, waction);
			hRequest = WinHttpOpenRequest(hConnect,
				wmethod,
				waction,
				NULL, 
				WINHTTP_NO_REFERER,
				WINHTTP_DEFAULT_ACCEPT_TYPES,
				0);
			delete[] wmethod;
			delete[] waction;
			__ReturnHttpErrorIfFailed(hRequest, FailedToOpenRequest);

			// to make sure request is cleared
			__HandlesReleaser hRequestR(hRequest);

			// set additional headers
			LPCWSTR headers = WINHTTP_NO_ADDITIONAL_HEADERS;
			if (additionalHeaders.size()) Just::String::To::LpcwStr(additionalHeaders, headers);

			// set content
			LPCWSTR contentBuff = WINHTTP_NO_REQUEST_DATA;
			if (content.size()) Just::String::To::LpcwStr(content, contentBuff);

			// send the Request.
			bResults = WinHttpSendRequest(hRequest,
				headers,
				(DWORD)additionalHeaders.length(),
				&contentBuff,
				(DWORD)content.length(),
				(DWORD)content.length(),
				(DWORD)0);
			if (headers) delete[] headers;
			if (contentBuff) delete[] contentBuff;
			__ReturnHttpErrorIfFailed(bResults, FailedToSendRequest);

			// wait to recieve response
			bResults = WinHttpReceiveResponse(hRequest, NULL);
			__ReturnHttpErrorIfFailed(bResults, FailedToReceiveResponse);

			// read actual data from response
			DWORD dwSize = 0;
			DWORD dwDownloaded = 0;
			do
			{
				// get how much data we have to read
				dwSize = 0;
				bResults = WinHttpQueryDataAvailable(hRequest, &dwSize);
				__ReturnHttpErrorIfFailed(bResults, NoHttpDataAvailable);

				// allocate space for the buffer.
				char* pszOutBuffer = new char[dwSize + 1];
				
				// read the Data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				bResults = WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded);
				if (!bResults) { delete[] pszOutBuffer; }
				__ReturnHttpErrorIfFailed(bResults, FailedToReadHttpData);

				// add to response
				ret.Text += pszOutBuffer;
				ret.TotalBytesRead += dwSize;

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;

			} while (dwSize > 0);

			// return response
			return ret;
		}

		/*!
		* \fn	HttpResponse Send(std::string url, int port = 80)
		*
		* \brief	Send an Http request.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \param	url 				Full url to send request to.
		* \param	method				Request type (GET / POST / PUT /...)
		* \param	content				(Optional) Content to send.
		* \param	additionalHeaders	(Optional) Additional headers.
		* \param	port				(Optional) Port to connect to.
		*
		* \return	A HttpResponse.
		*/
		HttpResponse Send(const std::string& url,
			const std::string& method = "GET",
			const std::string& content = std::string(),
			const std::unordered_map<std::string, std::string>& additionalHeaders = std::unordered_map<std::string, std::string>(),
			USHORT port = 80)
		{
			// split host and and action parts.
			// first check if URL contains "http:", then we find the first / that is not part of the http:// part and split based on it.
			bool gotHttp = url.substr(0, 5).find("http:") == 0;
			auto hostEnd = url.find('/', gotHttp ? strlen("http://")+1 : 0);
			auto host = hostEnd == std::string::npos ? url : url.substr(0, hostEnd);
			auto action = hostEnd == std::string::npos ? "/" : url.substr(hostEnd);
			
			// if host contains /, for example from http://, remove it.
			auto hostStart = host.rfind("/");
			if (hostStart != std::string::npos) { host = host.substr(hostStart + 1); }

			// convert headers to string
			auto headers = Just::String::From::Map(additionalHeaders, ":", "\n");

			// send http request
			return Send(host, method, action, content, headers, port);
		}

		/*!
		 * \fn	HttpResponse SendForm(const std::string& url, const std::string& type = "POST", const std::unordered_map<std::string, std::string> data = std::unordered_map<std::string, std::string>(), USHORT port = 80)
		 *
		 * \brief	Sends an HTTP form.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 *
		 * \param	url		  	URL of the document.
		 * \param	method	  	(Optional) The method of HTTP request.
		 * \param	data	  	(Optional) The form data to send.
		 * \param	port	  	(Optional) Port to connect to.
		 *
		 * \return	A HttpResponse.
		 */
		HttpResponse SendForm(const std::string& url,
			const std::string& method = "POST",
			const std::unordered_map<std::string, std::string> data = std::unordered_map<std::string, std::string>(),
			USHORT port = 80)
		{
			auto headers = std::unordered_map<std::string, std::string>();
			headers["Content-Type"] = "application/x-www-form-urlencoded";
			auto content = Just::String::From::Map(data, "=", "&");
			return Send(url, method, content, headers, port);
		}

		/*!
		 * \fn	HttpResponse Get(const std::string& url, const std::unordered_map<std::string, std::string> additionalHeaders = std::unordered_map<std::string, std::string>(), USHORT port = 80)
		 *
		 * \brief	Send HTTP GET request.
		 *
		 * \author	Ronen Ness
		 * \date	10/19/2018
		 *
		 * \param	url				 	URL of the document.
		 * \param	port			 	(Optional) Port to connect to.
		 *
		 * \return	A HttpResponse.
		 */
		HttpResponse Get(const std::string& url, USHORT port = 80)
		{
			static std::string method = "GET";
			static std::unordered_map<std::string, std::string> headers;
			return Send(url, method, std::string(), headers, port);
		}

		/*!
		* \fn	HttpResponse Post(const std::string& url, const std::unordered_map<std::string, std::string> additionalHeaders = std::unordered_map<std::string, std::string>(), USHORT port = 80)
		*
		* \brief	Send HTTP POST request.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \param	url				 	URL of the document.
		* \param	data				(Optional) Data to send with request.
		* \param	port			 	(Optional) Port to connect to.
		*
		* \return	A HttpResponse.
		*/
		HttpResponse Post(const std::string& url,
			const std::unordered_map<std::string, std::string> data = std::unordered_map<std::string, std::string>(),
			USHORT port = 80)
		{
			static std::string method = "POST";
			return SendForm(url, method, data, port);
		}

		/*!
		* \fn	HttpResponse Put(const std::string& url, const std::unordered_map<std::string, std::string> additionalHeaders = std::unordered_map<std::string, std::string>(), USHORT port = 80)
		*
		* \brief	Send HTTP PUT request.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \param	url				 	URL of the document.
		* \param	data				(Optional) Data to send with request.
		* \param	port			 	(Optional) Port to connect to.
		*
		* \return	A HttpResponse.
		*/
		HttpResponse Put(const std::string& url,
			const std::unordered_map<std::string, std::string> data = std::unordered_map<std::string, std::string>(),
			USHORT port = 80)
		{
			static std::string method = "PUT";
			return SendForm(url, method, data, port);
		}

		/*!
		* \fn	HttpResponse Delete(const std::string& url, const std::unordered_map<std::string, std::string> additionalHeaders = std::unordered_map<std::string, std::string>(), USHORT port = 80)
		*
		* \brief	Send HTTP DELETE request.
		*
		* \author	Ronen Ness
		* \date	10/19/2018
		*
		* \param	url				 	URL of the document.
		* \param	port			 	(Optional) Port to connect to.
		*
		* \return	A HttpResponse.
		*/
		HttpResponse Delete(const std::string& url, USHORT port = 80)
		{
			static std::string method = "DELETE";
			return Send(url, method, std::string(), std::unordered_map<std::string, std::string>(), port = port);
		}
	}
}
#endif



// ::SharedMemory\SharedMemory.h::

/*!
* \file	Source\SharedMemory\SharedMemory.h.
*
* \brief	Creating and using Shared Memory between processes.
*/
// #pragma once
#ifdef _WIN32
#include <string>
#include <windows.h>
// #include "../Strings/To/All.h"

namespace Just
{
	namespace SharedMemory
	{
		/**
		* Manage a shared memory connection.
		*/
		class Client
		{
		private:

			// file handle
			HANDLE _MapFile;

			// buffer
			LPCTSTR _Buffer;

			// shared memory size
			int _BufferSize;

		public:

			/**
			* Constructor.
			*/
			Client() : _MapFile(NULL), _Buffer(NULL), _BufferSize(0) {}

			/**
			* Destructor.
			*/
			~Client()
			{
				Close();
			}

			/*!
			* \fn	bool CreateNew(const std::string& path, int bufferSize)
			*
			* \brief	Create a new shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	path 				Shared memory file path.
			* \param	bufferSize			Shared memory buffer size.
			*
			* \return	If succeed to create the shared memory.
			*/
			bool CreateNew(const std::string& path, int bufferSize)
			{
				// if already init throw exception
				if (IsValid()) throw new std::exception("Shared Memory already connected!");

				// convert path to wide string
				LPCWSTR converted;
				String::To::LpcwStr(path, converted);

				// create shared memory
				_MapFile = CreateFileMapping(
					INVALID_HANDLE_VALUE,    // use paging file
					NULL,                    // default security
					PAGE_READWRITE,          // read/write access
					0,                       // maximum object size (high-order DWORD)
					bufferSize,              // maximum object size (low-order DWORD)
					converted);				 // name of mapping object
				delete[] converted;

				// if had error stop here
				if (_MapFile == NULL)
				{
					return false;
				}

				// get mapping
				_Buffer = (LPTSTR)MapViewOfFile(_MapFile,
					FILE_MAP_ALL_ACCESS, 
					0,
					0,
					bufferSize);

				// if failed, close the file handle and stop here
				if (_Buffer == NULL)
				{
					Close();
					return false;
				}

				// success
				_BufferSize = bufferSize;
				return true;
			}

			/*!
			* \fn	bool Connect(const std::string& path, int bufferSize)
			*
			* \brief	Connect to existing shared memory other processed previously opened.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	path 				Shared memory file path.
			* \param	bufferSize			Shared memory buffer size.
			*
			* \return	If succeed to connect to the shared memory.
			*/
			bool Connect(const std::string& path, int bufferSize)
			{
				// if already init throw exception
				if (IsValid()) throw new std::exception("Shared Memory already connected!");

				// convert path to wide string
				LPCWSTR converted;
				String::To::LpcwStr(path, converted);

				// create shared memory
				_MapFile = OpenFileMapping(
					FILE_MAP_ALL_ACCESS,   // read/write access
					FALSE,                 // do not inherit the name
					converted);            // name of mapping object
				delete[] converted;

				// if had error stop here
				if (_MapFile == NULL)
				{
					return false;
				}

				// get mapping
				_Buffer = (LPTSTR)MapViewOfFile(_MapFile,
					FILE_MAP_ALL_ACCESS,
					0,
					0,
					bufferSize);

				// if failed, close the file handle and stop here
				if (_Buffer == NULL)
				{
					Close();
					return false;
				}

				// success
				_BufferSize = bufferSize;
				return true;
			}

			/*!
			* \fn	bool ConnectOrCreate(const std::string& path, int bufferSize)
			*
			* \brief	Try to connect to existing shared memory and if fail, try to create it.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	path 				Shared memory file path.
			* \param	bufferSize			Shared memory buffer size.
			*
			* \return	If succeed to connect / create the shared memory.
			*/
			bool ConnectOrCreate(const std::string& path, int bufferSize)
			{
				return CreateNew(path, bufferSize) || Connect(path, bufferSize);
			}

			/*!
			* \fn	void Write(void* data, int dataLen = 0, int offset = 0)
			*
			* \brief	Write to shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	data 				Data buffer to write.
			* \param	dataLen				Data buffer size, in bytes. Must match data buffer. Default to shared memory size.
			* \param	offset				Offset in buffer to write into.
			* Note: if exceed shared memory size will throw exception.
			*/
			void WriteBuffer(const void* data, int dataLen = 0, int offset = 0)
			{
				if (!IsValid()) throw new std::exception("Cannot call write when shared memory is not valid!");
				if (dataLen == 0) dataLen = _BufferSize;
				if (offset + dataLen > _BufferSize) throw new std::exception("Exceeded shared memory size!");
				CopyMemory((PVOID)(_Buffer + offset), data, dataLen);
			}

			/*!
			* \fn	inline void Write(int val, int offset = 0)
			*
			* \brief	Write an integer into shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	val 				Integer value to write.
			* \param	offset				Offset in buffer to write into.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void WriteInt(int val, int offset = 0)
			{
				WriteBuffer(&val, sizeof(val), offset);
			}

			/*!
			* \fn	inline void Write(bool val, int offset = 0)
			*
			* \brief	Write a bool into shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	val 				Bool value to write.
			* \param	offset				Offset in buffer to write into.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void WriteBool(bool val, int offset = 0)
			{
				WriteBuffer(&val, sizeof(val), offset);
			}

			/*!
			* \fn	inline void Write(char val, int offset = 0)
			*
			* \brief	Write a char into shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	val 				Char value to write.
			* \param	offset				Offset in buffer to write into.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void WriteChar(char val, int offset = 0)
			{
				WriteBuffer(&val, sizeof(val), offset);
			}

			/*!
			* \fn	inline void WriteStr(const LPCWSTR& val, int offset = 0)
			*
			* \brief	Write a string into shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	val 				String value to write.
			* \param	offset				Offset in buffer to write into.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void WriteStr(const LPCWSTR& val, int offset = 0)
			{
				WriteBuffer(val, (int)(_tcslen(val) * sizeof(TCHAR)), offset);
			}

			/*!
			* \fn	void Read(void* data, int dataLen = 0, int offset = 0)
			*
			* \brief	Read from shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	data 				Data buffer to read into. Must be allocated and released by caller.
			* \param	dataLen				Data buffer size, in bytes. Must match data buffer. Default to shared memory size.
			* \param	offset				Offset in buffer to read from.
			* Note: if exceed shared memory size will throw exception.
			*/
			void ReadBuffer(void* data, int dataLen = 0, int offset = 0) const
			{
				if (!IsValid()) throw new std::exception("Cannot call read when shared memory is not valid!");
				if (dataLen == 0) dataLen = _BufferSize;
				if (offset + dataLen > _BufferSize) throw new std::exception("Exceeded shared memory size!");
				CopyMemory(data, (PVOID)(_Buffer + offset), dataLen);
			}

			/*!
			* \fn	inline void Read(int& out, int offset = 0) const
			*
			* \brief	Read an integer from shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	out 				Integer value to read into.
			* \param	offset				Offset in buffer to read from.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void ReadInt(int& out, int offset = 0) const
			{
				ReadBuffer(&out, sizeof(out), offset);
			}

			/*!
			* \fn	inline void Read(bool& out, int offset = 0) const
			*
			* \brief	Read a bool from shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	val 				Bool value to read into.
			* \param	offset				Offset in buffer to read from.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void ReadBool(bool& out, int offset = 0) const
			{
				ReadBuffer(&out, sizeof(out), offset);
			}

			/*!
			* \fn	inline void Read(char& out, int offset = 0) const
			*
			* \brief	Read a bool from shared memory.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	val 				Char value to read into.
			* \param	offset				Offset in buffer to read from.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void ReadChar(char& out, int offset = 0) const
			{
				ReadBuffer(&out, sizeof(out), offset);
			}

			/*!
			* \fn	inline void ReadStr(TCHAR* out, int maxLen = 0) const
			*
			* \brief	Read the whole shared memory as a string.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \param	val 				Char* value to read into. Must be a buffer in the size of the shared memory.
			* \param	maxLen 				Expected string len to read. If not provided, will read whole shared memory buffer.
			* Note: if exceed shared memory size will throw exception.
			*/
			inline void ReadStr(TCHAR* out, int maxLen = 0) const
			{
				ReadBuffer(out, maxLen * (sizeof(TCHAR) / sizeof(char)));
			}

			/*!
			* \fn	inline bool IsValid() const
			*
			* \brief	Check if valid and can be used to read / write.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \return	If shared memory is initialized and ready.
			*/
			inline bool IsValid() const { return _MapFile != NULL && _Buffer != NULL; }
			
			/*!
			* \fn	inline int GetSize() const
			*
			* \brief	Get shared memory buffer size.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*
			* \return	Shared memory buffer size.
			*/
			inline int GetSize() const { return _BufferSize; }

			/*!
			* \fn	void Close()
			*
			* \brief	Close this handle. 
			* 			When all handles of a shared memory are closed, the platform may release it.
			*
			* \author	Ronen Ness
			* \date		11/13/2018
			*/
			void Close()
			{
				if (_Buffer) UnmapViewOfFile(_Buffer);
				if (_MapFile) CloseHandle(_MapFile);
				_Buffer = NULL;
				_MapFile = NULL;
				_BufferSize = 0;
			}
		};
	}
}
#endif



// ::DLLs\Load.h::

/*!
 * \file	Source\DLLs\Load.h.
 *
 * \brief	Dynamically load dlls.
 */
// #pragma once
#ifdef _WIN32
#include <string>
#include <windows.h>

namespace Just
{
	namespace DLLs
	{
		/*!
		 * \fn	bool Load(const std::string& dllPath)
		 *
		 * \brief	Loads a DLL from path.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	dllPath	Full path of the DLL file.
		 *
		 * \return	True if succeed to load DLL, false otherwise.
		 */
		bool Load(const std::string& dllPath)
		{
			return LoadLibrary(LPCWSTR(dllPath.c_str())) != NULL;
		}

		/*!
		 * \fn	void* GetMethodFromDLL(const std::string& dllPath, const std::string& methodName)
		 *
		 * \brief	Gets a method from DLL.
		 *
		 * \author	Ronen Ness
		 * \date	10/18/2018
		 *
		 * \param	dllPath   	Full path of the DLL file.
		 * \param	methodName	Name of the method to get.
		 *
		 * \return	Method pointer, or null if failed to load DLL or get method.
		 */
		void* GetMethod(const std::string& dllPath, const std::string& methodName)
		{
			// load library
			HINSTANCE hGetProcIDDLL = LoadLibrary(LPCWSTR(dllPath.c_str()));

			// if failed to load dll return null
			if (!hGetProcIDDLL) {
				return NULL;
			}

			// get function from DLL
			return GetProcAddress(hGetProcIDDLL, methodName.c_str());
		}
	}
}
#endif

