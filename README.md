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
	curl -O http://www.openframeworks.cc/versions/v0.8.1/of_v0.8.1_linuxarmv6l_release.tar.gz
	mkdir openFrameworks
	tar vxfz of_v0.8.1_linuxarmv6l_release.tar.gz -C openFrameworks --strip-components 1
	cd /home/pi/openFrameworks/scripts/linux/debian_armv6l
	sudo ./install_dependencies.sh
	sed -i 's/VC_IMAGE_TRANSFORM_T/DISPMANX_TRANSFORM_T/g' /home/pi/openFrameworks/libs/openFrameworks/app/ofAppEGLWindow.cpp
	make Release -C /home/pi/openFrameworks/libs/openFrameworksCompiled/project

Tendría que instalar el addon ofxOMXPlayer 

	cd /home/pi/openFrameworks/addons
	git clone --depth 1 https://github.com/jvcleave/ofxOMXPlayer

Para usar los GPIO necesitamos de la librería wiringPi instalada. Para eso:

	cd
	git clone git://git.drogon.net/wiringPi
	cd wiringPi
	./build

Una vez terminado estos pasos clonar este repo en el directorio myApps en OF

	cd /home/pi/openFrameworks/apps/myApps/
	git clone --depth 1 https://github.com/patriciogonzalezvivo/RPIVideoTriger
	
Una vez clonado tiene q compilarlo

	cd RPIVideoTriger
	make

No se olvide de cambiar los videos por los que usted quiera. Están en el directorio ```/home/pi/openFrameworks/apps/myApps/RPIVideoTriger/bin/data/videos```

