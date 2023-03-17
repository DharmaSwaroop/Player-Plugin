# Player_Plugin

## Description
Player plugin is being implemented in thunder framework. This custom player is created as one of the services inside ThunderNanaoServices. The features that are implemented in the player are,
- Setting the path of the video file
- Basic Play/Pause with the key 'p'
- Setting up new url
- Activating and deactivating the loop mode

*As this player is implemented as a service in thunder framework, these features are accessed via JSON requests.*

## Steps to follow to use this Player
1. First install all the necessary thunder files from the [Thunder repo.](https://github.com/rdkcentral/Thunder).
2. Place the Player folder in the examples folder inside ThunderNanoServices.
3. Open the terminal and set up the environment by following the steps mentioned in thunder repo.
4. Run the following cmake and make commands.
```
cmake -HThunderNanoServices -Bbuild/ThunderNanoServices -DCMAKE_INSTALL_PREFIX=${THUNDER_INSTALL_DIR}/usr -DCMAKE_MODULE_PATH=${THUNDER_INSTALL_DIR}/tools/cmake -DPLUGIN_PLAYER=ON
```
