#include "../../includes/handlers/Get.hpp"

ft::Buffer	ft::response::Get::getRespone()
{
	return readFromFile_(req_.getUrl());
}