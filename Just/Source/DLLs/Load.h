/*!
 * \file	Source\DLLs\Load.h.
 *
 * \brief	Dynamically load dlls.
 */
#pragma once
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