// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "LoaderParticleSystem.hpp"
#include "Cache.hpp"
#include "scene/ParticleSystemData.hpp"

namespace ouzel
{
    namespace assets
    {
        LoaderParticleSystem::LoaderParticleSystem():
            Loader({"json"})
        {
        }

        bool LoaderParticleSystem::loadAsset(const std::string& filename, const std::vector<uint8_t>& data)
        {
            scene::ParticleSystemData particleSystemData;
            if (!particleSystemData.init(data))
            {
                return false;
            }

            cache->setParticleSystemData(filename, particleSystemData);

            return true;
        }
    } // namespace assets
} // namespace ouzel
