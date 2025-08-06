#ifndef PRODUCT_CONTROLLER_HPP
#define PRODUCT_CONTROLLER_HPP

#include <crow.h>
#include <crow/middlewares/cors.h>

namespace softadastra::commerce::products
{
    void ProductController(crow::App<crow::CORSHandler> &app);
}

#endif // PRODUCT_CONTROLLER_HPP
