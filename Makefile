all: KaynakcaYonetimi
KaynakcaYonetimi:
	g++ main.cpp main.h kaynakcayonetimi.cpp kaynakcayonetimi.h `wx-config --cxxflags --libs` -o KaynakcaYonetimi
install:
	cp -rf KaynakcaYonetimi /usr/local/bin/KaynakcaYonetimi
uninstall:
	rm -rf /usr/local/bin/KaynakcaYonetimi
clean:
	rm -f KaynakcaYonetimi
