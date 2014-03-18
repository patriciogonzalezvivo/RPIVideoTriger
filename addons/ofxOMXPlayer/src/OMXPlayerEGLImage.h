#pragma once
#include "OMXPlayerVideoBase.h"


#include "OMXEGLImage.h"


#include <deque>
#include <sys/types.h>



class OMXPlayerEGLImage : public OMXPlayerVideoBase
{
	public:
		OMXPlayerEGLImage();
		~OMXPlayerEGLImage();

		bool Open(COMXStreamInfo& hints, OMXClock *av_clock, EGLImageKHR eglImage);
		bool OpenDecoder();
		bool Close();

		ofxOMXPlayerSettings settings;
		OMXEGLImage*				eglImageDecoder;
		EGLImageKHR eglImage;
};

