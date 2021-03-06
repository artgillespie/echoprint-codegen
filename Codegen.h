//
//  Copyright 2011 The Echo Nest. All rights reserved.
//

#ifndef CODEGEN_H
#define CODEGEN_H

// Entry point for generating codes from PCM data.
#define VERSION 4.00

#include <memory>
#include <string>

#include "Common.h"
#include "AudioBufferInput.h"
#include "Spectrogram.h"

using namespace std;

#ifdef _MSC_VER
    #ifdef CODEGEN_EXPORTS
        #define CODEGEN_API __declspec(dllexport)
        #pragma message("Exporting codegen.dll")
    #else
        #define CODEGEN_API __declspec(dllimport)
        #pragma message("Importing codegen.dll")
    #endif
#else
    #define CODEGEN_API
#endif

class Fingerprint;
class CODEGEN_API Codegen {
public:
    Codegen(const float* pcm, uint numSamples, int start_offset);
    Codegen(auto_ptr<AudioBufferInput>pAudio, auto_ptr<Spectrogram>p16Spectrogram, auto_ptr<Spectrogram>p512Spectrogram, int start_offset);

    string getCodeString(){return _CodeString;}
    int getNumCodes(){return _NumCodes;}
    float getVersion() { return VERSION; }
private:
    Fingerprint* computeFingerprint(auto_ptr<AudioBufferInput>pAudio, auto_ptr<Spectrogram>p16Spectrogram, auto_ptr<Spectrogram>p512Spectrogram, int start_offset);
    void setCodeString(Fingerprint *pFingerprint);

    string compress(const string& s);
    string _CodeString;
    int _NumCodes;
};

#endif
