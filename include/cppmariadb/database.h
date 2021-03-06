#pragma once

#include <string>
#include <cppmariadb/config.h>
#include <cppmariadb/enums.h>
#include <cppmariadb/forward/connection.h>

namespace cppmariadb
{

    struct database
    {
        using error_code_t = ::cppmariadb::error_code;

        static inline connection    connect    (const std::string&     host,
                                                const uint&            port,
                                                const std::string&     user,
                                                const std::string&     password,
                                                const std::string&     database,
                                                const client_flags&    flags);
        static inline error_code_t  error_code (MYSQL* handle);
        static inline std::string   error_msg  (MYSQL* handle);
    };

}