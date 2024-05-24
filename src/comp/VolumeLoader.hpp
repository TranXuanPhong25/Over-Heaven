#ifndef VOLUME_LOADER_H_
#define VOLUME_LOADER_H_
#include "../core/Constants.hpp"
#include "../thirdParty/tinyxml2_10.0.0/tinyxml2.hpp"
class VolumeLoader
{
public:
    static void saveVolume();
    static void loadVolume();
};

#endif // !VOLUME_LOADER_H_