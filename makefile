cAudioVis: CAudioVis.o onsetsds.o AudioInputter.o AudioInputter.o AudioDataProcessor.o BpmAnalyzer.o AbstractVisOutputProcessor.o ConsoleVisOutputProcessor.o GpioVisOutputProcessor.o AbstractVisualizer.o AbstractFCSVisOutputter.o FCSVisOutputterHub.o FCSVisOutputterInitializer.o FourChannelSpecVisualizer.o MultiColorFCSVisOutputter.o SingleColorFCSVisOutputter.o
	gcc -o cAudioVis CAudioVis.o onsetsds.o AudioInputter.o AudioInputter.o AudioDataProcessor.o BpmAnalyzer.o AbstractVisOutputProcessor.o ConsoleVisOutputProcessor.o GpioVisOutputProcessor.o AbstractVisualizer.o AbstractFCSVisOutputter.o FCSVisOutputterHub.o FCSVisOutputterInitializer.o FourChannelSpecVisualizer.o MultiColorFCSVisOutputter.o SingleColorFCSVisOutputter.o -lasound -lfftw3f -lwiringPi

CAudioVis.o: CAudioVis.cpp
	gcc -c CAudioVis.cpp
onsetsds.o: onsetsds.c
	gcc -c onsetsds.c
AudioInputter.o: AudioInputter.cpp
	gcc -c AudioInputter.cpp
AudioDataProcessor.o: AudioProcessors/AudioDataProcessor.cpp
	gcc -c AudioProcessors/AudioDataProcessor.cpp
BpmAnalyzer.o: AudioProcessors/BpmAnalyzer.cpp
	gcc -c AudioProcessors/BpmAnalyzer.cpp
AbstractVisOutputProcessor.o: OutputProcessors/AbstractVisOutputProcessor.cpp
	gcc -c OutputProcessors/AbstractVisOutputProcessor.cpp
ConsoleVisOutputProcessor.o: OutputProcessors/ConsoleVisOutputProcessor.cpp
	gcc -c OutputProcessors/ConsoleVisOutputProcessor.cpp
GpioVisOutputProcessor.o: OutputProcessors/GpioVisOutputProcessor.cpp
	gcc -c OutputProcessors/GpioVisOutputProcessor.cpp
AbstractVisualizer.o: OutputProcessors/Visualizers/AbstractVisualizer.cpp
	gcc -c OutputProcessors/Visualizers/AbstractVisualizer.cpp
AbstractFCSVisOutputter.o: OutputProcessors/Visualizers/FourChannelSpecVisualizer/AbstractFCSVisOutputter.cpp
	gcc -c OutputProcessors/Visualizers/FourChannelSpecVisualizer/AbstractFCSVisOutputter.cpp
FCSVisOutputterHub.o: OutputProcessors/Visualizers/FourChannelSpecVisualizer/FCSVisOutputterHub.cpp
	gcc -c OutputProcessors/Visualizers/FourChannelSpecVisualizer/FCSVisOutputterHub.cpp
FCSVisOutputterInitializer.o: OutputProcessors/Visualizers/FourChannelSpecVisualizer/FCSVisOutputterInitializer.cpp
	gcc -c OutputProcessors/Visualizers/FourChannelSpecVisualizer/FCSVisOutputterInitializer.cpp
FourChannelSpecVisualizer.o: OutputProcessors/Visualizers/FourChannelSpecVisualizer/FourChannelSpecVisualizer.cpp
	gcc -c OutputProcessors/Visualizers/FourChannelSpecVisualizer/FourChannelSpecVisualizer.cpp
MultiColorFCSVisOutputter.o: OutputProcessors/Visualizers/FourChannelSpecVisualizer/MultiColorFCSVisOutputter.cpp
	gcc -c OutputProcessors/Visualizers/FourChannelSpecVisualizer/MultiColorFCSVisOutputter.cpp
SingleColorFCSVisOutputter.o: OutputProcessors/Visualizers/FourChannelSpecVisualizer/SingleColorFCSVisOutputter.cpp
	gcc -c OutputProcessors/Visualizers/FourChannelSpecVisualizer/SingleColorFCSVisOutputter.cpp