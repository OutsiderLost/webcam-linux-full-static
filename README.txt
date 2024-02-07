Creating a static executable for webcam management for older linux.
--------------------------------------------------------------------

=== Opencv translations ===

(example: older debian)
-> https://cdimage.debian.org/mirror/cdimage/archive/
-> 11.0.0-live/	2021-08-14 22:21
-> debian-live-11.0.0-amd64-xfce.iso
(Kali releases of the similar vintage) # cat /proc/version -> (Debian 10.2.1-6)
Linux kali 5.10.0-kali3-amd64 #1 SMP Debian 5.10.13-1kali1 (2021-02-08) x86_64 GNU/Linux
Linux kali 5.10.0-kali9-amd64 #1 SMP Debian 5.10.46-4kali1 (2021-08-09) x86_64 GNU/Linux
(note: On Kali Linux, custom translation can only be done if the previously installed dependencies exist! -> dpkg -l | grep -E 'binutils |g\+\+ |cmake |make ')

(search: opencv download linux)
-> https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html
sudo apt update && sudo apt install -y cmake g++ wget unzip
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip
mkdir -p build && cd build
(full static build configuration, only with tools that are sure to work!)
mkdir -p /opt/custom_ocv && cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/opt/custom_ocv -D BUILD_DOCS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_opencv_apps=OFF -D BUILD_opencv_python2=ON -D BUILD_opencv_python3=ON -D BUILD_PERF_TESTS=OFF -D BUILD_SHARED_LIBS=OFF -D OPENCV_GENERATE_PKGCONFIG=YES -D BUILD_TESTS=OFF -D ENABLE_PRECOMPILED_HEADERS=OFF-D FORCE_VTK=OFF -D WITH_FFMPEG=OFF -D WITH_GDAL=OFF -D WITH_IPP=OFF -D WITH_OPENEXR=OFF -D WITH_OPENGL=OFF -D WITH_QT=OFF -D WITH_TBB=OFF -D WITH_XINE=OFF -D BUILD_JPEG=ON -D BUILD_TIFF=ON -D BUILD_PNG=ON ../opencv-4.x
cmake --build .
cmake --install . # or make install

(optional: or translation based on existing files)
# cat custom_ocv*[1-3].tar.gz | tar -xzf - -C /opt

=== Translation of usable main program ===

export PKG_CONFIG_PATH=/opt/custom_ocv/lib/pkgconfig:$PKG_CONFIG_PATH

(1. method: current pkg-config with "-static" flag added)
pkg-config --cflags --libs --static opencv4 | sed 's/.*/g++ OCVimage.cpp -o OCVimage & -static/g;s/ /\n/g' | perl -ne 'print if ++$k{$_}==1' | paste -d ' ' -s

(2. method: basic general translation + current pkg-config)
echo "g++ OCVimage.cpp -o OCVimage -I/opt/custom_ocv/include/opencv4 -L/opt/custom_ocv/lib -static -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_calib3d -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -L/opt/custom_ocv/lib/opencv4/3rdparty -llibprotobuf -lade -littnotify -llibjpeg-turbo -llibwebp -llibpng -llibtiff -llibopenjp2 -lz -ldl -lm -lpthread -lrt -static-libgcc -static-libstdc++ -lpng -ljpeg -std=c++0x `pkg-config --cflags --libs --static opencv4`" | sed 's/ /\n/g' | perl -ne 'print if ++$k{$_}==1' | paste -d ' ' -s
(if don't work: remove no found "-modules" in row! -> echo "<COMMAND>" | sed 's/ -module//')

(3. method: basic general translation)
g++ OCVimage.cpp -o OCVimage -I/opt/custom_ocv/include/opencv4 -L/opt/custom_ocv/lib -static -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_calib3d -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core -L/opt/custom_ocv/lib/opencv4/3rdparty -llibprotobuf -lade -littnotify -llibjpeg-turbo -llibwebp -llibpng -llibtiff -llibopenjp2 -lz -ldl -lm -lpthread -lrt -static-libgcc -static-libstdc++ -lpng -ljpeg -std=c++0x
(if don't work: remove no found "-modules" in row! -> echo "<COMMAND>" | sed 's/ -module//')

(test)
chmod +x OCV* && ./OCVimage
chmod +x cam*.sh && ./camcheck.sh

=== Opencv python method ===

(note: recommended, stable operation, only requires storage space!)
cd ocv_python

python3 -m pip install opencv-python
python3 -m pip install numpy # recommended
python3 -m pip install PyQt5 # optional

(optional: or use based on existing modules)
cat ocv_py*[1-3].tar.gz | tar -xzf - && rm -rf *-info

(test)
chmod +x ocv*.py && python3 ocvtest.py


