all: KaynakcaYonetimi
KaynakcaYonetimi:
	g++ -lsqlite3 -lwxcode_`wx-config --basename | cut -d'_' -f 2`_wxsqlite3-`wx-config --release` `wx-config --cxxflags --libs` -o KaynakcaYonetimi src/main.cpp src/main.h src/kaynakcayonetimi.cpp src/kaynakcayonetimi.h src/eklekitap.cpp src/eklekitap.h src/eklemakale.cpp src/eklemakale.h src/wxlibs.h
install:
	cp -rf KaynakcaYonetimi /usr/local/bin/KaynakcaYonetimi
uninstall:
	rm -rf /usr/local/bin/KaynakcaYonetimi
clean:
	rm -f KaynakcaYonetimi
