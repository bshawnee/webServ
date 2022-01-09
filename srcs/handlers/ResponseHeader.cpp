#include "../../includes/handlers/ResponseHeader.hpp"

ResponseHeader::ResponseHeader()
{
	_mapResponseCode[CONTINUE] = "100 Continue";
	_mapResponseCode[PROCESSING] = "102 Processing";
	_mapResponseCode[OK] = "200 OK";
	_mapResponseCode[CREATED] = "201 Created";
	_mapResponseCode[ACCEPTED] = "202 Accepted";
	_mapResponseCode[NO_CONTENT] = "204 No Content";
	_mapResponseCode[MOVED_PERMANENTLY] = "301 Moved Permanently";
	_mapResponseCode[BAD_REQUEST] = "400 Bad Request";
	_mapResponseCode[NOT_FOUND] = "404 Not Found";
	_mapResponseCode[METHOD_NOT_ALLOWED] = "405 Method Not Allowed";
	_mapResponseCode[REQUEST_TIMEOUT] = "408 Request Timeout";
	_mapResponseCode[LENGTH_REQUIRED] = "411 Length Required";
	_mapResponseCode[REQUEST_ENTRY_TOO_LARGE] = "413 Payload Too Large";
	_mapResponseCode[INTERNAL_SERVER_ERROR] = "500 Internal Server Error";
	_mapResponseCode[NOT_IMPLEMENTED] = "501 Not Implemented";
}

ResponseHeader::~ResponseHeader() {}

ResponseHeader::ResponseHeader(const ResponseHeader& ref) { *this = ref; }

ResponseHeader& ResponseHeader::operator=(const ResponseHeader& rhs)
{
	if (this == &rhs)
		return *this;
	_mapResponseCode = rhs._mapResponseCode;
	_typeRequest = rhs._typeRequest;
	_contentLength = rhs._contentLength;
	_keepConnection = rhs._keepConnection;
	_serverName = rhs._serverName;
	return *this;
}

void ResponseHeader::setContentLength(size_t length) { _contentLength = length; }

void ResponseHeader::setKeepConnection(bool keep) { _keepConnection = keep; }

void ResponseHeader::setResponseCode(responseCode code) { _currentCode = code; }

void ResponseHeader::setServerName(const std::string& serverName) { _serverName = serverName; }

void ResponseHeader::setTypeRequest(const std::string& typeRequest) { _typeRequest = typeRequest; }

const std::string ResponseHeader::getHeader() const
{
	std::string tmp;
	std::string tmp2;
	std::map<responseCode, std::string>::const_iterator it = _mapResponseCode.find(_currentCode);
	if (it != _mapResponseCode.end())
		tmp2 = it->second;
	tmp += "HTTP/1.1" + tmp2 + '\n' +
	"Server: " + _serverName + '\n' +
	"Content-Type: " + _typeRequest + '\n' +
	"Content-Length: " + utils::intToString(static_cast<int>(_contentLength)) + '\n';
	if (!_keepConnection)
		tmp += "Connection-Close: false\n\n";
	else
		tmp += "Connection-Close: keep-alive\n\n";
	return tmp;
}


const std::string& ResponseHeader::getTypeRequest() const { return _typeRequest; }

const std::string ResponseHeader::getResponseCode() const
{
	std::map<responseCode, std::string>::const_iterator it =  _mapResponseCode.find(_currentCode);
	std::string tmp;
	if (it != _mapResponseCode.end())
		tmp = it->second;
	return tmp;
}

const std::string& ResponseHeader::getServerName() const { return _serverName; }

bool ResponseHeader::getKeepConnection() const { return _keepConnection; }

size_t ResponseHeader::getContentLength() const { return _contentLength; }
