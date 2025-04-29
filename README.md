# elasticsearch_sender

Task:

Сделайте на С++ программу которая будет слать в elastic данные (любые + время) каждые 10 минут. При этом индекс должен создаваться каждый день в 00:00 новый в формате «index-dd-mm-yyyy».

Notes:

Done for Windows. Perhaps will be need to reconnect external libraries in:

Properties>C/C++>General>Additional Include Directories: ..\elasticHandler\external;..\elasticHandler\external\libcurl-vc-x64-release-dll-ipv6-sspi-schannel\include;

Properties>Linker>General>Additional Library directories: ..\elasticHandler\external\libcurl-vc-x64-release-dll-ipv6-sspi-schannel\lib;

Properties>Linker>Input>Additional Library directories: libcurl.lib

Also, perhaps need to reimport config.json & libcurl.lib with "Item Type": "Copy file"
