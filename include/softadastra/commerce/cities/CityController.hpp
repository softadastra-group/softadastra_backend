#ifndef CITY_CONTROLLER_HPP
#define CITY_CONTROLLER_HPP

#include <crow.h>
#include <crow/middlewares/cors.h>

namespace softadastra::commerce::cities
{
    void CityController(crow::App<crow::CORSHandler> &app);
}

#endif