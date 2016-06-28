// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include "SoundAL.h"
#include "AudioAL.h"
#include "SoundDataAL.h"
#include "core/Engine.h"
#include "utils/Utils.h"

namespace ouzel
{
    namespace audio
    {
        SoundAL::SoundAL()
        {
        }

        SoundAL::~SoundAL()
        {
            if (outputBuffer)
            {
                alDeleteBuffers(1, &outputBuffer);
            }

            if (sourceId)
            {
                alDeleteSources(1, &sourceId);
            }
        }

        void SoundAL::free()
        {
            Sound::free();

            if (outputBuffer)
            {
                alDeleteBuffers(1, &outputBuffer);
                outputBuffer = 0;
            }

            if (sourceId)
            {
                alDeleteSources(1, &sourceId);
                sourceId = 0;
            }
        }

        bool SoundAL::init(const SoundDataPtr& newSoundData)
        {
            if (!Sound::init(newSoundData))
            {
                return false;
            }

            free();

            alGenSources(1, &sourceId);

            if (AudioAL::checkOpenALErrors())
            {
                log("Failed to create OpenAL source");
                return false;
            }

            alGenBuffers(1, &outputBuffer);

            if (AudioAL::checkOpenALErrors())
            {
                log("Failed to create OpenAL buffer");
                return false;
            }

            ALenum format;

            if (soundData->getChannels() == 1)
            {
                if (soundData->getBitsPerSample() == 8)
                {
                    format = AL_FORMAT_MONO8;
                }
                else if (soundData->getBitsPerSample() == 16)
                {
                    format = AL_FORMAT_MONO16;
                }
                else
                {
                    log("Unsupported number of bits per sample");
                    return false;
                }
            }
            else if (soundData->getChannels() == 2)
            {
                if (soundData->getBitsPerSample() == 8)
                {
                    format = AL_FORMAT_STEREO8;
                }
                else if (soundData->getBitsPerSample() == 16)
                {
                    format = AL_FORMAT_STEREO16;
                }
                else
                {
                    log("Unsupported number of bits per sample");
                    return false;
                }
            }
            else
            {
                log("Unsupported number of channels");
                return false;
            }

            alBufferData(outputBuffer, format, soundData->getData().data(), soundData->getData().size(), soundData->getSamplesPerSecond());

            if (AudioAL::checkOpenALErrors())
            {
                log("Failed to upload OpenAL data");
                return false;
            }

            alSourcef(sourceId, AL_PITCH, 1.0f);
            alSourcef(sourceId, AL_GAIN, 1.0f);

            alSourcei(sourceId, AL_BUFFER, outputBuffer);

            if (AudioAL::checkOpenALErrors())
            {
                log("Failed to set OpenAL buffer");
                return false;
            }

            ready = true;

            return true;
        }

        bool SoundAL::play(bool repeatSound)
        {
            if (!Sound::play(repeatSound))
            {
                return false;
            }

            alSourcei(sourceId, AL_LOOPING, repeatSound ? AL_TRUE : AL_FALSE);
            alSourcePlay(sourceId);

            if (AudioAL::checkOpenALErrors())
            {
                log("Failed to play OpenAL source");
                return false;
            }

            return true;
        }

        bool SoundAL::stop(bool resetSound)
        {
            if (!Sound::stop(resetSound))
            {
                return false;
            }

            if (resetSound)
            {
                alSourceStop(sourceId);
            }
            else
            {
                alSourcePause(sourceId);
            }

            if (AudioAL::checkOpenALErrors())
            {
                log("Failed to stop OpenAL source");
                return false;
            }

            return true;
        }

        bool SoundAL::reset()
        {
            if (!Sound::reset())
            {
                return false;
            }

            alSourceRewind(sourceId);

            if (AudioAL::checkOpenALErrors())
            {
                log("Failed to rewind OpenAL source");
                return false;
            }

            return true;
        }
    } // namespace audio
} // namespace ouzel