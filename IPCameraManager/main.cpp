#include "ConfigParser.h"
#include <format>
#include "Types.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

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

std::map<std::string, long long> CameraExecutionCache;


long long GetTimeSinceEpoch() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		).count();
}

bool ShouldStartNewRecording(types::CameraInfo& cameraInfo) {
	return (GetTimeSinceEpoch() - CameraExecutionCache[cameraInfo.CameraName]) > (cameraInfo.VideoDuration * 1000);
}

int main() {
	while (true)
	{
		try {
			ConfigParser configParser("config.json");

			types::Config config = configParser.getConfig();


			for (auto cameraInfo : config.Cameras)
			{
				if (!ShouldStartNewRecording(cameraInfo))
				{
					continue;
				}

				CameraExecutionCache[cameraInfo.CameraName] = GetTimeSinceEpoch();

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


				const auto task = [command]() {
					std::system(command.c_str());
				};

				auto t1 = std::thread::thread(task);

				t1.detach();
			}

			return EXIT_SUCCESS;

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		catch (std::exception e)
		{
			return EXIT_FAILURE;
		}
	}
	
}