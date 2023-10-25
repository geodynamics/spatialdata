pdflatex csgeolocal.tex

for fin in *.pdf; do
  fout1=`echo $fin | sed -e s/\.pdf/1\.svg/g`
  fout=`echo $fin | sed -e s/\.pdf/\.svg/g`
  mutool convert -F svg -o $fout $fin && mv -f $fout1 $fout
done 
