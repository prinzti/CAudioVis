cAudioVis: CAudioVis.o onsetsds.o AudioInputter.o AudioInputter.o AudioProcessors.o OutputProcessors.o AbstractVisualizer.o FourChannelSpecVisualizer.o
	gcc -o cAudioVis CAudioVis.o onsetsds.o AudioInputter.o AudioInputter.o AudioProcessors.o OutputProcessors.o AbstractVisualizer.o FourChannelSpecVisualizer.o -lasound -lfftw3f -lwiringPi
	
CAudioVis.o: CAudioVis.cpp
	gcc -c CAudioVis.cpp
onsetsds.o: onsetsds.c
	gcc -c onsetsds.c
AudioInputter.o: AudioInputter.cpp
	gcc -c AudioInputter.cpp
AudioProcessors.o: AudioProcessors/AudioDataProcessor.cpp
	gcc -c AudioProcessors/*.cpp -o AudioProcessors.o
OutputProcessors.o: OutputProcessors/AbstractVisOutputProcessor.cpp
	gcc -c OutputProcessors/*.cpp -o OutputProcessors.o
AbstractVisualizer.o: OutputProcessors/Visualizers/AbstractVisualizer.cpp
	gcc -c OutputProcessors/Visualizers/AbstractVisualizer.cpp -o AbstractVisualizer.o
FourChannelSpecVisualizer.o: OutputProcessors/Visualizers/FourChannelSpecVisualizer/AbstractFCSVisOutputter.cpp
	gcc -c OutputProcessors/Visualizers/FourChannelSpecVisualizer/*.cpp -o FourChannelSpecVisualizer.o