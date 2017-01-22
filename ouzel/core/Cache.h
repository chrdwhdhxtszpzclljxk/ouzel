// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "utils/Types.h"
#include "utils/Noncopyable.h"
#include "scene/SpriteFrame.h"
#include "scene/ParticleDefinition.h"
#include "gui/BMFont.h"

namespace ouzel
{
    class Cache: public Noncopyable
    {
    public:
        Cache();

        void preloadTexture(const std::string& filename, bool dynamic = false, bool mipmaps = true);
        graphics::TextureResourcePtr getTexture(const std::string& filename, bool dynamic = false, bool mipmaps = true) const;
        void setTexture(const std::string& filename, const graphics::TextureResourcePtr& texture);
        void releaseTextures();

        graphics::ShaderResourcePtr getShader(const std::string& shaderName) const;
        void setShader(const std::string& shaderName, const graphics::ShaderResourcePtr& shader);

        graphics::BlendStateResourcePtr getBlendState(const std::string& blendStateName) const;
        void setBlendState(const std::string& blendStateName, const graphics::BlendStateResourcePtr& blendState);

        void preloadSpriteFrames(const std::string& filename, bool mipmaps = true);
        const std::vector<scene::SpriteFrame>& getSpriteFrames(const std::string& filename, bool mipmaps = true) const;
        void setSpriteFrames(const std::string& filename, const std::vector<scene::SpriteFrame>& frames);
        void releaseSpriteFrames();

        void preloadParticleDefinition(const std::string& filename);
        const scene::ParticleDefinition& getParticleDefinition(const std::string& filename) const;

        void preloadBMFont(const std::string& filename);
        const BMFont& getBMFont(const std::string& filename) const;

    protected:
        mutable std::unordered_map<std::string, graphics::TextureResourcePtr> textures;
        mutable std::unordered_map<std::string, graphics::ShaderResourcePtr> shaders;
        mutable std::unordered_map<std::string, scene::ParticleDefinition> particleDefinitions;
        mutable std::unordered_map<std::string, graphics::BlendStateResourcePtr> blendStates;
        mutable std::unordered_map<std::string, std::vector<scene::SpriteFrame>> spriteFrames;
        mutable std::unordered_map<std::string, BMFont> bmFonts;
    };
}
