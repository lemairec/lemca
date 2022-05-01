echo "#### Begin";

echo "#### MAKE BUILD";
rm -rf ~/lemca/build
mkdir ~/lemca/build
echo "#### COMPIL";
cd ~/lemca/build && cmake .. && make

echo "#### OK";
