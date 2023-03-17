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
   
   make -C build/ThunderNanoServices && make -C build/ThunderNanoServices install
   ```
5. Start the WPEFreamework using the command given below.

   ```
   PATH=${THUNDER_INSTALL_DIR}/usr/bin:${PATH} LD_LIBRARY_PATH=${THUNDER_INSTALL_DIR}/usr/lib:${LD_LIBRARY_PATH} WPEFramework -c ${THUNDER_INSTALL_DIR}/etc/WPEFramework/config.json
   ```
6. Open a new terminal and use the below curl commands to access the features.
   - To set the path od the video file:
   
     ```
     curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc": "2.0","id": 42,"method": "Player.1.pathset","params":{"path":"/home/dkaper335/Downloads/music-box-11543.mp4"}}' http://127.0.0.1:55555/jsonrpc
     ```
   - To Play/Pause the video:
   
     ```
     curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc": "2.0","id": 42,"method": "Player.1.p"}' http://127.0.0.1:55555/jsonrpc
     ```
   - To activate the loop mode:
   
     ```
     curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc": "2.0","id": 42,"method": "Player.1.loop","params":{"loop":"1"}}' http://127.0.0.1:55555/jsonrpc
     ```
   - To decativate the loop mode:
   
     ```
     curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc": "2.0","id": 42,"method": "Player.1.loop","params":{"loop":"0"}}' http://127.0.0.1:55555/jsonrpc
     ```
7. Give 'Q' in the first terminal to exit the WPEFramework. 

