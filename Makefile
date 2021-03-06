all: kaynakcayonetimi
kaynakcayonetimi:
	g++ -lsqlite3 -lwxsqlite3-`wx-config --release` `wx-config --cxxflags --libs` -o kaynakcayonetimi src/main.cpp src/main.h src/kaynakcayonetimi.cpp src/kaynakcayonetimi.h src/eklekitap.cpp src/eklekitap.h src/eklemakale.cpp src/eklemakale.h src/ekledokuman.cpp src/ekledokuman.h src/ekledosya.cpp src/ekledosya.h src/bulisbn.cpp src/bulisbn.h src/buldoi.cpp src/buldoi.h src/ekleliste.cpp src/ekleliste.h src/gosterliste.cpp src/gosterliste.h src/ekleajanda.cpp src/ekleajanda.h src/arama.cpp src/arama.h src/md5.cpp src/md5.h src/wxlibs.h
install:
	cp -Rf ${CURDIR} /usr/share/kaynakcayonetimi
	ln -s /usr/share/kaynakcayonetimi/kaynakcayonetimi /bin/kaynakcayonetimi
	ln -s /usr/share/kaynakcayonetimi/resource/icons/kaynakcayonetimi.xpm /usr/share/pixmaps/kaynakcayonetimi.xpm
	cp -f ${CURDIR}/kaynakcayonetimi.desktop /usr/share/applications/kaynakcayonetimi.desktop
uninstall:
	rm -Rf /usr/share/kaynakcayonetimi
	rm -f /usr/share/applications/kaynakcayonetimi.desktop
	rm -f /usr/share/pixmaps/kaynakcayonetimi.xpm
	rm -f /bin/kaynakcayonetimi
clean:
	rm -f kaynakcayonetimi
