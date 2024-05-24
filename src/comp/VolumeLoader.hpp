#ifndef VOLUME_LOADER_H_
#define VOLUME_LOADER_H_
#include "../core/Constants.hpp"
#include "../thirdParty/tinyxml2_10.0.0/tinyxml2.hpp"
/**
 * @class VolumeLoader
 * @brief A class responsible for saving and loading volumes.
 */
class VolumeLoader
{
public:
    /**
     * @brief Saves the volume.
     */
    static void saveVolume();

    /**
     * @brief Loads the volume.
     */
    static void loadVolume();
};

#endif // !VOLUME_LOADER_H_