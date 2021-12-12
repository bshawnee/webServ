#include "../../includes/handlers/ResponseFactory.h"

const std::string ft::Response::availableMethod[AVAILABLE_METHOD_COUNT] = {
	"GET",
	"POST",
	"PUT"
	"NONE"
};

static ft::response::AResponse*	getGetResponse(HttpRequest& req)
{
	return new ft::response::Get(req);
}

static ft::response::AResponse*	getPostResponse(HttpRequest& req)
{
	return NULL;
}

static ft::response::AResponse*	getPutResponse(HttpRequest& req)
{
	return NULL;
}

ft::response::AResponse*	ft::Response::accept(HttpRequest& req)
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
	return func[i](req);
}

ft::Buffer	handle(ft::Buffer& b)
{
	HttpRequest req(b.getFullData());
	ft::response::AResponse* res = ft::Response::accept(req);
	ft::Buffer buf = res->getRespone();
	delete res;
	return buf;
}