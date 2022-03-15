#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "json.hpp"

namespace types {
	using json = nlohmann::json;

	struct CameraInfo {
	public:
		std::string CameraName;
		std::string IP;
		std::string Port;
		std::string Username;
		std::string Password;
		std::string ConnectionURL;
		double FramesPerSecond = 15;
		uint32_t VideoDuration = 30;
		std::string OutputFormat;		
	};

	struct Config {
	public:		
		double HardDriveUsageThreshold;
		std::string FilesDirectory;
		std::vector<CameraInfo> Cameras;
		std::filesystem::path FFMPEGPath;
	};

	inline void from_json(const json& j, CameraInfo& p) {
		j.at("cameraName").get_to(p.CameraName);
		j.at("ip").get_to(p.IP);
		j.at("port").get_to(p.Port);
		j.at("username").get_to(p.Username);
		j.at("password").get_to(p.Password);
		j.at("connectionURL").get_to(p.ConnectionURL);
		j.at("framesPerSecond").get_to(p.FramesPerSecond);
		j.at("videoDuration").get_to(p.VideoDuration);
		j.at("outputFormat").get_to(p.OutputFormat);
	}

	inline void to_json(json& j, const CameraInfo& p) {
		
	}

	inline void from_json(const json& j, Config& p) {
		j.at("hardDriveUsageThreshold").get_to(p.HardDriveUsageThreshold);
		j.at("filesDirectory").get_to(p.FilesDirectory);
		j.at("cameras").get_to(p.Cameras);
		j.at("ffmpegPath").get_to(p.FFMPEGPath);
	}

	inline void to_json(json& j, const Config& p) {

	}
}
