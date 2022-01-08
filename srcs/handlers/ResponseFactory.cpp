#include "../../includes/handlers/ResponseFactory.h"

const static std::string g_availableMethod[AVAILABLE_METHOD_COUNT] = {
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
	req.getUrl();
	return NULL;
}

static ft::response::AResponse*	getPutResponse(HttpRequest& req)
{
	req.getUrl();
	return NULL;
}

ft::response::AResponse*	ft::response::accept(HttpRequest& req)
{
	methodFunc func[AVAILABLE_METHOD_COUNT] = {
		getGetResponse,
		getPostResponse,
		getPutResponse,
		NULL
	};
	size_t i;
	for (i = 0; i < AVAILABLE_METHOD_COUNT; i++)
		if (!g_availableMethod[i].compare(req.getHttpMethod()))
			break ;
	return (func[i])(req);
}

ft::Buffer	handle(ft::Buffer& b)
{
	HttpRequest req(b.getData());
	ft::response::AResponse* res = ft::response::accept(req);
	ft::Buffer buf = res->getResponse();
	delete res;
	return buf;
}