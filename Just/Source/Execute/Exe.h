/*!
 * \file	Source\Execute\Exe.h.
 *
 * \brief	Execute exe files.
 */
#pragma once

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