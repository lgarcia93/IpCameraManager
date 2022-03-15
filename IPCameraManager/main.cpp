#include "ConfigParser.h"
#include <format>
#include "Types.h"
#include <chrono>
#include <iostream>
#include <sstream>

#define _CRT_SECURE_NO_WARNINGS

std::string formatted_date() {
	std::time_t time = std::time(0);

	struct tm timeInfo;

	localtime_s(&timeInfo, &time);

	std::stringstream ss;

	ss << timeInfo.tm_mday
		<< '-'
		<< timeInfo.tm_mon + 1
		<< '-'
		<< timeInfo.tm_year + 1900
		<< '_'
		<< timeInfo.tm_hour
		<< '-'
		<< timeInfo.tm_min
		<< '-'
		<< timeInfo.tm_sec;

	return ss.str();


}

int main() {

	try {
		ConfigParser configParser("config.json");

		types::Config config = configParser.getConfig();

		for (const auto cameraInfo : config.Cameras)
		{
			std::string test;

			std::format("{}", test);

			std::string connectionURL = cameraInfo.ConnectionURL;

			if (cameraInfo.ConnectionURL.empty())
			{
				connectionURL = std::format(
					"rtsp://{}:{}@{}:{}/onvif1",
					cameraInfo.Username,
					cameraInfo.Password,
					cameraInfo.IP,
					cameraInfo.Port
				);
			}


			auto fileName = std::format("{}_{}", cameraInfo.CameraName, formatted_date());

			auto outputPath = std::filesystem::path(std::format("{}/{}", config.FilesDirectory, fileName));

			auto command = std::format(
				"ffmpeg -y -t {} -r {} -i {} -vcodec copy -map 0 -r {} -f {}",
				cameraInfo.VideoDuration,
				cameraInfo.FramesPerSecond,
				connectionURL,
				cameraInfo.FramesPerSecond,
				outputPath.string()
			);

			std::system(command.c_str());
		}

		return EXIT_SUCCESS;
	}
	catch (std::exception e)
	{
		return EXIT_FAILURE;
	}
}