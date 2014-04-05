Hola Profe,

Siga estos pasos para instalar primero algunas herramientas básicas, como el cliente GIT:

	sudo apt-get update
	sudo apt-get upgrade
	sudo apt-get avahi-daemon git-core

Luego para instalar OF siga este [tutorial](http://openframeworks.cc/setup/raspberrypi/Raspberry-Pi-Getting-Started.html) que más o menos le dirá:

	sudo raspi-config 

Dele 192MB of ram al CPU para compilar las librerías de OF luego puede volverlo a 64 

	sudo reboot

	...

	sudo apt-get update
	sudo apt-get upgrade
	cd
	curl -O http://www.openframeworks.cc/versions/v0.8.0/of_v0.8.0_linuxarmv6l_release.tar.gz
	mkdir openFrameworks
	tar vxfz of_v0.8.0_linuxarmv6l_release.tar.gz -C openFrameworks --strip-components 1
	cd /home/pi/openFrameworks/scripts/linux/debian_armv6l
	sudo ./install_dependencies.sh
	sed -i 's/VC_IMAGE_TRANSFORM_T/DISPMANX_TRANSFORM_T/g' /home/pi/openFrameworks/libs/openFrameworks/app/ofAppEGLWindow.cpp
	make Release -C /home/pi/openFrameworks/libs/openFrameworksCompiled/project

Para usar los GPIO necesitamos de la librería wiringPi instalada. Para eso:

	cd
	git clone git://git.drogon.net/wiringPi
	cd wiringPi
	./build

