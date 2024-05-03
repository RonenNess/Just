/*!
* \file	Source\Http\HttpRequests.h.
*
* \brief	Send HTTP requests.
*/
#pragma once

#ifdef _WIN32

#include <string.h>
#include <windows.h>
#include <sstream>
#include <unordered_map>
#include <winhttp.h>
#include "../Strings/To/All.h"
#include "../Strings/From/Maps.h"

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
			auto headers = Just::String::ParseMap(additionalHeaders, ":", "\n");

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
			auto content = Just::String::ParseMap(data, "=", "&");
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