#Nathaniel Fuller
#cmsc 455 hw5

from pydub import *
import numpy as np

file = AudioSegment.from_wav("short_count.wav")

frameRate = file.frame_rate
octaves = -0.5

newRate = int(file.frame_rate * (2.0 ** octaves))

higherPitch = file._spawn(file.raw_data, overrides={"frame_rate": newRate})

higherPitchFinal = higherPitch.set_frame_rate(44100)

higherPitchFinal.export("newfile.wav", format="wav")
