# IpCameraManager

To compile this project, you need C++ 20 support.

# Format of the config files
```
{    
    //this will be used to delete videos when this percentage of the disk is full
    "hardDriveUsageThreshold": 85.0,
    "filesDirectory": "",
    "cameras": [
        {
            "cameraName": "External Camera",
            "ip": "192.168.1.100",
            "port": "554",
            "username": "admin",
            "password": "yourpassword",
            "connectionURL": "",
            "framesPerSecond": 15,
            "videoDuration": 30,
            "outputFormat": "mp4"
        }
        ...other camera objets
    ],
    //path of the ffmpeg executable
    //leave it empty if its in the environment
    "ffmpegPath": ""
}
```