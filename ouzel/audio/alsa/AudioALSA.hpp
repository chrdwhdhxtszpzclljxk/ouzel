// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "core/CompileConfig.h"

#if OUZEL_SUPPORTS_ALSA

#include <alsa/asoundlib.h>

#include "audio/Audio.hpp"

namespace ouzel
{
    namespace audio
    {
        class AudioALSA: public Audio
        {
            friend Engine;
        public:
            virtual ~AudioALSA();

        protected:
            AudioALSA();
            virtual bool init(bool debugAudio) override;
        };
    } // namespace audio
} // namespace ouzel

#endif