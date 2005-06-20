cat egm96 | sed -e s/D+/E+/g | sed -e s/D-/E-/g | \
  awk '{ printf("%20.12E,%20.12E,\n", $3, $4)}' > egm96.new
cat corrcoef | sed -e s/D+/E+/g | sed -e s/D-/E-/g | \
awk '{ printf("%20.12E,%20.12E,\n", $3, $4)}' > corrcoef.new
