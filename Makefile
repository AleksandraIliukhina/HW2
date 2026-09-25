all:
	g++ TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
	g++ TimeCode.cpp PaintDryTimer.cpp -o pdt