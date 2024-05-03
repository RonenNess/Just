/*!
 * \file	Source\Execute\Scripts.h.
 *
 * \brief	Execute different scripts.
 */
#pragma once

#ifdef _WIN32
#include "Command.h"

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