/*!
 * \file	Source\Execute\Scripts.h.
 *
 * \brief	Execute different scripts.
 */
#pragma once

#ifdef _WIN32
#include "Exe.h"

namespace Just
{
	namespace Execute
	{
		/*!
		 * \fn	ProcessOutput ExecuteScript(const std::string& scriptType, const std::string& scriptPath, const std::string& params = std::string())
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
		ProcessOutput ExecuteScript(const std::string& scriptType, const std::string& scriptPath, const std::string& params = std::string())
		{
			return ExecuteCommand(scriptType + " \"" + scriptPath + "\" " + params);
		}

		/*!
		 * \fn	ProcessOutput ExecutePythonScript(const std::string& scriptPath, const std::string& params = std::string())
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
		ProcessOutput ExecutePythonScript(const std::string& scriptPath, const std::string& params = std::string())
		{
			static std::string type = "python";
			return ExecuteScript(type, scriptPath, params);
		}

		/*!
		* \fn	ProcessOutput ExecutePerlScript(const std::string& scriptPath, const std::string& params = std::string())
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
		ProcessOutput ExecutePerlScript(const std::string& scriptPath, const std::string& params = std::string())
		{
			static std::string type = "perl";
			return ExecuteScript(type, scriptPath, params);
		}

		/*!
		* \fn	ProcessOutput ExecuteRubyScript(const std::string& scriptPath, const std::string& params = std::string())
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
		ProcessOutput ExecuteRubyScript(const std::string& scriptPath, const std::string& params = std::string())
		{
			static std::string type = "ruby";
			return ExecuteScript(type, scriptPath, params);
		}
	}
}
#endif