echo "#### Begin";

echo "#### MAKE BUILD";
rm -rf ~/lemca/build
mkdir ~/lemca/build
echo "#### COMPIL";
cd ~/lemca/build && cmake .. && make

echo "#### PREPARE OPT";
rm -rf /opt/lemca;

mkdir -p /opt/lemca;
mkdir -p /opt/lemca/bin
mkdir -p /opt/lemca/etc

mv ~/lemca/build/lemca /opt/lemca/bin/

echo "#### OK";
