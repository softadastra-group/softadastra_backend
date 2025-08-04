#ifndef CATEGORY_CONTROLLER_HPP
#define CATEGORY_CONTROLLER_HPP

#include <crow.h>
#include <crow/middlewares/cors.h>

namespace softadastra::commerce::categories
{
    void CategoryController(crow::App<crow::CORSHandler> &app);
}

#endif // CATEGORY_CONTROLLER_HPP
