sudo apt update -y
sudo apt install -y libsdl2-dev
sudo apt install -y libsdl2-image-dev
sudo apt install -y libsdl2-mixer-dev
sudo apt install -y zlib1g-dev
sudo apt install -y libpng-dev

if [ $? -ne 0 ]; then
echo "[ERROR]No se instalaron correctamente las dependencias"
else
echo "Se instalaron correctamente las dependencias"
fi

echo "Ha terminado la instalacion de SDL2. Consulte el archivo README.md para mas informacion."
#zenity --info --title="MetalSlug" --text=
