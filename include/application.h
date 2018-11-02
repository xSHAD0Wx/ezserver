#ifndef EZSERVER_APPLICATION_H
#define EZSERVER_APPLICATION_H

#include "iapplication.h"
#include <services/ilogger.h>
#include <boost/di.hpp>

namespace ezserver
{
    /**
     * Main application class
     */
    class Application : public ezserver::shared::IApplication {
    public:
        /// Base class method override
        virtual bool Startup() override;

        /**
         * Default DI constrcutor
         */
        BOOST_DI_INJECT(Application, const std::shared_ptr<ezserver::shared::services::ILogger>& logger)
            : logger_(logger) {}

    private:
        /// A Service to manage app logs
        std::weak_ptr<ezserver::shared::services::ILogger> logger_;
    };

    /**
     * A Lambda to export this module
     */
    const auto application_module = [] {
        return boost::di::make_injector(
            boost::di::bind<ezserver::shared::IApplication>.to<Application>()
        );
    };
}

#endif //EZSERVER_APPLICATION_H