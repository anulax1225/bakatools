#include "log.h"

namespace Bk {

	std::shared_ptr<spdlog::logger> Log::p_core_logger;
	std::shared_ptr<spdlog::logger> Log::p_app_logger;

	void Log::init(std::string core, bool file_log = false)
	{
		std::vector<spdlog::sink_ptr> log_sinks;
		log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		if (file_log) log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("bakara.log", true));

		log_sinks[0]->set_pattern("%^[%T] %n: %v%$");
		log_sinks[1]->set_pattern("[%T] [%l] %n: %v");

		p_core_logger = std::make_shared<spdlog::logger>(core, begin(log_sinks), end(log_sinks));
		spdlog::register_logger(p_core_logger);
		p_core_logger->set_level(spdlog::level::trace);
		p_core_logger->flush_on(spdlog::level::trace);

		p_app_logger = std::make_shared<spdlog::logger>("APP", begin(log_sinks), end(log_sinks));
		spdlog::register_logger(p_app_logger);
		p_app_logger->set_level(spdlog::level::trace);
		p_app_logger->flush_on(spdlog::level::trace);
	}

}