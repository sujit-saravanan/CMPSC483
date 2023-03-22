#!/bin/bash
mkdir install
cd install

yay -S rang-git -y
yay -S cpp-httplib-compiled -y
yay -S sqlite -y
yay -S ninja -y
yay -S base-devel -y
yay -S cmake -y

git clone https://github.com/sujit-saravanan/stitch.git
cd stitch/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja .
ninja -j 20
cd ..
sudo cp output/stitch /usr/bin

cd ../..
rm -rf install

stitch run dev
