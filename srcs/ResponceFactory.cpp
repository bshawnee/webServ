#include "../includes/ResponseFactory.h"

const std::string ft::Response::availableMethod[AVAILABLE_METHOD_COUNT] = {
	"GET",
	"POST",
	"PUT"
	"NONE"
};

static ft::AResponse*	getGetResponse(const std::string& url)
{
	return NULL;
}

static ft::AResponse*	getPostResponse(const std::string& url)
{
	return NULL;
}

static ft::AResponse*	getPutResponse(const std::string& url)
{
	return NULL;
}

ft::AResponse*	ft::Response::accept(const HttpRequest& req)
{
	methodFunc func[AVAILABLE_METHOD_COUNT] = {
		getGetResponse,
		getPostResponse,
		getPutResponse,
		NULL
	};
	size_t i;
	for (i = 0; i < AVAILABLE_METHOD_COUNT; i++)
		if (!availableMethod[i].compare(req.getHttpMethod()))
			break ;
	return func[i](req.getUrl());
}