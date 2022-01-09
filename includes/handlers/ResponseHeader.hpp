#ifndef RESPONSE_HEADER_HPP
# define RESPONSE_HEADER_HPP
# include <map>
# include <string>
# include "../utils.h"

class ResponseHeader {
public:
	enum responseCode {
		CONTINUE = 100,
		SWITCHING_PROTOCOL,
		PROCESSING,
		EARLY_HINTS,
		OK = 200,
		CREATED,
		ACCEPTED,
		NON_AUTHORITIVE_INFO,
		NO_CONTENT,
		RESET_CONTENT,
		PARTICAL_CONTENT,
		MULTIPLE_CHOISE = 300,
		MOVED_PERMANENTLY,
		FOUND,
		SEE_OTHER,
		NOT_MODIFIED,
		USE_PROXY,
		SWITCH_PROXY,
		TEMPORARY_REDIRECT,
		PERMANENTLY_REDIRECT,
		BAD_REQUEST = 400,
		UNAUTHORIZED,
		PAYMANENT_REQUIRED,
		FORBIDDEN,
		NOT_FOUND,
		METHOD_NOT_ALLOWED,
		NOT_ACCEPTABLE,
		PROXY_AUTH_REQUIRED,
		REQUEST_TIMEOUT,
		CONFLICT,
		GONE,
		LENGTH_REQUIRED,
		PRECONDITION_FAILED,
		REQUEST_ENTRY_TOO_LARGE,
		REQUEST_URI_TOO_LONG,
		UNSUPPORTED_MEDIA_TYPE,
		REQUESTED_RANGE_NOT_SATISFIABLE,
		EXPECTATION_FAILED,
		INTERNAL_SERVER_ERROR = 500,
		NOT_IMPLEMENTED,
		BAD_GATEWAY,
		SERVICE_UNAVAILABLE,
		GATEWAY_TIMEOUT,
		HTTP_VERSION_NOT_SUPPORTED
	};
	ResponseHeader();
	ResponseHeader(const ResponseHeader& ref);

	~ResponseHeader();

	ResponseHeader& operator=(const ResponseHeader& rhs);
	//Setters
	void setTypeRequest(const std::string& typeRequest);
	void setResponseCode(responseCode code);
	void setContentLength(size_t length);
	void setKeepConnection(bool keep = false);
	void setServerName(const std::string& serverName);
	//Getters
	const std::string getHeader() const;
	const std::string& getTypeRequest() const;
	const std::string getResponseCode() const;
	size_t getContentLength() const;
	bool getKeepConnection() const;
	const std::string& getServerName() const;
private:
	std::map<responseCode, std::string> _mapResponseCode;
	std::string _typeRequest;
	responseCode _currentCode;
	size_t _contentLength;
	bool _keepConnection;
	std::string _serverName;

};

#endif
