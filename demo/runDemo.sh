#!bash
echo "*****************************************"
echo "You have requested to START Demo for IPSI"
echo "Please wait..."
sleep 2
echo "*****************************************"
printf "\n"
echo "------START Building all Demo Application---------"
printf "\n"

cd ../ipsi
make
cd ../demo
cd Controller
make
cd ../Service1
make
cd ../Service2
make
cd ../
printf "\n"
echo "----- COMPLETED Building all Demo Application ----------"
printf "\n"

echo "----------!Please wait.. Lauching Terminal!-------------"
sleep 3
printf "\n"

cd Service2
xterm  -T "Service 2" -fa 'Monospace' -fs 14 -e bash -c "sh $(pwd)/run.sh" &
cd ../Service1
sleep 1
xterm -T "Service 1" -fa 'Monospace' -fs 14 -e bash -c "sh $(pwd)/run.sh" &
cd ../Controller
sleep 1
xterm  -T "Controller" -fa 'Monospace' -fs 14 -e bash -c "sh $(pwd)/run.sh" &
cd ../

echo "----------!ALL 3 Terminals are now UP!------------------"
printf "\n"
echo "NOTE : Please exit all XTERM terminals before attempting to re-run Demo script"
printf "\n"
echo "*******************************************"
