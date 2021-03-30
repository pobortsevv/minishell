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
; echo df
| echo sdf
    ;   echo sd
    |echo sdf
echo > "\"text.txt
echo ;;
echo ;    ;   :q
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
