#include "VolumeLoader.hpp"

void VolumeLoader::saveVolume()
{
    int currentVolume = Mix_Volume(-1, -1);
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *root;
    if (doc.LoadFile(SAVE_PATH) == tinyxml2::XML_SUCCESS)
    {
        root = doc.RootElement();
        if (root)
        {
            tinyxml2::XMLElement *volume = root->FirstChildElement("Volume");
            if (volume)
            {
                volume->SetAttribute("value", currentVolume);
            }
            else
            {
                volume = doc.NewElement("Volume");
                volume->SetAttribute("value", currentVolume);
                root->InsertEndChild(volume);
            }
        }
    }
    else
    {
        root = doc.NewElement("SaveData");
        doc.InsertFirstChild(root);

        tinyxml2::XMLElement *volume = doc.NewElement("Volume");
        volume->SetAttribute("value", currentVolume);
        root->InsertEndChild(volume);
    }

    try
    {
        std::filesystem::create_directories("save");
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    doc.SaveFile(SAVE_PATH);
}

void VolumeLoader::loadVolume()
{
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(SAVE_PATH) == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLElement *root = doc.RootElement();
		if (!root)
		{
			return;
		}
		tinyxml2::XMLElement *volume = root->FirstChildElement("Volume");
		if (!volume)
		{
			return;
		}
		int value = MIX_MAX_VOLUME;
		volume->QueryIntAttribute("value", &value);
		Mix_VolumeMusic(value);
		Mix_Volume(-1, value);
		
	}

}
