/*!
* \file	Source\SharedMemory\SharedMemory.h.
*
* \brief	Creating and using Shared Memory between processes.
*/
#pragma once
#ifdef _WIN32
#include <string>
#include <windows.h>
#include "../Strings/Convert/StringConvert.h"

namespace Just
{
	namespace SharedMemory
	{
		/**
		* Holding a shared memory connection.
		*/
		class SharedMemoryClient
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
			SharedMemoryClient() : _MapFile(NULL), _Buffer(NULL), _BufferSize(0) {}

			/**
			* Destructor.
			*/
			~SharedMemoryClient()
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
				StringConvert::StringToLPCWSTR(path, converted);

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
				StringConvert::StringToLPCWSTR(path, converted);

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