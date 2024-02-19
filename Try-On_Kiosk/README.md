# Virtual Try-On Kiosk 

We employed [Mediapipe](https://developers.google.com/mediapipe) to capture and transmit coordinate data, which was subsequently sent to Unity through a local UDP connection. Within the Unity environment, these coordinates were then utilized to manipulate a hand model that had been loaded into the scene.

## Technology Stack:

- Mediapipe for coordinate data extraction
- Unity for the 3D environment and hand model
- UDP connection for local data transfer

## Usage
This directory functions as a standalone Unity project, allowing you to execute it directly by loading it into your Unity environment. After launching the environment, execute the [main.py](/Try-On_Kiosk/PythonSripts/main.py) script located in the [PythonScripts](/Try-On_Kiosk/PythonSripts) directory.

## Demo Video
[_click here_](https://www.youtube.com/shorts/NkBH4w60zgU)
