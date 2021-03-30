export TE"ST=""123"
echo $TEST

export 'TEST'="321"
echo $TEST

echo " ''''''''"
echo "\\"
echo "   '$PATH'   "
e\c\h\o "\$PWD"
echo $PWD$PWD
echo "$PWD"$PWD
echo "$PWD""$PWD"

# ошибки 
echo > "\"text.txt
echo ;;
echo ;    ;   
echo ||
echo |     | 
echo ;|
echo ;           | 
echo |;
echo |    ;
echo ><
echo >           < 
echo <>
echo <       > 
echo <<
echo <      < 
echo >
echo >           
echo << <
echo << <
echo >>>
echo >>>

#TODO нормальная работа у нас сега!!!! файл создается
echo > \"test.txtls
