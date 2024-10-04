#pragma once

#include <bakatoolspch.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Bk {
	class Log
	{
        public:
            static void Init(std::string core, bool file_log = false);

            static std::shared_ptr<spdlog::logger>& get_core_logger() { return p_core_logger; }
            static std::shared_ptr<spdlog::logger>& get_app_logger() { return p_app_logger; }
        private:
            static std::shared_ptr<spdlog::logger> p_core_logger;
            static std::shared_ptr<spdlog::logger> p_app_logger;
	};

    #define BK_STATIC_CORE_TRACE(...)    Log::get_core_logger()->trace(__VA_ARGS__)
    #define BK_STATIC_CORE_INFO(...)     Log::get_core_logger()->info(__VA_ARGS__)
    #define BK_STATIC_CORE_WARNING(...)  Log::get_core_logger()->warn(__VA_ARGS__)
    #define BK_STATIC_CORE_ERROR(...)    Log::get_core_logger()->error(__VA_ARGS__)
    #define BK_STATIC_CORE_CRITICAL(...) Log::get_core_logger()->critical(__VA_ARGS__)

    #define BK_STATIC_TRACE(...)         Bk::Log::get_app_logger()->trace(__VA_ARGS__)
    #define BK_STATIC_INFO(...)          Bk::Log::get_app_logger()->info(__VA_ARGS__)
    #define BK_STATIC_WARNING(...)       Bk::Log::get_app_logger()->warn(__VA_ARGS__)
    #define BK_STATIC_ERROR(...)         Bk::Log::get_app_logger()->error(__VA_ARGS__)
    #define BK_STATIC_CRITICAL(...)      Bk::Log::get_app_logger()->critical(__VA_ARGS__)

    #ifdef BK_DEBUG
        #define BK_CORE_TRACE(...)    Log::get_core_logger()->trace(__VA_ARGS__)
        #define BK_CORE_INFO(...)     Log::get_core_logger()->info(__VA_ARGS__)
        #define BK_CORE_WARNING(...)  Log::get_core_logger()->warn(__VA_ARGS__)
        #define BK_CORE_ERROR(...)    Log::get_core_logger()->error(__VA_ARGS__)
        #define BK_CORE_CRITICAL(...) Log::get_core_logger()->critical(__VA_ARGS__)

        #define BK_TRACE(...)         Bk::Log::get_app_logger()->trace(__VA_ARGS__)
        #define BK_INFO(...)          Bk::Log::get_app_logger()->info(__VA_ARGS__)
        #define BK_WARNING(...)       Bk::Log::get_app_logger()->warn(__VA_ARGS__)
        #define BK_ERROR(...)         Bk::Log::get_app_logger()->error(__VA_ARGS__)
        #define BK_CRITICAL(...)      Bk::Log::get_app_logger()->critical(__VA_ARGS__)
    #else
        #define BK_CORE_TRACE(...)    
        #define BK_CORE_INFO(...)     
        #define BK_CORE_WARNING(...)     
        #define BK_CORE_ERROR(...)    
        #define BK_CORE_CRITICAL(...) 

        #define BK_TRACE(...)         
        #define BK_INFO(...)          
        #define BK_WARNING(...)          
        #define BK_ERROR(...)         
        #define BK_CRITICAL(...)       
    #endif
}